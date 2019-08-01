
// ModuleIntegrationTestDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "sensor\SensorModule.h"
#include "sensor\IOHub.h"

#include "robot\AMRController.h"

// CModuleIntegrationTestDlg 대화 상자
class CModuleIntegrationTestDlg : public CDialogEx
{
// 생성입니다.
public:
	CModuleIntegrationTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODULEINTEGRATIONTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	sensor::CSensorModule ** m_sensor;
	sensor::CIOHub * m_IOHub;
	LaserScanData m_LaserData1;

	robot::CAMRController * m_AMRController;

	void UpdateUI();
	void UILaserScanDataUpdate(sensor::CSensorModule *, int);
	void UIComizoaDataUpdate();
	void UIGuideDataUpdate();
	void UIGyroDataUpdate();
	void UIMotionUpdate();
	void UIEventManagerUpdate();
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void DrawDoubleBuffering();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_listLaserScanData;
	CEdit m_editLaser1IP1;
	CEdit m_editLaser1IP2;
	CEdit m_editLaser1IP3;
	CEdit m_editLaser1IP4;
	CEdit m_editLaser1Port;
	CEdit m_editLaser1Res;
	CEdit m_editLaser1Start;
	CEdit m_editLaser1End;
	CEdit m_editLaser1State;
	CEdit m_editLaser2IP1;
	CEdit m_editLaser2IP2;
	CEdit m_editLaser2IP3;
	CEdit m_editLaser2IP4;
	CEdit m_editLaser2Port;
	CEdit m_editLaser2State;
	CEdit m_editLaser2Res;
	CEdit m_editLaser2Start;
	CEdit m_editLaser2End;
	afx_msg void OnBnClickedButtonLaser1Connect();
	afx_msg void OnDestroy();
	int m_radioLaser1UpsideDown;
	int m_radioLaser2UpsideDown;
	afx_msg void OnBnClickedButtonLaser2Connect();
	afx_msg void OnBnClickedButtonLaser1Reset();
	afx_msg void OnBnClickedButtonLaser2Reset();
	CEdit m_editComizoaID;
	CEdit m_editComizoaState;
	CListCtrl m_listComizoaData;
	afx_msg void OnLvnItemchangedListComizoaData(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_staticIOData;
	afx_msg void OnBnClickedButtonComizoaConnect();
	afx_msg void OnBnClickedButtonComizoaReset();
	CEdit m_editGuideDeviceNum;
	CEdit m_editGuideDeviceID1;
	CEdit m_editGuideDeviceID2;
	CEdit m_editGuideDevice1Left;
	CEdit m_editGuideDevice1Centor;
	CEdit m_editGuideDevice1Right;
	CEdit m_editGuideDevice1Marker;
	CEdit m_editGuideDevice2Left;
	CEdit m_editGuideDevice2Centor;
	CEdit m_editGuideDevice2Right;
	CEdit m_editGuideDevice2Marker;
	CEdit m_editGuideState;
	afx_msg void OnBnClickedButtonGuideConnect();
	afx_msg void OnBnClickedButtonGuideReset();
	CEdit m_editGuidePort;
	CEdit m_editGyroPort;
	CEdit m_editGyroBaudrate;
	CEdit m_editGyroYaw;
	CEdit m_editGyroPitch;
	CEdit m_editGyroRoll;
	CEdit m_editGyroState;
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButtonGyroConnect();
	afx_msg void OnBnClickedButtonGyroReset();
	CListBox m_listEventManager;
	afx_msg void OnBnClickedButtonErrorclear();
	afx_msg void OnBnClickedCancel();
	CButton m_checkLaser2UpsideDown;
	CButton m_checkLaser1UpsideDown;
	afx_msg void OnBnClickedButtonLaser1Cancel();
	afx_msg void OnBnClickedButtonLaser2Cancel();
	afx_msg void OnBnClickedButtonLaser1Apply();
	afx_msg void OnBnClickedButtonLaser2Apply();
	CEdit m_editMotionSpeed;
	CEdit m_editMotionAccel;
	CEdit m_editMotionDecel;
	CEdit m_editMotionState;
	CStatic m_editMotionData;
	afx_msg void OnBnClickedButtonMotionConnect();
	afx_msg void OnBnClickedButtonMotionReset();
	afx_msg void OnBnClickedButtonMotionApply();
	afx_msg void OnBnClickedButtonMotionCancel();
	afx_msg void OnBnClickedButtonMotionMove();
	CEdit m_editObstacle;
	CEdit m_editRotation;
	CEdit m_editDrive;
	CEdit m_editCurRotate;
	CEdit m_editCurDrive;
	afx_msg void OnBnClickedButtonObstacle();
	CEdit m_editAMRState;
	afx_msg void OnBnClickedButtonMotionServoOn();
	afx_msg void OnBnClickedButtonMotionServoOff();
	afx_msg void OnBnClickedButtonMotionEstop();
	afx_msg void OnBnClickedButtonMotionStop();
	afx_msg void OnBnClickedButtonDrive();
	afx_msg void OnBnClickedButtonRotate();
	CEdit m_editMotionLift2;
	CEdit m_editMotionLeft;
	CEdit m_editMotionRight;
	CEdit m_editMotionLift1;
};
