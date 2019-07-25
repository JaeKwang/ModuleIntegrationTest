
// ModuleIntegrationTestDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "sensor\SensorModule.h"

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
	LaserScanData m_LaserData1;

	void UpdateUI();
	void UILaserScanDataUpdate(sensor::CSensorModule *, int);
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
};
