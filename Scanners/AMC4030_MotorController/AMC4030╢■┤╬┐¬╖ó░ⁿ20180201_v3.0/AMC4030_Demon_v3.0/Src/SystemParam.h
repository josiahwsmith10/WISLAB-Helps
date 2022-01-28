#ifndef SYSTEMPARAM_H_BY_TP_20170323
#define SYSTEMPARAM_H_BY_TP_20170323

//#include "Commdefine.h"
//////////////////////////////////////////////////////////////
////////////////////////////~{O5M32NJ}=a99Le~}////////////////////
#define MAX_AXIS_NUM		3
typedef struct _SYS_MACHINE_PARAM_SET
{
    float fTimerPeriod;            
    float fWorkPrecision;          
    float fArcCheckPrecision;      
    float fMinLen;                 
    float fMaxFeedSpeed;           

    WORD   nAccelType;             
    WORD 	nHomePowerOn;          

    float fMaxAccelSpeed;          
    float fAccelSpeed;             
    float fFastAccelSpeed;         
    float fJAccelSpeed;            
    DWORD  nRsv[20];


} SYS_MACHINE_PARAM,*PSYS_MACHINE_PARAM;


typedef struct _AXIS_PARAM_SET
{
    float   nPulseFactorUp;              
    float   nPulseFactorDown;            
    int	    nPulseLogic;				 

    float fMaxSpeed;                     
    float fMaxPos;                       

    int   nEnableBackLash;               
    float fBackLashLen;                  
    float fBackLashSpeed;                

    int   nHomeDir;                      
    float fHomeSpeed;                    
    float fHomeCheckDis;                
    float fHomeZeroSpeed;                
    float fHomeOrgSpeed;                 
    float fHomePosOffset;                
              
    DWORD  nRsv[20];


} AXIS_PARAM,*PAXIS_PARAM;

typedef struct _SYSTEM_PARAM
{
    SYS_MACHINE_PARAM       MachineParam;               
    AXIS_PARAM              tAxisParam[MAX_AXIS_NUM];     
    DWORD          dwRsv[100];

} SYS_PARAM,*PSYS_PARAM;


extern SYS_PARAM		g_tSysParam;
//~{6AEdVCND<~!#~}
int SYS_ReadSysCfgFile();
int SYS_ReadSysCfgFile_ini(char* iniPath);
//~{P4EdVCND<~!#~}
int SYS_WriteSysCfgFile();
int SYS_WriteSysCfgFile_ini(char* iniPath);

int SYS_LoadDefaultSysCfgFile();






#endif