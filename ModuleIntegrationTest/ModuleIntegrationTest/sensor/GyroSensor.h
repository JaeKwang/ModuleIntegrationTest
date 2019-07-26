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
		bool m_bValueInitialized;
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

		void ResetThetaDegTo(double dTargetDeg);
		bool Initialize();
		int OnReceiveData();

	public:
		
		CGyroSensor(string sensorName, int port, int nRate);
		virtual ~CGyroSensor();
		int SerialInitialize();

		int ConnectAct() override;
		int ResetAct() override;
		int UpdateData() override;
		int DisconnectAct() override;

		// Getter & Setter
		int setPort(int iPort);
		int setBaudrate(int DRate);
		int setConnectionTimeout(int nTimeout);
		int setReconnectionCount(int iCount);
		int setDataTimeout(int nTimeout);

		int getData(double* dDataYaw, double* dDataPitch, double* dDataRoll);
		int getThetaDeg(eAxisType eAxis, double* dData);
		int getDeltaThetaDeg(double dData);
		int getPort() { return m_iport; }
		int getBaudrate() { return m_nBaudrate; }
		int getConnectionTimeout() { return m_iConnectionTimeout; }
		int getReconnectionCount() { return m_iReconnectionCount; }
		int getDataTimeout() { return m_iDataTimeout; }
	};
}
