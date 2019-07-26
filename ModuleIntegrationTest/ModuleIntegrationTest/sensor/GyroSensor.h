#pragma once
#include "afxwin.h"
#include "GyroSensor.h"
#include "SensorModule.h"
#include <iostream>
#include "comm\SerialComm.h"
#include <afxmt.h>

#define MAX_TIMEOUT 1000
#define	MAX_RECONNECT_COUNT 10
namespace sensor
{
	enum eAxisType {
		eYaw = 0,
		ePitch,
		eRoll,
	};

	class CGyroSensor : public CSensorModule
	{
	private:

	public:
		static const int IR_SENSOR_NUM = 4;
		static const int IR_DOWN_SENSOR_NUM = 4;
		static const int IR_SENSOR_MAX_DISTANCE = 3; //3m

	public:
		double m_dDeltaRefData;
	private:
		CSerialComm *m_Serial;

		unsigned char rxbuf_for_GYRO[MAXBLOCK];

		int start_index;
		int end_index;
		int count_index;

		double m_dData, m_dPitch, m_dRoll;
		double m_dRefData, m_dRefPitch, m_dRefRoll;
		int m_iport;
		int m_iConnectionTimeout;
		int m_iReconnectionCount;
		int m_iDataTimeout;
		int m_nBaudrate;
		bool m_bTerminated;

		bool m_bValueInitialized;
		//double m_dAngle;

	public:
		//iAxis - 0: Yaw, 1: Pitch, 2:Roll
		int getThetaDeg(eAxisType eAxis, double* dData);
		int getDeltaThetaDeg(double dData);

		int GetPort() { return m_iport; }
		int GetBaudrate() { return m_nBaudrate; }
		int GetConnectionTimeout() { return m_iConnectionTimeout; }
		int GetReconnectionCount() { return m_iReconnectionCount; }
		int GetDataTimeout() { return m_iDataTimeout; }

		void ResetThetaDegTo(double dTargetDeg);
		bool Initialize();
		int ConnectAct();

		int OnReceiveData();
		int UpdateData();

		CGyroSensor(string sensorName, int port, int nRate);
		virtual ~CGyroSensor();
		int SerialInitialize();
		int DisconnectAct();
		int TerminateAct();
		void ErrorClear();
		int ReconnectAct();
		int ResetAct();
		int SetPort(int iPort);
		int SetBaudrate(int DRate);
		int getData(double* dDataYaw, double* dDataPitch, double* dDataRoll);
		int SetConnectionTimeout(int nTimeout);
		int SetReconnectionCount(int iCount);
		int SetDataTimeout(int nTimeout);
	};
}
