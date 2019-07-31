#pragma once

#include "SensorModule.h"
#include "driver/CmmsdkDef.h"

#define CME_FILE_NAME "C:\\potenit\\motor_param\\Default.cme2"
#define MAX_TIMEOUT 5000
#define	MAX_RECONNECT_COUNT 10
#define Acceleration 1000
#define Deceleration 1000
#define ENCMAX (2147483647.0) // robotcube�� ���
#define ROTATION_CHECK_RANGE		3.0	

namespace sensor 
{
	enum eMotorAxis
	{
		//Conveyor�� ���Ŀ� �߰�
		REV_LIFT_MOTOR = 0,
		FWD_LIFT_MOTOR,
		RIGHT_DRIVE_MOTOR,
		LEFT_DRIVE_MOTOR,
	};
	enum eAccelMode 
	{
		eKeep = -1,
		eConstant,
		eTrapeziodal,
		eS_Curve,
	};
	enum eCounterName
	{
		eCounter_Command,
		eCounter_Feed,
		eCounter_Deviation,
		eCounter_General, 
		eCoutner_Remained,
	};

	class CComizoaMotionController : public CSensorModule
	{
	private:
		int ConnectAct() override;
		int ResetAct() override;
		int UpdateData() override;
		int DisconnectAct() override;

		double m_dRightEncoder;
		double m_dLeftEncoder;
		double m_dRightTarget;
		double m_dLeftTarget;

	public:
		CComizoaMotionController(std::string);
		~CComizoaMotionController();
		
		int Initialize();
		bool m_bConnected;
		int SetDataTimeout(int nTimeout);
		int SetConnectionTimeout(int nTimeout);
		int SetReconnectionCount(int iCount);
		int GetConnectionTimeout() { return m_iConnectionTimeout; }
		int GetReconnectionCount() { return m_iReconnectionCount; }
		int GetDataTimeout() { return m_iDataTimeout; }
		
		int m_iThreadPeriod;
		bool isDoneMotion(eMotorAxis eAxis);
		int MotionStop(bool bEMG, eMotorAxis eAxis, bool isWaiting, bool isBlocking);
		int SetMotionSpeed(eMotorAxis eAxis, int lSpeedMode, double dWorkSpeed, double dAccel, double dDecel);
		int SetMotionSpeed(int eAccelMode, double left, double right);

		int InitializeFromFile();
		
		int GetDriveMotorVelocity(double *left, double *right);
		int SetLiftMotorCount(int iCount) { return m_iLiftMotorCount = iCount; }
		int GetLiftMotorCount() { return m_iLiftMotorCount =1; }
		int SetServoOnOff(eMotorAxis eAxis, bool bOn);
		int SetPosition(eMotorAxis eAxis, eCounterName eCounter, double dPos);
		int ResetPosition(eMotorAxis eAxis);
		int GetPosition(eMotorAxis eAxis, eCounterName eCounter, double dCurPos);
		int InitDrivingMotorSpeed();
		int SetDriveWheelCount();
		int InitLiftMotor();
		int LiftMotorHoming();
		int LiftUpDown(bool bUpside);
		int CheckEncodeerValue(double dInputEncoder, double *dEncoderL, double *dEncoderR);


		long m_lLeftMotorDirection, m_lRightMotorDirection;
		bool m_bDriveMotorBrake = true;  //On : True, Off : False
		bool m_bLiftMotorBrake = true; //On : True, Off : False
		double m_dLiftUpLimint;
		double m_dLiftDownLimit;
		int m_iDataTimeout;
		int m_iConnectionTimeout;
		int m_iLiftMotorCount;
		int m_iReconnectionCount;
		double m_dGyroTargetAngle;
		
		// Getter & Setter
		void setRightTarget(double);
		void setLeftTarget(double);
		double getLeftEncoder();
		double getRightEncoder();
	};
}