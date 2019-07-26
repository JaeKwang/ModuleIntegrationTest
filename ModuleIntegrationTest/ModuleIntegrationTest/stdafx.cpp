
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// ModuleIntegrationTest.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

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