
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// ModuleIntegrationTest.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"


eventManager::CEventManager *g_eventManager = new eventManager::CEventManager();

void Wait(DWORD dwMilliSecond)
{
	DWORD dwStart;
	dwStart = GetTickCount();
	//MSG msg;

	while (GetTickCount() - dwStart < dwMilliSecond)
	{
		Sleep(1);
		//dwtemp = GetTickCount();
		//while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		//{
		//	TranslateMessage(&msg);
		//	DispatchMessage(&msg);
		//}
	}
}