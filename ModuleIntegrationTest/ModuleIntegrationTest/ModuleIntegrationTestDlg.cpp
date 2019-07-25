
// ModuleIntegrationTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ModuleIntegrationTest.h"
#include "ModuleIntegrationTestDlg.h"
#include "afxdialogex.h"

#include "sensor\SICKLaserScanner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace sensor;
using namespace eventManager;
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

	// LMS 2, Gyro 1, Cancard 1, Motion 1, ComizoaIO 1
	m_sensor = new sensor::CSensorModule *[6];
	m_sensor[0] = new CSICKLaserScanner("LMS_Front", LMS1xx, "192.168.1.161", 2111, false);
	m_sensor[1] = new CSICKLaserScanner("LMS_Rear", LMS1xx, "192.168.0.1", 2111, false);

	UpdateUI();

	SetTimer(1, 100, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CModuleIntegrationTestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//for (int i = 0; i < 8; i++)
	delete m_sensor[0];
	g_eventManager->PushTask(MSG_INFO, "", INFO_PROGRAM_TERMINATED, true, false);
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
		int step = lms->getResolDeg();
		for (int i = 0; i < col; i++) {
			long dist = m_LaserData1.dist[i*step];
			m_listLaserScanData.SetItem(nIndex, i + 1, LVIF_TEXT, CA2CT(std::to_string(dist).c_str()), 0, 0, 0, NULL);
		}
	}
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
