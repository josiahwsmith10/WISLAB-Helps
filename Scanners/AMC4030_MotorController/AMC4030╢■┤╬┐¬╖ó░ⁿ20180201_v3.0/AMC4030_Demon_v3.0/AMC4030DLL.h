#pragma once

//DLL接口函数定义
typedef int (WINAPI* API_COM_API_SetComType)(int nType);//设置通讯类型
typedef int (WINAPI* API_COM_API_OpenLink)(int nID,int nBound);//打开连接。
typedef int (WINAPI* API_COM_API_GetMachineStatus)(unsigned char* unStatus);//获取机器状态字。
typedef int (WINAPI* API_COM_API_ReadFileData)(int nSrc,int StartAdd,int len,unsigned char* pOutput);
typedef int (WINAPI* API_COM_API_WriteFileData)(int nSrc,int StartAdd,int len,unsigned char* pInput);
typedef int (WINAPI* API_COM_API_Jog)(int nAxis,float fDis,float Speed);
typedef int (WINAPI* API_COM_API_Home)(int nXAxisSet,int nYAxisSet,int nZAxisSet);
typedef int (WINAPI* API_COM_API_StopAxis)(int nXAxisSet,int nYAxisSet,int nZAxisSet);
typedef int (WINAPI* API_COM_API_StopAll)();	
typedef int (WINAPI* API_COM_API_SetOutputBit)(int OutputID,int nStatus);
typedef int (WINAPI* API_COM_API_GetLastError)(unsigned int* dwErr);//
typedef int (WINAPI* API_COM_API_DowloadSystemCfg)(char* iniPath);//
typedef int (WINAPI* API_COM_API_SendData)(int nLen,unsigned char* pData);
typedef int (WINAPI* API_COM_API_ReadData)(int nLen,unsigned char* pInput,unsigned char* pOutput);
typedef int (WINAPI* API_COM_API_DowloadFile)(char* szPath,int nType,int ShowProcess);
class CAMC4030DLL		
{	
		HINSTANCE hDllLib;
public:
	CAMC4030DLL(void);
	~CAMC4030DLL(void);


		//接口函数指针变量定义
//	API_InitBoard			p_InitBoard;
	API_COM_API_SetComType					p_COM_API_SetComType;
	API_COM_API_OpenLink					p_COM_API_OpenLink	;		
	API_COM_API_GetMachineStatus			p_COM_API_GetMachineStatus;		 
	API_COM_API_ReadFileData				p_COM_API_ReadFileData;
	API_COM_API_WriteFileData				p_COM_API_WriteFileData;
	API_COM_API_Jog							p_COM_API_Jog;	
	API_COM_API_Home						p_COM_API_Home;
	API_COM_API_StopAxis					p_COM_API_StopAxis;
	API_COM_API_StopAll						p_COM_API_StopAll;	
	API_COM_API_SetOutputBit				p_COM_API_SetOutputBit;
	API_COM_API_GetLastError				p_COM_API_GetLastError;
	API_COM_API_DowloadSystemCfg			p_COM_API_DowloadSystemCfg;//
	API_COM_API_SendData					p_COM_API_SendData;
	API_COM_API_ReadData					p_COM_API_ReadData;
	API_COM_API_DowloadFile					p_COM_API_DowloadFile;
public:
	int	COM_API_SetComType(int nType);//设置通讯类型
	int	COM_API_OpenLink(int nID,int nBound);//打开连接。
	int	COM_API_GetMachineStatus(unsigned char* unStatus);//获取机器状态字。

	int	COM_API_ReadFileData(int nSrc,int StartAdd,int len,unsigned char* pOutput);
	int	COM_API_WriteFileData(int nSrc,int StartAdd,int len,unsigned char* pInput);

	int	COM_API_Jog(int nAxis,float fDis,float Speed);
	int	COM_API_Home(int nXAxisSet,int nYAxisSet,int nZAxisSet);
	int	COM_API_StopAxis(int nXAxisSet,int nYAxisSet,int nZAxisSet);
	int	COM_API_StopAll();	
	int	COM_API_SetOutputBit(int OutputID,int nStatus);
	int	COM_API_GetLastError(unsigned int* dwErr);//
	int	COM_API_DowloadSystemCfg(char* iniPath);//
	int COM_API_DowloadFile(char* szPath,int nType,int ShowProcess);
	int	COM_API_SendData(int nLen,unsigned char* pData);
	int	COM_API_ReadData(int nLen,unsigned char* pInput,unsigned char* pOutput);

};

extern CAMC4030DLL  g_cDll;