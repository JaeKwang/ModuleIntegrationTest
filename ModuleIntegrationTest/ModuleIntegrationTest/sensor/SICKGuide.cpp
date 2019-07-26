#include "stdafx.h"
#include "SICKGuide.h"

using namespace sensor;
using namespace std;

CSICKGuide::CSICKGuide(string name, int nPort, int nBaudrate_k, int nTimeOut_ms, int nDeviceNum) :CSensorModule(name) {
	m_nPort = nPort;
	m_nBaudrate_k = nBaudrate_k;
	m_nTimeOut_ms = nTimeOut_ms;
	m_nFrameType = 0;
	m_bSynchronousMode = true;

	m_nDeviceNum = nDeviceNum;
	m_lDeviceID = new ULONG[m_nDeviceNum];
	guide_lcp1 = new short[m_nDeviceNum];
	guide_lcp2 = new short[m_nDeviceNum];
	guide_lcp3 = new short[m_nDeviceNum];
	guide_lcp = new unsigned char[m_nDeviceNum];
	guide_status = new unsigned char[m_nDeviceNum];
	guide_line_exists = new int[m_nDeviceNum];
	guide_marker = new int[m_nDeviceNum];
	guide_linelev = new int[m_nDeviceNum];
	guide_line_good = new bool[m_nDeviceNum];
	guide_reading_code = new bool[m_nDeviceNum];

	cReadData_8Byte_One = new unsigned char*[m_nDeviceNum];

	for (int i = 0; i < m_nDeviceNum; i++) {
		cReadData_8Byte_One[i] = new unsigned char[8];
		m_lDeviceID[i] = 394 + i;
	}
}
CSICKGuide::~CSICKGuide() {
	DisconnectAct();
}
int CSICKGuide::ConnectAct() {
	if (m_nPort == -1 || m_nBaudrate_k == -1)
		return RETURN_FAILED;
	if (CanOpen() == INVALID_HANDLE_VALUE)
		return RETURN_FAILED;
	// Device Init
	if (EnterResetMode() < 0 || SetBaud() < 0 || SetTimeOut() < 0 || EnterWorkMode() < 0)
	{
		CanClose();
		m_hDevice = INVALID_HANDLE_VALUE;
		return RETURN_FAILED;
	}
	return RETURN_NON_ERROR;
}


int CSICKGuide::ResetAct() {

	return RETURN_NON_ERROR;
}


int CSICKGuide::UpdateData() 
{
	short int nLength_one;
	int npackets;
	ULONG can_id_one;
	for (int i = 0; i < m_nDeviceNum; i++) {
		npackets = CanReadOne(&can_id_one, cReadData_8Byte_One[i], &nLength_one, (short)1);
		if (can_id_one == m_lDeviceID[i]) {
			short temp1, temp2, temp3;// , temp4;
			memcpy(&temp1, cReadData_8Byte_One[i], 2);
			memcpy(&temp2, cReadData_8Byte_One[i] + 2, 2);
			memcpy(&temp3, cReadData_8Byte_One[i] + 4, 2);

			guide_lcp1[i] = temp1;
			guide_lcp2[i] = temp2;
			guide_lcp3[i] = temp3;
			guide_lcp[i] = cReadData_8Byte_One[i][6];
			guide_status[i] = cReadData_8Byte_One[i][7];

			guide_line_exists[i] = (int)(cReadData_8Byte_One[i][6] & 0x07);
			guide_marker[i] = (int)((cReadData_8Byte_One[i][6] & 0xF0) >> 4);
			if (cReadData_8Byte_One[i][7] & 0x01)
			{
				guide_line_good[i] = true;
			}
			else
			{
				guide_line_good[i] = false;
			}

			guide_linelev[i] = (int)((cReadData_8Byte_One[i][7] & 0x0E) >> 1);
			if (cReadData_8Byte_One[i][7] & 0x40)
			{
				guide_reading_code[i] = true;
			}
			else
			{
				guide_reading_code[i] = false;
			}
		}
		else
		{
			break;
		}

	}

	return RETURN_NON_ERROR;
}


int CSICKGuide::DisconnectAct() {

	return RETURN_NON_ERROR;
}


