#pragma once
#include "mybutton.h"


// CManualPad 对话框
typedef struct _MACHINE_STATUS_
{
	DWORD	dwWorkStatus;		
	BYTE	dwHomeDone;			
	BYTE	nID;					
	WORD	FirmVer;		
	int		nPos[3];		
	int		RealSpeed[3];	
	DWORD	nAlmCode;	
	WORD	dwInputStatus;			
	WORD 	dwOutputStatus;		
	DWORD	Rsv[4];				
}MACHINE_STATUS,*PMACHINE_STATUS;

class CManualPad : public CDialogEx
{
	DECLARE_DYNAMIC(CManualPad)

public:
	CManualPad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManualPad();

// 对话框数据
	enum { IDD = IDD_DLG_MANUAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg	LRESULT OnMsgFunc(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
public:
	int ntp;
	CMyButton m_Btn_X_N;

	CMyButton m_Btn_X_P;
	CMyButton m_Btn_Y_N;
	CMyButton m_Btn_Y_P;
	CMyButton m_Btn_Z_N;
	CMyButton m_Btn_Z_P;
	MACHINE_STATUS tMachineStatus;
	DWORD  m_LastInput;
	DWORD  m_LastOutput;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckStepEnable();
	afx_msg void OnBnClickedCheckOut1();
	afx_msg void OnBnClickedBtnXHome();
	afx_msg void OnBnClickedBtnYHome();
	afx_msg void OnBnClickedBtnZHome();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckOut2();
	afx_msg void OnBnClickedCheckOut3();
	afx_msg void OnBnClickedCheckOut4();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
