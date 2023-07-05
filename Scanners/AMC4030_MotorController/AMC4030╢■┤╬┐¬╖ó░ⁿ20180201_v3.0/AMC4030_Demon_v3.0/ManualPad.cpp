// ManualPad.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AMC4030_Demon.h"
#include "ManualPad.h"
#include "afxdialogex.h"
#include "AMC4030_DemonDlg.h"
#include "AMC4030DLL.h"
//extern int m_tabCurrent;//��ǰѡ�е�pageҳ

// CManualPad �Ի���
int flag = 0;
IMPLEMENT_DYNAMIC(CManualPad, CDialogEx)

CManualPad::CManualPad(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualPad::IDD, pParent)
{

}

CManualPad::~CManualPad()
{
}

void CManualPad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_X_N, m_Btn_X_N);
	DDX_Control(pDX, IDC_BTN_X_P, m_Btn_X_P);
	DDX_Control(pDX, IDC_BTN_Y_N, m_Btn_Y_N);
	DDX_Control(pDX, IDC_BTN_Y_P, m_Btn_Y_P);
	DDX_Control(pDX, IDC_BTN_Z_N, m_Btn_Z_N);
	DDX_Control(pDX, IDC_BTN_Z_P, m_Btn_Z_P);
}


BEGIN_MESSAGE_MAP(CManualPad, CDialogEx)
	ON_MESSAGE(WM_THREADMSG, OnMsgFunc)
	ON_BN_CLICKED(IDC_CHECK_STEP_ENABLE, &CManualPad::OnBnClickedCheckStepEnable)
	ON_BN_CLICKED(IDC_CHECK_OUT1, &CManualPad::OnBnClickedCheckOut1)
	ON_BN_CLICKED(IDC_BTN_X_HOME, &CManualPad::OnBnClickedBtnXHome)
	ON_BN_CLICKED(IDC_BTN_Y_HOME, &CManualPad::OnBnClickedBtnYHome)
	ON_BN_CLICKED(IDC_BTN_Z_HOME, &CManualPad::OnBnClickedBtnZHome)
	ON_BN_CLICKED(IDC_BTN_STOP, &CManualPad::OnBnClickedBtnStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_OUT2, &CManualPad::OnBnClickedCheckOut2)
	ON_BN_CLICKED(IDC_CHECK_OUT3, &CManualPad::OnBnClickedCheckOut3)
	ON_BN_CLICKED(IDC_CHECK_OUT4, &CManualPad::OnBnClickedCheckOut4)
END_MESSAGE_MAP()


