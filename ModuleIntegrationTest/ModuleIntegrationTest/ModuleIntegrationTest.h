
// ModuleIntegrationTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CModuleIntegrationTestApp:
// �� Ŭ������ ������ ���ؼ��� ModuleIntegrationTest.cpp�� �����Ͻʽÿ�.
//

class CModuleIntegrationTestApp : public CWinApp
{
public:
	CModuleIntegrationTestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CModuleIntegrationTestApp theApp;