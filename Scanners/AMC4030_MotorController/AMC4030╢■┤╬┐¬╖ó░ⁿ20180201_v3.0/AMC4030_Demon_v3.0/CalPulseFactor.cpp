// CalPulseFactor.cpp : 实现文件
//

#include "stdafx.h"
#include "AMC4030_Demon.h"
#include "CalPulseFactor.h"
#include "afxdialogex.h"


// CCalPulseFactor 对话框
float m_fPulseDown;
float m_fPulseUp;
IMPLEMENT_DYNAMIC(CCalPulseFactor, CDialogEx)

CCalPulseFactor::CCalPulseFactor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalPulseFactor::IDD, pParent)
	, m_fDown(0)
	, m_fUp(0)
{

}

CCalPulseFactor::~CCalPulseFactor()
{
}

void CCalPulseFactor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PULSE_DWON, m_fDown);
	DDX_Text(pDX, IDC_EDIT_PULSE_UP, m_fUp);
}


BEGIN_MESSAGE_MAP(CCalPulseFactor, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCalPulseFactor::OnBnClickedOk)
END_MESSAGE_MAP()


// CCalPulseFactor 消息处理程序


void CCalPulseFactor::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_fPulseDown = m_fDown;
	m_fPulseUp = m_fUp;
	CDialogEx::OnOK();
}


BOOL CCalPulseFactor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
			m_fDown = m_fPulseDown;
	m_fUp = m_fPulseUp;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
