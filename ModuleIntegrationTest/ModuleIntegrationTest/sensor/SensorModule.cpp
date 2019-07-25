#include "stdafx.h"

#include <time.h>
#include "SensorModule.h"

using namespace sensor;
using namespace eventManager;
using namespace std;

CSensorModule::CSensorModule(string name) :m_strSensorName(name) {
	g_eventManager->PushTask(MSG_INFO, getSensorName(), INFO_MODULE_CREATE_SUCCEED, true, false);
	m_bStateMachineThreadLoop = false;
	m_eState = STATE_INIT;
	m_nThreadPeriod = 100;
	m_nDataCheckCount = 3;
}
CSensorModule::~CSensorModule() {
	m_bStateMachineThreadLoop = false;
	// Thread Terminate
	if (m_StateMachineThread.joinable())
	{
		if (m_StateMachineThread.joinable())
			m_StateMachineThread.join();
	}
	// Memory clear
	AutoCSLock cs(m_cs);
	while (!m_cmds.empty())
	{
		delete &(m_cmds.front());
		m_cmds.pop();
	}
	g_eventManager->PushTask(MSG_INFO, getSensorName(), INFO_MODULE_DELETE_SUCCEED, true, false);
}
// State Machine Functions
int CSensorModule::ThreadFunction_StateMachine(CSensorModule *sensor) {
	int nReconnectionCount = 0;
	int nDataCheckCount = 0;
	while (sensor->m_bStateMachineThreadLoop) {
		// Clock Start
		clock_t start, runtime;
		start = clock();

		// State Machine
		if (!sensor->m_cmds.empty()) {
			eSensorCommand cmd = sensor->PopCommand();
			switch (sensor->m_eState) {
			case STATE_INIT:
				if (cmd == CMD_CONNECT) {
					sensor->m_eState = STATE_PROGRESSING;
					// ConnectAct�� �����ϸ� Run, �ƴϸ� Error
					if (sensor->ConnectAct() == RETURN_NON_ERROR) {
						g_eventManager->PushTask(MSG_INFO, sensor->getSensorName(), INFO_CONNECT_SUCCEED, true, false);
						sensor->m_eState = STATE_RUN;
					}
					else {
						g_eventManager->PushTask(MSG_ERROR, sensor->getSensorName(), ERROR_CONNECT_FAILED, true, true);
						sensor->m_eState = STATE_ERROR;
					}
					start = clock();
				}
				break;
			case STATE_PROGRESSING:
				if (cmd == CMD_ERROR)
					sensor->m_eState = STATE_ERROR;
				break;
			case STATE_RUN:
				// ���� Thread ����
				if (cmd == CMD_DISCONNECT) {
					sensor->m_eState = STATE_PROGRESSING;
					if (sensor->DisconnectAct() == RETURN_NON_ERROR) {
						g_eventManager->PushTask(MSG_INFO, sensor->getSensorName(), INFO_DISCONNECT_SUCCEED, true, false);
						sensor->m_eState = STATE_INIT;
					}
					else {
						g_eventManager->PushTask(MSG_ERROR, sensor->getSensorName(), ERROR_DISCONNECT_FAILED, true, true);
						sensor->m_eState = STATE_ERROR;
					}
					start = clock();
				}
				else if (cmd == CMD_ERROR)
					sensor->m_eState = STATE_ERROR;
				break;
			case STATE_ERROR:
				if (cmd == CMD_RESET) {
					sensor->m_eState = STATE_PROGRESSING;
					// Reset�� �����ϸ� , �ƴϸ� Error
					if (sensor->ResetAct() == RETURN_NON_ERROR) {
						g_eventManager->clearError(sensor->getSensorName());
						g_eventManager->PushTask(MSG_INFO, sensor->getSensorName(), INFO_RESET_SUCCEED, true, false);
						sensor->m_eState = STATE_RUN;
					}
					else {
						g_eventManager->PushTask(MSG_ERROR, sensor->getSensorName(), ERROR_RESET_FAILED, true, true);
						sensor->m_eState = STATE_INIT;
					}
					start = clock();
				}
				break;
			}
		}

		// Run ������ ���� ������ ������Ʈ
		if (sensor->getStatus() == STATE_RUN) {
			int errorCode = sensor->UpdateData();

			// Get data ������
			if (errorCode == RETURN_NON_ERROR)
				nDataCheckCount = 0;
			// �����Ͱ� �з����ͼ� ��� �������ݰ� ���� �ʴ� ���
			else if (errorCode == RETURN_DATA_CHECK_FAILED)
			{
				// ���� Ŭ����???
				nDataCheckCount++;
				if (nDataCheckCount >= sensor->m_nDataCheckCount) {
					nDataCheckCount = 0;
					g_eventManager->PushTask(MSG_ERROR, sensor->getSensorName(), ERROR_DATA_CHECK_COUNT_REACHED, true, true);
					sensor->OccurError();
				}
			}
			// �����͸� Thread �ֱ� �ȿ� ���� ������ ���
			else
			{
				g_eventManager->PushTask(MSG_ERROR, sensor->getSensorName(), ERROR_EXCEED_THREAD_CYCLE, true, true);
				sensor->OccurError();
			}
		}

		// Keep the Thread Period
		runtime = clock() - start;
		if (sensor->m_nThreadPeriod - runtime > 0)
			Sleep(sensor->m_nThreadPeriod - runtime);
		else {
			g_eventManager->PushTask(MSG_ERROR, sensor->getSensorName(), ERROR_EXCEED_THREAD_CYCLE, true, true);
			sensor->OccurError();
		}
	}
	return RETURN_NON_ERROR;
}
int CSensorModule::PushCommand(eSensorCommand input) {
	if (m_cmds.size() > 5)
		return RETURN_FAILED;
	m_cs.Lock();
	m_cmds.push(input);

	// thread start
	if (!m_StateMachineThread.joinable()) {
		m_bStateMachineThreadLoop = true;
		m_StateMachineThread = std::thread(ThreadFunction_StateMachine, this);
	}
	m_cs.Unlock();
	return RETURN_NON_ERROR;
}
eSensorCommand CSensorModule::PopCommand()
{
	m_cs.Lock();
	eSensorCommand cmd = m_cmds.front();
	m_cmds.pop();
	m_cs.Unlock();
	return cmd;
}
void CSensorModule::Connect() { PushCommand(CMD_CONNECT); }
void CSensorModule::Reset() { PushCommand(CMD_RESET); }
void CSensorModule::Disconnect() { PushCommand(CMD_DISCONNECT); }
void CSensorModule::OccurError() { PushCommand(CMD_ERROR); }

// Getter & Setter
int CSensorModule::getStatus() { return m_eState; }
int CSensorModule::getThreadPeriod() { return m_nThreadPeriod; }
int CSensorModule::getDataCheckCount() { return m_nDataCheckCount; }
std::string CSensorModule::getSensorName() { return m_strSensorName; }
int CSensorModule::setThreadPeriod(int nPeriod) {
	if (getStatus() == STATE_RUN) {
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_RESTRICTED_STATE, true, false);
		return RETURN_FAILED;
	}
	if (nPeriod < 0 || nPeriod > 200) {
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_THREAD_PERIOD, true, false);
		return RETURN_FAILED;
	}
	m_nThreadPeriod = nPeriod;
	return RETURN_NON_ERROR;
}
int CSensorModule::setDataCheckCount(int nCount) {
	if (getStatus() == STATE_RUN) {
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_RESTRICTED_STATE, true, false);
		return RETURN_FAILED;
	}
	if (nCount < 0 || nCount > 10) {
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_DATA_CHECK_COUNT, true, false);
		return RETURN_FAILED;
	}
	m_nDataCheckCount = nCount;
	return RETURN_NON_ERROR;
}
void CSensorModule::setSensorName(std::string s) { m_strSensorName = s; }