// ******************   private   ***************************
bool CSICKGuide::CanWrite(int *nID, unsigned char cWriteData_8byte[][8], int *nLength, int nDataCuount_Max1024)
{
	DWORD dwWrite;
	canmsg_t WriteBuffer[1024];

	for (int i = 0; i < nDataCuount_Max1024; i++)
	{
		ZeroMemory(&WriteBuffer[i], sizeof(canmsg_t));
		WriteBuffer[i].flags = m_nFrameType;
		WriteBuffer[i].id = nID[i];
		WriteBuffer[i].cob = 0;
		WriteBuffer[i].length = nLength[i];
		for (int j = 0; j < 8; j++)
		{
			WriteBuffer[i].data[j] = cWriteData_8byte[i][j];
		}
	}

	if (WriteFile(m_hDevice, WriteBuffer, nDataCuount_Max1024, &dwWrite, 0))
	{
		if (dwWrite != nDataCuount_Max1024)	return false;

		return true;
	}
	else
	{
		return false;
	}
}
int CSICKGuide::CanReadOne(ULONG *nID, unsigned char *cReadData_8byteOne, short int *nLength, int nReadCount_Max1024)
{
	DWORD dwRead = 0;
	canmsg_t ReadBuffer;
	ZeroMemory(&ReadBuffer, sizeof(canmsg_t));

	if (ReadFile(m_hDevice, &ReadBuffer, 1, &dwRead, 0))
	{
		if (dwRead == 0)	return 0;
		if (dwRead == 1)
		{
			*nID = ReadBuffer.id;
			*nLength = ReadBuffer.length;
			for (int j = 0; j < *nLength; j++)
			{
				cReadData_8byteOne[j] = ReadBuffer.data[j];
			}
		}
		else
		{
		}
		return dwRead;
	}
	else
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_IO_PENDING)
		{
			//pengding
		}
		else if (dwError == ERROR_INVALID_PARAMETER)
		{
			//parameter error
		}
		else if (dwError == ERROR_OPERATION_ABORTED)
		{
			//cancelled
		}
		else if (dwError == ERROR_GEN_FAILURE)
		{
			//bus off
		}
		return 0;
	}
}
int CSICKGuide::ClearRxFifo()
{
	Command_par_t cmd;
	BOOL flag;
	ULONG ulOutLen;

	cmd.cmd = CMD_CLEARBUFFERS;
	flag = DeviceIoControl(m_hDevice,
		(ULONG)CAN_IOCTL_COMMAND,
		&cmd,
		sizeof(Command_par_t),
		NULL,
		0,
		&ulOutLen,
		0
	);
	if (!flag)
	{
		return OPERATION_ERROR;
	}

	return SUCCESS;
}
int CSICKGuide::EnterResetMode()
{
	Command_par_t cmd;
	BOOL flag;
	ULONG ulOutLen;

	cmd.cmd = CMD_STOP;
	flag = DeviceIoControl(m_hDevice,
		(ULONG)CAN_IOCTL_COMMAND,
		&cmd,
		sizeof(Command_par_t),
		NULL,
		0,
		&ulOutLen,
		0
	);
	if (!flag)
	{
		return OPERATION_ERROR;
	}

	return SUCCESS;
}
HANDLE CSICKGuide::CanOpen()
{
	TCHAR *tcPort = new TCHAR[5];
	_stprintf(tcPort, _T("can%d"), m_nPort);

	TCHAR CanName[20] = TEXT("\\\\.\\");
	_tcscat(CanName, tcPort);
	m_hDevice = NULL;
	if (m_bSynchronousMode)
	{
		m_hDevice = CreateFile(CanName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	else {
		m_hDevice = CreateFile(CanName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
			NULL);
	}

	return m_hDevice;
}

int CSICKGuide::CanClose()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		if (!CloseHandle(m_hDevice))
			return OPERATION_ERROR;
	}
	return SUCCESS;
}
int CSICKGuide::SetBaud()
{
	Config_par_t config;
	BOOL flag;
	ULONG  ulOutLen;

	config.target = CONF_TIMING;
	config.val1 = m_nBaudrate_k;
	flag = DeviceIoControl(m_hDevice,
		(ULONG)CAN_IOCTL_CONFIG,
		&config,
		sizeof(Config_par_t),
		NULL,
		0,
		&ulOutLen,
		0
	);
	if (!flag)
	{
		return OPERATION_ERROR;
	}

	return SUCCESS;
}
int CSICKGuide::SetTimeOut()
{
	Config_par_t config;
	BOOL flag;

	ULONG ulOutLen;
	config.target = CONF_TIMEOUT;
	config.val2 = m_nTimeOut_ms;
	config.val1 = m_nTimeOut_ms;
	flag = DeviceIoControl(m_hDevice,
		(ULONG)CAN_IOCTL_CONFIG,
		&config,
		sizeof(Config_par_t),
		NULL,
		0,
		&ulOutLen,
		0
	);
	if (!flag)
	{
		return OPERATION_ERROR;
	}

	return SUCCESS;
}
int CSICKGuide::EnterWorkMode()
{
	Command_par_t cmd;
	BOOL flag;
	ULONG ulOutLen;

	cmd.cmd = CMD_START;
	flag = DeviceIoControl(m_hDevice,
		(ULONG)CAN_IOCTL_COMMAND,
		&cmd,
		sizeof(Command_par_t),
		NULL,
		0,
		&ulOutLen,
		0
	);
	if (!flag)
	{
		return OPERATION_ERROR;
	}

	return SUCCESS;
}
void CSICKGuide::getFrontData(short* lcp1, short* lcp2, short* lcp3) {
	*lcp1 = guide_lcp1[0];
	*lcp2 = guide_lcp2[0];
	*lcp3 = guide_lcp3[0];
}
void CSICKGuide::getRearData(short* lcp1, short* lcp2, short* lcp3) {
	*lcp1 = guide_lcp1[1];
	*lcp2 = guide_lcp2[1];
	*lcp3 = guide_lcp3[1];
}
int CSICKGuide::getFrontMarker() {
	return guide_marker[0];
}
int CSICKGuide::getRearMarker() {
	return guide_marker[1];
}

int CSICKGuide::setDeviceID(int index, ULONG id) {
	if (index < 0 || index > m_nDeviceNum)
		return RETURN_FAILED;
	m_lDeviceID[index] = id;
	return RETURN_NON_ERROR;
}

ULONG CSICKGuide::getDeviceID(int index) {
	if (index < 0 || index > m_nDeviceNum)
		return 0;
	return m_lDeviceID[index];
}
int CSICKGuide::getDeviceNum() {
	return m_nDeviceNum;
}
int CSICKGuide::setPort(int port) {
	if (port < 0)
		return RETURN_FAILED;
	m_nPort = port;
	return RETURN_NON_ERROR;
}
int CSICKGuide::getPort() {
	return m_nPort;
}