
// ModuleIntegrationTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ModuleIntegrationTest.h"
#include "ModuleIntegrationTestDlg.h"
#include "afxdialogex.h"

#include "sensor\SICKLaserScanner.h"
#include "sensor\SICKGuide.h"
#include "sensor\GyroSensor.h"
#include "sensor\ComizoaMotionController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace sensor;
using namespace eventManager;
using namespace IO_List;
using namespace robot;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CModuleIntegrationTestDlg 대화 상자



CModuleIntegrationTestDlg::CModuleIntegrationTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODULEINTEGRATIONTEST_DIALOG, pParent)
	, m_radioLaser1UpsideDown(0)
	, m_radioLaser2UpsideDown(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModuleIntegrationTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LASERSCANDATA, m_listLaserScanData);
	DDX_Control(pDX, IDC_EDIT_LASER1_IP1, m_editLaser1IP1);
	DDX_Control(pDX, IDC_EDIT_LASER1_IP2, m_editLaser1IP2);
	DDX_Control(pDX, IDC_EDIT_LASER1_IP3, m_editLaser1IP3);
	DDX_Control(pDX, IDC_EDIT_LASER1_IP4, m_editLaser1IP4);
	DDX_Control(pDX, IDC_EDIT_LASER1_PORT, m_editLaser1Port);
	DDX_Control(pDX, IDC_EDIT_LASER1_RES, m_editLaser1Res);
	DDX_Control(pDX, IDC_EDIT_LASER1_START, m_editLaser1Start);
	DDX_Control(pDX, IDC_EDIT_LASER1_END, m_editLaser1End);
	DDX_Control(pDX, IDC_EDIT_LASER1_STATE, m_editLaser1State);
	DDX_Control(pDX, IDC_EDIT_LASER2_IP1, m_editLaser2IP1);
	DDX_Control(pDX, IDC_EDIT_LASER2_IP2, m_editLaser2IP2);
	DDX_Control(pDX, IDC_EDIT_LASER2_IP3, m_editLaser2IP3);
	DDX_Control(pDX, IDC_EDIT_LASER2_IP4, m_editLaser2IP4);
	DDX_Control(pDX, IDC_EDIT_LASER2_PORT, m_editLaser2Port);
	DDX_Control(pDX, IDC_EDIT_LASER2_STATE, m_editLaser2State);
	DDX_Control(pDX, IDC_EDIT_LASER2_RES, m_editLaser2Res);
	DDX_Control(pDX, IDC_EDIT_LASER2_START, m_editLaser2Start);
	DDX_Control(pDX, IDC_EDIT_LASER2_STOP, m_editLaser2End);
	DDX_Control(pDX, IDC_EDIT_COMIZOA_ID, m_editComizoaID);
	DDX_Control(pDX, IDC_EDIT_COMIZOA_STATE, m_editComizoaState);
	DDX_Control(pDX, IDC_LIST_COMIZOA_DATA, m_listComizoaData);
	DDX_Control(pDX, IDC_STATIC_COMIZOA_PIN_NAME, m_staticIOData);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE_NUM, m_editGuideDeviceNum);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE1_ID, m_editGuideDeviceID1);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE2_ID, m_editGuideDeviceID2);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE1_LEFT, m_editGuideDevice1Left);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE1_CENTOR, m_editGuideDevice1Centor);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE1_RIGHT, m_editGuideDevice1Right);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE1_MARKER, m_editGuideDevice1Marker);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE2_LEFT, m_editGuideDevice2Left);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE2_CENTOR, m_editGuideDevice2Centor);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE2_RIGHT, m_editGuideDevice2Right);
	DDX_Control(pDX, IDC_EDIT_GUIDE_DEVICE2_MARKER, m_editGuideDevice2Marker);
	DDX_Control(pDX, IDC_EDIT_GUIDE_STATE, m_editGuideState);
	DDX_Control(pDX, IDC_EDIT_GUIDE_PORT, m_editGuidePort);
	DDX_Control(pDX, IDC_EDIT_GYRO_PORT, m_editGyroPort);
	DDX_Control(pDX, IDC_EDIT_GYRO_BAUDRATE, m_editGyroBaudrate);
	DDX_Control(pDX, IDC_EDIT_GYRO_YAW, m_editGyroYaw);
	DDX_Control(pDX, IDC_EDIT_GYRO_PITCH, m_editGyroPitch);
	DDX_Control(pDX, IDC_EDIT_GYRO_ROLL, m_editGyroRoll);
	DDX_Control(pDX, IDC_EDIT_GYRO_STATE, m_editGyroState);
	DDX_Control(pDX, IDC_LIST3, m_listEventManager);
	DDX_Control(pDX, IDC_CHECK_LASER2_UPSIDEDOWN, m_checkLaser2UpsideDown);
	DDX_Control(pDX, IDC_CHECK_LASER1_UPSIDEDOWN, m_checkLaser1UpsideDown);
	DDX_Control(pDX, IDC_EDIT_MOTION_SPEED, m_editMotionSpeed);
	DDX_Control(pDX, IDC_EDIT_MOTION_ACCEL, m_editMotionAccel);
	DDX_Control(pDX, IDC_EDIT_MOTION_DECEL, m_editMotionDecel);
	DDX_Control(pDX, IDC_EDIT_MOTION_STATE, m_editMotionState);
	DDX_Control(pDX, IDC_STATIC_MOTION_POS, m_editMotionData);
	DDX_Control(pDX, IDC_EDIT23, m_editObstacle);
	DDX_Control(pDX, IDC_EDIT22, m_editRotation);
	DDX_Control(pDX, IDC_EDIT21, m_editDrive);
	DDX_Control(pDX, IDC_EDIT_CUR_ROTATE, m_editCurRotate);
	DDX_Control(pDX, IDC_EDIT_CUR_DRIVE, m_editCurDrive);
	DDX_Control(pDX, IDC_EDIT_AMR_MAIN_STATE, m_editAMRState);
	DDX_Control(pDX, IDC_EDIT43, m_editMotionLift2);
	DDX_Control(pDX, IDC_EDIT33, m_editMotionLeft);
	DDX_Control(pDX, IDC_EDIT41, m_editMotionRight);
	DDX_Control(pDX, IDC_EDIT42, m_editMotionLift1);
}

