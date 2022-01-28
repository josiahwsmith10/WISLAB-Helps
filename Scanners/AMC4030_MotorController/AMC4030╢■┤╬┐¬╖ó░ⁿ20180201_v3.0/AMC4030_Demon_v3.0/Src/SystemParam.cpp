
#include "stdafx.h"
#include "SystemParam.h"
#include "inifile.h"
SYS_PARAM		g_tSysParam;

BYTE			m_ParaBuf[20000];
//读配置文件。
int SYS_ReadSysCfgFile()
{
	TCHAR filePATH[_MAX_PATH];
	TCHAR InifilePATH[_MAX_PATH];
//	TCHAR LogfilePATH[_MAX_PATH];
	int i;

	GetModuleFileName(NULL, filePATH, _MAX_PATH);
	TCHAR *fileExt = _tcsrchr(filePATH, _T('\\'));//找到最后一个‘.'
	*++fileExt = 0;
	wsprintf(InifilePATH,_T("%sSysCfg.DAT"),filePATH);

	CFile fFile;
	if(!fFile.Open(InifilePATH,CFile::modeRead))
	{//打开失败。
		//加载默认的配置参数。
		SYS_LoadDefaultSysCfgFile();
		return 0;
	}
	fFile.Read(&g_tSysParam,sizeof(SYS_PARAM));
	fFile.Close();
	return 0;
}
//写配置文件。
int SYS_WriteSysCfgFile()
{
	TCHAR filePATH[_MAX_PATH];
	TCHAR InifilePATH[_MAX_PATH];
//	TCHAR LogfilePATH[_MAX_PATH];
	int i;

	GetModuleFileName(NULL, filePATH, _MAX_PATH);
	TCHAR *fileExt = _tcsrchr(filePATH, _T('\\'));//找到最后一个‘.'
	*++fileExt = 0;
	wsprintf(InifilePATH,_T("%sSysCfg.DAT"),filePATH);

	CFile fFile;
	if(!fFile.Open(InifilePATH,CFile::modeCreate|CFile::modeWrite))
	{//打开失败。
		//加载默认的配置参数。
		return -1;
	}
	fFile.Write(&g_tSysParam,sizeof(SYS_PARAM));
	fFile.Close();
	return 0;
}
int SYS_LoadDefaultSysCfgFile()
{
	for(int i=0; i<MAX_AXIS_NUM;i++)
	{
		g_tSysParam.tAxisParam[i].fMaxPos = 100;
		g_tSysParam.tAxisParam[i].nPulseFactorDown = 10.0;
		g_tSysParam.tAxisParam[i].nPulseFactorUp = 10000.0;
		g_tSysParam.tAxisParam[i].fHomeSpeed = 20;
		g_tSysParam.tAxisParam[i].nHomeDir = -1;
		g_tSysParam.tAxisParam[i].fHomePosOffset = 5.0;
		g_tSysParam.tAxisParam[i].nEnableBackLash = 0;//不使能
		g_tSysParam.tAxisParam[i].fBackLashLen = 0;

		g_tSysParam.tAxisParam[i].fBackLashSpeed = 10;            
		g_tSysParam.tAxisParam[i].nPulseLogic = 1;
		g_tSysParam.tAxisParam[i].fMaxSpeed = 400;                
		g_tSysParam.tAxisParam[i].fHomeCheckDis = 50;                 
		g_tSysParam.tAxisParam[i].fHomeZeroSpeed = 10;                
		g_tSysParam.tAxisParam[i].fHomeOrgSpeed = 5;                 

	}
	g_tSysParam.MachineParam.fTimerPeriod = 1.0;          
    g_tSysParam.MachineParam.fWorkPrecision = 0.005;        
    g_tSysParam.MachineParam.fArcCheckPrecision =0.01 ;    
    g_tSysParam.MachineParam.fMinLen =0.02 ;               
    g_tSysParam.MachineParam.fMaxFeedSpeed = 400;         
    
	g_tSysParam.MachineParam.nAccelType = 0;           
	g_tSysParam.MachineParam.nHomePowerOn = 0;         
    
	g_tSysParam.MachineParam.fMaxAccelSpeed = 20000;    
    g_tSysParam.MachineParam.fAccelSpeed = 200;           
    g_tSysParam.MachineParam.fFastAccelSpeed = 400;       
    g_tSysParam.MachineParam.fJAccelSpeed =10000 ;    
	return 0;
}
void PM_AssignPara(int8_t* pchData,DWORD dwSize)
{
    int8_t chSection[30];
    int8_t chAxis[6] = {'X','Y','Z'};
    int32_t i;

    //加载参数INI文件
    load_read_ini(pchData,dwSize);
    //机械配置参数
    g_tSysParam.MachineParam.fTimerPeriod = read_profile_float("MachineParam","fTimerPeriod",1.0);//机器插补周期1ms
    g_tSysParam.MachineParam.fWorkPrecision = read_profile_float("MachineParam","fWorkPrecision",0.005);//圆弧拆分精度
    g_tSysParam.MachineParam.fArcCheckPrecision = read_profile_float("MachineParam","fArcCheckPrecision",0.01);//圆弧检测精度
    g_tSysParam.MachineParam.fMinLen = read_profile_float("MachineParam","fMinLen",0.01);//最小线段
    g_tSysParam.MachineParam.fMaxFeedSpeed = read_profile_float("MachineParam","fMaxFeedSpeed",400);//最大进给速度
    g_tSysParam.MachineParam.nAccelType = read_profile_int("MachineParam","nAccelType",0);
	    g_tSysParam.MachineParam.nHomePowerOn = read_profile_int("MachineParam","wHomePowerOn",0);
    g_tSysParam.MachineParam.fMaxAccelSpeed = read_profile_float("MachineParam","fMaxAccelSpeed",20000);//向心或拐弯加速度
    g_tSysParam.MachineParam.fAccelSpeed = read_profile_float("MachineParam","fAccelSpeed",1000);
    g_tSysParam.MachineParam.fJAccelSpeed = read_profile_float("MachineParam","fJAccelSpeed",10000);
    g_tSysParam.MachineParam.fFastAccelSpeed = read_profile_float("MachineParam","fFastAccelSpeed",1000);

	
    //轴参数
    memcpy(chSection+1,"AxisParam",sizeof("AxisParam"));
    for(i=0;i<MAX_AXIS_NUM;i++)
    {
        chSection[0] = chAxis[i];
        g_tSysParam.tAxisParam[i].nPulseFactorUp = read_profile_float(chSection,"nPulseFactorUp",5000);
        g_tSysParam.tAxisParam[i].nPulseFactorDown = read_profile_float(chSection,"nPulseFactorDown",10);
        g_tSysParam.tAxisParam[i].nPulseLogic = read_profile_int(chSection,"nPulseLogic",1);
        g_tSysParam.tAxisParam[i].fMaxSpeed = read_profile_float(chSection,"fMaxSpeed",400);
		g_tSysParam.tAxisParam[i].fMaxPos = read_profile_float(chSection,"fMaxPos",600);

        g_tSysParam.tAxisParam[i].nHomeDir = read_profile_int(chSection,"nHomeDir",-1);
		g_tSysParam.tAxisParam[i].fHomeSpeed = read_profile_float(chSection,"fHomeSpeed",20);
        g_tSysParam.tAxisParam[i].fHomeCheckDis = read_profile_float(chSection,"fHomeCheckDis",50);
        g_tSysParam.tAxisParam[i].fHomeZeroSpeed = read_profile_float(chSection,"fHomeZeroSpeed",10);
        g_tSysParam.tAxisParam[i].fHomeOrgSpeed = read_profile_float(chSection,"fHomeOrgSpeed",5);
        g_tSysParam.tAxisParam[i].fHomePosOffset = read_profile_float(chSection,"fHomePosOffset",5);

        g_tSysParam.tAxisParam[i].nEnableBackLash= read_profile_int(chSection,"nEnableBacklash",0);
        g_tSysParam.tAxisParam[i].fBackLashLen= read_profile_float(chSection,"fBacklashLen",0);
        g_tSysParam.tAxisParam[i].fBackLashSpeed= read_profile_float(chSection,"fBacklashSpeed",0);

    }
 
}
///////////////////////////////////////////////////////////////
int SYS_ReadSysCfgFile_ini(char* iniPath)
{
#if 1
	CFile fFile;
#ifdef _UNICODE
		TCHAR uName[300] ={ 0};
		MultiByteToWideChar (CP_ACP, 0, iniPath, -1, uName, 300);
#else
	char* uName = iniPath;
#endif
	if(!fFile.Open(uName,CFile::modeRead))
	{//打开失败。
		//加载默认的配置参数。
		SYS_LoadDefaultSysCfgFile();
		SYS_WriteSysCfgFile_ini(iniPath);
		return -1;
	}
	DWORD dwSize = fFile.GetLength();
	if(dwSize > MAX_INI_SIZE )
    {
       fFile.Close();
        return -1;
    }
    DWORD dwRtn = fFile.Read(m_ParaBuf,dwSize);
    if(dwRtn == 0)
    {
        fFile.Close();
        return -1;
    }

    if(dwRtn == dwSize)
    {
        //取得参数数据
        PM_AssignPara((int8_t*)m_ParaBuf,dwSize);
        fFile.Close();
    }
    else
    {
     fFile.Close();
        return -1;
    }
	return 0;
#else
	FILE *fFile;
	if((fFile = fopen(iniPath,"rt"))==NULL)
	{//没找到，生产默认的配置文件。
		SYS_LoadDefaultSysCfgFile();
		SYS_WriteSysCfgFile_ini(iniPath);//生产INI文件。
		fFile = fopen(iniPath,"rt");//重新打开。
	//	return -1;
	}
	fseek(fFile,0L,SEEK_END);  
    int dwSize=ftell(fFile);  
	 rewind(fFile);
	DWORD dwRtn ;
	//= fFile.Read(m_ParaBuf,dwSize);
	dwRtn = fread(m_ParaBuf,1,dwSize,fFile);
		fclose(fFile);
	 if(dwRtn == 0)
    {
        return -1;
    }

    if(dwRtn )
    {
        //取得参数数据
        PM_AssignPara((int8_t*)m_ParaBuf,dwSize);
    }
    else
    {
        return -1;
    }
#endif
}

