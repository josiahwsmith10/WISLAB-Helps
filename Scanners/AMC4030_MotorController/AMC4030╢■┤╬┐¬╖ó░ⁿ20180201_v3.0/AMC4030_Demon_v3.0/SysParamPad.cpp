// SysParamPad.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AMC4030_Demon.h"
#include "SysParamPad.h"
#include "afxdialogex.h"
#include "CalPulseFactor.h"
#include "AMC4030DLL.h"
// CSysParamPad �Ի���
extern float m_fPulseDown;
extern float m_fPulseUp;

IMPLEMENT_DYNAMIC(CSysParamPad, CDialogEx)

CSysParamPad::CSysParamPad(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysParamPad::IDD, pParent)
	, m_nAxisParamSel(0)
	, m_dbPulseFactor(0)
	, m_dbSysAccSpeed(0)
	, m_dbHomeSpeed(0)
	, m_dbHomeOffset(0)
	, m_dbBackLashLen(0)
	, m_fMaxPos(0)
{

}

CSysParamPad::~CSysParamPad()
{
}

void CSysParamPad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_RADIO_SYS_SEL_X, m_nAxisParamSel);
	DDX_Radio(pDX, IDC_RADIO_SYS_SEL_X, m_nAxisParamSel);
	DDX_Text(pDX, IDC_EDIT_SYS_PULSE_FACTOR, m_dbPulseFactor);
	DDX_Text(pDX, IDC_EDIT_SYS_ACC_SPEED, m_dbSysAccSpeed);
	DDX_Text(pDX, IDC_EDIT_SYS_HOME_SPEED, m_dbHomeSpeed);
	DDX_Text(pDX, IDC_EDIT_SYS_BACK_OFFSET, m_dbHomeOffset);
	DDX_Text(pDX, IDC_EDIT_SYS_BACKLASH, m_dbBackLashLen);
	DDX_Text(pDX, IDC_EDIT_SYS_MAX_POS, m_fMaxPos);
}


BEGIN_MESSAGE_MAP(CSysParamPad, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_SYS_SEL_X, &CSysParamPad::OnBnClickedRadioSysSelX)
	ON_BN_CLICKED(IDC_RADIO_SYS_SEL_Y, &CSysParamPad::OnBnClickedRadioSysSelY)
	ON_BN_CLICKED(IDC_RADIO_SYS_SEL_Z, &CSysParamPad::OnBnClickedRadioSysSelZ)
	ON_BN_CLICKED(IDC_BTN_SYS_DOWNLOAD_PARAM, &CSysParamPad::OnBnClickedBtnSysDownloadParam)
	ON_BN_CLICKED(IDC_BTN_SYS_UPDATA_PARAM, &CSysParamPad::OnBnClickedBtnSysUpdataParam)
	ON_BN_CLICKED(IDC_BTN_SYS_PULSE_FACTOR, &CSysParamPad::OnBnClickedBtnSysPulseFactor)
END_MESSAGE_MAP()


// CSysParamPad ��Ϣ�������


