#pragma once

#include "util\CriticalSection.h"
#include "util\semaphore.h"
#include <map>
#include <thread>
#include <queue>
namespace eventManager {
	enum eEventCode {
		//*************** INFO CODE ***************//
		INFO_PROGRAM_START = 1000,
		INFO_PROGRAM_TERMINATED,
		// 센서 모듈 Level
		INFO_MODULE_CREATE_SUCCEED = 1500,
		INFO_MODULE_DELETE_SUCCEED,
		INFO_CONNECT_SUCCEED,
		INFO_RESET_SUCCEED,
		INFO_DISCONNECT_SUCCEED,

		//*************** WARN CODE ***************//
		// 센서 모듈 Level
		WARN_INVALID_THREAD_PERIOD,
		WARN_INVALID_DATA_CHECK_COUNT,
		WARN_INVALID_COMIZOA_ID,
		WARN_RESTRICTED_STATE,


		//*************** ERROR CODE ***************//
		// 센서 모듈 Level
		ERROR_EXCEED_THREAD_CYCLE = 4500,
		ERROR_DATA_CHECK_COUNT_REACHED,
		ERROR_CONNECT_FAILED,
		ERROR_RESET_FAILED,
		ERROR_DISCONNECT_FAILED,
		// IO Hub
		ERROR_INITIALIZATION_FAILED,
		ERROR_FILE_READ_FAILED,
		ERROR_NOT_DEFINED_PIN,
		ERROR_NOT_MATCHED_DIO_PIN_NUMBER,
		ERROR_DAEMON_IS_NOT_RUNNING,
		ERROR_LOADING_LIBRARY_FAILED,
		ERROR_LOADING_DEVICE_FAILED,
		ERROR_SEARCH_DEVICE_FAILED,
		ERROR_IO_PIN_SETTING_FAILED,
	};
	enum eMessageType {
		MSG_ERROR = 1,
		MSG_WARN,
		MSG_INFO,
		MSG_REPORT,
	};
	class CEventNode {
	public:
		CEventNode(eMessageType m, std::string t, eEventCode e, bool bFileSave, bool bSendACS) {
			m_MsgType = m;
			m_eventTarget = t;
			m_eventCode = e;
			m_bFileSave = bFileSave;
			m_bSendACS = bSendACS;

			// Info
			m_mEventCode[INFO_PROGRAM_START] = "===========\tStart\t===========";
			m_mEventCode[INFO_PROGRAM_TERMINATED] = "===========\t End\t===========\n";
			// [센서모듈]
			m_mEventCode[INFO_MODULE_CREATE_SUCCEED] = "Module create succeed";
			m_mEventCode[INFO_MODULE_DELETE_SUCCEED] = "Module delete succeed";
			m_mEventCode[INFO_CONNECT_SUCCEED] = "Connection  succeed";
			m_mEventCode[INFO_RESET_SUCCEED] = "Reset succeed";
			m_mEventCode[INFO_DISCONNECT_SUCCEED] = "Disconnect succeed";

			// warn
			// [센서모듈]
			m_mEventCode[WARN_INVALID_THREAD_PERIOD] = "Detect an inappropriate thread period parameter variation";
			m_mEventCode[WARN_INVALID_DATA_CHECK_COUNT] = "Detect an inappropriate data check count parameter variation";
			m_mEventCode[WARN_RESTRICTED_STATE] = "Limit changes due to state constraints";
			m_mEventCode[WARN_INVALID_COMIZOA_ID] = "Comizoa ID is invalied";

			// Error
			// [센서모듈]
			m_mEventCode[ERROR_INITIALIZATION_FAILED] = "Initialization failed";
			m_mEventCode[ERROR_CONNECT_FAILED] = "Connect failed";
			m_mEventCode[ERROR_RESET_FAILED] = "Reset failed";
			m_mEventCode[ERROR_DISCONNECT_FAILED] = "Disconnect failed";
			m_mEventCode[ERROR_EXCEED_THREAD_CYCLE] = "Runtime exceeds thread period";
			m_mEventCode[ERROR_DATA_CHECK_COUNT_REACHED] = "Over data check count";
			m_mEventCode[ERROR_FILE_READ_FAILED] = "Reading a file is failed";
			m_mEventCode[ERROR_NOT_DEFINED_PIN] = "Detect access not defined pin number";
			m_mEventCode[ERROR_NOT_MATCHED_DIO_PIN_NUMBER] = "Not matched DIO pin number with detected pin number";
			m_mEventCode[ERROR_DAEMON_IS_NOT_RUNNING] = "The ceSDKDaemon.exe is not running";
			m_mEventCode[ERROR_LOADING_LIBRARY_FAILED] = "Loading library is failed";
			m_mEventCode[ERROR_LOADING_DEVICE_FAILED] = "Loading device is failed";
			m_mEventCode[ERROR_SEARCH_DEVICE_FAILED] = "Searching device is failed";
			m_mEventCode[ERROR_IO_PIN_SETTING_FAILED] = "DIO module pin setting failed";

		}
		eMessageType m_MsgType;
		std::string m_eventTarget;
		eEventCode m_eventCode;
		bool m_bFileSave;
		bool m_bSendACS;
		std::map<eEventCode, std::string> m_mEventCode;
	};
	class CEventManager
	{
	private:
		CriticalSection m_cs;
		cSemaphore m_sema;
		std::queue<CEventNode*> m_tasks;
		std::thread m_thread;
		bool m_isThreadLoop;
		std::string m_ErrorList;

		CEventNode* PopTask();
		void Wait();
		void Terminate();
		void clearError();
		static int ThreadFunction(CEventManager *wqSemaphore);
		char* CStringToChar(CString&, char*, int);
		static void  WriteLog(int, char*, ...);

	public:
		CEventManager();
		virtual ~CEventManager();
		void setMainDlg(CDialogEx *a);
		int PushTask(eMessageType, std::string, eEventCode, bool, bool);
		std::string toString() { return m_ErrorList; }
	};
}