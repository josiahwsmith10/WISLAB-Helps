// MyAbout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AMC4030_Demon.h"
#include "MyAbout.h"
#include "afxdialogex.h"
#include "AMC4030DLL.h"

// CMyAbout �Ի���

IMPLEMENT_DYNAMIC(CMyAbout, CDialogEx)

CMyAbout::CMyAbout(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyAbout::IDD, pParent)
{

}

CMyAbout::~CMyAbout()
{
}

void CMyAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BTN_UPDATE_FIRMWARE, m_Process);
	DDX_Control(pDX, IDC_PROGRESS_UPDATE, m_Process);
	//DDX_Control(pDX, IDC_CHECK_TEST, m_nCheckTest);
}


BEGIN_MESSAGE_MAP(CMyAbout, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_UPDATE_FIRMWARE, &CMyAbout::OnBnClickedBtnUpdateFirmware)
	ON_BN_CLICKED(IDC_BTN_UPDATE_FIRMWARE2, &CMyAbout::OnBnClickedBtnUpdateFirmware2)
END_MESSAGE_MAP()


// CMyAbout ��Ϣ�������


void CMyAbout::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	
}


BOOL CMyAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Process.SetRange(0,100);

	m_Process.SetStep(10);
	HICON m_hicn1;
	//m_hicn1=AfxGetApp()->LoadIcon(IDI_ICON_LED_OFF);
	
//	((CButton*)GetDlgItem(IDC_CHECK_TEST))->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_LED_OFF)));
//	m_nCheckTest.SetIcon(IDI_ICON_LED_OFF,IDI_ICON_LED_ON);
//	m_nCheckTest.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_Process.ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMyAbout::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//MessageBox(_T("122")); 
}


BOOL CMyAbout::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �ڴ����ר�ô����/����û���
	CString tmp;
	BYTE  buf[2000] = {0};
	switch (message)
	{
	case (WM_USER+20):
		//��ȡ�汾�ţ�
		if(g_cDll.COM_API_OpenLink(3,115200) != 1)
		{//û�����ϡ�
			tmp.LoadString(IDS_SHOW_LINK_FAILT);
			m_dwSn = 0;
			m_dwVer = 0;
			SetDlgItemText(IDC_STA_BOARD_VER,_T("V 0. 0. 0. 0"));
			SetDlgItemText(IDC_STA_BOARD_SN,_T("0x00000000"));
			MessageBox(tmp);
			return TRUE;
		}
		g_cDll.COM_API_GetMachineStatus(buf);
		memcpy(&m_dwVer,&buf[6],2);
		//#define COM_GET_BOARD_SN                           0xFFEC//����������к�
		buf[0] = 0xEC;
		buf[1] = 0xFF;
		g_cDll.COM_API_ReadData(2,buf,buf);
		memcpy(&m_dwSn,&buf[4],4);
		//tmp.Format(_T("V %2.2x,%2.2x,%2.2x,%2.2x"),(m_dwSn>>12)&0xf,(m_dwSn>>8)&0xf,(m_dwSn>>4)&0xf,(m_dwSn)&0xf);
		tmp.Format(_T("V %x,%x,%x,%x"),(m_dwVer>>12)&0xf,(m_dwVer>>8)&0xf,(m_dwVer>>4)&0xf,(m_dwVer)&0xf);
		SetDlgItemText(IDC_STA_BOARD_VER,tmp);
		tmp.Format(_T("0x%8.8x"),m_dwSn);
		SetDlgItemText(IDC_STA_BOARD_SN,tmp);
		return TRUE;
		break;
	default:
		break;
	}
	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}


