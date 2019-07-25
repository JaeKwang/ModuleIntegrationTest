#pragma once

#include "sensor\SensorModule.h"

class CSockTcp;

namespace sensor {
	enum eSICKLaserScannerModel {
		TiMxxx,
		LMS1xx,
	};
	class CSICKLaserScanner : public CSensorModule {
	private:
		// ������ ����
		char* m_cpIP;
		int m_nPort;
		int m_nConnectionTimeout;
		int m_nDataTimeout;

		eSICKLaserScannerModel m_eModel;
		int m_nFreqency;
		double m_dAngleResolution;
		int m_nStartAngle;
		int m_nEndAngle;
		bool m_bUpsideDown;

		CSockTcp *m_client;

		// Switching Double Buffer
		bool m_bBufferSwitch;
		LaserScanData m_bufferA, m_bufferB;
		unsigned char *m_res;
		int m_nResSize;

		// private function
		int ConnectAct() override;
		int DisconnectAct() override;
		int ResetAct() override;
		int UpdateData() override;
		void SetLaserScanData();
		int DeviceInitialize();
		int Send(std::string);
		int Recv(unsigned char **,int *);
		std::string DecToHexString(int);
		std::string IntToString(int);
		int AcquireData(int *);
		int DecodeScanDataAll_LMS100(int);

	public:
		/* ������ ��ĳ���� �Ķ���͸� �����ϴ� �Լ�
		Parameter
		1. model : enum���� ���ǵ� ������ ��ĳ�� �� (LMS1xx, TiM5xx, ... )
		2. sensorName : ������ ������ �̸�
		3. ip : ipv4 �ּ�
		4. port : ipv4 ��Ʈ ��ȣ
		5. upsideDown : ������ ��ĳ�ʰ� ������ �޸� ��� true, else false
		Return Value
		1. ���� : ���� ����
		2. ERROR_NON (0) : ����
		Reference
		1. �𵨺� ������ �Ķ���� ����
		2. �Ķ���� ���� Validation üũ
		*/
		CSICKLaserScanner(std::string, eSICKLaserScannerModel, std::string, int, bool);
		~CSICKLaserScanner();
		
		// Getter & Setter
		int getData(LaserScanData *);
		int getModel();
		int getFreqency();
		double getAngleResolution();
		int getStartAngle();
		int getEndAngle();
		bool getUpsideDown();
		int getResolDeg();
		int getConnectionTimeout();
		int getDataTimeout();
		int getPort();
		std::string getIP();
		int setModel(int);
		int setFreqency(int);
		int setAngleResolution(double);
		int setStartAngle(double);
		int setEndAngle(double);
		int setUpsideDown(bool);
		int setIP(std::string);
		int setPort(int);
		int setConnectionTimeout(int);
		int setDataTimeout(int);
	};
}