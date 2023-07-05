
// AMC4030_DemonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AMC4030_Demon.h"
#include "AMC4030_DemonDlg.h"
#include "afxdialogex.h"
#include "ManualPad.h"
#include "AMC4030DLL.h"
//TABSTEP1:
#include "SysParamPad.h"
#include "MyAbout.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int m_tabCurrent;//��ǰѡ�е�pageҳ

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAMC4030_DemonDlg �Ի���



CAMC4030_DemonDlg::CAMC4030_DemonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAMC4030_DemonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAMC4030_DemonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CAMC4030_DemonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CAMC4030_DemonDlg::OnSelchangeTab)
END_MESSAGE_MAP()


// CAMC4030_DemonDlg ��Ϣ�������

BOOL CAMC4030_DemonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SetWindowText(_T("AMC4030 v3.0"));
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	g_cDll.COM_API_SetComType(2);
	TabCtrl_Init();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAMC4030_DemonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAMC4030_DemonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAMC4030_DemonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
int CAMC4030_DemonDlg::TabCtrl_Init()
{

	::ZeroMemory(&m_tabPages, sizeof(m_tabPages));

	m_tabPages[0]=new CManualPad;
	//TABSTEP2://����ʵ����
	m_tabPages[PAGE_SYS_PARAM]=new CSysParamPad;
	m_tabPages[PAGE_SYS_MY_ABOUT] = new CMyAbout;
//	m_tabPages[2]=new CDlgTransparent;
//	m_tabPages[3]=new CDlgShadeButtonST;
//	m_tabPages[4]=new CDlgAbout;

	m_nNumberOfPages=MAX_PAGE_NUM;
	m_tabCurrent = 0;
	m_tabPages[PAGE_MANUL]->Create(IDD_DLG_MANUAL, &m_TabCtrl);
	//TABSTEP3:������Դ
	m_tabPages[PAGE_SYS_PARAM]->Create(IDD_DLG_SYS_PARAM, &m_TabCtrl);
	m_tabPages[PAGE_SYS_MY_ABOUT]->Create(IDD_DLG_MY_ABOUT, &m_TabCtrl);

	m_tabPages[PAGE_MANUL]->ShowWindow(SW_SHOW);
	//TABSTEP4://���ؽ���
	m_tabPages[PAGE_SYS_PARAM]->ShowWindow(SW_HIDE);
	m_tabPages[PAGE_SYS_MY_ABOUT]->ShowWindow(SW_HIDE);

	//�ƶ��Ի����λ�õ�TABCtrl��
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	m_TabCtrl.GetClientRect(&tabRect);
	m_TabCtrl.GetItemRect(0, &itemRect);

	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-1;
	nYc=tabRect.bottom-nY-1;

	m_tabPages[PAGE_MANUL]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
//	m_tabPages[1]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);

	for(int i=1;i<m_nNumberOfPages;i++)
	{
		m_tabPages[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
		CString str;
	str.LoadString(IDS_MANUL_TABPAGE1_TITL);
	m_TabCtrl.InsertItem(0, str);
	//TABSTEP5://���ӱ�����
	str.LoadString(IDS_SYS_PARM_TABPAGE_TITL);
	m_TabCtrl.InsertItem(1, str);

	str.LoadString(IDS_ABOUTBOX);
	m_TabCtrl.InsertItem(2, str);
//	m_cTabCtrl.InsertItem(1, _T("Frame2"));
	return 0;
}


//PAGE�л�����
void CAMC4030_DemonDlg::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//TABSTEP6://�л����档
	 m_tabCurrent = m_TabCtrl.GetCurSel();
	switch(m_tabCurrent)
	{
	case PAGE_MANUL:
			m_tabPages[PAGE_MANUL]->ShowWindow(SW_SHOW);
			m_tabPages[PAGE_SYS_PARAM]->ShowWindow(SW_HIDE);
			m_tabPages[PAGE_SYS_MY_ABOUT]->ShowWindow(SW_HIDE);
			break;
	case PAGE_SYS_PARAM:
			m_tabPages[PAGE_SYS_PARAM]->ShowWindow(SW_SHOW);
			m_tabPages[PAGE_MANUL]->ShowWindow(SW_HIDE);
			m_tabPages[PAGE_SYS_MY_ABOUT]->ShowWindow(SW_HIDE);
			break;
	case PAGE_SYS_MY_ABOUT:
			m_tabPages[PAGE_SYS_MY_ABOUT]->ShowWindow(SW_SHOW);
			m_tabPages[PAGE_MANUL]->ShowWindow(SW_HIDE);
			m_tabPages[PAGE_SYS_PARAM]->ShowWindow(SW_HIDE);
			::SendMessage(m_tabPages[PAGE_SYS_MY_ABOUT]->m_hWnd,(WM_USER+20), SBUTTON_DOWN,0);  
			break;
	}

}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
