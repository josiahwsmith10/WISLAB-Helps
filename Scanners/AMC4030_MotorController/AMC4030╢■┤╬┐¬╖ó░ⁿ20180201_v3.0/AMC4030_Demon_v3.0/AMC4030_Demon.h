
// AMC4030_Demon.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAMC4030_DemonApp:
// �йش����ʵ�֣������ AMC4030_Demon.cpp
//

class CAMC4030_DemonApp : public CWinApp
{
public:
	CAMC4030_DemonApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAMC4030_DemonApp theApp;