BOOL CSysParamPad::OnInitDialog()
{
	int i;
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
////////////////////////////////////////////////////////
//��ȡϵͳ·������ϵͳ�����ļ�����ֵ
	TCHAR filePATH[_MAX_PATH];
	
	TCHAR LogfilePATH[_MAX_PATH];
	GetModuleFileName(NULL, filePATH, _MAX_PATH);
	TCHAR *fileExt = _tcsrchr(filePATH, _T('\\'));//�ҵ����һ����.'
	*++fileExt = 0;
	wsprintf(LogfilePATH,_T("%sSystemCfg.ini"),filePATH);

#ifdef _UNICODE
		i = WideCharToMultiByte( CP_ACP,0,LogfilePATH,-1,NULL,0,NULL,NULL );
    WideCharToMultiByte( CP_ACP,0,LogfilePATH,-1,InifilePATH,i,NULL,NULL);
#else
	memcpy(InifilePATH,LogfilePATH,_MAX_PATH);
#endif
//////////////////////////////////////////////////////////
	m_nAxisParamSel = 0;
	m_nAxisParamLastSel = -1;
	//��ȡ������
//	SYS_ReadSysCfgFile();
	SYS_ReadSysCfgFile_ini(InifilePATH);
	//���½������ݡ�
	m_dbPulseFactor = g_tSysParam.tAxisParam[m_nAxisParamSel].nPulseFactorDown/g_tSysParam.tAxisParam[m_nAxisParamSel].nPulseFactorUp;
	m_fMaxPos = g_tSysParam.tAxisParam[m_nAxisParamSel].fMaxPos;
	m_dbHomeSpeed = g_tSysParam.tAxisParam[m_nAxisParamSel].fHomeSpeed;
	m_dbHomeOffset = g_tSysParam.tAxisParam[m_nAxisParamSel].fHomePosOffset;

	//���㷽��
	((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->AddString(_T("N"));
	((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->AddString(_T("P"));

	for(i=0;i<MAX_AXIS_NUM;i++)
	{
		m_tAxisParam[i] = g_tSysParam.tAxisParam[i];
	}
		//���㷽��
	if(m_tAxisParam[m_nAxisParamSel].nHomeDir == 1)
	((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->SetCurSel(1);
	else
	((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->SetCurSel(0);

	
	
	//�����϶����
	m_dbBackLashLen =g_tSysParam.tAxisParam[m_nAxisParamSel].fBackLashLen;
	
	//�����϶ʹ�ܡ�
	if(m_tAxisParam[m_nAxisParamSel].nEnableBackLash)
		((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->SetCheck(TRUE);	
	else
		((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->SetCheck(FALSE);
	m_dbSysAccSpeed = g_tSysParam.MachineParam.fAccelSpeed;
	//�������ݸ�����Ϣ��
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CSysParamPad::UpdateDataFrame(int FrameID)
{
	UpdateData(TRUE);
	//���ؼ���Ϣˢ�µ������б��档
	if(m_nAxisParamLastSel>=0)
	{
	//	m_tAxisParam[m_nAxisParamLastSel].dbPulseFactorUp =1000;
	//	m_tAxisParam[m_nAxisParamLastSel].dbPulseFactorDown =100;
		m_tAxisParam[m_nAxisParamLastSel].fMaxPos = m_fMaxPos;
		m_tAxisParam[m_nAxisParamLastSel].fHomeSpeed = m_dbHomeSpeed;
		m_tAxisParam[m_nAxisParamLastSel].fHomePosOffset = m_dbHomeOffset;
		m_tAxisParam[m_nAxisParamLastSel].nHomeDir = ((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->GetCurSel();
		if(m_tAxisParam[m_nAxisParamLastSel].nHomeDir ==0)
			m_tAxisParam[m_nAxisParamLastSel].nHomeDir = -1;
		m_tAxisParam[m_nAxisParamLastSel].fBackLashLen = m_dbBackLashLen;
		m_tAxisParam[m_nAxisParamLastSel].nEnableBackLash = 0;
		
		if(((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->GetCheck())
		{
			m_tAxisParam[m_nAxisParamLastSel].nEnableBackLash = 1;
		}
	}
	m_nAxisParamSel = FrameID;
	m_nAxisParamLastSel = m_nAxisParamSel;
//���������ļ���ʾ����
	m_dbPulseFactor = (double)m_tAxisParam[m_nAxisParamSel].nPulseFactorDown/m_tAxisParam[m_nAxisParamSel].nPulseFactorUp;
	m_fMaxPos = m_tAxisParam[m_nAxisParamSel].fMaxPos;
	m_dbHomeSpeed = m_tAxisParam[m_nAxisParamSel].fHomeSpeed;
	m_dbHomeOffset = m_tAxisParam[m_nAxisParamSel].fHomePosOffset;
	//���㷽��
	if(m_tAxisParam[m_nAxisParamSel].nHomeDir == 1)
		((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->SetCurSel(1);
	else
		((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->SetCurSel(0);

	m_dbBackLashLen =m_tAxisParam[m_nAxisParamSel].fBackLashLen;

	//�����϶ʹ�ܡ�
	if(m_tAxisParam[m_nAxisParamSel].nEnableBackLash)
	((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->SetCheck(TRUE);	
	else
		((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->SetCheck(FALSE);
	m_dbSysAccSpeed = g_tSysParam.MachineParam.fAccelSpeed;
	
	UpdateData(FALSE);
}

void CSysParamPad::OnBnClickedRadioSysSelX()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateDataFrame(0);
}


void CSysParamPad::OnBnClickedRadioSysSelY()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateDataFrame(1);
}


void CSysParamPad::OnBnClickedRadioSysSelZ()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateDataFrame(2);
}


void CSysParamPad::OnBnClickedBtnSysDownloadParam()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		int i;
	int nRtn;
	UpdateData(TRUE);
	if(m_nAxisParamLastSel == -1)//û���л������档���޸�X��Ĳ�������ֹ�޸ĺ�û�и��µ��ļ���
	{
		i = m_nAxisParamSel;
	}
	else
		i = m_nAxisParamLastSel;
	//if(m_nAxisParamLastSel>=0)//�������ݡ�
	{
		m_tAxisParam[i].fMaxPos = m_fMaxPos;
		m_tAxisParam[i].fHomeSpeed = m_dbHomeSpeed;
		m_tAxisParam[i].fHomePosOffset = m_dbHomeOffset;
		m_tAxisParam[i].nHomeDir = ((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->GetCurSel();
		if(m_tAxisParam[i].nHomeDir ==0)
			m_tAxisParam[i].nHomeDir = -1;
		m_tAxisParam[i].fBackLashLen = m_dbBackLashLen;
		m_tAxisParam[i].nEnableBackLash = 0;
		
		if(((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->GetCheck())
		{
			m_tAxisParam[i].nEnableBackLash = 1;
		}
	}

	//���浽ϵͳ���������С�
	for( i=0;i<3;i++)
	{
		g_tSysParam.tAxisParam[i]=m_tAxisParam[i];
	}
	g_tSysParam.MachineParam.fAccelSpeed = m_dbSysAccSpeed;

	//���浽Ӳ��
	SYS_WriteSysCfgFile_ini(InifilePATH);

	//���ص���������
	if(1==g_cDll.COM_API_DowloadSystemCfg(InifilePATH))
	{
		CString str;
		str.LoadString(IDS_DOWNLOAD_SUCC);
		MessageBox(str);
	}

}


void CSysParamPad::OnBnClickedBtnSysUpdataParam()
{
#define ONCE_SEND_DATA 500
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i;
	if(g_cDll.COM_API_OpenLink(3,115200) != 1)
	{//û�����ϡ�
		CString str;
		str.LoadString(IDS_COMM_FAILT);
		MessageBox(str);
		return;
	}
	PBYTE buf = (PBYTE)&g_tSysParam;
	int size = sizeof(g_tSysParam);

	for(i=0;i<size;)
	{

		if((i+ONCE_SEND_DATA)<= size)
		{
			g_cDll.COM_API_ReadFileData(1,i,ONCE_SEND_DATA,&buf[i]);
			i += ONCE_SEND_DATA;
		}
		else
		{
			int len =size -i;
			g_cDll.COM_API_ReadFileData(1,i,len,&buf[i]);
			i += len;
			break;
		}
	}

	//��������
	//m_tAxisParam[m_nAxisParamSel] = g_tSysParam.tAxisParam[m_nAxisParamSel];
	for(i=0;i<MAX_AXIS_NUM;i++)
	{
		m_tAxisParam[i] = g_tSysParam.tAxisParam[i];
	}

	//���������ļ���ʾ����
//���������ļ���ʾ����
	m_dbPulseFactor = (double)m_tAxisParam[m_nAxisParamSel].nPulseFactorDown/m_tAxisParam[m_nAxisParamSel].nPulseFactorUp;
	m_fMaxPos = m_tAxisParam[m_nAxisParamSel].fMaxPos;
	m_dbHomeSpeed = m_tAxisParam[m_nAxisParamSel].fHomeSpeed;
	m_dbHomeOffset = m_tAxisParam[m_nAxisParamSel].fHomePosOffset;
			//���㷽��
	if(m_tAxisParam[m_nAxisParamSel].nHomeDir == 1)
		((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->SetCurSel(1);
	else
		((CComboBox*)GetDlgItem(IDC_COMBO_HOME_DIR))->SetCurSel(0);

	m_dbBackLashLen =m_tAxisParam[m_nAxisParamSel].fBackLashLen;

	//�����϶ʹ�ܡ�
	if(m_tAxisParam[m_nAxisParamSel].nEnableBackLash)
	((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->SetCheck(TRUE);	
	else
		((CButton*)GetDlgItem(IDC_CHECK_BACKLASH_EN))->SetCheck(FALSE);
	m_dbSysAccSpeed = g_tSysParam.MachineParam.fAccelSpeed;
	UpdateData(FALSE);
}


void CSysParamPad::OnBnClickedBtnSysPulseFactor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_fPulseDown = m_tAxisParam[m_nAxisParamSel].nPulseFactorDown;
	m_fPulseUp = m_tAxisParam[m_nAxisParamSel].nPulseFactorUp;
	CCalPulseFactor dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_tAxisParam[m_nAxisParamSel].nPulseFactorDown = m_fPulseDown;
	  m_tAxisParam[m_nAxisParamSel].nPulseFactorUp = m_fPulseUp;
	}
	m_dbPulseFactor = (double)m_fPulseDown/m_fPulseUp;
	UpdateData(FALSE);
}