int SYS_WriteSysCfgFile_ini(char* iniPath)
{
	int8_t chSection[30];
    int8_t chAxis[10] = {'X','\0','Y','\0','Z','\0'};
    int32_t i;
	reset_write_ini();
//写头文件
    write_profile_section("Head");
	write_profile_int("Head","MachineType",4030);
	write_profile_int("Head","Version",1000);
	write_profile_section("HeadEnd");
 
    //机械配置参数
    write_profile_float("MachineParam","fTimerPeriod",g_tSysParam.MachineParam.fTimerPeriod);
    write_profile_float("MachineParam","fWorkPrecision",g_tSysParam.MachineParam.fWorkPrecision);
    write_profile_float("MachineParam","fArcCheckPrecision",g_tSysParam.MachineParam.fArcCheckPrecision);
    write_profile_float("MachineParam","fMinLen",g_tSysParam.MachineParam.fMinLen);
    write_profile_float("MachineParam","fMaxFeedSpeed",g_tSysParam.MachineParam.fMaxFeedSpeed);
    write_profile_int("MachineParam","nAccelType",g_tSysParam.MachineParam.nAccelType);
	write_profile_int("MachineParam","wHomePowerOn",g_tSysParam.MachineParam.nHomePowerOn);

    write_profile_float("MachineParam","fMaxAccelSpeed",g_tSysParam.MachineParam.fMaxAccelSpeed );
    write_profile_float("MachineParam","fAccelSpeed",g_tSysParam.MachineParam.fAccelSpeed);
	write_profile_float("MachineParam","fFastAccelSpeed",g_tSysParam.MachineParam.fFastAccelSpeed);
    write_profile_float("MachineParam","fJAccelSpeed",g_tSysParam.MachineParam.fJAccelSpeed);

    //轴参数
    memcpy(chSection+1,"AxisParam",sizeof("AxisParam"));
    //for(i=0;i<MAX_AXIS_NUM;i++)
    for(i=0;i<MAX_AXIS_NUM;i++)//只写前4个轴的。
    {
        chSection[0] = chAxis[2*i];

        write_profile_float(chSection,"nPulseFactorUp",g_tSysParam.tAxisParam[i].nPulseFactorUp );
        write_profile_float(chSection,"nPulseFactorDown",g_tSysParam.tAxisParam[i].nPulseFactorDown);
        write_profile_int(chSection,"nPulseLogic",g_tSysParam.tAxisParam[i].nPulseLogic);

        write_profile_float(chSection,"fMaxSpeed",g_tSysParam.tAxisParam[i].fMaxSpeed);
		write_profile_float(chSection,"fMaxPos",g_tSysParam.tAxisParam[i].fMaxPos);


        write_profile_int(chSection,"nEnableBacklash",g_tSysParam.tAxisParam[i].nEnableBackLash );
        write_profile_float(chSection,"fBacklashLen",g_tSysParam.tAxisParam[i].fBackLashLen );
        write_profile_float(chSection,"fBacklashSpeed",g_tSysParam.tAxisParam[i].fBackLashSpeed);

		write_profile_int(chSection,"nHomeDir",g_tSysParam.tAxisParam[i].nHomeDir);        
        write_profile_float(chSection,"fHomeSpeed",g_tSysParam.tAxisParam[i].fHomeSpeed);
        write_profile_float(chSection,"fHomeCheckDis",g_tSysParam.tAxisParam[i].fHomeCheckDis);
        write_profile_float(chSection,"fHomeZeroSpeed",g_tSysParam.tAxisParam[i].fHomeZeroSpeed);
        write_profile_float(chSection,"fHomeOrgSpeed",g_tSysParam.tAxisParam[i].fHomeOrgSpeed );
        write_profile_int(chSection,"fHomePosOffset",g_tSysParam.tAxisParam[i].fHomePosOffset);
    }

	int dwSize;
    get_write_ini((char*)m_ParaBuf,&dwSize);

#if 1
	CFile fFile;
#ifdef _UNICODE
		TCHAR uName[300] ={ 0};
		MultiByteToWideChar (CP_ACP, 0, iniPath, -1, uName, 300);
#else
	char* uName = iniPath;
#endif
	if(!fFile.Open(uName,CFile::modeCreate|CFile::modeWrite))
	{//打开失败。
		//加载默认的配置参数。
		return -1;
	}
     fFile.Write(m_ParaBuf,dwSize);
	 fFile.Close();
     
	
#else
	//写入到文本文件。
	FILE *fFile;
	if((fFile = fopen(iniPath,"wt+"))==NULL)//"rt"
	{
		return -1;
	}
	fwrite(m_ParaBuf,1,dwSize,fFile);
	fclose(fFile);
#endif

	return 0;

}