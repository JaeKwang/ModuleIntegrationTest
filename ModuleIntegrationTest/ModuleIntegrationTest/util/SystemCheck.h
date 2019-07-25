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

	int CSystemCheck::CheckPID(CString strProcessName);		// ���μ��� �̸����� ���μ��� ID ���(������ �����ϴ� ��찡 �����Ƿ� �������� ���μ����� ������ �Ѱ���)
	vector<DWORD> m_vtlPID;

	DWORD CSystemCheck::GetPIDFromWnd(HWND hwnd);				// ������ �ڵ�� ���μ��� ���̵� ���
	HWND CSystemCheck::GetWinHandle(DWORD pid);				// ���μ��� ���̵�� ������ �ڵ� ���

	bool CSystemCheck::ProcessKill(CString strProcessName);	// ���μ��� �̸����� ���μ��� ������ ���̱�(���μ��� �̸��� ���� ���μ����� ��� ����)
	bool CSystemCheck::ProcessKill(DWORD pid);					// ���μ��� ���̵�� ���μ��� ������ ���̱�

////////////////////////////////////////////////////////////////////////////////////////////////////

	HRESULT CSystemCheck::GetCpuTemperature(LPLONG pTemperature);
};
