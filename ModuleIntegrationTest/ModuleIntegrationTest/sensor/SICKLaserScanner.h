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
		// 생성자 변수
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
		/* 레이저 스캐너의 파라미터를 변경하는 함수
		Parameter
		1. model : enum으로 정의된 레이저 스캐너 모델 (LMS1xx, TiM5xx, ... )
		2. sensorName : 센서별 고유한 이름
		3. ip : ipv4 주소
		4. port : ipv4 포트 번호
		5. upsideDown : 레이저 스캐너가 뒤집혀 달린 경우 true, else false
		Return Value
		1. 음수 : 수행 실패
		2. ERROR_NON (0) : 성공
		Reference
		1. 모델별 최적의 파라미터 세팅
		2. 파라미터 값의 Validation 체크
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