BEGIN_MESSAGE_MAP(CModuleIntegrationTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_LASER1_CONNECT, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Connect)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_LASER2_CONNECT, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Connect)
	ON_BN_CLICKED(IDC_BUTTON_LASER1_RESET, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Reset)
	ON_BN_CLICKED(IDC_BUTTON_LASER2_RESET, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Reset)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COMIZOA_DATA, &CModuleIntegrationTestDlg::OnLvnItemchangedListComizoaData)
	ON_BN_CLICKED(IDC_BUTTON_COMIZOA_CONNECT, &CModuleIntegrationTestDlg::OnBnClickedButtonComizoaConnect)
	ON_BN_CLICKED(IDC_BUTTON_COMIZOA_RESET, &CModuleIntegrationTestDlg::OnBnClickedButtonComizoaReset)
	ON_BN_CLICKED(IDC_BUTTON_GUIDE_CONNECT, &CModuleIntegrationTestDlg::OnBnClickedButtonGuideConnect)
	ON_BN_CLICKED(IDC_BUTTON_GUIDE_RESET, &CModuleIntegrationTestDlg::OnBnClickedButtonGuideReset)
	ON_BN_CLICKED(IDC_BUTTON_GYRO_CONNECT, &CModuleIntegrationTestDlg::OnBnClickedButtonGyroConnect)
	ON_BN_CLICKED(IDC_BUTTON_GYRO_RESET, &CModuleIntegrationTestDlg::OnBnClickedButtonGyroReset)
	ON_BN_CLICKED(IDC_BUTTON_ERRORCLEAR, &CModuleIntegrationTestDlg::OnBnClickedButtonErrorclear)
	ON_BN_CLICKED(IDCANCEL, &CModuleIntegrationTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LASER1_CANCEL, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Cancel)
	ON_BN_CLICKED(IDC_BUTTON_LASER2_CANCEL, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Cancel)
	ON_BN_CLICKED(IDC_BUTTON_LASER1_APPLY, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Apply)
	ON_BN_CLICKED(IDC_BUTTON_LASER2_APPLY, &CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Apply)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_CONNECT, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionConnect)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_RESET, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionReset)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_APPLY, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionApply)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_CANCEL, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionCancel)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_MOVE, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionMove)
	ON_BN_CLICKED(IDC_BUTTON_OBSTACLE, &CModuleIntegrationTestDlg::OnBnClickedButtonObstacle)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_SERVO_ON, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionServoOn)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_SERVO_OFF, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionServoOff)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_ESTOP, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionEstop)
	ON_BN_CLICKED(IDC_BUTTON_MOTION_STOP, &CModuleIntegrationTestDlg::OnBnClickedButtonMotionStop)
	ON_BN_CLICKED(IDC_BUTTON_DRIVE, &CModuleIntegrationTestDlg::OnBnClickedButtonDrive)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE, &CModuleIntegrationTestDlg::OnBnClickedButtonRotate)
END_MESSAGE_MAP()


// CModuleIntegrationTestDlg 메시지 처리기

BOOL CModuleIntegrationTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	g_eventManager->PushTask(MSG_INFO, "", INFO_PROGRAM_START, true, false);

	m_AMRController = new CAMRController();
	
	// LMS 2, Gyro 1, Cancard 1, Motion 1, ComizoaIO 1
	m_sensor = new CSensorModule *[5];
	m_AMRController->getSensor(0, &m_sensor[0]);
	m_AMRController->getSensor(1, &m_sensor[1]);
	m_AMRController->getSensor(2, &m_sensor[2]);
	m_AMRController->getSensor(3, &m_sensor[3]);
	
	m_sensor[4] = new CComizoaMotionController("Motion");
	m_AMRController->getIOHub(&m_IOHub);
	
	UpdateUI();

	SetTimer(1, 100, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CModuleIntegrationTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	SAFE_DELETE(m_sensor[2]);
	SAFE_DELETE(m_sensor[3]);
	SAFE_DELETE(m_sensor[4]);
	SAFE_DELETE(m_AMRController);
	g_eventManager->PushTask(MSG_INFO, "", INFO_PROGRAM_TERMINATED, true, false);
	SAFE_DELETE(g_eventManager);
	SAFE_DELETEA(m_sensor);
}

void CModuleIntegrationTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CModuleIntegrationTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//DrawDoubleBuffering();
		CDialogEx::OnPaint();
	}
}


