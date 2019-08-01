#include "stdafx.h"
#include "ComizoaMotionController.h"
#include "driver/Cmmsdk.h"

using namespace eventManager;
using namespace sensor;
using namespace std;

CComizoaMotionController::CComizoaMotionController(string name):CSensorModule(name)
{
	setThreadPeriod(100);
	SetDataTimeout(100);
	m_iConnectionTimeout = 100;
	m_dLiftUpLimint = 0.0;
	m_dLiftDownLimit = 0.0;
	m_bConnected = false;
	m_dGyroTargetAngle = 0.0;

	if (cmmLoadDll() != TRUE) //DLL을 로드합니다.
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LOADING_LIBRARY_FAILED, true, false);
		return;
	}

	//디바이스를 로드 합니다.
	if (cmmGnDeviceLoad(cmTRUE, &m_nNumAxes) != cmERR_NONE)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LOADING_DEVICE_FAILED, true, false);
		return;
	}

	m_dEncoder = new double[m_nNumAxes];
	m_dSpeed = new double[m_nNumAxes];
	m_dAccel = new double[m_nNumAxes];
	m_dDecel = new double[m_nNumAxes];

}

CComizoaMotionController::~CComizoaMotionController() 
{
	if (m_bConnected)
	{
		MotionStop(true, LEFT_DRIVE_MOTOR, 0, 0);
		MotionStop(true, RIGHT_DRIVE_MOTOR, 0, 0);
	}
	Disconnect();
	while (getStatus() != STATE_INIT);
	SAFE_DELETE(m_dDecel);
	SAFE_DELETE(m_dAccel);
	SAFE_DELETE(m_dSpeed);
	SAFE_DELETE(m_dEncoder);
}

