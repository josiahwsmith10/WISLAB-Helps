
// AMC4030_DemonDlg.h : 头文件
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
// CAMC4030_DemonDlg 对话框
class CAMC4030_DemonDlg : public CDialogEx
{
// 构造
public:
	CAMC4030_DemonDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AMC4030_DEMON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	int TabCtrl_Init();//初始化tab页。
	afx_msg void OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};
extern int m_tabCurrent;//当前选中的page页
