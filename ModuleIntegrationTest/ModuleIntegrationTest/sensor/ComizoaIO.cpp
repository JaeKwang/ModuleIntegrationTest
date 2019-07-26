#include "stdafx.h"
#include "ComizoaIO.h"
#include "util\SystemCheck.h"
#include "driver\ceSDK.h"

using namespace sensor;
using namespace std;
using namespace IO_List;

CComizoaIO::CComizoaIO(string name, long lNodeID, DIOModule* DIOModules, int nDIONum)
	:CSensorModule(name) {
	m_lNodeID = lNodeID;
	m_DIOModule = DIOModules;
	m_nDIONum = nDIONum;
	m_ReadData = new long[m_nDIONum];
	m_WriteData = new long[m_nDIONum];
	for (int i = 0; i < m_nDIONum; i++)
	{
		m_ReadData[i] = 0;
		m_WriteData[i] = 0;
	}
	setThreadPeriod(50);
	if (initialization() == RETURN_NON_ERROR)
		OccurError();

	m_bInitialized = false;
	if (initialization() == RETURN_NON_ERROR)
		m_bInitialized = true;
}
int CComizoaIO::initialization() {
	// Comizoa Daemon ���α׷��� �����ִ��� Ȯ��
	CSystemCheck clSystemCheck;
	int nCount_PID = clSystemCheck.CheckPID(_T("ceSDKDaemon.exe"));

	if (nCount_PID < 1)
	{
		HINSTANCE ret = ::ShellExecute(NULL, _T("open"), _T("ceSDKDaemon.exe"), NULL, _T("C:\\Program Files\\COMIZOA\\AUTOMATION3\\COMMON\\Apps\\cEIP\\x86\\ceNM-IP Based\\Daemon"), SW_SHOW);
		_RPTN(_CRT_WARN, "ret: %d\n", ret);
		Sleep(1000);
	}
	nCount_PID = clSystemCheck.CheckPID(_T("ceSDKDaemon.exe"));
	if (nCount_PID < 1)
	{
		// ���α׷��� ���� �����Ҽ� ���� ��Ȳ�̹Ƿ� ����
		g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_DAEMON_IS_NOT_RUNNING, true, true);
		return RETURN_FAILED;
	}

	if (ceLoadDll() != CE_TRUE)
	{
		//DLL�� �ε� ����
		g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_LOADING_LIBRARY_FAILED, true, true);
		return RETURN_FAILED;
	}
	return RETURN_NON_ERROR;
}
CComizoaIO::~CComizoaIO() 
{
	DisconnectAct();
	if (m_bInitialized)
		ceUnloadDll();
}
int CComizoaIO::ConnectAct() 
{
	if (!m_bInitialized) {
		if (initialization() == RETURN_NON_ERROR)
			m_bInitialized = true;
		else
			return RETURN_FAILED;
	}

	// ����̽� �ε�
	if (ceGnLoad() != ceERR_NONE)
	{
		//����̽��� �ε� ����
		g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_LOADING_DEVICE_FAILED, true, true);
		return RETURN_FAILED;
	}

	//NM-IP ����� ������ Ȯ���Ѵ�.
	long nIsSearchedDev = 0, nNodeCnt = 0;
	ceGnIsSearchedDevice(&nIsSearchedDev);

	if (nIsSearchedDev == CE_FALSE) {
		//���ڴ� ����� ����� ����, Ÿ�Ӿƿ�, ������, ã�Ƴ� ��� ���� �Դϴ�.
		if (ceGnSearchDevice(10, 100, FALSE, &nNodeCnt) != ceERR_NONE) {
			g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_SEARCH_DEVICE_FAILED, true, true);
			return RETURN_FAILED;
		}
	}
	else
		ceGnSearchDevice(10, 100, FALSE, &nNodeCnt);

	if (nNodeCnt == CE_FALSE && nIsSearchedDev == CE_FALSE) {
		g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_SEARCH_DEVICE_FAILED, true, true);
		return RETURN_FAILED;
	}

	// NODE_ID�� �ȸ����� ���⼭ ���α׷��� ���� (Comizoa SDK���� ����ó���� �ȵǾ�����)
	long nMotModuleCnt, nDioModuleCnt, nAiModuleCnt, nAoModuleCnt, nCountModuleCnt;
	 // �ش� ���� ��忡 ���� Ž���� ��� ���� �� ������ ��ȯ�մϴ�.
	ceGnModuleCount_Motion(m_lNodeID, &nMotModuleCnt);
	// �ش� ���� ��忡 ���� Ž���� DIO ��� ������ ��ȯ�մϴ�.
	ceGnModuleCount_Dio(m_lNodeID, &nDioModuleCnt);
	// �ش� ���� ��忡 ���� Ž���� AI ��� ������ ��ȯ�մϴ�.
	ceGnModuleCount_Ai(m_lNodeID, &nAiModuleCnt);
	// �ش� ���� ��忡 ���� Ž���� AO ��� ������ ��ȯ�մϴ�.
	ceGnModuleCount_Ao(m_lNodeID, &nAoModuleCnt);
	// �ش� ���� ��忡 ���� Ž���� MDIO ä���� ���� ��� ��� ������ ��ȯ�մϴ�.
	ceGnModuleCount_Mdio(m_lNodeID, &nMotModuleCnt);
	// �ش� ���� ��忡 ���� Ž���� ī���� ��� ������ ��ȯ�մϴ�.
	ceGnModuleCount_Cnt(m_lNodeID, &nCountModuleCnt);

	// Slave Card ���� üũ
	if (nDioModuleCnt != m_nDIONum) {
		g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_NOT_MATCHED_DIO_PIN_NUMBER, true, true);
		return RETURN_FAILED;
	}

	long nTotalAxes, nTotalDioCh, nTotalAiCh, nTotalAoCh, nTotalMdioCh, nTotalCntCh;
	// Ž���� ��ü ��� ���� �� ���� ��ȯ�մϴ�.
	ceGnTotalMotionChannel(&nTotalAxes);
	// Ž���� ��ü DIO ä�� ������ ��ȯ�մϴ�.
	ceGnTotalDIOChannel(&nTotalDioCh);
	// Ž���� ��ü AI ä�� ������ ��ȯ�մϴ�.
	ceGnTotalAIChannel(&nTotalAiCh);
	// Ž���� ��ü AO ä�� ������ ��ȯ�մϴ�.
	ceGnTotalAOChannel(&nTotalAoCh);
	// Ž���� ��ü MDIO ä�� ������ ��ȯ�մϴ�.
	ceGnTotalMDIOChannel(&nTotalMdioCh);
	// Ž���� ��ü ī���� ä�� ������ ��ȯ�մϴ�.
	ceGnTotalCNTChannel(&nTotalCntCh);

	// IO Pin ���� üũ
	int nDIOPinSum = 0;
	for (int i = 0; i < m_nDIONum; i++)
	{
		nDIOPinSum += m_DIOModule[i].nDINumber;
		nDIOPinSum += m_DIOModule[i].nDONumber;
	}
	if (nTotalDioCh != nDIOPinSum)
	{
		g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_NOT_MATCHED_DIO_PIN_NUMBER, true, true);
		return RETURN_FAILED;
	}

	// IO ī�� ����
	ceGnResetNode(m_lNodeID, CE_RESET_ALL);
	
	// Input Output pin ����
	long lState;
	cedioMulti_Get(0, 8, &lState);
	cedioMulti_Get(8, 8, &lState);
	for (int i = 0; i < m_nDIONum; i++)
	{
		if (cedioModeMulti_Set(m_DIOModule[i].nDIStart, m_DIOModule[i].nDINumber, 0x0) == ceERR_NONE)
		{
			cedioModeMulti_Get(m_DIOModule[i].nDIStart, m_DIOModule[i].nDINumber, &lState);
			if (lState != 0x0)
			{
				g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_IO_PIN_SETTING_FAILED, true, true);
				return RETURN_FAILED;
			}
		}
		long data = (0x1 << m_DIOModule[i].nDONumber) -1;
		if (m_DIOModule[i].nDONumber == 32) data = 0xFFFFFFFF;
		if (cedioModeMulti_Set(m_DIOModule[i].nDOStart, m_DIOModule[i].nDONumber, data) == ceERR_NONE)
		{
			cedioModeMulti_Get(m_DIOModule[i].nDOStart, m_DIOModule[i].nDONumber, &lState);
			if (lState != data)
			{
				g_eventManager->PushTask(eventManager::MSG_ERROR, getSensorName(), eventManager::ERROR_IO_PIN_SETTING_FAILED, true, true);
				return RETURN_FAILED;
			}
		}
	}
	return RETURN_NON_ERROR;
}
int CComizoaIO::DisconnectAct() 
{
	if (!m_bInitialized)
		return RETURN_FAILED;
	ceGnResetNode(m_lNodeID, CE_RESET_ALL);
	ceGnUnload();
	return RETURN_NON_ERROR;
}
int CComizoaIO::ResetAct() 
{
	if (!m_bInitialized)
		return RETURN_FAILED;
	long nSwEmgStatus;
	if (ceGnEmergency_Get(m_lNodeID, &nSwEmgStatus) == ceERR_NONE)
	{
		switch (nSwEmgStatus)
		{
		case CE_FALSE: // ����Ʈ���� Emergency ��Ȱ�� ����
			ceGnEmergency_Set(m_lNodeID, CE_TRUE);
			break;
		case CE_TRUE: // ����Ʈ���� Emergency Ȱ�� ����
			ceGnEmergency_Set(m_lNodeID, CE_FALSE);
			break;
		}
	}
	ceGnResetNode(1, CE_RESET_ALL);
	return ConnectAct();
}
int CComizoaIO::UpdateData() 
{
	long nIsActive; 
	ceGnNodeIsActive(m_lNodeID, &nIsActive);
	// ��� ���� ���� üũ
	if (nIsActive == CE_FALSE)
		return RETURN_FAILED;
	
	long a = 0;
	cedioMulti_Get(0, 16, &a);
	int index = 0;
	for (int i = 0; i < m_nDIONum; i++) {
		if (cedioMulti_Get(index, m_DIOModule[i].nPinNum, &m_ReadData[i]) != ceERR_NONE)
			return RETURN_FAILED;
		if (cedioMulti_Put(index, m_DIOModule[i].nPinNum, m_WriteData[i]) != ceERR_NONE)
			return RETURN_FAILED;
		index += m_DIOModule[i].nPinNum;
	}	
	return RETURN_NON_ERROR;
}

int CComizoaIO::bitSet(int moduleNum, int pin, bool value) {
	if (moduleNum < 0)
		return RETURN_FAILED;
	int errorCode;
	if (value != bitRead(moduleNum, pin, &errorCode)) {
		if(value)
			m_WriteData[moduleNum] = m_WriteData[moduleNum] + (0x01 << pin);
		else
			m_WriteData[moduleNum] = m_WriteData[moduleNum] - (0x01 << pin);
	}
	return RETURN_NON_ERROR;
}
bool CComizoaIO::bitRead(int moduleNum, int pin, int* errorCode) {
	if (moduleNum < 0) {
		*errorCode = RETURN_FAILED;
		return false;
	}
	*errorCode = RETURN_NON_ERROR;
	return (m_ReadData[moduleNum] >> pin) & 0x01;
}

long CComizoaIO::getNodeID() {
	return m_lNodeID;
}
int CComizoaIO::setNodeID(long id) {
	if (id < 0 || id > 255) {
		g_eventManager->PushTask(eventManager::MSG_WARN, getSensorName(), eventManager::WARN_INVALID_COMIZOA_ID, true, false);
		return RETURN_FAILED;
	}
	m_lNodeID = id;
	return RETURN_NON_ERROR;
}
