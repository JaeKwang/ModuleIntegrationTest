#include "stdafx.h"
#include "GyroSensor.h"
#include "../EventManager/EventManager.h"

#define PACKET_SIZE 26
using namespace sensor;
using namespace eventManager;
using namespace std;

// initialize pointer
CGyroSensor::CGyroSensor(string sensorName, int port, int DRate) :CSensorModule(sensorName)
{
	setSensorName(sensorName);
	setPort(port);
	setBaudrate(DRate);
	Initialize();
}

CGyroSensor::~CGyroSensor()
{
	Disconnect();
	while (getStatus() != STATE_INIT);
}

bool CGyroSensor::Initialize()
{
	m_dData = 0.;
	m_bValueInitialized = false;

	m_dRefData = 0.;
	start_index = 0;
	end_index = 0;
	count_index = 0;
	m_Serial = NULL;
	m_Serial = new CSerialComm();

	if (m_Serial == NULL)
	{
		return false;
	}
	return true;
}

int CGyroSensor::ConnectAct()
{
	//port, baudrate, databit, stopbit, paritybit
	m_Serial->SetComport(m_iport, m_nBaudrate, 8, 0, 0);

	if (!m_Serial->CreateCommInfo()) {
		return RETURN_FAILED;
	}

	if (!m_Serial->OpenComport())
	{
		return RETURN_FAILED;
	}

	if (SerialInitialize() != 0)
	{
		return RETURN_FAILED;
	}
	m_Serial->m_bStartFlag = TRUE;

	return RETURN_NON_ERROR;
}

int CGyroSensor::DisconnectAct()
{
	int iRes = 0;
	BOOL bResult = FALSE;
	if (m_Serial->hComm != NULL)
	{
		bResult = m_Serial->DestroyComm();
	}
	iRes = bResult ? 0 : 1;
	return iRes;
}

int CGyroSensor::SerialInitialize()
{

	OVERLAPPED os;								// Declaration the OVERLAPPED structure

	if (m_Serial == NULL) return -1;			// if npComm handle doesn't have no comports attached, it returns error

	memset(&os, 0, sizeof(OVERLAPPED));	// initiaization the structure OVERLAPPED os
	os.hEvent = CreateEvent(NULL,			// no security
		TRUE,							// explicit reset req
		FALSE,							// initial event reset
		NULL);							// no name

										// event creation failure
	if (os.hEvent == NULL) {
		AfxMessageBox(_T("Fail to Create Event!"), MB_OK);

		return RETURN_FAILED;
	}

	//EV_RXCHAR is set as event, other events are ignored
	if (!SetCommMask(m_Serial->hComm, EV_RXCHAR)) {
		return RETURN_FAILED;
	}

	return RETURN_NON_ERROR;
}

int CGyroSensor::OnReceiveData()
{
	bool DataCheck = false;

	unsigned char chDataBlock[MAXBLOCK];

	int nLength = 0;
	nLength = m_Serial->GetBlock(chDataBlock);

	if (nLength == 0)
	{
		return false;
	}

	if (nLength > (MAXBLOCK - PACKET_SIZE))
	{
		nLength = (MAXBLOCK - PACKET_SIZE);
	}

	for (int i = 0; i < nLength; i++)
	{
		rxbuf_for_GYRO[count_index + i] = chDataBlock[i];
	}
	count_index += nLength;


	bool find_packet = false;

	if (count_index < PACKET_SIZE)
	{
		return false;
	}
	else
	{
		for (int i = 0; i <= (count_index - PACKET_SIZE); i++)
		{
			if (rxbuf_for_GYRO[i] != 0xA6 || rxbuf_for_GYRO[i + 1] != 0xA6)
			{
				m_Serial->clearport();
				continue;
			}

			BYTE checkSum_temp = 0;
			for (int j = i + 2; j < i + 25; j++)
			{
				checkSum_temp = checkSum_temp + rxbuf_for_GYRO[j];
			}

			if (checkSum_temp != rxbuf_for_GYRO[i + 25])
			{
				continue;
			}
			else
			{
				find_packet = true;
				start_index = i;
				i = i + PACKET_SIZE - 1;
			}
		}
	}

	if (!find_packet)
	{
		return false;
	}
	else
	{
		short rate;
		short angle;
		short angle_roll, angle_pitch, angle_yaw;
		short rate_roll, rate_pitch, rate_yaw;
		short acc_x, acc_y, acc_z;
		double dAngle, dPitch, dRoll;

		// unit: angle: 0.01 [deg], rate: 0.01 [deg/sec], acc: 1 [mg] ,caution: checksum is 1 byte.
		memcpy(&angle_roll, rxbuf_for_GYRO + start_index + 3, sizeof(short));
		memcpy(&angle_pitch, rxbuf_for_GYRO + start_index + 5, sizeof(short));
		memcpy(&angle_yaw, rxbuf_for_GYRO + start_index + 7, sizeof(short));

		memcpy(&rate_roll, rxbuf_for_GYRO + start_index + 9, sizeof(short));
		memcpy(&rate_pitch, rxbuf_for_GYRO + start_index + 11, sizeof(short));
		memcpy(&rate_yaw, rxbuf_for_GYRO + start_index + 13, sizeof(short));

		memcpy(&acc_x, rxbuf_for_GYRO + start_index + 15, sizeof(short));
		memcpy(&acc_y, rxbuf_for_GYRO + start_index + 17, sizeof(short));
		memcpy(&acc_z, rxbuf_for_GYRO + start_index + 19, sizeof(short));


		rate = rate_yaw;
		angle = angle_yaw;

		DataCheck = true;

		dAngle = -(double)angle;
		dPitch = -(double)angle_pitch;
		dRoll = -(double)angle_roll;



		if (!m_bValueInitialized)
		{
			m_bValueInitialized = true;
			m_dRefData = dAngle / 100.0;
			m_dRefPitch = dPitch / 100.0;
			m_dRefRoll = dRoll / 100.0;
			m_dDeltaRefData = dAngle / 100.0;
		}
		m_dData = dAngle / 100.0;
		m_dPitch = dPitch / 100.0;
		m_dRoll = dRoll / 100.0;


		int restart_index = 0;
		for (int k = start_index + PACKET_SIZE; k < count_index; k++)
		{
			rxbuf_for_GYRO[restart_index] = rxbuf_for_GYRO[k];
			restart_index++;
		}
		count_index = restart_index;
	}

	return RETURN_NON_ERROR;
}


