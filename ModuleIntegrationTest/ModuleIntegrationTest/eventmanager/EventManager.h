#pragma once

#include "util\CriticalSection.h"
#include "util\semaphore.h"
#include "util\PINIReadWriter.h"
#include <map>
#include <thread>
#include <queue>

namespace eventManager {
	enum eEventCode {
		//*************** INFO CODE ***************//
		INFO_PROGRAM_START = 0,
		INFO_PROGRAM_TERMINATED = 1,
		INFO_MODULE_CREATE_SUCCEED = 1000,
		INFO_MODULE_DELETE_SUCCEED,
		INFO_MODULE_DELETE_FAILED,
		INFO_CONNECT_SUCCEED,
		INFO_RESET_SUCCEED,
		INFO_DISCONNECT_SUCCEED,

		//*************** WARN CODE ***************//
		// 센서 모듈 Level
		WARN_INVALID_THREAD_PERIOD = 2000,
		WARN_INVALID_DATA_CHECK_COUNT,
		WARN_INVALID_COMIZOA_ID,
		WARN_RESTRICTED_STATE,
		WARN_INVALID_CONNECTION_TIMEOUT,
		WARN_INVALID_DATA_TIMEOUT,
		WARN_INVALID_PORTNO,
		WARN_INVALID_BAUDRATE,
		WARN_INVALID_ANGLE_RESOLUTION,
		WARN_INVALID_MOTION_SPEED_SETTING,

		//*************** ERROR CODE ***************//
		// 센서 모듈 Level
		ERROR_EXCEED_THREAD_CYCLE = 4000,
		ERROR_DATA_CHECK_COUNT_REACHED,
		ERROR_CONNECT_FAILED,
		ERROR_RESET_FAILED,
		ERROR_DISCONNECT_FAILED,
		ERROR_INITIALIZATION_FAILED,
		ERROR_FILE_READ_FAILED,
		ERROR_NOT_DEFINED_PIN,
		ERROR_NOT_MATCHED_DIO_PIN_NUMBER,
		ERROR_DAEMON_IS_NOT_RUNNING,
		ERROR_LOADING_LIBRARY_FAILED,
		ERROR_LOADING_DEVICE_FAILED,
		ERROR_SEARCH_DEVICE_FAILED,
		ERROR_IO_PIN_SETTING_FAILED,
		ERROR_MOTION_STOP_FAILED,
		ERROR_MOTION_EMG_STOP_FAILED,
		ERROR_SERVO_ON_FAILED,
		ERROR_SERVO_OFF_FAILED,
		ERROR_SET_POSITION_FAILED,
		ERROR_RESET_POSITION_FAILED,
		ERROR_LIFT_HOMING_FAILED,
		ERROR_LIFT_UPDOWN_FAILED,
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
		}
		CEventNode(eMessageType m, std::string t, eEventCode e) {
			m_MsgType = m;
			m_eventTarget = t;
			m_eventCode = e;
		}
		eMessageType m_MsgType;
		std::string m_eventTarget;
		eEventCode m_eventCode;
		bool m_bFileSave;
		bool m_bSendACS;
	};

	class CEventManager
	{
	private:
		CriticalSection m_cs;
		cSemaphore m_sema;
		std::queue<CEventNode*> m_tasks;
		std::thread m_thread;
		bool m_isThreadLoop;
		std::vector<std::vector<CEventNode>> m_ArrayList;
		PINIReadWriter* m_pINIReaderWriter;
		std::map<eEventCode, std::string> m_EventCodeTable;

		void pushList(CEventNode*);
		int findNode(CEventNode*);
		CEventNode* PopTask();
		void Wait();
		void Terminate();
		static int ThreadFunction(CEventManager *wqSemaphore);
		char* CStringToChar(CString&, char*, int);
		static void  WriteLog(int, char*, ...);

	public:
		CEventManager();
		virtual ~CEventManager();
		int PushTask(eMessageType, std::string, eEventCode, bool, bool);
		std::vector<std::vector<CEventNode>> getErrorArrayList();
		std::map<eEventCode, std::string> getEventCodeTable();
		void clearError();
		void clearError(std::string sensorName);
	};
}