HCURSOR CModuleIntegrationTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CModuleIntegrationTestDlg::DrawDoubleBuffering()
{
	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(rect);

	CDC MemDC;
	CBitmap *pOldBitmap;
	CBitmap bmp;

	MemDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = (CBitmap *)MemDC.SelectObject(&bmp);
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
	MemDC.SelectObject(pOldBitmap);
	//DrawImage(&MemDC);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	//MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}


BOOL CModuleIntegrationTestDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;
}


void CModuleIntegrationTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		// UI Update
		UILaserScanDataUpdate(m_sensor[0], 0);
		UILaserScanDataUpdate(m_sensor[1], 1);
		UIComizoaDataUpdate();
		UIGuideDataUpdate();
		UIGyroDataUpdate();
		UIMotionUpdate();
		UIEventManagerUpdate();


		switch (m_AMRController->getState()) {
		case STATE_AMR_INIT:
			m_editAMRState.SetWindowTextW(_T("AMR needs to initialize"));
			break;
		case STATE_AMR_PROGRESSING:
			m_editAMRState.SetWindowTextW(_T("AMR is initializing"));
			break;
		case STATE_AMR_RUN:
			m_editAMRState.SetWindowTextW(_T("ready to run"));
			break;
		case STATE_AMR_ERROR_SENSOR_STATE:
			m_editAMRState.SetWindowTextW(_T("Sensor is Error"));
			break;
		case STATE_AMR_ERROR_EMERGENCY:
			m_editAMRState.SetWindowTextW(_T("Emergency Stop"));
			break;
		case STATE_AMR_ERROR_CRASH:
			m_editAMRState.SetWindowTextW(_T("AMR is crashed"));
			break;
		case STATE_AMR_ERROR_OBSTACLE:
			m_editAMRState.SetWindowTextW(_T("Obstacle is detected"));
			break;
		}

	}
	CDialogEx::OnTimer(nIDEvent);
}


void CModuleIntegrationTestDlg::UpdateUI() {
	CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[0]);
	std::string IP = lms->getIP();
	std::string delimiter = ".";
	std::string token = IP.substr(0, IP.find(delimiter));

	// IP Address Update
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP1.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP2.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP3.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP4.SetWindowText(CA2T(token.c_str()));
	m_editLaser1Port.SetWindowText(CA2T(std::to_string(lms->getPort()).c_str()));

	// Parameters Update
	m_editLaser1Res.SetWindowText(CA2T(std::to_string(lms->getAngleResolution()).c_str()));
	m_editLaser1Start.SetWindowText(CA2T(std::to_string(lms->getStartAngle()).c_str()));
	m_editLaser1End.SetWindowText(CA2T(std::to_string(lms->getEndAngle()).c_str()));
	m_checkLaser1UpsideDown.SetCheck(lms->getUpsideDown());
	
	lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[1]);
	IP = lms->getIP();
	delimiter = ".";
	token = IP.substr(0, IP.find(delimiter));

	// IP Address Update
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP1.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP2.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP3.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP4.SetWindowText(CA2T(token.c_str()));
	m_editLaser2Port.SetWindowText(CA2T(std::to_string(lms->getPort()).c_str()));

	// Parameters Update
	m_editLaser2Res.SetWindowText(CA2T(std::to_string(lms->getAngleResolution()).c_str()));
	m_editLaser2Start.SetWindowText(CA2T(std::to_string(lms->getStartAngle()).c_str()));
	m_editLaser2End.SetWindowText(CA2T(std::to_string(lms->getEndAngle()).c_str()));
	m_checkLaser2UpsideDown.SetCheck(lms->getUpsideDown());

	// List Update
	for (int i = 0; i < m_listLaserScanData.GetItemCount(); i++) {
		m_listLaserScanData.DeleteColumn(i);
	}
	int col = int(lms->getEndAngle() - lms->getStartAngle());
	m_listLaserScanData.InsertColumn(0, _T("구분"), LVCFMT_CENTER, 50, -1);
	for (int i = 1; i < col + 1; i++) {
		CString a;
		a.Format(_T("%d"), int(lms->getStartAngle()) + i - 1);
		LPCTSTR szTemp = a;
		m_listLaserScanData.InsertColumn(i, szTemp, LVCFMT_CENTER, 100, -1);
	}
	m_listLaserScanData.InsertItem(0, _T("Front"));
	m_listLaserScanData.InsertItem(1, _T("Rear"));

	int step = lms->getAngleResolution();
	for (int i = 0; i < col; i++) {
		m_listLaserScanData.SetItem(0, i + 1, LVIF_TEXT, _T("-"), 0, 0, 0, NULL);
		m_listLaserScanData.SetItem(1, i + 1, LVIF_TEXT, _T("-"), 0, 0, 0, NULL);
	}

	// Comizoa UI
	//UI Update
	m_editComizoaID.SetWindowText(CA2T(std::to_string(m_IOHub->getComizoaID()).c_str()));
	m_listComizoaData.DeleteAllItems();
	m_listComizoaData.InsertColumn(0, _T("PinNum"), LVCFMT_LEFT, 100);
	for (int i = 0; i < m_IOHub->getDIOModuleNumber(); i++)
		m_listComizoaData.InsertColumn(i + 1, CA2CT(("DIO" + std::to_string(i)).c_str()), LVCFMT_CENTER, 100);

	int nMaxNum = 0;
	DIOModule* dioModule = m_IOHub->getDIOModule();
	for (int i = 0; i < m_IOHub->getDIOModuleNumber(); i++) {
		int nPin = dioModule[i].nDINumber + dioModule[i].nDONumber;
		if (nMaxNum < nPin)
			nMaxNum = nPin;
	}
	for (int i = 0; i < nMaxNum; i++)
		m_listComizoaData.InsertItem(i + 1, CA2CT(("Pin" + std::to_string(i)).c_str()));

	// update IO data		
	IOPinType * in = m_IOHub->getDIModule();
	IOPinType * out = m_IOHub->getDOModule();

	int errorCode;
	for (int i = 0; i < PIN_SIZE; i++) {
		bool bValue = m_IOHub->bitRead((eDI_Code)i, &errorCode);
		if (errorCode == RETURN_NON_ERROR)
			m_listComizoaData.SetItemText(in[i].nPinBase + in[i].nPinPosition, in[i].nDIONumber + 1, _T("-"));
	}
	for (int i = 0; i < POUT_SIZE; i++) {
		bool bValue = m_IOHub->bitRead((eDO_Code)i, &errorCode);
		if (errorCode == RETURN_NON_ERROR)
			m_listComizoaData.SetItemText(out[i].nPinBase + out[i].nPinPosition, out[i].nDIONumber + 1, _T("-"));
	}

	// Guide Sensor
	CSICKGuide* guide = dynamic_cast<CSICKGuide*>(m_sensor[2]);
	m_editGuideDeviceNum.SetWindowText(CA2T(std::to_string(guide->getDeviceNum()).c_str()));
	m_editGuideDeviceID1.SetWindowText(CA2T(std::to_string(guide->getDeviceID(0)).c_str()));
	m_editGuideDeviceID2.SetWindowText(CA2T(std::to_string(guide->getDeviceID(1)).c_str()));
	m_editGuidePort.SetWindowText(CA2T(std::to_string(guide->getPort()).c_str()));
	m_editGuideDevice1Left.SetWindowText(_T("-"));
	m_editGuideDevice1Centor.SetWindowText(_T("-"));
	m_editGuideDevice1Right.SetWindowText(_T("-"));
	m_editGuideDevice1Marker.SetWindowText(_T("-"));
	m_editGuideDevice2Left.SetWindowText(_T("-"));
	m_editGuideDevice2Centor.SetWindowText(_T("-"));
	m_editGuideDevice2Right.SetWindowText(_T("-"));
	m_editGuideDevice2Marker.SetWindowText(_T("-"));

	// Gyro Sensor
	CGyroSensor* gyro = dynamic_cast<CGyroSensor*>(m_sensor[3]);
	m_editGyroPort.SetWindowText(CA2T(std::to_string(gyro->getPort()).c_str()));
	m_editGyroBaudrate.SetWindowText(CA2T(std::to_string(gyro->getBaudrate()).c_str()));
	m_editGyroYaw.SetWindowText(_T("-"));
	m_editGyroPitch.SetWindowText(_T("-"));
	m_editGyroRoll.SetWindowText(_T("-"));

	// Motion
	m_editMotionSpeed.SetWindowText(_T("10"));
	m_editMotionAccel.SetWindowText(_T("1000"));
	m_editMotionDecel.SetWindowText(_T("1000"));
	m_editMotionData.SetWindowText(_T("0, 0"));

	// Operation
	m_editObstacle.SetWindowText(_T("0"));
	m_editDrive.SetWindowText(_T("0"));
	m_editRotation.SetWindowText(_T("0"));
}


void CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Connect()
{
	CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[0]);

	// Get IP & Port
	CString str[5];
	m_editLaser1IP1.GetWindowTextW(str[0]);
	m_editLaser1IP2.GetWindowTextW(str[1]);
	m_editLaser1IP3.GetWindowTextW(str[2]);
	m_editLaser1IP4.GetWindowTextW(str[3]);
	m_editLaser1Port.GetWindowTextW(str[4]);

	std::string ip;
	unsigned int port;
	for (int i = 0; i < 4; i++) {
		ip.append((CStringA)str[i]);
		if (i < 3) ip.append(".");
	}
	port = _ttoi(str[4]);

	lms->setIP(ip);
	lms->setPort(port);

	m_sensor[0]->Connect();
}


void CModuleIntegrationTestDlg::UILaserScanDataUpdate(sensor::CSensorModule * input, int nIndex) {
	switch (input->getStatus()) {
	case STATE_INIT:
		if(nIndex == 0)
			m_editLaser1State.SetWindowTextW(_T("Init"));
		else
			m_editLaser2State.SetWindowTextW(_T("Init"));
		break;
	case STATE_PROGRESSING:
		if (nIndex == 0)
			m_editLaser1State.SetWindowTextW(_T("Prog"));
		else
			m_editLaser2State.SetWindowTextW(_T("Prog"));
		break;
	case STATE_RUN:
		if (nIndex == 0)
			m_editLaser1State.SetWindowTextW(_T("Run"));
		else
			m_editLaser2State.SetWindowTextW(_T("Run"));
		break;
	case STATE_ERROR:
		if (nIndex == 0)
			m_editLaser1State.SetWindowTextW(_T("Error"));
		else
			m_editLaser2State.SetWindowTextW(_T("Error"));
		break;
	}

	// Print Data
	if (input->getStatus() == STATE_RUN) {
		CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(input);
		lms->getData(&m_LaserData1);
		int col = int(lms->getEndAngle() - lms->getStartAngle());
		int step = lms->getAngleResolution();
		for (int i = 0; i < col; i++) {
			long dist = m_LaserData1.dist[i*step];
			m_listLaserScanData.SetItem(nIndex, i + 1, LVIF_TEXT, CA2CT(std::to_string(dist).c_str()), 0, 0, 0, NULL);
		}
	}
}


