#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "BtnST.h"

// CMyAbout 对话框

class CMyAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CMyAbout)

public:
	CMyAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyAbout();

// 对话框数据
	enum { IDD = IDD_DLG_MY_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	WORD m_dwVer;
	DWORD m_dwSn;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnBnClickedBtnUpdateFirmware();
//	CButton m_Process;
	CProgressCtrl m_Process;
//	CButtonST m_nCheckTest;
	afx_msg void OnBnClickedBtnUpdateFirmware2();
};
