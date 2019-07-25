#include "stdafx.h"
#include "eventmanager\EventManager.h"
#include <direct.h>
#include <string>

#define LOGLEVEL 4

using namespace eventManager;

CEventManager::CEventManager()
	: m_isThreadLoop(false)
{
	_mkdir("./logfiles");
}

CEventManager::~CEventManager()
{
	clearError();
}

int CEventManager::PushTask(eMessageType m, std::string t, eEventCode e, bool bFileSave, bool bSendACS)
{
	CEventNode *task = new CEventNode(m, t, e, bFileSave, bSendACS);

	m_cs.Lock();
	m_tasks.push(task);
	// thread start
	if (!m_thread.joinable())
	{
		m_isThreadLoop = true;
		m_thread = std::thread(CEventManager::ThreadFunction, this);
	}
	m_cs.Unlock();
	m_sema.Signal();
	if (task == NULL) return 0;
	return task->m_eventCode;
}


CEventNode* CEventManager::PopTask()
{
	m_sema.Wait();
	m_cs.Lock();
	CEventNode *task = m_tasks.front();
	m_tasks.pop();
	m_cs.Unlock();
	return task;
}
// wait all task finish
// no optimize
void CEventManager::Wait()
{
	while (!m_tasks.empty())
		Sleep(10);
}
// thread terminate
void CEventManager::Terminate()
{
	if (m_thread.joinable())
	{
		//PushTask(NULL); // finish thread

		m_isThreadLoop = false;
		if (m_thread.joinable())
			m_thread.join();
	}
}
void CEventManager::clearError()
{
	m_ErrorList = "";
	// wait all task finish
	if (m_thread.joinable())
	{
		//PushTask(NULL); // finish thread
		if (m_thread.joinable())
			m_thread.join();
	}

	m_sema.Clear();

	AutoCSLock cs(m_cs);
	while (!m_tasks.empty())
	{
		delete m_tasks.front();
		m_tasks.pop();
	}
}
int CEventManager::ThreadFunction(CEventManager *mng)
{
	while (mng->m_isThreadLoop)
	{
		CEventNode *task = mng->PopTask();
		if (!task) // end thread command
			break;
		if (task->m_bFileSave)
			WriteLog(task->m_MsgType, "%s: %s", task->m_eventTarget.c_str(), task->m_mEventCode[task->m_eventCode].c_str());
		delete task;
	}
	return 1;
}
char* CEventManager::CStringToChar(CString& _strSource, char* _szResult, int _nSizeResult)
{
	if (WideCharToMultiByte(CP_ACP, 0, _strSource, -1, _szResult, _nSizeResult, NULL, NULL) == 0)
		return NULL;
	else
		return _szResult;
}
void  CEventManager::WriteLog(int nLevel, char* pFormat, ...)
{
	if (nLevel > LOGLEVEL)
		return;
	try
	{
		char chMsg[1000] = { 0, };
		va_list ap;

		va_start(ap, pFormat);
		vsprintf(chMsg, pFormat, ap);
		va_end(ap);

		SYSTEMTIME oT;
		::GetLocalTime(&oT);
		char pLogFile[200];
		if (nLevel == 4)
			sprintf(pLogFile, "./logfiles/%04d%02d%02d_Report.log", oT.wYear, oT.wMonth, oT.wDay);
		else
			sprintf(pLogFile, "./logfiles/%04d%02d%02d.log", oT.wYear, oT.wMonth, oT.wDay);
		FILE* pLog = fopen(pLogFile, "a");
		if (pLog)
		{
			switch (nLevel)
			{
			case 1:
				fprintf(pLog, "%04d-%02hu-%02hu %02hu:%02hu:%02hu.%03hu\t[ERROR] %s\n"
					, oT.wYear, oT.wMonth, oT.wDay, oT.wHour, oT.wMinute, oT.wSecond, oT.wMilliseconds, chMsg);
				break;
			case 2:
				fprintf(pLog, "%04d-%02hu-%02hu %02hu:%02hu:%02hu.%03hu\t[WARN] %s\n"
					, oT.wYear, oT.wMonth, oT.wDay, oT.wHour, oT.wMinute, oT.wSecond, oT.wMilliseconds, chMsg);
				break;
			case 3:
				fprintf(pLog, "%04d-%02hu-%02hu %02hu:%02hu:%02hu.%03hu\t[INFO] %s\n"
					, oT.wYear, oT.wMonth, oT.wDay, oT.wHour, oT.wMinute, oT.wSecond, oT.wMilliseconds, chMsg);
				break;
			case 4:
				fprintf(pLog, "%04d-%02hu-%02hu %02hu:%02hu:%02hu.%03hu\t[REPORT] %s\n"
					, oT.wYear, oT.wMonth, oT.wDay, oT.wHour, oT.wMinute, oT.wSecond, oT.wMilliseconds, chMsg);
				break;
			default:
				break;
			}
			fclose(pLog);
		}

		if ((nLevel & 4) == 4)
		{
		}
	}
	catch (...)
	{
		;
	}
}