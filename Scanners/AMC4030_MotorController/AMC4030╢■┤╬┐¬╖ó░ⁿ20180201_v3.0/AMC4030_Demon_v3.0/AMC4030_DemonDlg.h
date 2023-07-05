
// AMC4030_DemonDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

enum TabPageID
{
	PAGE_MANUL=0,
	PAGE_SYS_PARAM,
	PAGE_SYS_MY_ABOUT,
	MAX_PAGE_NUM
};
// CAMC4030_DemonDlg �Ի���
class CAMC4030_DemonDlg : public CDialogEx
{
// ����
public:
	CAMC4030_DemonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AMC4030_DEMON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;
	CDialog* m_tabPages[MAX_PAGE_NUM];
	int m_nNumberOfPages;
	

public:
	int TabCtrl_Init();//��ʼ��tabҳ��
	afx_msg void OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};
extern int m_tabCurrent;//��ǰѡ�е�pageҳ