// CManualPad ��Ϣ�������
LRESULT CManualPad::OnMsgFunc(WPARAM wParam,LPARAM lParam)
{
	return 0;
	CString str ;
	float fSpeed;
	float fDis = 99999.999f;
	
	switch(wParam)
	{
	case SBUTTON_DOWN:
		UpdateData(TRUE);
		GetDlgItemText(IDC_EDIT_MANUL_SPEED,str);
		fSpeed=_wtof(str);
	//�����ѡ���˾���ģʽ������¾��롣
	if(((CButton*)GetDlgItem(IDC_CHECK_STEP_ENABLE ))->GetCheck())
	{
		GetDlgItemText(IDC_EDIT_STEP_DIS,str);
		 fDis = _wtof(str);
	}
		if((fSpeed>0)&&(fDis>0))
		{
		if(lParam ==(LPARAM)m_Btn_X_N.m_hWnd)
		{
			TRACE(_T("X- BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(0,-1*fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_X_P.m_hWnd)
		{
			TRACE(_T("X+ BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(0,fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Y_N.m_hWnd)
		{
			TRACE(_T("Y- BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(1,-1*fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Y_P.m_hWnd)
		{
			TRACE(_T("Y+ BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(1,fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Z_N.m_hWnd)
		{
			TRACE(_T("Z- BTN DOWN\r\n"));

			g_cDll.COM_API_Jog(2,-1*fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Z_P.m_hWnd)
		{
			TRACE(_T("Z+ BTN DOWN\r\n"));

			g_cDll.COM_API_Jog(2,fDis,fSpeed);
		}
		}
	
		break;
	case SBUTTON_UP:
		TRACE(_T("btn up\r\n"));
		//����ǲ���ģʽ�򲻷���ֹͣ���
		if(((CButton*)GetDlgItem(IDC_CHECK_STEP_ENABLE))->GetCheck())
			break;
//		WaitForSingleObject(g_hCom_mutex,INFINITE);
		g_cDll.COM_API_StopAll();
		//ReleaseMutex(g_hCom_mutex);*/
		break;
	}
	return 0;
}

BOOL CManualPad::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemInt(IDC_EDIT_MANUL_SPEED,50);
	SetDlgItemInt(IDC_EDIT_STEP_DIS,20);
	GetDlgItem(IDC_EDIT_STEP_DIS)->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_CHECK_STEP_ENABLE))->SetCheck(FALSE);


	SetTimer(1,100,NULL);
	m_LastInput = 0;
	m_LastOutput = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CManualPad::OnBnClickedCheckStepEnable()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(((CButton*)GetDlgItem(IDC_CHECK_STEP_ENABLE))->GetCheck())
	{
		GetDlgItem(IDC_EDIT_STEP_DIS)->EnableWindow(TRUE);
		//((CButton*)GetDlgItem(IDC_EDIT_STEP_DIS))->Enable();	
	}
	else
	{
		GetDlgItem(IDC_EDIT_STEP_DIS)->EnableWindow(FALSE);
	}
}





void CManualPad::OnBnClickedBtnXHome()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		g_cDll.COM_API_Home(1,0,0);
}


void CManualPad::OnBnClickedBtnYHome()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_cDll.COM_API_Home(0,1,0);
}


void CManualPad::OnBnClickedBtnZHome()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_cDll.COM_API_Home(0,0,1);
}


void CManualPad::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		g_cDll.COM_API_StopAll();
}
void CManualPad::OnBnClickedCheckOut1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nStatus = 0;
	if(((CButton*)GetDlgItem(IDC_CHECK_OUT1))->GetCheck())
	{
		nStatus = 1;	
	}
	else
	{
		nStatus = 0;
	}
	g_cDll.COM_API_SetOutputBit(1,nStatus);

}
void CManualPad::OnBnClickedCheckOut2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int nStatus = 0;
	if(((CButton*)GetDlgItem(IDC_CHECK_OUT2))->GetCheck())
	{
		nStatus = 1;	
	}
	else
	{
		nStatus = 0;
	}
	g_cDll.COM_API_SetOutputBit(2,nStatus);
}


void CManualPad::OnBnClickedCheckOut3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int nStatus = 0;
	if(((CButton*)GetDlgItem(IDC_CHECK_OUT3))->GetCheck())
	{
		nStatus = 1;	
	}
	else
	{
		nStatus = 0;
	}
	g_cDll.COM_API_SetOutputBit(3,nStatus);
}


void CManualPad::OnBnClickedCheckOut4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int nStatus = 0;
	if(((CButton*)GetDlgItem(IDC_CHECK_OUT4))->GetCheck())
	{
		nStatus = 1;	
	}
	else
	{
		nStatus = 0;
	}
	g_cDll.COM_API_SetOutputBit(4,nStatus);
}

void CManualPad::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int i;
	CString tmp;
	//������ֶ�������ʼ״̬����

	if(flag)
	{
		CDialogEx::OnTimer(nIDEvent);
		return;//�����ˡ�
	}
	flag++;
	if(m_tabCurrent== PAGE_MANUL)
	{
		
		//STPE1:��ѯ�Ƿ�Ϳ��ƿ�������
		if(g_cDll.COM_API_OpenLink(3,115200) != 1)
		{//û�����ϡ�
			tmp.LoadString(IDS_SHOW_LINK_FAILT);
			SetDlgItemText(IDC_EDIT_SHOW_LINK ,tmp);
			CDialogEx::OnTimer(nIDEvent);
			flag = 0;
			return;
		}

		//�����Ͽ��ƿ���
	//	tmp.LoadString(IDS_SHOW_LINK_OK);
	//	SetDlgItemText(IDC_EDIT_SHOW_LINK,tmp);
		//��ȡ����������״̬��
		//ͨѶ�ӿڡ����ӡ�

		 i = g_cDll.COM_API_GetMachineStatus((PBYTE)&tMachineStatus);
		 if(i!=1)
		 {
			 flag = 0;
			 CDialogEx::OnTimer(nIDEvent);
			 return;
		 }
		 if(tMachineStatus.dwWorkStatus & 0x04)
		 {
			 tmp.LoadString(IDS_STATUS_JOG);
		 }
		 else if(tMachineStatus.dwWorkStatus & 0x08)
		 {
			 tmp.LoadString(IDS_STATUS_HOME);
		 }
		 else
			 tmp.LoadString(IDS_STATUS_IDLE);
		 SetDlgItemText(IDC_EDIT_SHOW_LINK,tmp);
		 //����λ�á�
		 tmp.Format(_T("%.3f"),(1.0*tMachineStatus.nPos[0]/100000.0));
		 SetDlgItemText(IDC_EDIT_SHOW_X_POS,tmp);
		 tmp.Format(_T("%.3f"),(1.0*tMachineStatus.nPos[1]/100000.0));
		 SetDlgItemText(IDC_EDIT_SHOW_Y_POS,tmp);
		 tmp.Format(_T("%.3f"),(1.0*tMachineStatus.nPos[2]/100000.0));
		 SetDlgItemText(IDC_EDIT_SHOW_Z_POS,tmp);

	
		//�����:
		if(tMachineStatus.dwInputStatus & 0x01)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN1))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN1))->SetCheck(FALSE);

		if(tMachineStatus.dwInputStatus & 0x02)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN2))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN2))->SetCheck(FALSE);

		if(tMachineStatus.dwInputStatus & 0x04)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN3))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN3))->SetCheck(FALSE);

		if(tMachineStatus.dwInputStatus & 0x08)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN4))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_IN4))->SetCheck(FALSE);
		
		//ԭ��
		if(tMachineStatus.dwInputStatus & 0x10)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_ORG1))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_ORG1))->SetCheck(FALSE);
		if(tMachineStatus.dwInputStatus & 0x20)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_ORG2))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_ORG2))->SetCheck(FALSE);
		if(tMachineStatus.dwInputStatus & 0x40)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_ORG3))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_ORG3))->SetCheck(FALSE);

		//�����
		if(tMachineStatus.dwOutputStatus & 0x01)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT1))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT1))->SetCheck(FALSE);

		if(tMachineStatus.dwOutputStatus & 0x02)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT2))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT2))->SetCheck(FALSE);

		if(tMachineStatus.dwOutputStatus & 0x04)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT3))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT3))->SetCheck(FALSE);

		if(tMachineStatus.dwOutputStatus & 0x08)
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT4))->SetCheck(TRUE);
		else
			((CButton*)GetDlgItem(IDC_CHECK_SHOW_OUT4))->SetCheck(FALSE);
	
	//	UpdateData(FALSE);
	}
	flag = 0;
	CDialogEx::OnTimer(nIDEvent);
}