void CModuleIntegrationTestDlg::UIComizoaDataUpdate() {
	switch (m_IOHub->getStatus()) {
	case STATE_INIT:
		m_editComizoaState.SetWindowTextW(_T("Init"));
		break;
	case STATE_PROGRESSING:
		m_editComizoaState.SetWindowTextW(_T("Prog"));
		break;
	case STATE_RUN:
		m_editComizoaState.SetWindowTextW(_T("Run"));
		break;
	case STATE_ERROR:
		m_editComizoaState.SetWindowTextW(_T("Error"));
		break;
	}

	// Print Data
	if (m_IOHub->getStatus() == STATE_RUN) {
		// get IO data		
		DIOModule * dioModule = m_IOHub->getDIOModule();
		IOPinType * in = m_IOHub->getDIModule();
		IOPinType * out = m_IOHub->getDOModule();

		int errorCode;
		for (int i = 0; i < PIN_SIZE; i++) {
			bool bValue = m_IOHub->bitRead((eDI_Code)i, &errorCode);
			if (errorCode == RETURN_NON_ERROR) {
				if (bValue)
					m_listComizoaData.SetItemText(in[i].nPinBase + in[i].nPinPosition, in[i].nDIONumber + 1, _T("TRUE"));
				else
					m_listComizoaData.SetItemText(in[i].nPinBase + in[i].nPinPosition, in[i].nDIONumber + 1, _T("FALSE"));
			}
		}
		for (int i = 0; i < POUT_SIZE; i++) {
			bool bValue = m_IOHub->bitRead((eDO_Code)i, &errorCode);
			if (errorCode == RETURN_NON_ERROR) {
				if (bValue)
					m_listComizoaData.SetItemText(out[i].nPinBase + out[i].nPinPosition, out[i].nDIONumber + 1, _T("TRUE"));
				else
					m_listComizoaData.SetItemText(out[i].nPinBase + out[i].nPinPosition, out[i].nDIONumber + 1, _T("FALSE"));
			}
		}
	}
}


void CModuleIntegrationTestDlg::UIGuideDataUpdate() {
	switch (m_sensor[2]->getStatus()) {
	case STATE_INIT:
		m_editGuideState.SetWindowTextW(_T("Init"));
		break;
	case STATE_PROGRESSING:
		m_editGuideState.SetWindowTextW(_T("Prog"));
		break;
	case STATE_RUN:
		m_editGuideState.SetWindowTextW(_T("Run"));
		break;
	case STATE_ERROR:
		m_editGuideState.SetWindowTextW(_T("Error"));
		break;
	}

	if (m_sensor[2]->getStatus() == STATE_RUN) {
		short a[3];
		((CSICKGuide *)m_sensor[2])->getFrontData(&a[0], &a[1], &a[2]);
		short b[3];
		((CSICKGuide *)m_sensor[2])->getRearData(&b[0], &b[1], &b[2]);
		short markerF = ((CSICKGuide *)m_sensor[2])->getFrontMarker();
		short markerR = ((CSICKGuide *)m_sensor[2])->getRearMarker();

		m_editGuideDevice1Left.SetWindowText(CA2T(std::to_string(a[0]).c_str()));
		m_editGuideDevice1Centor.SetWindowText(CA2T(std::to_string(a[1]).c_str()));
		m_editGuideDevice1Right.SetWindowText(CA2T(std::to_string(a[2]).c_str()));
		m_editGuideDevice1Marker.SetWindowText(CA2T(std::to_string(markerF).c_str()));

		m_editGuideDevice2Left.SetWindowText(CA2T(std::to_string(b[0]).c_str()));
		m_editGuideDevice2Centor.SetWindowText(CA2T(std::to_string(b[1]).c_str()));
		m_editGuideDevice2Right.SetWindowText(CA2T(std::to_string(b[2]).c_str()));
		m_editGuideDevice2Marker.SetWindowText(CA2T(std::to_string(markerR).c_str()));
	}
}


void CModuleIntegrationTestDlg::UIGyroDataUpdate() {
	switch (m_sensor[3]->getStatus())
	{
	case STATE_INIT:
		m_editGyroState.SetWindowTextW(_T("Init"));
		break;
	case STATE_PROGRESSING:
		m_editGyroState.SetWindowTextW(_T("Progress"));
		break;
	case STATE_RUN:
		m_editGyroState.SetWindowTextW(_T("Run"));
		break;
	case STATE_ERROR:
		m_editGyroState.SetWindowTextW(_T("Error"));
		break;
	}

	if (m_sensor[3]->getStatus() == STATE_RUN)
	{
		double dYaw, dPitch, dRoll;
		((CGyroSensor *)m_sensor[3])->getData(&dYaw, &dPitch, &dRoll);

		m_editGyroYaw.SetWindowText(CA2CT(std::to_string(dYaw).c_str()));
		m_editGyroPitch.SetWindowText(CA2CT(std::to_string(dPitch).c_str()));
		m_editGyroRoll.SetWindowText(CA2CT(std::to_string(dRoll).c_str()));
	}
}

