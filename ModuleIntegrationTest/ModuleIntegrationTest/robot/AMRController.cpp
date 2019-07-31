#include "stdafx.h"
#include "robot\AMRController.h"
#include "sensor\SICKLaserScanner.h"

using namespace eventManager;
using namespace robot;
using namespace sensor;
using namespace std;

CAMRController::CAMRController(){
	// Sensor
	m_nNumOfSensor = 2;
	m_nNumOfLaserScanner = 2;
	m_sensor = new CSensorModule *[m_nNumOfLaserScanner];
	m_sensor[0] = new CSICKLaserScanner("LMS_Front", LMS1xx, "192.168.1.160", 2111, false);
	m_sensor[1] = new CSICKLaserScanner("LMS_Rear", LMS1xx, "192.168.1.161", 2111, false);
	m_IOHub = new CIOHub("./inifiles/CJ_AMR_IO_List.ini");

	// Obstacle Checker
	m_obstacleChecker = new CObstacleChecker();
	m_obstacleChecker->setRobotSize(1000, 1000);

	// Thread
	m_nThreadPeriod = 100;
	m_bAMRControlThreadLoop = true;
	m_AMRControlThread = std::thread(ThreadFunctionAMRControl, this);
}

CAMRController::~CAMRController() {

	// Thread Terminate
	m_bAMRControlThreadLoop = false;
	if (m_AMRControlThread.joinable())
	{
		if (m_AMRControlThread.joinable())
			m_AMRControlThread.join();
	}

	// Memory delete
	SAFE_DELETE(m_obstacleChecker);
	SAFE_DELETE(m_IOHub);
	for (int i = 0; i < m_nNumOfSensor; i++)
		SAFE_DELETE(m_sensor[i]);
}

int CAMRController::ThreadFunctionAMRControl(CAMRController * controller) {
	while (controller->m_bAMRControlThreadLoop) {
		// Clock Start
		clock_t start, runtime;
		start = clock();

		int nState = STATE_AMR_INIT;

		bool bAllSensorIsReady = true;
		// Sensor Error Check
		for (int i = 0; i < controller->m_nNumOfSensor; i++) {
			if (controller->m_sensor[i]->getStatus() == STATE_ERROR) {
				nState = STATE_AMR_ERROR_SENSOR_STATE;
				break;
			}
			else if (controller->m_sensor[i]->getStatus() == STATE_PROGRESSING)
				nState = STATE_AMR_PROGRESSING;
			else if (controller->m_sensor[i]->getStatus() != STATE_RUN)
				bAllSensorIsReady = false;
		}
		if (bAllSensorIsReady)
			nState = STATE_AMR_RUN;

		// IO Error Check
		if (controller->m_IOHub->getStatus() == STATE_RUN)
		{
			int errorCode;
			vector<bool> errorVector;
			vector<bool> valueVector;
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::EMS_TP, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::EMS1, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::EMS2, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::EMS3, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::EMS4, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::BUMPER1, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::BUMPER2, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::BUMPER3, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::BUMPER4, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);
			valueVector.push_back(controller->m_IOHub->bitRead(IO_List::SAFETY_PLC_OUT, &errorCode));
			errorCode == RETURN_NON_ERROR ? errorVector.push_back(true) : errorVector.push_back(false);

			// E-Stop
			for (int i = 0; i < 5; i++)
				if (errorVector[i] & valueVector[i])
					nState = STATE_AMR_ERROR_EMERGENCY;

			// Bumper
			for (int i = 5; i < 10; i++)
				if (errorVector[i] & valueVector[i])
					nState = STATE_AMR_ERROR_CRASH;
		}

		// Obstacle Check
		if (controller->m_sensor[0]->getStatus() == STATE_RUN) {
			CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(controller->m_sensor[0]);
			LaserScanData scan;
			lms->getData(&scan);
			controller->m_obstacleChecker->setPosition(500, 500, 45);
			if (controller->m_obstacleChecker->ObjectDetect(scan, &controller->m_nObstacleX, &controller->m_nObstacleY)) {
				nState = STATE_AMR_ERROR_OBSTACLE;
			}
		}
		if (controller->m_sensor[1]->getStatus() == STATE_RUN) {
			CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(controller->m_sensor[1]);
			LaserScanData scan;
			lms->getData(&scan);
			controller->m_obstacleChecker->setPosition(-500, -500, 255);
			if (controller->m_obstacleChecker->ObjectDetect(scan, &controller->m_nObstacleX, &controller->m_nObstacleY)) {
				nState = STATE_AMR_ERROR_OBSTACLE;
			}
		}
		
		// 상태 체크 완료
		controller->m_AMRState = nState;
		
		// 상태에 따른 IO 출력
		/*
		if (controller->m_IOHub->getStatus() == STATE_RUN)
		{
			switch (nState) {
			case STATE_AMR_ERROR_OBSTACLE:
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH1, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH2, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH3, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH4, true);
				break;
			case STATE_AMR_ERROR_CRASH:
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH1, true);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH2, true);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH3, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH4, true);
				break;
			case STATE_AMR_ERROR_EMERGENCY:
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH1, true);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH2, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH3, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH4, true);
				break;
			default:
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH1, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH2, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH3, false);
				controller->m_IOHub->bitSet(IO_List::SPEAKER_CH4, false);
			}
		}
		*/
		// Run 이 아니면 모터 정지후 아무것도 안함 (continue)
		if (controller->m_AMRState != STATE_AMR_RUN) {
			// Motion Stop
			continue;
		}

		// Keep the Thread Period
		runtime = clock() - start;
		if (controller->m_nThreadPeriod - runtime > 0)
			Sleep(controller->m_nThreadPeriod - runtime);
		else
			g_eventManager->PushTask(MSG_ERROR, "AMR Controller", ERROR_EXCEED_THREAD_CYCLE, true, false);
	}
	return RETURN_NON_ERROR;
}

void CAMRController::setObstacleRange(int nRange) {
	m_obstacleChecker->setStopZone(nRange, nRange, nRange, nRange);
}

int CAMRController::getSensor(int index, CSensorModule** sensor) {
	if (index < 0 || index > m_nNumOfLaserScanner)
		return RETURN_FAILED;
	*sensor = m_sensor[index];
	return RETURN_NON_ERROR;
}

int CAMRController::getIOHub(CIOHub ** sensor) {
	*sensor = m_IOHub;
	return RETURN_NON_ERROR;
}

int CAMRController::getState() {
	return m_AMRState;
}