void CMyAbout::OnBnClickedBtnUpdateFirmware()
{
	int len,nRtn;
////////////////////////////////////////////////
#define ONCE_SEND_DATA 500
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
			CString str;
	CString fliter =_T(" FirmWare(*.bin)|*.bin|All Files (*.*)|*.*||");
	CFileDialog flg(TRUE,
		NULL,//_T("AMC4030.bin"),
		NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		fliter);
	if(flg.DoModal()!= IDOK)return ;
	CString filename = flg.GetPathName();
	int i;
	int nID;
	//ȷ���ļ�����
	CString sufixx = flg.GetFileExt(); //GetFileExt����ѡ���ļ�����չ�ļ���
	sufixx.MakeUpper();
	if(sufixx != _T("BIN"))
	{
		return  ;
	}
#if 1
//////////////////////////////////////////////////////////////////////////////////
#ifdef _UNICODE
	char temp[200];
	i = WideCharToMultiByte( CP_ACP,0,filename.GetBuffer(0),-1,NULL,0,NULL,NULL );
    WideCharToMultiByte( CP_ACP,0,filename.GetBuffer(0),-1,temp,i,NULL,NULL);

#else
	char* temp = filename.GetBuffer(0) ;
#endif
     nRtn = g_cDll.COM_API_DowloadFile(temp,3,1);
	 if(nRtn ==1)
	 {
		 str.LoadString(IDS_UPDATA_SUCC);
	 }
	 else
		 str.LoadString(IDS_UPDATA_FAIL);
	 MessageBox(str);
	return;
#endif
////////////////////////////////////////////////////////////////////////////////////
	m_Process.SetRange(0,100);
	m_Process.SetPos(0);
	m_Process.ShowWindow(SW_SHOW);
	CFile fFile;
	if(!fFile.Open(filename,CFile::modeRead))
	{//��ʧ�ܡ�
		return ;
	}
	
	BYTE* buf;
	len = fFile.GetLength();
	buf = new BYTE[len+1];
	memset(buf,0,len+1);
	fFile.Read(buf,len);
	buf[len] = 0;
	fFile.Close();

	//���ع̼���
	if(g_cDll.COM_API_OpenLink(3,115200) != 1)
	{//û�����ϡ�

		str.LoadString(IDS_SHOW_LINK_FAILT);
		MessageBox(str);
		return ;
	}
	int Last,Cur;
	Last = Cur = 0;
	for(i=0;i<len;)
	{
			Cur = 1.0*i/len*100;
			if(Cur != Last)
			{
				m_Process.SetPos(Cur);
			//	wndProgress.PeekAndPump();
				Last = Cur;
			}
		if((i+ONCE_SEND_DATA)<= len)
		{
			if(i==0)
				nRtn = g_cDll.COM_API_WriteFileData(3,0,ONCE_SEND_DATA,&buf[i]);
			else
				nRtn = g_cDll.COM_API_WriteFileData(3,1,ONCE_SEND_DATA,&buf[i]);
			i += ONCE_SEND_DATA;
		}
		else
		{
			int len1 =len -i;
			if(i==0)
				nRtn = g_cDll.COM_API_WriteFileData(3,0,len1,&buf[i]);
			else
				nRtn = g_cDll.COM_API_WriteFileData(3,1,len1,&buf[i]);
			i += len1;
			break;
		}
		if(nRtn !=1)break;//ͨѶ�쳣��
	
	}
	m_Process.ShowWindow(SW_HIDE);
//	Sleep(100);
	if(nRtn == 1)
	{

		str.LoadString(IDS_DOWNLOAD_SUCC);
		MessageBox(str);

	}
	else
	{
		str.LoadString(IDS_DOWNLOAD_FAILT);
		MessageBox(str);
	}

}


void CMyAbout::OnBnClickedBtnUpdateFirmware2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int len,nRtn;
////////////////////////////////////////////////
#define ONCE_SEND_DATA 500
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
			CString str;
	CString fliter =_T(" FirmWare(*.bin)|*.bin|All Files (*.*)|*.*||");
	CFileDialog flg(TRUE,
		NULL,//_T("AMC4030.bin"),
		NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		fliter);
	if(flg.DoModal()!= IDOK)return ;
	CString filename = flg.GetPathName();
	int i;
	int nID;
	//ȷ���ļ�����
	CString sufixx = flg.GetFileExt(); //GetFileExt����ѡ���ļ�����չ�ļ���
	sufixx.MakeUpper();
	if(sufixx != _T("ELO"))
	{
		return  ;
	}
#if 1
//////////////////////////////////////////////////////////////////////////////////
#ifdef _UNICODE
	char temp[200];
	i = WideCharToMultiByte( CP_ACP,0,filename.GetBuffer(0),-1,NULL,0,NULL,NULL );
    WideCharToMultiByte( CP_ACP,0,filename.GetBuffer(0),-1,temp,i,NULL,NULL);

#else
	char* temp = filename.GetBuffer(0) ;
#endif
     nRtn = g_cDll.COM_API_DowloadFile(temp,2,1);
	 if(nRtn ==1)
	 {
		 str.LoadString(IDS_UPDATA_SUCC);
	 }
	 else
		 str.LoadString(IDS_UPDATA_FAIL);
	 MessageBox(str);
	return;
#endif
}