int CComizoaMotionController::ConnectAct() 
{
	if (InitDrivingMotorSpeed() != RETURN_NON_ERROR)
		return RETURN_FAILED;

	if (InitializeFromFile() != RETURN_NON_ERROR)
		return RETURN_FAILED;

	//속도 체크 주기 설정
	cmmCfgSetActSpdCheck(cmTRUE, 50);
	SetDriveWheelCount();

	SetServoOnOff(LEFT_DRIVE_MOTOR, true);
	SetServoOnOff(RIGHT_DRIVE_MOTOR, true);

	cmmCfgSetSpeedPattern(LEFT_DRIVE_MOTOR, cmSMODE_T, 0, Acceleration, Deceleration);
	cmmCfgSetSpeedPattern(RIGHT_DRIVE_MOTOR, cmSMODE_T, 0, Acceleration, Deceleration);

	cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
	cmmSxVMoveStart(RIGHT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE

	m_lLeftMotorDirection = cmDIR_P;
	m_lRightMotorDirection = cmDIR_P;

	MotionStop(false, LEFT_DRIVE_MOTOR, cmFALSE, cmFALSE);
	MotionStop(false, RIGHT_DRIVE_MOTOR, cmFALSE, cmFALSE);

	ResetPosition(LEFT_DRIVE_MOTOR);
	ResetPosition(RIGHT_DRIVE_MOTOR);

	m_bConnected = true;
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::DisconnectAct() 
{

	cmmGnDeviceUnload();
	cmmUnloadDll();
	m_bConnected = false;

	return RETURN_NON_ERROR;
}

int CComizoaMotionController::ResetAct() 
{
	cmmGnDeviceReset();	

	return RETURN_NON_ERROR;
}

int CComizoaMotionController::UpdateData()
{
	
	for (int i = 0; i < m_nNumAxes; i++) {
		// Get Encoder
		cmmStGetPosition(i, cmCNT_FEED, &m_dEncoder[i]);

		// Get Speed Model
		long mode;
		cmmCfgGetSpeedPattern(i, &mode, &m_dSpeed[i], &m_dAccel[i], &m_dDecel[i]);

	}

	
	/*
	if(cmmStReadMioStatuses(LEFT_DRIVE_MOTOR, &nMioStates) == cmERR_NONE) {
		if (nMioStates >> cmIOST_ALM & 0x1)
			OccurError();

	}
	if (cmmStReadMioStatuses(RIGHT_DRIVE_MOTOR, &nMioStates) == cmERR_NONE) {
		if (nMioStates >> cmIOST_ALM & 0x1)
			OccurError();
	}
	*/
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::InitDrivingMotorSpeed()
{
	if (!isDoneMotion(LEFT_DRIVE_MOTOR))
	{
		if (MotionStop(true, LEFT_DRIVE_MOTOR, cmFALSE, cmFALSE))
		{
			SetMotionSpeed(LEFT_DRIVE_MOTOR, eTrapeziodal, 0, 50000, 50000);
		}
		else
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_MOTION_STOP_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	else
	{
		SetMotionSpeed(LEFT_DRIVE_MOTOR, eTrapeziodal, 0, Acceleration, Deceleration);
	}

	if (!isDoneMotion(RIGHT_DRIVE_MOTOR))
	{
		if (MotionStop(true, RIGHT_DRIVE_MOTOR, cmFALSE, cmFALSE))
		{
			SetMotionSpeed(RIGHT_DRIVE_MOTOR, eTrapeziodal, 0, 50000, 50000);
		}
		else
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_MOTION_STOP_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	else
	{
		SetMotionSpeed(RIGHT_DRIVE_MOTOR, eTrapeziodal, 0, Acceleration, Deceleration);
	}

	//IO 읽어 드려서 break 반영
	//	GetceNM();	
	
	return RETURN_NON_ERROR;
}

// Getter & Setter
int CComizoaMotionController::SetDataTimeout(int nTimeout) 
{
	if (nTimeout < 0)
		return RETURN_NON_ERROR;
	if (nTimeout > MAX_TIMEOUT)
		//g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_TIMEOUT_IS_LARGE, true, false);
		m_iDataTimeout = nTimeout;
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::SetConnectionTimeout(int nTimeout)
{
	if (nTimeout < 0 || nTimeout > MAX_TIMEOUT)
	{
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_CONNECTION_TIMEOUT, true, true);
		return RETURN_FAILED;
	}
	m_iConnectionTimeout = nTimeout;
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::SetReconnectionCount(int iCount)
{
	if (iCount < 0 || iCount > MAX_RECONNECT_COUNT)
	{
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_CONNECTION_TIMEOUT, true, true);
		return RETURN_FAILED;
	}
	m_iReconnectionCount = iCount;
	return RETURN_NON_ERROR;
}

bool CComizoaMotionController::isDoneMotion(eMotorAxis eAxis)
{
	long lIsDone;
	if (cmmSxIsDone(eAxis, &lIsDone) == cmERR_NONE)
	{		
		return lIsDone == cmTRUE ? true:false;
	}

	return false;
}

int CComizoaMotionController::SetMotionSpeed(eMotorAxis eAxis, int lSpeedMode, double dWorkSpeed, double dAccel, double dDecel)
{
	long ldir = 0;
	if (eAxis == LEFT_DRIVE_MOTOR)
	{
		ldir = m_lLeftMotorDirection;
		
	}
	else if (eAxis == RIGHT_DRIVE_MOTOR)
	{
		ldir = m_lRightMotorDirection;
	}

	if (cmmCfgSetSpeedPattern(eAxis, lSpeedMode, dWorkSpeed, dAccel, dDecel) != cmERR_NONE || 
		cmmSxVMoveStart(eAxis, m_lLeftMotorDirection) != cmERR_NONE)
	{
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_MOTION_SPEED_SETTING, true, false);
		return RETURN_NON_ERROR;
	}

	return RETURN_NON_ERROR;
}


int CComizoaMotionController::SetMotionSpeed(int eAccelMode, double left, double right)
{
	long stateLeftServo; long stateRightServo;

	if (cmmGnGetServoOn(LEFT_DRIVE_MOTOR, &stateLeftServo) != cmERR_NONE || 
		cmmGnGetServoOn(RIGHT_DRIVE_MOTOR, &stateRightServo) != cmERR_NONE )
	{
		g_eventManager->PushTask(MSG_WARN, getSensorName(), WARN_INVALID_MOTION_SPEED_SETTING, true, false);
		return RETURN_FAILED;
	}

	if (stateLeftServo == cmFALSE || stateRightServo == cmFALSE)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_SERVO_ON_FAILED, true, false);
		return RETURN_FAILED;
	}

	if (left > 0.0)
	{
		if (m_lLeftMotorDirection == cmDIR_P)
		{
			long stat; cmmStReadMotionState(LEFT_DRIVE_MOTOR, &stat);
			if (stat == cmMST_STOP)
				cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);

			cmmCfgSetSpeedPattern(LEFT_DRIVE_MOTOR, eAccelMode, left, Acceleration, Deceleration); //rpm
																					//cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
			cmmOverrideSpeedSet(LEFT_DRIVE_MOTOR);
		}
		else
		{
			cmmSxStop(LEFT_DRIVE_MOTOR, cmFALSE, cmFALSE);
			cmmCfgSetSpeedPattern(LEFT_DRIVE_MOTOR, eAccelMode, 0, Acceleration, Deceleration); //rpm
			cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
			m_lLeftMotorDirection = cmDIR_P;
		}
	}
	else if (left < 0.0)
	{
		if (m_lLeftMotorDirection == cmDIR_N)
		{
			long stat; cmmStReadMotionState(LEFT_DRIVE_MOTOR, &stat);
			if (stat == cmMST_STOP)
				cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_N);


			cmmCfgSetSpeedPattern(LEFT_DRIVE_MOTOR, eAccelMode, -left, Acceleration, Deceleration); //rpm
																					 //cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
			cmmOverrideSpeedSet(LEFT_DRIVE_MOTOR);
		}
		else
		{
			cmmSxStop(LEFT_DRIVE_MOTOR, cmFALSE, cmFALSE);
			cmmCfgSetSpeedPattern(LEFT_DRIVE_MOTOR, eAccelMode, 0, Acceleration, Deceleration); //rpm
			cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_N);//Positive dir V-MOVE
			m_lLeftMotorDirection = cmDIR_N;
		}
	}
	else
	{
		cmmCfgSetSpeedPattern(LEFT_DRIVE_MOTOR, cmSMODE_T, left, Acceleration, Deceleration); //rpm
																				//cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
		cmmOverrideSpeedSet(LEFT_DRIVE_MOTOR);
	}


	if (right > 0.0)
	{
		if (m_lRightMotorDirection == cmDIR_P)
		{
			long stat; cmmStReadMotionState(RIGHT_DRIVE_MOTOR, &stat);
			if (stat == cmMST_STOP)
				cmmSxVMoveStart(RIGHT_DRIVE_MOTOR, cmDIR_P);

			cmmCfgSetSpeedPattern(RIGHT_DRIVE_MOTOR, eAccelMode, right, Acceleration, Deceleration); //rpm
																								   //cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
			cmmOverrideSpeedSet(RIGHT_DRIVE_MOTOR);
		}
		else
		{
			cmmSxStop(RIGHT_DRIVE_MOTOR, cmFALSE, cmFALSE);
			cmmCfgSetSpeedPattern(RIGHT_DRIVE_MOTOR, eAccelMode, 0, Acceleration, Deceleration); //rpm
			cmmSxVMoveStart(RIGHT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
			m_lRightMotorDirection = cmDIR_P;
		}
	}
	else if (right < 0.0)
	{
		if (m_lRightMotorDirection == cmDIR_N)
		{
			long stat; cmmStReadMotionState(RIGHT_DRIVE_MOTOR, &stat);
			if (stat == cmMST_STOP)
				cmmSxVMoveStart(RIGHT_DRIVE_MOTOR, cmDIR_N);


			cmmCfgSetSpeedPattern(RIGHT_DRIVE_MOTOR, eAccelMode, -right, Acceleration, Deceleration); //rpm
																									//cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
			cmmOverrideSpeedSet(RIGHT_DRIVE_MOTOR);
		}
		else
		{
			cmmSxStop(RIGHT_DRIVE_MOTOR, cmFALSE, cmFALSE);
			cmmCfgSetSpeedPattern(RIGHT_DRIVE_MOTOR, eAccelMode, 0, Acceleration, Deceleration); //rpm
			cmmSxVMoveStart(RIGHT_DRIVE_MOTOR, cmDIR_N);//Positive dir V-MOVE
			m_lRightMotorDirection = cmDIR_N;
		}
	}
	else
	{
		cmmCfgSetSpeedPattern(RIGHT_DRIVE_MOTOR, cmSMODE_T, right, Acceleration, Deceleration); //rpm
																							  //cmmSxVMoveStart(LEFT_DRIVE_MOTOR, cmDIR_P);//Positive dir V-MOVE
		cmmOverrideSpeedSet(RIGHT_DRIVE_MOTOR);
	}

	return RETURN_NON_ERROR;
}

