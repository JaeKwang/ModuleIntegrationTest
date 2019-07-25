// SystemCheck.h: interface for the CSystemCheck class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>

using namespace std;

class CSystemCheck  
{
public:
	CSystemCheck();
	virtual ~CSystemCheck();

////////////////////////////////////////////////////////////////////////////////////////////////////

	int CSystemCheck::CheckPID(CString strProcessName);		// 프로세스 이름으로 프로세스 ID 얻기(여러개 존재하는 경우가 있으므로 실행중인 프로세스의 갯수를 넘겨줌)
	vector<DWORD> m_vtlPID;

	DWORD CSystemCheck::GetPIDFromWnd(HWND hwnd);				// 윈도우 핸들로 프로세스 아이디 얻기
	HWND CSystemCheck::GetWinHandle(DWORD pid);				// 프로세스 아이디로 윈도우 핸들 얻기

	bool CSystemCheck::ProcessKill(CString strProcessName);	// 프로세스 이름으로 프로세스 강제로 죽이기(프로세스 이름이 같은 프로세스를 모두 죽임)
	bool CSystemCheck::ProcessKill(DWORD pid);					// 프로세스 아이디로 프로세스 강제로 죽이기

////////////////////////////////////////////////////////////////////////////////////////////////////

	HRESULT CSystemCheck::GetCpuTemperature(LPLONG pTemperature);
};