BOOL CManualPad::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
		CString str ;
	float fSpeed;
	float fDis = 99999.999f;
	int nRtn;
//	static int ttt = 0;
	// TODO: �ڴ����ר�ô����/����û���
	switch(message)  
    {  
	case SBUTTON_DOWN:
		UpdateData(TRUE);
		GetDlgItemText(IDC_EDIT_MANUL_SPEED,str);
		fSpeed=_wtof(str);
	//�����ѡ���˾���ģʽ������¾��롣
	if(((CButton*)GetDlgItem(IDC_CHECK_STEP_ENABLE ))->GetCheck())
	{
		GetDlgItemText(IDC_EDIT_STEP_DIS,str);
		 fDis = _wtof(str);
	}
		if((fSpeed>0)&&(fDis>0))
		{
		if(lParam ==(LPARAM)m_Btn_X_N.m_hWnd)
		{
		//	TRACE(_T("X- BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(0,-1*fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_X_P.m_hWnd)
		{
		//	TRACE(_T("X+ BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(0,fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Y_N.m_hWnd)
		{
		//	TRACE(_T("Y- BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(1,-1*fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Y_P.m_hWnd)
		{
		//	TRACE(_T("Y+ BTN DOWN\r\n"));
			g_cDll.COM_API_Jog(1,fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Z_N.m_hWnd)
		{
		//	TRACE(_T("Z- BTN DOWN\r\n"));

			g_cDll.COM_API_Jog(2,-1*fDis,fSpeed);
		}
		else if(lParam ==(LPARAM)m_Btn_Z_P.m_hWnd)
		{
		//	TRACE(_T("Z+ BTN DOWN\r\n"));

			g_cDll.COM_API_Jog(2,fDis,fSpeed);
		}
		}
	
		break;
	case SBUTTON_UP:
		//TRACE(_T("btn up\r\n"));
		//����ǲ���ģʽ�򲻷���ֹͣ���
		if(((CButton*)GetDlgItem(IDC_CHECK_STEP_ENABLE))->GetCheck())
			break;
		nRtn = g_cDll.COM_API_StopAll();
		if(nRtn == -6)
		{//����
			::PostMessage(m_hWnd, SBUTTON_UP,0,0); 
			//ttt++;
			//TRACE(_T("STOP,overlapped %d\r\n"),ttt);
		}
		break;
	}  
    
	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}
