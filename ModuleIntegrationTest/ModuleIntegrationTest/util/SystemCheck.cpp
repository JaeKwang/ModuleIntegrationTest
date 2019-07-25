// SystemCheck.cpp: implementation of the CSystemCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemCheck.h"

#include <tlhelp32.h>

//////////////////////////////////////////////////////////////////////

// CPU �µ� üũ
#define _WIN32_DCOM

#include <comdef.h>
#include <wbemidl.h>
 
#pragma comment(lib, "wbemuuid.lib")

//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////
// Construction / Destruction //
////////////////////////////////

CSystemCheck::CSystemCheck()
{
	m_vtlPID.clear();
}

CSystemCheck::~CSystemCheck()
{
	m_vtlPID.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// ���μ��� �̸����� ���μ��� ID ���(������ �����ϴ� ��찡 �����Ƿ� �������� ���μ����� ������ �Ѱ���)
int CSystemCheck::CheckPID(CString strProcessName)
{
	m_vtlPID.clear();

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe32 = {0, };

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if(!Process32First(hProcessSnap, &pe32))
	{
		OutputDebugString(_T("Error checking process"));

		CloseHandle(hProcessSnap);

		return 0;
	}

	do
	{
		if(StrCmpW(pe32.szExeFile, strProcessName) == 0)
		{
			m_vtlPID.push_back(pe32.th32ProcessID);
		}
	} while(Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	if(m_vtlPID.size() == 0)
		return 0;
	else
		return m_vtlPID.size();
}

// ������ �ڵ�� ���μ��� ���̵� ���
DWORD CSystemCheck::GetPIDFromWnd(HWND hwnd)
{
	DWORD pid;
	::GetWindowThreadProcessId(hwnd, &pid);

	return pid;
}

// ���μ��� ���̵�� ������ �ڵ� ���
HWND CSystemCheck::GetWinHandle(DWORD pid)
{
	HWND tempHwnd = ::FindWindow(NULL, NULL);	// �ֻ��� ������ �ڵ� ã��
	while(tempHwnd != NULL)
	{
		if(::GetParent(tempHwnd) == NULL)		// �ֻ��� �ڵ����� üũ, ��ư � �ڵ��� ���� �� �����Ƿ� �����ϱ� ����
		{
			if(pid == GetPIDFromWnd(tempHwnd))
			{
				return tempHwnd;
			}
		}

		tempHwnd = ::GetWindow(tempHwnd, GW_HWNDNEXT); // ���� ������ �ڵ� ã��
	}

	return NULL;
} 

// ���μ��� �̸����� ���μ��� ������ ���̱�(���μ����� ���� ���μ����� ��� ����)
bool CSystemCheck::ProcessKill(CString strProcessName)
{
	bool bResult = false;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe32 = {0, };

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if(!Process32First(hProcessSnap, &pe32))
	{
		OutputDebugString(_T("ProcessKill() Error RTSP_Recorder checking process"));
		CloseHandle(hProcessSnap);

		return bResult;
	}

	do
	{
		if(StrCmpW(pe32.szExeFile, strProcessName) == 0)
		{
			HANDLE hGetProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, pe32.th32ProcessID);

			TerminateProcess(hGetProcess, 0);
			CloseHandle(hGetProcess);

			bResult = true;
		}
	} while(Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	return bResult;
}

// ���μ��� ���̵�� ���μ��� ������ ���̱�
bool CSystemCheck::ProcessKill(DWORD pid)
{
	HANDLE hGetProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, pid);

	TerminateProcess(hGetProcess, 0);
	CloseHandle(hGetProcess);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// CPU �µ� üũ
HRESULT CSystemCheck::GetCpuTemperature(LPLONG pTemperature)
{
	if(pTemperature == NULL)
		return E_INVALIDARG;
 
	*pTemperature = -1;

	HRESULT ci = CoInitialize(NULL);
	HRESULT hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if(SUCCEEDED(hr))
	{
		IWbemLocator *pLocator = NULL;
		hr = CoCreateInstance(CLSID_WbemAdministrativeLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLocator);
		if(SUCCEEDED(hr))
		{
			IWbemServices *pServices = NULL;
			BSTR ns = SysAllocString(L"ROOT\\WMI");
			hr = pLocator->ConnectServer(ns, NULL, NULL, NULL, 0, NULL, NULL, &pServices);
			pLocator->Release();
			SysFreeString(ns);
			if(SUCCEEDED(hr))
			{
				BSTR query = SysAllocString(L"SELECT * FROM MSAcpi_ThermalZoneTemperature");
				BSTR wql = SysAllocString(L"WQL");

				IEnumWbemClassObject *pEnum = NULL;
				hr = pServices->ExecQuery(wql, query, WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY, NULL, &pEnum);
				SysFreeString(wql);
				SysFreeString(query);
				pServices->Release();
				if(SUCCEEDED(hr))
				{
					IWbemClassObject *pObject = NULL;
					ULONG returned = 0;
					hr = pEnum->Next(WBEM_INFINITE, 1, &pObject, &returned);
					pEnum->Release();
					if(SUCCEEDED(hr))
					{
						BSTR temp = SysAllocString(L"CurrentTemperature");
						VARIANT v;
						VariantInit(&v);
						hr = pObject->Get(temp, 0, &v, NULL, NULL);
						pObject->Release();
						SysFreeString(temp);
						if(SUCCEEDED(hr))
						{
							//*pTemperature = V_I4(&v);
							*pTemperature = v.lVal;
						}
						VariantClear(&v);
					}
				}
			}
		}
	}

	if(ci == S_OK)
	{
		CoUninitialize();
	}

	return hr;
}
