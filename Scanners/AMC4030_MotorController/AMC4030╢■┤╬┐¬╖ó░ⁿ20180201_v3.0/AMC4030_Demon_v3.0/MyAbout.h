#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "BtnST.h"

// CMyAbout �Ի���

class CMyAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CMyAbout)

public:
	CMyAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyAbout();

// �Ի�������
	enum { IDD = IDD_DLG_MY_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
