// qqpattren.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "global.h"


// CqqpattrenApp:
// �йش����ʵ�֣������ qqpattren.cpp
//

class CqqpattrenApp : public CWinApp
{
public:
	CqqpattrenApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CqqpattrenApp theApp;