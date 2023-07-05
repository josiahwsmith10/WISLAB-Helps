
/*************************************************
  Copyright (C), 1988-1999, step-Servo. Co., Ltd.
  �ļ���:     inifile.c
  ��  ��: 
	1��ini��ʽ�������ɼ�����ģ��
 
     ��  ע:       
   �޸ļ�¼:    
    1. ����: 2013-10-24
       ����: �� ��
       ����:
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

//ini���ݳ���
int32_t m_nIniSize;
//ini���ݻ���
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
//    ��������:	��ȡini�ַ���
//              section-����
//              key-����
//              value-��ֵ���ַ���
//              default_value-Ĭ��ֵ 
//    �������:  
//      ����ֵ: 0-�ɹ� -1ʧ��
//        ��ע: 
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
//    ��������:	д��ini��ֵ
//    �������: 
//              section-����
//              key-����
//              value-��ֵ���ַ���
// 
//    �������:  
//      ����ֵ: 
//        ��ע: ��д��ini����ǰ����һ��
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

	//û�н���
	if( -1 == sec_s)
	{
		//�½��ļ�
		if(0==m_nIniSize)
		{
			sprintf(m_chiniBuf+m_nIniSize,"[%s]\r\n%s=%s\r\n",section,key,value);

			//�ַ����ĳ���
			m_nIniSize += strlen(section)+strlen(key)+strlen(value)+2+2+2+1;
		}
		else
		{
			sprintf(m_chiniBuf+m_nIniSize,"[%s]\r\n%s=%s\r\n",section,key,value);
			//�ַ����ĳ���
			m_nIniSize += strlen(section)+strlen(key)+strlen(value)+2+2+2+1;
		}
	}
	else
	{
			sprintf(m_chiniBuf+m_nIniSize,"%s=%s\r\n",key,value);
			//�ַ����ĳ���
			m_nIniSize += strlen(key)+strlen(value)+2+1;
	}
	return 0;
}

///////////////////////////////////////////////////
//    ��������:	д�븴λ
//    �������:  
//    �������:  
//      ����ֵ: 
//        ��ע: ��д��ini����ǰ����һ��
///////////////////////////////////////////////////
void reset_write_ini()
{
	m_nIniSize = 0;
	m_chiniBuf[0] = 0;
//	memset(m_chiniBuf,'\0',MAX_INI_SIZE);
}


///////////////////////////////////////////////////
//    ��������:	��ini�ļ����ݷ��뱾ģ��
//    �������:  
//              pinidata-ini�ļ�����
//              size-����
//      ����ֵ: 0-�ɹ� 1-ʧ��
//        ��ע: 
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
//    ��������:	��ȡд���ini��ʽ����
//    �������:  
//    �������:  
//              pinidata-ini�ļ�����
//              size-����
//      ����ֵ: 0-�ɹ� 1-ʧ��
//        ��ע: д��ini���ݺ����
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
//    ��������:	��ȡini�ļ�ָ��������������ʽ��ֵ
//    �������:  
//              section-����
//              key-����
//              default_value-Ĭ��ֵ 
//      ����ֵ: ������ʽ��ֵ
//        ��ע: 
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
//    ��������:	��ȡini�ļ�ָ�������ĸ����ʽ��ֵ
//    �������:  
//              section-����
//              key-����
//              default_value-Ĭ��ֵ
//              datastring-ini�ļ�����  
//      ����ֵ: �����ʽ��ֵ
//        ��ע: 
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
//    ��������:	ֱ�����ļ����дһ���ַ�����
//    �������:  
//              section-����
//              key-����
//              value-��ֵ
//    �������:
//              datastring-ini��ʽ�ļ����� 
//      ����ֵ: 0-�ɹ� -1����
//        ��ע: 
///////////////////////////////////////////////////
int32_t write_profile_section( const int8_t *section)
{
	sprintf(m_chiniBuf+m_nIniSize,"[%s]\r\n",section);
			//�ַ����ĳ���
	m_nIniSize += strlen(section)+2+2;
	return 0;
}
///////////////////////////////////////////////////
//    ��������:	��ָ�������ĸ�������ֵ������INI��ʽ����
//    �������:  
//              section-����
//              key-����
//              value-��ֵ
//    �������:
//              datastring-ini��ʽ�ļ����� 
//      ����ֵ: 0-�ɹ� -1����
//        ��ע: 
///////////////////////////////////////////////////
int32_t write_profile_int( const int8_t *section, const int8_t *key,int32_t value)
{

    int8_t chbuf[32] = {0};

	sprintf(chbuf,"%d",value);
	
	return write_profile_string(section,key,chbuf);
}

///////////////////////////////////////////////////
//    ��������:	��ָ�������ĸ��踡����ֵ������INI��ʽ����
//    �������:  
//              section-����
//              key-����
//              value-��ֵ
//    �������:
//              datastring-ini��ʽ�ļ�����
//      ����ֵ: 0-�ɹ� -1����
//        ��ע: 
///////////////////////////////////////////////////
int32_t write_profile_float( const int8_t *section, const int8_t *key,float32_t value)
{
	
    int8_t chbuf[32] = {0};


	sprintf(chbuf,"%f",value);
	
	return write_profile_string(section,key,chbuf);
}

