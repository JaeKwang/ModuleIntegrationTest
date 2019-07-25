#pragma once
#include "afxwin.h"
#include <afxmt.h>
#include "SensorModule.h"
#include "comm\SerialComm.h"

#define MAX_TIMEOUT 5000
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
		DWORD m_dBaudrate;
		bool m_bTerminated;

		bool m_bValueInitialized;
		//double m_dAngle;

	public:
		//iAxis - 0: Yaw, 1: Pitch, 2:Roll
		int getThetaDeg(eAxisType eAxis, double* dData);
		int getDeltaThetaDeg(double dData);

		int getPitchDeg();
		int getRollDeg();

		int GetPort() { return m_iport; }
		double GetBaudrate() { return m_dBaudrate; }
		int GetConnectionTimeout() { return m_iConnectionTimeout; }
		int GetReconnectionCount() { return m_iReconnectionCount; }
		int GetDataTimeout() { return m_iDataTimeout; }

		void ResetThetaDegTo(double dTargetDeg);
		bool Initialize();
		int ConnectAct();

		int OnReceiveData();
		int UpdateData();

		CGyroSensor(string sensorName, int port, DWORD DRate);		
		virtual ~CGyroSensor();
		int SerialInitialize();
		int DisconnectAct();
		int TerminateAct();
		void ErrorClear();
		int ReconnectAct();
		int ResetAct();
		int SetPort(int iPort);
		int SetBaudrate(DWORD DRate);
		int getData(double* dDataYaw, double* dDataPitch, double* dDataRoll);
		int SetConnectionTimeout(int nTimeout);
		int SetReconnectionCount(int iCount);
		int SetDataTimeout(int nTimeout);
	};
}
