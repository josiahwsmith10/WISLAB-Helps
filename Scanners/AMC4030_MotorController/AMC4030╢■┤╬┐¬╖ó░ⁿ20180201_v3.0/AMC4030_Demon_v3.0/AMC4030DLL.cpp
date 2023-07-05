#include "stdafx.h"
#include "AMC4030DLL.h"
CAMC4030DLL  g_cDll;

CAMC4030DLL::CAMC4030DLL(void)
{
	hDllLib = LoadLibrary(_T("AMC4030.dll"));
	
	if(hDllLib != NULL)
	{
		p_COM_API_SetComType =(API_COM_API_SetComType)GetProcAddress(hDllLib,(LPCSTR)("COM_API_SetComType"));
		p_COM_API_OpenLink	=(API_COM_API_OpenLink)GetProcAddress(hDllLib,(LPCSTR)("COM_API_OpenLink"));
		p_COM_API_GetMachineStatus =(API_COM_API_GetMachineStatus)GetProcAddress(hDllLib,(LPCSTR)("COM_API_GetMachineStatus"));		
		p_COM_API_ReadFileData =(API_COM_API_ReadFileData)GetProcAddress(hDllLib,(LPCSTR)("COM_API_ReadFileData"));		
		p_COM_API_WriteFileData	=(API_COM_API_WriteFileData)GetProcAddress(hDllLib,(LPCSTR)("COM_API_WriteFileData"));
		p_COM_API_Jog =(API_COM_API_Jog)GetProcAddress(hDllLib,(LPCSTR)("COM_API_Jog"))	;
		p_COM_API_Home =(API_COM_API_Home)GetProcAddress(hDllLib,(LPCSTR)("COM_API_Home"))	;
		p_COM_API_StopAxis =(API_COM_API_StopAxis)GetProcAddress(hDllLib,(LPCSTR)("COM_API_StopAxis"))	;
		p_COM_API_StopAll = (API_COM_API_StopAll)GetProcAddress(hDllLib,(LPCSTR)("COM_API_StopAll"))	;
		p_COM_API_SetOutputBit = (API_COM_API_SetOutputBit)GetProcAddress(hDllLib,(LPCSTR)("COM_API_SetOutputBit"))	;
		p_COM_API_GetLastError = (API_COM_API_GetLastError)GetProcAddress(hDllLib,(LPCSTR)("COM_API_GetLastError"));	
		p_COM_API_DowloadSystemCfg = (API_COM_API_DowloadSystemCfg)GetProcAddress(hDllLib,(LPCSTR)("COM_API_DowloadSystemCfg"));	
		p_COM_API_SendData = (API_COM_API_SendData)GetProcAddress(hDllLib,(LPCSTR)("COM_API_SendData"));
		p_COM_API_ReadData = (API_COM_API_ReadData)GetProcAddress(hDllLib,(LPCSTR)("COM_API_ReadData"));
		p_COM_API_DowloadFile = (API_COM_API_DowloadFile)GetProcAddress(hDllLib,(LPCSTR)("COM_API_DowloadFile"));

	}
}


CAMC4030DLL::~CAMC4030DLL(void)
{

}
int CAMC4030DLL::COM_API_SetComType(int nType)
{
	if(p_COM_API_SetComType)
	{
		return p_COM_API_SetComType(nType);
	}
	return -10;
}
int CAMC4030DLL::COM_API_OpenLink(int nID,int nBound)
{
	if(p_COM_API_OpenLink)
	{
		return p_COM_API_OpenLink(nID,nBound);
	}
	return -10;
}
int CAMC4030DLL::COM_API_GetMachineStatus(unsigned char* unStatus)
{
	if(p_COM_API_GetMachineStatus)
	{
		return p_COM_API_GetMachineStatus(unStatus);
	}
	return -10;
}
int CAMC4030DLL::COM_API_ReadFileData(int nSrc,int StartAdd,int len,unsigned char* pOutput)
{
	if(p_COM_API_ReadFileData)
	{
		return p_COM_API_ReadFileData(nSrc,StartAdd,len,pOutput);
	}
	return -10;
}
int CAMC4030DLL::COM_API_WriteFileData(int nSrc,int StartAdd,int len,unsigned char* pInput)
{
	if(p_COM_API_WriteFileData)
	{
		return p_COM_API_WriteFileData(nSrc,StartAdd,len,pInput);
	}
	return -10;
}
int CAMC4030DLL::COM_API_Jog(int nAxis,float fDis,float Speed)
{
	if(p_COM_API_Jog)
	{
		return p_COM_API_Jog(nAxis,fDis,Speed);
	}
	return -10;
}
int CAMC4030DLL::COM_API_Home(int nXAxisSet,int nYAxisSet,int nZAxisSet)
{
	if(p_COM_API_Home)
	{
		return p_COM_API_Home(nXAxisSet,nYAxisSet,nZAxisSet);
	}
	return -10;
}
int CAMC4030DLL::COM_API_StopAxis(int nXAxisSet,int nYAxisSet,int nZAxisSet)
{
	if(p_COM_API_StopAxis)
	{
		return p_COM_API_StopAxis(nXAxisSet,nYAxisSet,nZAxisSet);
	}
	return -10;
}
int CAMC4030DLL::COM_API_StopAll()
{
	if(p_COM_API_StopAll)
	{
		return p_COM_API_StopAll();
	}
	return -10;
}
int CAMC4030DLL::COM_API_SetOutputBit(int OutputID,int nStatus)
{
	if(p_COM_API_SetOutputBit)
	{
		return p_COM_API_SetOutputBit(OutputID,nStatus);
	}
	return -10;
}
int CAMC4030DLL::COM_API_GetLastError(unsigned int* dwErr)
{
	if(p_COM_API_GetLastError)
	{
		return p_COM_API_GetLastError(dwErr);
	}
	return -10;
}
int CAMC4030DLL::COM_API_DowloadSystemCfg(char* iniPath)
{
	if(p_COM_API_DowloadSystemCfg)
	{
		return p_COM_API_DowloadSystemCfg(iniPath);
	}
	return -10;
}
int CAMC4030DLL::COM_API_DowloadFile(char* szPath,int nType,int ShowProcess)
{
	if(p_COM_API_DowloadFile)
	{
		return p_COM_API_DowloadFile(szPath,nType,ShowProcess);
	}
	return -10;
}

int CAMC4030DLL::COM_API_SendData(int nLen,unsigned char* pData)
{
	if(p_COM_API_SendData)
	{
		return p_COM_API_SendData(nLen,pData);
	}
	return -10;
}
int CAMC4030DLL::COM_API_ReadData(int nLen,unsigned char* pInput,unsigned char* pOutput)
{
	if(p_COM_API_ReadData)
	{
		return p_COM_API_ReadData(nLen,pInput,pOutput);
	}
	return -10;
}
