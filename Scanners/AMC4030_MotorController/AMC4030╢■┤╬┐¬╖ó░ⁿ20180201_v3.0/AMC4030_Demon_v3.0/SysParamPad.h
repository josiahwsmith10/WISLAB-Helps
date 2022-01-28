#pragma once

#include "SystemParam.h"
#include "afxwin.h"
// CSysParamPad �Ի���
extern SYS_PARAM g_tSysParam;

class CSysParamPad : public CDialogEx
{
	DECLARE_DYNAMIC(CSysParamPad)

public:
	CSysParamPad(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysParamPad();

// �Ի�������
	enum { IDD = IDD_DLG_SYS_PARAM };
private:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void UpdateDataFrame(int FrameID);
	AXIS_PARAM  m_tAxisParam[3];
	char InifilePATH[_MAX_PATH];
//	CButton m_nAxisParamSel;
	int m_nAxisParamSel;
	int m_nAxisParamLastSel;
	double m_dbPulseFactor;
	double m_dbSysAccSpeed;
	double m_dbHomeSpeed;
	double m_dbHomeOffset;
	double m_dbBackLashLen;
	double m_fMaxPos;
	afx_msg void OnBnClickedRadioSysSelX();
	afx_msg void OnBnClickedRadioSysSelY();
	afx_msg void OnBnClickedRadioSysSelZ();
	afx_msg void OnBnClickedBtnSysDownloadParam();
	afx_msg void OnBnClickedBtnSysUpdataParam();
	afx_msg void OnBnClickedBtnSysPulseFactor();
};
