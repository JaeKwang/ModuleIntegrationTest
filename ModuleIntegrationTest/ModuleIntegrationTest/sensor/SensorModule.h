#pragma once
#include <queue>
#include <string>
#include <thread>
#include "util\CriticalSection.h"

namespace sensor {
	enum eSensorCommand {
		CMD_CONNECT,
		CMD_RESET,
		CMD_DISCONNECT,
		CMD_ERROR,
	};
	enum eReturnCode {
		RETURN_NON_ERROR = 0,
		RETURN_DATA_CHECK_FAILED,
		RETURN_FAILED,
	};
	enum eSensorStatus {
		STATE_INIT,
		STATE_PROGRESSING,
		STATE_RUN,
		STATE_ERROR,
	};
	class CSensorModule {
	private:
		// State Machine 관련 멤버
		eSensorStatus m_eState;
		std::thread m_StateMachineThread;
		bool m_bStateMachineThreadLoop;
		std::queue<eSensorCommand> m_cmds;
		CriticalSection m_cs;
		static int ThreadFunction_StateMachine(CSensorModule *); // 비동기 Thread

																 // Thread 관련 멤버
		int m_nThreadPeriod;
		int m_nDataCheckCount;
		int m_nTerminateTimeout;
	protected:
		std::string m_strSensorName;

		virtual int ConnectAct() = 0;
		virtual int ResetAct() = 0;
		virtual int UpdateData() = 0;
		virtual int DisconnectAct() = 0;
		eSensorCommand PopCommand();
		int PushCommand(eSensorCommand);

	public:
		CSensorModule(std::string);
		virtual ~CSensorModule() = 0;
		void OccurError();
		void Connect();
		void Reset();
		void Disconnect();

		// Getter & Setter
		int getStatus();
		int getThreadPeriod();
		int getDataCheckCount();
		std::string getSensorName();
		int setThreadPeriod(int p);
		void setSensorName(std::string s);
		int setDataCheckCount(int);
	};
}