int CComizoaMotionController::GetDriveMotorVelocity(double *left, double *right)
{
	// left, right: rpm

	//long state;
	// cmCNT_COMM: 0, cmCNT_FEED: 1
	if (cmmStGetSpeed(LEFT_DRIVE_MOTOR, cmCNT_FEED, left) != cmERR_NONE ||
		cmmStGetSpeed(RIGHT_DRIVE_MOTOR, cmCNT_FEED, right) != cmERR_NONE)
	{
		return RETURN_FAILED;
	}

	return RETURN_NON_ERROR;
}

int CComizoaMotionController::SetServoOnOff(eMotorAxis eAxis, bool bOn)
{
	if (cmmGnSetServoOn(eAxis, bOn) != cmERR_NONE)
	{
		if (bOn)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_SERVO_ON_FAILED, true, false);
		}
		else
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_SERVO_OFF_FAILED, true, false);
		}
		
		return RETURN_FAILED;
	}
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::SetPosition(eMotorAxis eAxis, eCounterName eCounter, double dPos)
{
	if (cmmStSetPosition(eAxis, eCounter, dPos) != cmERR_NONE)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_SET_POSITION_FAILED, true, false);
		RETURN_FAILED;
	}	
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::GetPosition(eMotorAxis eAxis, eCounterName eCounter, double dCurPos) 
{
	if (cmmStGetPosition(eAxis, eCounter_Command, &dCurPos) != cmERR_NONE)
	{
		return RETURN_FAILED;
	}
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::SetDriveWheelCount()
{
	// Reset Drive Wheel count

	double nCommCount = 0.0; // Command Count
	double nFeedCount = 0.0; // Feedback Count

							 //Left Drive Motor
	if (GetPosition(LEFT_DRIVE_MOTOR, eCounter_Feed, nFeedCount) == RETURN_NON_ERROR)
	{
		if (nFeedCount != 0)
		{
			SetPosition(LEFT_DRIVE_MOTOR, eCounter_Feed, 0);
		}
	}

	if (GetPosition(LEFT_DRIVE_MOTOR, eCounter_Command, nCommCount) == RETURN_NON_ERROR)
	{
		if (nCommCount != 0)
		{
			// Command 카운트를 0 으로 설정
			cmmStSetPosition(LEFT_DRIVE_MOTOR, cmCNT_COMM, 0);
		}
	}

	//Right Drive Motor
	if (GetPosition(RIGHT_DRIVE_MOTOR, eCounter_Feed, nFeedCount) == RETURN_NON_ERROR)
	{
		if (nFeedCount != 0)
		{
			SetPosition(RIGHT_DRIVE_MOTOR, eCounter_Feed, 0);
		}
	}

	if (GetPosition(RIGHT_DRIVE_MOTOR, eCounter_Command, nCommCount) == RETURN_NON_ERROR)
	{
		if (nCommCount != 0)
		{
			// Command 카운트를 0 으로 설정
			cmmStSetPosition(RIGHT_DRIVE_MOTOR, cmCNT_COMM, 0);
		}
	}

	return RETURN_NON_ERROR;
}

int CComizoaMotionController::MotionStop(bool bEMG, eMotorAxis eAxis, bool isWaiting, bool isBlocking)
{
	//no : Normal Stop, true : EMG Stop

	if (bEMG != true)
	{
		if (cmmSxStop(eAxis, isWaiting, isBlocking) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_MOTION_STOP_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	else
	{
		if (cmmSxStopEmg(eAxis) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_MOTION_EMG_STOP_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	return RETURN_NON_ERROR;
}


int CComizoaMotionController::InitializeFromFile()
{
	// szSystemDir[MAX_PATH];
	// 윈도우즈 시스템 디렉토리명 얻어오기 (일반적으로는 C:\Windows\System32) */
	//GetSystemDirectory((LPWSTR)szSystemDir, MAX_PATH);
	//sprintf(szCmeFilePath, "%s\\%s", szSystemDir, CME_FILE_NAME);
	char szCmeFilePath[MAX_PATH];
	sprintf(szCmeFilePath, "%s", CME_FILE_NAME);
	if (cmmGnInitFromFile(szCmeFilePath) != cmERR_NONE)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_INITIALIZATION_FAILED, true, false);
		return RETURN_FAILED;
	}
	else
	{
		// CME 파일에서 정의한 축수와 실제 장착되어 있는 모션 축수를 비교확인
		long nNumAxes_installed, nNumAxes_defined;
		cmmAdvGetNumAvailAxes(&nNumAxes_installed); // 현재 실제로 PC 에 장착되어 있는 모션축 수
		cmmAdvGetNumDefinedAxes(&nNumAxes_defined); // CME 파일에서 정의한 축 수(CME 파일이 지정되지 않는 경우에는 현재 장착된 축 수와 일치)

		if (nNumAxes_defined != nNumAxes_defined)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_INITIALIZATION_FAILED, true, false);
			return RETURN_FAILED;
		}
	}

	return RETURN_NON_ERROR;
}
int CComizoaMotionController::ResetPosition(eMotorAxis eAxis)
{
	if (cmmStSetPosition(eAxis, eCounter_Command, 0.0) != cmERR_NONE ||
		cmmStSetPosition(eAxis, eCounter_Feed, 0.0) != cmERR_NONE)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_RESET_POSITION_FAILED, true, false);
		return RETURN_FAILED;
	}
	return RETURN_NON_ERROR;
}