void CModuleIntegrationTestDlg::UIMotionUpdate() {
	switch (m_sensor[4]->getStatus())
	{
	case STATE_INIT:
		m_editMotionState.SetWindowTextW(_T("Init"));
		break;
	case STATE_PROGRESSING:
		m_editMotionState.SetWindowTextW(_T("Progress"));
		break;
	case STATE_RUN:
		m_editMotionState.SetWindowTextW(_T("Run"));
		break;
	case STATE_ERROR:
		m_editMotionState.SetWindowTextW(_T("Error"));
		break;
	}
	
	if (m_sensor[4]->getStatus() == STATE_RUN) 
	{
		CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
		m_editMotionData.SetWindowText(CA2T((to_string((int)motion->getEncoder(LEFT_DRIVE_MOTOR)) + ", " + to_string((int)motion->getEncoder(RIGHT_DRIVE_MOTOR))).c_str()));
		m_editMotionLeft.SetWindowText(CA2T(("Speed:" + std::to_string((int)motion->getSpeed(LEFT_DRIVE_MOTOR)) + "\nAcc:" + std::to_string((int)motion->getAccel(LEFT_DRIVE_MOTOR)) + "\nDecel" + std::to_string((int)motion->getDecel(LEFT_DRIVE_MOTOR))).c_str()));
		m_editMotionRight.SetWindowText(CA2T(("Speed:" + std::to_string((int)motion->getSpeed(RIGHT_DRIVE_MOTOR)) + "\nAcc:" + std::to_string((int)motion->getAccel(RIGHT_DRIVE_MOTOR)) + "\nDecel" + std::to_string((int)motion->getDecel(RIGHT_DRIVE_MOTOR))).c_str()));
		m_editMotionLift1.SetWindowText(CA2T(("Speed:" + std::to_string((int)motion->getSpeed(REV_LIFT_MOTOR)) + "\nAcc:" + std::to_string((int)motion->getAccel(REV_LIFT_MOTOR)) + "\nDecel" + std::to_string((int)motion->getDecel(REV_LIFT_MOTOR))).c_str()));
		m_editMotionLift2.SetWindowText(CA2T(("Speed:" + std::to_string((int)motion->getSpeed(FWD_LIFT_MOTOR)) + "\nAcc:" + std::to_string((int)motion->getAccel(FWD_LIFT_MOTOR)) + "\nDecel" + std::to_string((int)motion->getDecel(FWD_LIFT_MOTOR))).c_str()));
	}
}
void CModuleIntegrationTestDlg::UIEventManagerUpdate() {
	m_listEventManager.ResetContent();
	vector<vector<CEventNode>> list = g_eventManager->getErrorArrayList();
	map<eEventCode, string> table = g_eventManager->getEventCodeTable();
	for (int i = 0; i < list.size(); i++)
		for (int j = 0; j < list[i].size(); j++) 
			m_listEventManager.AddString(CA2T((list[i][j].m_eventTarget +" : " + table[list[i][j].m_eventCode]).c_str()));
}

void CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Connect()
{
	CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[1]);

	// Get IP & Port
	CString str[5];
	m_editLaser2IP1.GetWindowTextW(str[0]);
	m_editLaser2IP2.GetWindowTextW(str[1]);
	m_editLaser2IP3.GetWindowTextW(str[2]);
	m_editLaser2IP4.GetWindowTextW(str[3]);
	m_editLaser2Port.GetWindowTextW(str[4]);

	std::string ip;
	unsigned int port;
	for (int i = 0; i < 4; i++) {
		ip.append((CStringA)str[i]);
		if (i < 3) ip.append(".");
	}
	port = _ttoi(str[4]);

	lms->setIP(ip);
	lms->setPort(port);

	m_sensor[1]->Connect();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Reset()
{
	m_sensor[0]->Reset();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Reset()
{
	m_sensor[1]->Reset();
}


void CModuleIntegrationTestDlg::OnLvnItemchangedListComizoaData(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* nmcd = (NMLVCUSTOMDRAW*)pNMHDR;

	int row = nmcd->iIconEffect;
	int col = nmcd->iIconPhase - 1;

	int errCode;
	IOPinType pin;

	errCode = m_IOHub->findPin(col, row, &pin);
	if(errCode != RETURN_NON_ERROR)
		m_staticIOData.SetWindowText(CA2T(("-\n" + std::to_string(col+1) + ", " + std::to_string(row+1)).c_str()));
	else {
		m_staticIOData.SetWindowText(CA2T((pin.strPinName + "\n" + std::to_string(col + 1) + ", " + std::to_string(row + 1)).c_str()));
		if (m_IOHub->bitRead(pin.nDIONumber, pin.nPinBase, pin.nPinPosition, &errCode))
			m_IOHub->bitSet(pin.nDIONumber, pin.nPinBase, pin.nPinPosition, false);
		else
			m_IOHub->bitSet(pin.nDIONumber, pin.nPinBase, pin.nPinPosition, true);
	}
	*pResult = 0;
}


void CModuleIntegrationTestDlg::OnBnClickedButtonComizoaConnect()
{
	CString str;
	m_editComizoaID.GetWindowTextW(str);
	m_IOHub->setComizoaID(_ttoi(str));
	m_IOHub->Connect();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonComizoaReset()
{
	m_IOHub->Reset();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonGuideConnect()
{
	CSICKGuide* s = dynamic_cast<CSICKGuide*>(m_sensor[2]);
	CString str;
	m_editGuidePort.GetWindowTextW(str);
	s->setPort(_ttoi(str));
	m_sensor[2]->Connect();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonGuideReset()
{
	m_sensor[2]->Reset();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonGyroConnect()
{
	CGyroSensor* s = dynamic_cast<CGyroSensor*>(m_sensor[3]);
	CString str;
	m_editGyroPort.GetWindowTextW(str);
	s->setPort(_ttoi(str));
	m_editGyroBaudrate.GetWindowTextW(str);
	s->setBaudrate(_ttoi(str));
	m_sensor[3]->Connect();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonGyroReset()
{
	m_sensor[3]->Reset();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonErrorclear()
{
	g_eventManager->clearError();
}


void CModuleIntegrationTestDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Cancel()
{
	CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[0]);
	std::string IP = lms->getIP();
	std::string delimiter = ".";
	std::string token = IP.substr(0, IP.find(delimiter));

	// IP Address Update
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP1.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP2.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP3.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser1IP4.SetWindowText(CA2T(token.c_str()));
	m_editLaser1Port.SetWindowText(CA2T(std::to_string(lms->getPort()).c_str()));

	// Parameters Update
	m_editLaser1Res.SetWindowText(CA2T(std::to_string(lms->getAngleResolution()).c_str()));
	m_editLaser1Start.SetWindowText(CA2T(std::to_string(lms->getStartAngle()).c_str()));
	m_editLaser1End.SetWindowText(CA2T(std::to_string(lms->getEndAngle()).c_str()));
	m_checkLaser1UpsideDown.SetCheck(lms->getUpsideDown());
}


void CModuleIntegrationTestDlg::OnBnClickedButtonLaser1Apply()
{
	CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[0]);

	// Get IP & Port
	CString str[5];
	m_editLaser1IP1.GetWindowTextW(str[0]);
	m_editLaser1IP2.GetWindowTextW(str[1]);
	m_editLaser1IP3.GetWindowTextW(str[2]);
	m_editLaser1IP4.GetWindowTextW(str[3]);
	m_editLaser1Port.GetWindowTextW(str[4]);

	std::string ip;
	unsigned int port;
	for (int i = 0; i < 4; i++) {
		ip.append((CStringA)str[i]);
		if (i < 3) ip.append(".");
	}
	port = _ttoi(str[4]);

	lms->setIP(ip);
	lms->setPort(port);

	CString s;
	m_editLaser1Res.GetWindowTextW(s);
	lms->setAngleResolution(_ttoi(s));
	m_editLaser1Start.GetWindowTextW(s);
	lms->setStartAngle(_ttoi(s));
	m_editLaser1End.GetWindowTextW(s);
	lms->setEndAngle(_ttoi(s));
	lms->setUpsideDown(m_checkLaser1UpsideDown.GetCheck());

	UpdateUI();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Cancel()
{

	CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[1]);
	std::string IP = lms->getIP();
	std::string delimiter = ".";
	std::string token = IP.substr(0, IP.find(delimiter));

	// IP Address Update
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP1.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP2.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP3.SetWindowText(CA2T(token.c_str()));
	token = IP.substr(0, IP.find(delimiter));
	IP = IP.substr(IP.find(delimiter) + 1, IP.size());
	m_editLaser2IP4.SetWindowText(CA2T(token.c_str()));
	m_editLaser2Port.SetWindowText(CA2T(std::to_string(lms->getPort()).c_str()));

	// Parameters Update
	m_editLaser2Res.SetWindowText(CA2T(std::to_string(lms->getAngleResolution()).c_str()));
	m_editLaser2Start.SetWindowText(CA2T(std::to_string(lms->getStartAngle()).c_str()));
	m_editLaser2End.SetWindowText(CA2T(std::to_string(lms->getEndAngle()).c_str()));
	m_checkLaser2UpsideDown.SetCheck(lms->getUpsideDown());
	lms->setUpsideDown(m_checkLaser2UpsideDown.GetCheck());
}



void CModuleIntegrationTestDlg::OnBnClickedButtonLaser2Apply()
{
	CSICKLaserScanner* lms = dynamic_cast<CSICKLaserScanner*>(m_sensor[1]);

	// Get IP & Port
	CString str[5];
	m_editLaser1IP1.GetWindowTextW(str[0]);
	m_editLaser1IP2.GetWindowTextW(str[1]);
	m_editLaser1IP3.GetWindowTextW(str[2]);
	m_editLaser1IP4.GetWindowTextW(str[3]);
	m_editLaser1Port.GetWindowTextW(str[4]);

	std::string ip;
	unsigned int port;
	for (int i = 0; i < 4; i++) {
		ip.append((CStringA)str[i]);
		if (i < 3) ip.append(".");
	}
	port = _ttoi(str[4]);

	lms->setIP(ip);
	lms->setPort(port);

	CString s;
	m_editLaser2Res.GetWindowTextW(s);
	lms->setAngleResolution(_ttoi(s));
	m_editLaser2Start.GetWindowTextW(s);
	lms->setStartAngle(_ttoi(s));
	m_editLaser2End.GetWindowTextW(s);
	lms->setEndAngle(_ttoi(s));
	lms->setUpsideDown(m_checkLaser2UpsideDown.GetCheck());

	UpdateUI();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionConnect()
{
	m_sensor[4]->Connect();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionReset()
{
	m_sensor[4]->Reset();
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionApply()
{
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);

}

void CModuleIntegrationTestDlg::OnBnClickedButtonMotionCancel()
{
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	//m_editMotionSpeed.SetWindowText(CA2T(std::to_string(motion->get()).c_str()));
	//m_editMotionAccel.SetWindowText(CA2T(std::to_string(motion->get()).c_str()));
	//m_editMotionDecel.SetWindowText(CA2T(std::to_string(motion->getEndAngle()).c_str()));
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionMove()
{
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	int iAccPattern;
	double dSpeed = 0;
	double dGearRatio = 1.0;
	double dWheelRadius = 125;
	double dEncoderResolution = 6000;
	double dPulse[3] = { 0.0 };
	long lAxis[2] = { 0L };
	double dDistList[2] = { 0.0 };

	CString strSpeed, strPattern, strAccel, strDecel, strDistance;
	m_editMotionSpeed.GetWindowTextW(strSpeed);// pulse/sec

	m_editMotionAccel.GetWindowTextW(strAccel);
	m_editMotionDecel.GetWindowTextW(strDecel);

	motion->SetServoOnOff(LEFT_DRIVE_MOTOR, true);
	motion->SetServoOnOff(RIGHT_DRIVE_MOTOR, true);
	//cmmCfgSetSpeedPattern(LEFT_DRIVE_MOTOR, iAccPattern - 1, _ttof(strSpeed), _ttof(strAccel), _ttof(strDecel));
	//cmmCfgSetSpeedPattern(RIGHT_DRIVE_MOTOR, iAccPattern - 1, _ttof(strSpeed), _ttof(strAccel), _ttof(strDecel));

	motion->SetMotionSpeed(cmSMODE_C, _ttof(strSpeed), _ttof(strSpeed));
}


void CModuleIntegrationTestDlg::OnBnClickedButtonObstacle()
{
	CString str;
	m_editObstacle.GetWindowTextW(str);
	m_AMRController->setObstacleRange(_ttoi(str));
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionServoOn()
{
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	motion->SetServoOnOff(LEFT_DRIVE_MOTOR, true);
	motion->SetServoOnOff(RIGHT_DRIVE_MOTOR, true);
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionServoOff()
{
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	motion->SetServoOnOff(LEFT_DRIVE_MOTOR, false);
	motion->SetServoOnOff(RIGHT_DRIVE_MOTOR, false);
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionEstop()
{
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	motion->MotionStop(true, LEFT_DRIVE_MOTOR, cmFALSE, cmFALSE);
	motion->MotionStop(true, RIGHT_DRIVE_MOTOR, cmFALSE, cmFALSE);
}


void CModuleIntegrationTestDlg::OnBnClickedButtonMotionStop()
{
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	motion->MotionStop(false, LEFT_DRIVE_MOTOR, cmFALSE, cmFALSE);
	motion->MotionStop(false, RIGHT_DRIVE_MOTOR, cmFALSE, cmFALSE);
}



void CModuleIntegrationTestDlg::OnBnClickedButtonDrive()
{
	double dGearRatio = 1.0;
	double dWheelRadius = 125;
	double dEncoderResolution = 6000;

	CString dist;
	m_editDrive.GetWindowTextW(dist);
	
	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	motion->ResetPosition(LEFT_DRIVE_MOTOR);
	motion->ResetPosition(RIGHT_DRIVE_MOTOR);
	int pulse = (_ttof(dist) * dGearRatio * dEncoderResolution) / (2 * PI * dWheelRadius);
	bool dir = pulse > 0 ? true : false;
	
	CString strSpeed, strPattern, strAccel, strDecel, strDistance;
	m_editMotionSpeed.GetWindowTextW(strSpeed);// pulse/sec
	if (dir)
		motion->SetMotionSpeed(cmSMODE_C, _ttof(strSpeed), _ttof(strSpeed));
	else
		motion->SetMotionSpeed(cmSMODE_C, -_ttof(strSpeed), -_ttof(strSpeed));

	while (true) {
		if (dir) {
			if (motion->getEncoder(LEFT_DRIVE_MOTOR) > pulse || motion->getEncoder(RIGHT_DRIVE_MOTOR) < -pulse) {
				motion->MotionStop(true, LEFT_DRIVE_MOTOR, 0, 0);
				motion->MotionStop(true, RIGHT_DRIVE_MOTOR, 0, 0);
				break;
			}
		}
		else {
			if (motion->getEncoder(LEFT_DRIVE_MOTOR) < pulse || motion->getEncoder(RIGHT_DRIVE_MOTOR) > -pulse) {
				motion->MotionStop(true, LEFT_DRIVE_MOTOR, 0, 0);
				motion->MotionStop(true, RIGHT_DRIVE_MOTOR, 0, 0);
				break;
			}
		}
	}
}


void CModuleIntegrationTestDlg::OnBnClickedButtonRotate()
{
	CString angle, strSpeed;
	m_editRotation.GetWindowTextW(angle);
	m_editMotionSpeed.GetWindowTextW(strSpeed);

	CComizoaMotionController* motion = dynamic_cast<CComizoaMotionController*>(m_sensor[4]);
	if (_ttof(strSpeed) > 0) {
		motion->SetMotionSpeed(cmSMODE_C, -_ttof(strSpeed), _ttof(strSpeed));
	}
	else {
		motion->SetMotionSpeed(cmSMODE_C, _ttof(strSpeed), -_ttof(strSpeed));
	}
}
