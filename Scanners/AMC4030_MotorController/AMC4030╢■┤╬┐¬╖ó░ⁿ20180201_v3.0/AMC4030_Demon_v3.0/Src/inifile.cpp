
/*************************************************
  Copyright (C), 1988-1999, step-Servo. Co., Ltd.
  文件名:     inifile.c
  描  述: 
	1、ini格式数据生成及解析模块
 
     备  注:       
   修改记录:    
    1. 日期: 2013-10-24
       作者: 陈 鸿
       内容:
    2. ...
*************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <_isfuncdcl.h>
#endif
#include "inifile.h"

#define int32_t  int
#define int8_t	 char
#define float32_t	float
#define float64_t	double

#define LEFT_BRACE '['
#define RIGHT_BRACE ']'

//ini数据长度
int32_t m_nIniSize;
//ini数据缓冲
int8_t m_chiniBuf[MAX_INI_SIZE];


static int32_t newline(char c)
{
	return ('\n' == c ||  '\r' == c )? 1 : 0;
}
static int32_t end_of_string(char c)
{
	return '\0'==c? 1 : 0;
}
static int32_t left_barce(char c)
{
	return LEFT_BRACE == c? 1 : 0;
}
static int32_t isright_brace(char c )
{
	return RIGHT_BRACE == c? 1 : 0;
}
static int32_t parse_file(const int8_t *section, const int8_t *key, const int8_t *buf,
                        int32_t *sec_s,int32_t *sec_e,
                        int32_t *key_s,int32_t *key_e, int32_t *value_s, int32_t *value_e)
{
	const int8_t *p = buf;
	int i=0;

	*sec_e = *sec_s = *key_e = *key_s = *value_s = *value_e = -1;

	while( !end_of_string(p[i]) ) {
		//find the section
		if( ( 0==i ||  newline(p[i-1]) ) && left_barce(p[i]) )
		{
			int section_start=i+1;

			//find the ']'
			do {
				i++;
			} while( !isright_brace(p[i]) && !end_of_string(p[i]));

			if( 0 == strncmp(p+section_start,section, i-section_start)) {
				int newline_start=0;

				i++;

				//Skip over space char after ']'
				while(isspace(p[i])) {
					i++;
				}

				//find the section
				*sec_s = section_start;
				*sec_e = i;

				while( ! (newline(p[i-1]) && left_barce(p[i])) 
				&& !end_of_string(p[i]) ) {
					int j=0;
					//get a new line
					newline_start = i;

					while( !newline(p[i]) &&  !end_of_string(p[i]) ) {
						i++;
					}
					
					//now i  is equal to end of the line
					j = newline_start;

					if(';' != p[j]) //skip over comment
					{
						while(j < i && p[j]!='=') {
							j++;
							if('=' == p[j]) {
								if(strncmp(key,p+newline_start,j-newline_start)==0)
								{
									//find the key ok
									*key_s = newline_start;
									*key_e = j-1;

									*value_s = j+1;
									*value_e = i;

									return 1;
								}
							}
						}
					}

					i++;
				}
			}
		}
		else
		{
			i++;
		}
	}
	return 0;
}

///////////////////////////////////////////////////
//    功能描述:	读取ini字符串
//              section-节名
//              key-键名
//              value-键值，字符串
//              default_value-默认值 
//    输出参数:  
//      返回值: 0-成功 -1失败
//        备注: 
///////////////////////////////////////////////////
int32_t read_profile_string( const int8_t *section, const int8_t *key,int8_t *value,
                            int32_t size,const int8_t *default_value)
{

    int32_t sec_s,sec_e,key_s,key_e, value_s, value_e;

	//check parameters
	if((section == NULL)||(key == NULL))
	{
		return -1;
	}


	if(!parse_file(section,key,m_chiniBuf,&sec_s,&sec_e,&key_s,&key_e,&value_s,&value_e))
	{
		if(default_value!=NULL)
		{
			strncpy(value,default_value, size);
		}
		return -1; //not find the key
	}
	else
	{
		int cpcount = value_e -value_s;

		if( size-1 < cpcount)
		{
			cpcount =  size-1;
		}
	
		memset(value, 0, size);
		memcpy(value,m_chiniBuf+value_s, cpcount );
		value[cpcount] = '\0';

		return 0;
	}
}
///////////////////////////////////////////////////
//    功能描述:	写入ini键值
//    输入参数: 
//              section-节名
//              key-键名
//              value-键值，字符串
// 
//    输出参数:  
//      返回值: 
//        备注: 在写入ini数据前调用一次
///////////////////////////////////////////////////
int32_t write_profile_string(const int8_t *section,const int8_t *key,const int8_t *value)
{

    int32_t sec_s,sec_e,key_s,key_e, value_s, value_e;

	//check parameters
	if((section == NULL)||(key == NULL)||(value == NULL))
	{
		return -1;
	}

	if(m_nIniSize > MAX_INI_SIZE)
	{	
		return -1;	
	}

	parse_file(section,key,m_chiniBuf,&sec_s,&sec_e,&key_s,&key_e,&value_s,&value_e);

	//没有节名
	if( -1 == sec_s)
	{
		//新建文件
		if(0==m_nIniSize)
		{
			sprintf(m_chiniBuf+m_nIniSize,"[%s]\r\n%s=%s\r\n",section,key,value);

			//字符串的长度
			m_nIniSize += strlen(section)+strlen(key)+strlen(value)+2+2+2+1;
		}
		else
		{
			sprintf(m_chiniBuf+m_nIniSize,"[%s]\r\n%s=%s\r\n",section,key,value);
			//字符串的长度
			m_nIniSize += strlen(section)+strlen(key)+strlen(value)+2+2+2+1;
		}
	}
	else
	{
			sprintf(m_chiniBuf+m_nIniSize,"%s=%s\r\n",key,value);
			//字符串的长度
			m_nIniSize += strlen(key)+strlen(value)+2+1;
	}
	return 0;
}

///////////////////////////////////////////////////
//    功能描述:	写入复位
//    输入参数:  
//    输出参数:  
//      返回值: 
//        备注: 在写入ini数据前调用一次
///////////////////////////////////////////////////
void reset_write_ini()
{
	m_nIniSize = 0;
	m_chiniBuf[0] = 0;
//	memset(m_chiniBuf,'\0',MAX_INI_SIZE);
}


///////////////////////////////////////////////////
//    功能描述:	将ini文件数据放入本模块
//    输入参数:  
//              pinidata-ini文件数据
//              size-长度
//      返回值: 0-成功 1-失败
//        备注: 
///////////////////////////////////////////////////
int32_t load_read_ini(int8_t *pinidata,int32_t size)
{
	if(pinidata == NULL)
	{
		return -1;
	}
	if(size > MAX_INI_SIZE)
	{
		return -1;	
	}

	m_nIniSize = size;
//	memset(m_chiniBuf,'\0',MAX_INI_SIZE);
	memcpy(m_chiniBuf,pinidata,size);

	return 0;
}

///////////////////////////////////////////////////
//    功能描述:	获取写入的ini格式数据
//    输入参数:  
//    输出参数:  
//              pinidata-ini文件数据
//              size-长度
//      返回值: 0-成功 1-失败
//        备注: 写入ini数据后调用
///////////////////////////////////////////////////
int32_t get_write_ini(int8_t *pinidata,int32_t *size)
{
	if(pinidata == NULL)
	{
		return -1;
	}
	
	*size = m_nIniSize;
	memcpy(pinidata,m_chiniBuf,m_nIniSize);
	return 0;
}

///////////////////////////////////////////////////
//    功能描述:	读取ini文件指定键名的整数格式键值
//    输入参数:  
//              section-节名
//              key-键名
//              default_value-默认值 
//      返回值: 整数格式键值
//        备注: 
///////////////////////////////////////////////////
int32_t read_profile_int( const int8_t *section, const int8_t *key,int32_t default_value)
{
    int8_t chbuf[32] = {0};

	if(read_profile_string(section,key,chbuf,sizeof(chbuf),NULL))
	{
		return default_value;
	}
	else
	{
		return atoi(chbuf);
	}
}

///////////////////////////////////////////////////
//    功能描述:	读取ini文件指定键名的浮点格式键值
//    输入参数:  
//              section-节名
//              key-键名
//              default_value-默认值
//              datastring-ini文件数据  
//      返回值: 浮点格式键值
//        备注: 
///////////////////////////////////////////////////
float32_t read_profile_float( const int8_t *section, const int8_t *key,float32_t default_value)
{
    int8_t chbuf[32] = {0};
	if(read_profile_string(section,key,chbuf,sizeof(chbuf),NULL))
	{
		return default_value;
	}
	else
	{
		return atof(chbuf);
	}
}

///////////////////////////////////////////////////
//    功能描述:	直接在文件最后写一个字符串。
//    输入参数:  
//              section-节名
//              key-键名
//              value-键值
//    输出参数:
//              datastring-ini格式文件数据 
//      返回值: 0-成功 -1错误
//        备注: 
///////////////////////////////////////////////////
int32_t write_profile_section( const int8_t *section)
{
	sprintf(m_chiniBuf+m_nIniSize,"[%s]\r\n",section);
			//字符串的长度
	m_nIniSize += strlen(section)+2+2;
	return 0;
}
///////////////////////////////////////////////////
//    功能描述:	给指定键名的赋予整数值并生成INI格式数据
//    输入参数:  
//              section-节名
//              key-键名
//              value-键值
//    输出参数:
//              datastring-ini格式文件数据 
//      返回值: 0-成功 -1错误
//        备注: 
///////////////////////////////////////////////////
int32_t write_profile_int( const int8_t *section, const int8_t *key,int32_t value)
{

    int8_t chbuf[32] = {0};

	sprintf(chbuf,"%d",value);
	
	return write_profile_string(section,key,chbuf);
}

///////////////////////////////////////////////////
//    功能描述:	给指定键名的赋予浮点数值并生成INI格式数据
//    输入参数:  
//              section-节名
//              key-键名
//              value-键值
//    输出参数:
//              datastring-ini格式文件数据
//      返回值: 0-成功 -1错误
//        备注: 
///////////////////////////////////////////////////
int32_t write_profile_float( const int8_t *section, const int8_t *key,float32_t value)
{
	
    int8_t chbuf[32] = {0};


	sprintf(chbuf,"%f",value);
	
	return write_profile_string(section,key,chbuf);
}

