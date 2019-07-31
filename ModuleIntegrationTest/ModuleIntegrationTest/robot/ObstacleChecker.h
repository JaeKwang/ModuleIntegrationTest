#pragma once

namespace robot {
	class CObstacleChecker {
	private:
		int m_nRobotWidth;	// mm
		int m_nRobotHeight;	// mm
		int m_nXPos;	// mm
		int m_nYPos;	// mm 
		int m_nTheta;	// Degree

		int m_nObstacleFront, m_nObstacleRear, m_nObstacleLeft, m_nObstacleRight;

	public:
		CObstacleChecker();
		~CObstacleChecker();

		int setRobotSize(int nWidth, int nHeight);
		int setPosition(int nX, int nY, int nTheta);
		int setStopZone(int front, int rear, int left, int right);
		int ObjectDetect(LaserScanData scanData, int * nX, int * nY);
	};
}