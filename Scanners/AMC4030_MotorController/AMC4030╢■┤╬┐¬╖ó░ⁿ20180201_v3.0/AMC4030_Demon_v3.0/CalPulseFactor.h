#pragma once


// CCalPulseFactor �Ի���

class CCalPulseFactor : public CDialogEx
{
	DECLARE_DYNAMIC(CCalPulseFactor)

public:
	CCalPulseFactor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCalPulseFactor();

// �Ի�������
	enum { IDD = IDD_SET_PULSE_FACTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fDown;
	float m_fUp;
	virtual BOOL OnInitDialog();
};
