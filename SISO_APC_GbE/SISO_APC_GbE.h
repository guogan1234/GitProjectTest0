
// SISO_APC_GbE.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSISO_APC_GbEApp:
// �йش����ʵ�֣������ SISO_APC_GbE.cpp
//

class CSISO_APC_GbEApp : public CWinApp
{
public:
	CSISO_APC_GbEApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSISO_APC_GbEApp theApp;