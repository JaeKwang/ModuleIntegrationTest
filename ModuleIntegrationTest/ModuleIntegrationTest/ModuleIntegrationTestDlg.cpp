
// ModuleIntegrationTestDlg.cpp : ���� ����
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
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CModuleIntegrationTestDlg ��ȭ ����



CModuleIntegrationTestDlg::CModuleIntegrationTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODULEINTEGRATIONTEST_DIALOG, pParent)
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
END_MESSAGE_MAP()


// CModuleIntegrationTestDlg �޽��� ó����

BOOL CModuleIntegrationTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// LMS 2, Gyro 1, Cancard 1, Motion 1, ComizoaIO 1
	m_sensor = new sensor::CSensorModule *[6];
	m_sensor[0] = new CSICKLaserScanner("LMS_Front", LMS1xx, "192.168.0.1", 2111, false);
	m_sensor[1] = new CSICKLaserScanner("LMS_Rear", LMS1xx, "192.168.0.1", 2111, false);

	UpdateUI();

	SetTimer(1, 100, NULL);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.


void CModuleIntegrationTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawDoubleBuffering();
		CDialogEx::OnPaint();
	}
}


// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC();
}


BOOL CModuleIntegrationTestDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return TRUE;
}


void CModuleIntegrationTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 1) {
		// UI Update
		switch (m_sensor[0]->getStatus()) {
		case STATE_INIT:
			m_editLaser1State.SetWindowTextW(_T("Init"));
			break;
		case STATE_PROGRESSING:
			m_editLaser1State.SetWindowTextW(_T("Prog"));
			break;
		case STATE_RUN:
			m_editLaser1State.SetWindowTextW(_T("Run"));
			break;
		case STATE_ERROR:
			m_editLaser1State.SetWindowTextW(_T("Error"));
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
	((CButton*)GetDlgItem(IDC_RADIO_LASER1_UPSIDEDOWN))->SetCheck(lms->getUpsideDown());
	for (int i = 0; i < m_listLaserScanData.GetItemCount(); i++) {
		m_listLaserScanData.DeleteColumn(i);
	}
	int col = int(lms->getEndAngle() - lms->getStartAngle());
	m_listLaserScanData.InsertColumn(0, _T("����"), LVCFMT_CENTER, 50, -1);
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
	m_sensor[0]->Connect();
}
