// CalPulseFactor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AMC4030_Demon.h"
#include "CalPulseFactor.h"
#include "afxdialogex.h"


// CCalPulseFactor �Ի���
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


// CCalPulseFactor ��Ϣ�������


void CCalPulseFactor::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_fPulseDown = m_fDown;
	m_fPulseUp = m_fUp;
	CDialogEx::OnOK();
}


BOOL CCalPulseFactor::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
			m_fDown = m_fPulseDown;
	m_fUp = m_fPulseUp;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
