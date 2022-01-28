#pragma once


// CCalPulseFactor 对话框

class CCalPulseFactor : public CDialogEx
{
	DECLARE_DYNAMIC(CCalPulseFactor)

public:
	CCalPulseFactor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCalPulseFactor();

// 对话框数据
	enum { IDD = IDD_SET_PULSE_FACTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fDown;
	float m_fUp;
	virtual BOOL OnInitDialog();
};