int CComizoaMotionController::InitLiftMotor()
{
	int iMotorCount = GetLiftMotorCount();

	if (iMotorCount == 2)
	{
		SetServoOnOff(FWD_LIFT_MOTOR, true);
	}
	SetServoOnOff(REV_LIFT_MOTOR, true);

	Sleep(500);

	m_bDriveMotorBrake = true;
	m_bLiftMotorBrake = true;

	Sleep(500);

	// LIFT Motor Homing	
	if (LiftMotorHoming())
	{
		return RETURN_FAILED;
	}

	return RETURN_NON_ERROR;
}


int CComizoaMotionController::LiftMotorHoming()
{	
	long lSuccess;
	int nMotorCount = GetLiftMotorCount();	
	//	Homing
	if (nMotorCount == 2)
	{
		if (cmmMsUnregisterSlave(FWD_LIFT_MOTOR) != cmERR_NONE )
		{		
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
			return RETURN_FAILED;
		}
		if (cmmHomeMoveStart(FWD_LIFT_MOTOR, cmDIR_N) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
			return RETURN_FAILED;
		}

	}
	//Motor 1개일 경우
	if (cmmHomeMoveStart(REV_LIFT_MOTOR, cmDIR_N) != cmERR_NONE)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
		return RETURN_FAILED;
	}

	//Homing이 끝날때 까지 대기
	if (nMotorCount == 2)
	{
		if (cmmHomeWaitDone(FWD_LIFT_MOTOR, cmFALSE) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	if (cmmHomeWaitDone(REV_LIFT_MOTOR, cmFALSE) != cmERR_NONE)
	{
		if (cmmHomeWaitDone(FWD_LIFT_MOTOR, cmFALSE) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
			return RETURN_FAILED;
		}
	}

	if (nMotorCount == 2)
	{
		cmmHomeGetSuccess(FWD_LIFT_MOTOR, &lSuccess);
		if (!lSuccess)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	cmmHomeGetSuccess(REV_LIFT_MOTOR, &lSuccess);
	if (!lSuccess)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
		return RETURN_FAILED;
	}
	
	Sleep(1000);

	if (nMotorCount == 2)
	{
		if (cmmMsRegisterSlave(FWD_LIFT_MOTOR, 200, cmFALSE) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_HOMING_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	//m_dLiftUpLimint = RobotParameter::getInstance()->getLift_Up_Limit();
	//m_dLiftDownLimit = RobotParameter::getInstance()->getLift_Down_Limit();

	//Return Check
	if (LiftUpDown(false) != RETURN_NON_ERROR)
	{
		return RETURN_FAILED;
	}

	return RETURN_NON_ERROR;
}

int CComizoaMotionController::LiftUpDown(bool bUpside)
{
	long stateFWDLift, stateREVLift;

	if (cmmGnGetServoOn(FWD_LIFT_MOTOR, &stateFWDLift) != cmERR_NONE ||
		cmmGnGetServoOn(REV_LIFT_MOTOR, &stateREVLift) != cmERR_NONE)
	{
		g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_UPDOWN_FAILED, true, false);
		return RETURN_FAILED;
	}
	if (stateFWDLift == cmFALSE)
	{
		if (cmmGnSetServoOn(FWD_LIFT_MOTOR, true) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_UPDOWN_FAILED, true, false);
			return RETURN_FAILED;
		}
	}
	if (stateREVLift == cmFALSE)
	{		
		if (cmmGnSetServoOn(REV_LIFT_MOTOR, true) != cmERR_NONE)
		{
			g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_UPDOWN_FAILED, true, false);
			return RETURN_FAILED;	
		}
	}

	Sleep(100);
	m_bLiftMotorBrake = true;

	long ret;

	//Lift uP
	if (bUpside)
	{
		cmmSxMoveToStart(REV_LIFT_MOTOR, m_dLiftUpLimint);
		ret = cmmSxWaitDone(REV_LIFT_MOTOR, cmFALSE);
		if (ret != cmERR_NONE)
		{
			//Try again
			if (ret == -5008 || ret == -2147423119)
			{
				cmmSxMoveToStart(REV_LIFT_MOTOR, m_dLiftUpLimint);
				ret = cmmSxWaitDone(REV_LIFT_MOTOR, cmFALSE);
				if (ret != cmERR_NONE)
				{
					g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_UPDOWN_FAILED, true, false);
					return RETURN_FAILED;
				}
				else
				{
					//나중에 아래 부분 반드시 추가 --> Obstacle과 연관
					//m_AMRStatus.nLoadUnload = 1;
				}
			}
			else
			{
				g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_UPDOWN_FAILED, true, false);
				return RETURN_FAILED;
			}

		}
		else
		{
			//나중에 아래 부분 반드시 추가 --> Obstacle과 연관
			//m_AMRStatus.nLoadUnload = 1;
		}

	}
	else //Lift Down
	{
		cmmSxMoveToStart(REV_LIFT_MOTOR, m_dLiftDownLimit);
		ret = cmmSxWaitDone(REV_LIFT_MOTOR, cmFALSE);
		if (ret != cmERR_NONE)
		{
			if (ret == -5008 || ret == -2147423120)
			{
				cmmSxMoveToStart(REV_LIFT_MOTOR, m_dLiftDownLimit);
				ret = cmmSxWaitDone(REV_LIFT_MOTOR, cmFALSE);
				if (ret != cmERR_NONE)
				{
					g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_UPDOWN_FAILED, true, false);
					return RETURN_FAILED;
				}
				else
				{
					//나중에 아래 부분 반드시 추가 --> Obstacle과 연관
					//m_AMRStatus.nLoadUnload = 0;
				}
			}
			else
			{
				g_eventManager->PushTask(MSG_ERROR, getSensorName(), ERROR_LIFT_UPDOWN_FAILED, true, false);
				return RETURN_FAILED;
			}

		}
		else
		{
			//나중에 아래 부분 반드시 추가 --> Obstacle과 연관
			//m_AMRStatus.nLoadUnload = 0;
		}
	}

	m_bLiftMotorBrake = false;

	Sleep(100);

	SetServoOnOff(FWD_LIFT_MOTOR, false);
	SetServoOnOff(REV_LIFT_MOTOR, false);

	return RETURN_NON_ERROR;
}

int CComizoaMotionController::CheckEncodeerValue(double dInputEncoder, double *dEncoderL, double *dEncoderR)
{
	double dENCL = 5000000 + dInputEncoder;
	double dENCR = -5000000 + dInputEncoder;

	if (dENCL > ENCMAX)
	{
		dENCL = dENCL - ENCMAX;
	}
	else if (dENCL < -ENCMAX)
	{
		dENCL = dENCL + ENCMAX;
	}

	if (dENCR > ENCMAX)
	{
		dENCR = dENCR - ENCMAX;
	}
	else if (dENCR < -ENCMAX)
	{
		dENCR = dENCR + ENCMAX;
	}

	*dEncoderL = dENCL;
	*dEncoderR = dENCR;

	return 0;
}

double CComizoaMotionController::getEncoder(long Axis) { return m_dEncoder[Axis]; }
double CComizoaMotionController::getSpeed(long Axis) { return m_dSpeed[Axis]; }
double CComizoaMotionController::getAccel(long Axis) { return m_dAccel[Axis]; }
double CComizoaMotionController::getDecel(long Axis) { return m_dDecel[Axis]; }