int CGyroSensor::UpdateData()
{
	DWORD dwEvtMask;
	DWORD result = 0;
	int nLength;

	unsigned char InData[MAXBLOCK + 1];			// Array for receive data
												//waiting for EVENT when fConnectedis TRUE
	dwEvtMask = 0;									// Variable for created EVENT
	WaitCommEvent(m_Serial->hComm, &dwEvtMask, NULL);	// waiting for EVENT occur
	if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR) {	// if EV_RXCHAR EVENT occurs
		memset(InData, 0, MAXBLOCK); // Initialize the array InData to 0
		nLength = m_Serial->ReadCommBlock((LPSTR)InData, MAXBLOCK);
		if (nLength == 0)
			return RETURN_FAILED;
		else {
			m_Serial->SetReadData(InData, nLength);		// Receive data
			// 프로토콜 체크
			// return RETURN_DATA_CHECK_FAILED;
			OnReceiveData();
		}
	}
	else
		return RETURN_FAILED;

	return RETURN_NON_ERROR;
}

int	CGyroSensor::getThetaDeg(eAxisType eType, double* dData)
{
	double dResult = 0.0;
	switch (eType)
	{
	case eYaw: //0 Yaw
	{
		dResult = m_dData - m_dRefData;
		break;
	}
	case ePitch: // 1 Pitch
	{
		dResult = m_dPitch - m_dRefPitch;
		break;
	}
	case eRoll: // 2 Yaw
	{
		dResult = m_dRoll - m_dRefRoll;
		break;
	}
	default:
		break;
	}
	if (dResult > 180.0)			dResult -= 360.0;
	if (dResult < -180.0)			dResult += 360.0;

	*dData = dResult;
	return RETURN_NON_ERROR;
}

int CGyroSensor::getData(double* dDataYaw, double* dDataPitch, double* dDataRoll) {

	double dTempYaw = 0.0;
	double dTempPitch = 0.0;
	double dTempRoll = 0.0;
	getThetaDeg(eYaw, &dTempYaw);
	getThetaDeg(ePitch, &dTempPitch);
	getThetaDeg(eRoll, &dTempRoll);
	*dDataYaw = dTempYaw;
	*dDataPitch = dTempPitch;
	*dDataRoll = dTempRoll;

	return RETURN_NON_ERROR;
}

int	CGyroSensor::getDeltaThetaDeg(double dData)
{
	double dResult = m_dData - m_dDeltaRefData;
	if (dResult > 180.0)			dResult -= 360.0;
	if (dResult < -180.0)			dResult += 360.0;
	dData = dResult;
	m_dDeltaRefData = m_dData;
	return RETURN_NON_ERROR;
}

void CGyroSensor::ResetThetaDegTo(double dTargetDeg)
{
	m_dRefData = m_dData - dTargetDeg;
	if (m_dRefData > 180.0)		m_dRefData -= 360.0;
	if (m_dRefData < -180.0)	m_dRefData += 360.0;
}

int CGyroSensor::ResetAct()
{
	char * senddata;
	senddata = "$MIB,RESET*87";
	if (!m_Serial->WriteCommBlock(senddata, 13))
	{
		if (ConnectAct() != 0)
		{
			return RETURN_FAILED;
		}
	}
	m_bValueInitialized = false;
	m_Serial->clearport();

	Wait(100);
	return RETURN_NON_ERROR;
}

int CGyroSensor::setConnectionTimeout(int nTimeout)
{
	if (nTimeout < 0 || nTimeout > MAX_TIMEOUT)
	{
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_CONNECTION_TIMEOUT, true, true);
		return RETURN_FAILED;
	}
	m_iConnectionTimeout = nTimeout;
	return RETURN_NON_ERROR;
}

int CGyroSensor::setReconnectionCount(int iCount)
{
	if (iCount < 0 || iCount > MAX_RECONNECT_COUNT)
	{
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_CONNECTION_TIMEOUT, true, true);
		return RETURN_FAILED;
	}
	m_iReconnectionCount = iCount;
	return RETURN_NON_ERROR;
}

int CGyroSensor::setDataTimeout(int nTimeout) {
	if (nTimeout < 0 || MAX_TIMEOUT)
	{
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_DATA_TIMEOUT, true, false);
		return RETURN_FAILED;
	}

	m_iDataTimeout = nTimeout;
	return RETURN_NON_ERROR;
}

int CGyroSensor::setPort(int nPort) {
	if (nPort < 0 || nPort > 65555)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), WARN_INVALID_PORTNO, true, true);
		return RETURN_FAILED;
	}
	m_iport = nPort;
	return RETURN_NON_ERROR;
}

int CGyroSensor::setBaudrate(int nRate) {
	if (nRate < 0)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), WARN_INVALID_BAUDRATE, true, true);
		return RETURN_FAILED;
	}
	m_nBaudrate = nRate;
	return RETURN_NON_ERROR;
}

