#include "stdafx.h"
#include "robot\ObstacleChecker.h"

using namespace robot;
using namespace std;

CObstacleChecker::CObstacleChecker() {
	setPosition(0, 0, 0);
	setStopZone(0, 0, 0, 0);
}
CObstacleChecker::~CObstacleChecker() {
	
}

int CObstacleChecker::setPosition(int nX, int nY, int nTheta) {
	m_nXPos = nX;
	m_nYPos = nY;
	m_nTheta = nTheta;
	return RETURN_NON_ERROR;
}

int CObstacleChecker::setRobotSize(int nWidth, int nHeight) {
	m_nRobotWidth = nWidth;
	m_nRobotHeight = nHeight;
	return RETURN_NON_ERROR;
}

int CObstacleChecker::setStopZone(int nFront, int nRear, int nLeft, int nRight) {
	m_nObstacleFront = nFront;
	m_nObstacleRear = nRear;
	m_nObstacleLeft = nLeft;
	m_nObstacleRight = nRight;

	return RETURN_NON_ERROR;
}

int CObstacleChecker::ObjectDetect(LaserScanData data, int * X, int * Y)
{
	double dDeg3Rad = PI / 180.;
	for (int i = 0; i < data.nData_len; i++)
	{
		double dWordTheta = m_nTheta + data.nStart_angle + (i / data.nAngleResolution) + (1./ data.nAngleResolution)*(i%data.nAngleResolution);
		int nX = data.dist[i] * cos(dWordTheta*dDeg3Rad);
		int nY = data.dist[i] * sin(dWordTheta*dDeg3Rad);

		if (m_nObstacleFront > data.dist[i] && data.dist[i] > 5){
			*X = nX + m_nXPos;
			*Y = nY + m_nYPos;
			return 1;
		}
		
		return 0;
	}
	/*
	*ratio = m_dTranslationVelocity / m_dTranslationVelocity_Max;
	*angle = (indexoffset + index*unit)*degreeToRad;
	// 레이져 스캔 값을 AMR기준 상대좌표로 변환(전방 x, 좌측 y)
	double dObsPositionX = data[index] * cos(*angle) + xoffset;
	double dObsPositionY = data[index] * sin(*angle) + yoffset;
	*dist = dObsPositionX;
	// Warning Zone에 장애물이 감지 됨
	if ((dObsPositionX > 0 ? dObsPositionX < m_dFrontStop + (m_dFrontWarn - m_dFrontStop)* (*ratio) + fabs(xoffset) : -dObsPositionX < m_dFrontStop + fabs(xoffset)) &&
		(dObsPositionY > 0 ? dObsPositionY < m_dLeftStop + (m_dLeftWarn - m_dLeftStop)* dLeftZoneRatio + fabs(yoffset) : -dObsPositionY < m_dRightStop + (m_dRightWarn - m_dRightStop)* dRightZoneRatio + fabs(yoffset)))
	{
		if ((dObsPositionX > 0 ? dObsPositionX < m_dFrontStop + fabs(xoffset) : -dObsPositionX < m_dFrontStop + fabs(xoffset)) &&
			(dObsPositionY > 0 ? dObsPositionY < m_dLeftStop + fabs(yoffset) : -dObsPositionY < m_dRightStop + fabs(yoffset)))
		{
			return OBSTACLE_ZONE::OBSTACLE_STOP;
		}
		else {
			// Warning Zone
			for (int i = 0; i < m_nObstacleDetect_WeightTableCount_max10; i++) {
				if (m_dObstacleDetect_WeightTableRange[i] < *dist)
					*ratio = m_dObstacleDetect_WeightTableList[i];
			}
			return OBSTACLE_ZONE::OBSTACLE_WARN;
		}
	}
	// 장애물 감지 안됨
	else
	*/
	return 0;
}