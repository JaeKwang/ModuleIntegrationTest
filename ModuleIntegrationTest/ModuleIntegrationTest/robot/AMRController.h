#pragma once

#include "sensor\SensorModule.h"
#include "sensor\IOHub.h"
#include "ObstacleChecker.h"

namespace robot
{
	enum eAMRStatus {
		STATE_AMR_INIT,
		STATE_AMR_PROGRESSING,
		STATE_AMR_RUN,
		STATE_AMR_ERROR_SENSOR_STATE,
		STATE_AMR_ERROR_EMERGENCY,
		STATE_AMR_ERROR_CRASH,
		STATE_AMR_ERROR_OBSTACLE,
	};
	class CAMRController
	{
	private:
		int m_AMRState;

		// Sensor
		int m_nNumOfSensor;
		sensor::CSensorModule ** m_sensor;
		sensor::CIOHub * m_IOHub;
		int m_nNumOfLaserScanner;
		int m_nObstacle;
		int m_nThreadPeriod;

		// Obstacle Checker
		CObstacleChecker * m_obstacleChecker;
		int m_nObstacleX;
		int m_nObstacleY;

		// Main Control Thread
		std::thread m_AMRControlThread;
		bool m_bAMRControlThreadLoop;
		static int ThreadFunctionAMRControl(CAMRController *);

	public:
		CAMRController();
		~CAMRController();

		void setObstacleRange(int nRange);
		int getSensor(int, sensor::CSensorModule**);
		int getIOHub(sensor::CIOHub ** sensor);
		int getState();
	};
}
