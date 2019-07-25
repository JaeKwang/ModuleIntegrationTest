/*******************************************************************************
* [ ceSDKdef.h ]
* Header file for definitions of constants and data in ceSDK library
* - Update Date: 2008/03/26
* - Provider: COMIZOA Co., Ltd.
* - Phone: +82-42-936-6500~6
* - Fax  : +82-42-936-6507
* - URL  : http://www.comizoa.co.kr,  http://www.comizoa.com
********************************************************************************/

#ifndef __CESDK_DEF_H__
#define __CESDK_DEF_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DESCRIPTION_STRING				"COMIZOA Ethernet/IP Software Development Kit"

//////////////////////////////////////////////////////////////////////////
// General Defines
//////////////////////////////////////////////////////////////////////////
#define CE_TRUE	1
#define CE_FALSE 0

//////////////////////////////////////////////////////////////////////////
// cnGnResetNode
//////////////////////////////////////////////////////////////////////////
#define CE_RESET_DIO			0x00000001
#define CE_RESET_MOTION			0x00000002
#define CE_RESET_AIO			0x00000004
#define CE_RESET_ALL			CE_RESET_DIO | CE_RESET_MOTION | CE_RESET_AIO
#define CE_RESET_CFG_RESTORE	0x00010000

//////////////////////////////////////////////////////////////////////////
// General Error Codes
//////////////////////////////////////////////////////////////////////////
#define ceERR_NONE							   0
#define ceERR_INVALID_PARAMETER				-100

#define ceGnERR_TIMEOUT                     -101 // communication timeout error
#define ceGnERR_INVALID_PACKET              -102 // Packet data error
#define ceGnERR_CHECKSUM                    -103 // checksum mismatch
#define ceGnERR_FLASH_ERASE_FAIL            -104 // fali to erase flash-memory
#define ceGnERR_UNDEFINE_COMMAND            -105 // Undefined control command has been received

//////////////////////////////////////////////////////////////////////////
// Motion API Error Codes
//////////////////////////////////////////////////////////////////////////
#define cemERR_MEM_ALLOC_FAIL  -290 // Memory allocation fail
#define cemERR_GLOBAL_MEM_FAIL  -292 // Global memory allocation fail
#define cemERR_ISR_CONNEC_FAIL   -310 // ISR registration fail
#define cemERR_DIVIDE_BY_ZERO  -400 // Cause divide by zero error 
#define cemERR_WORNG_NUM_DATA  -500 // Number of data is too small or too big
#define cemERR_VER_MISMATCH   -600  // Version(of file or device) mismatch

#define cemERR_INVALID_DEVICE_ID  -1010 // Invalid device id => Load Device 또는 SetDeviceId()에서...
#define cemERR_INVALID_HANDLE  -1020
#define cemERR_UNSUPORTED_FUNC  -1030 
#define cemERR_INVALID_PARAMETER  -1101
#define cemERR_INVALID_CHANNEL  -1105
#define cemERR_INVALID_INPUT_RANGE -1111 // Invalid range value (AI, AO)
#define cemERR_INVALID_FREQ_RANGE -1121 // Invalid input or output frequency
#define cemERR_FILE_CREATE_FAIL  -1501 // File create fail 
#define cemERR_FILE_OPEN_FAIL  -1511 // File open fail
#define cemERR_FILE_READ_FAIL  -1522 // File reading fail
#define cemERR_EVENT_CREATE_FAIL  -1550 // Event handle creation fail   
#define cemERR_INT_INSTANCE_FAIL  -1560 // Interrupt event instance creation fail
#define cemERR_DITHREAD_CRE   -1570 // D/I state change monitor thread creation fail
#define cemERR_BUFFER_SMALL   -1580 // Buffer size is too small
#define cemERR_HIGH_TIMER_UNSUPP  -1590 // The installed hardware does not support a high-resolution performance counter (cemmUtlDelayMicroSec() function fails)
#define cemERR_OUT_OF_RANGE   -1600 // The range of some parameter is out of range

#define cemERR_ON_MOTION    -5001
#define cemERR_STOP_BY_SLP   -5002 // Abnormally stopped by positive soft limit
#define cemERR_STOP_BY_SLN   -5003 // Abnormally stopped by negative soft limit
#define cemERR_STOP_BY_CMP3   -5004 // Abnormally stopped by comparator3
#define cemERR_STOP_BY_CMP4   -5005 // Abnormally stopped by comparator4
#define cemERR_STOP_BY_CMP5   -5006 // Abnormally stopped by comparator5
#define cemERR_STOP_BY_ELP   -5007 // Abnormally stopped by (+) external limit
#define cemERR_STOP_BY_ELN   -5008 // Abnormally stopped by (-) external limit
#define cemERR_STOP_BY_ALM   -5009 // Abnormally stopped by alarm input signal
#define cemERR_STOP_BY_CSTP   -5010 // Abnormally stopped by CSTP input signal
#define cemERR_STOP_BY_CEMG   -5011 // Abnormally stopped by CEMG input signal
#define cemERR_STOP_BY_SD   -5012 // Abnormally stopped by SD input signal
#define cemERR_STOP_BY_DERROR  -5013 // Abnormally stopped by operation data error
#define cemERR_STOP_BY_IP   -5014 // Abnormally stopped by other axis error during interpolation
#define cemERR_STOP_BY_PO   -5015 // An overflow occurred in the PA/PB input buffer
#define cemERR_STOP_BY_AO   -5016 // Out of range position counter during interpolation
#define cemERR_STOP_BY_EE   -5017 // An EA/EB input error occurred (does not stop)
#define cemERR_STOP_BY_PE   -5018 // An PA/PB input error occurred (does not stop)
#define cemERR_STOP_BY_SLVERR  -5019 // Abnormally stopped because slave axis has been stopped
#define cemERR_STOP_BY_SEMG   -5020 // Abnormally stopped by software emergency setting

#define cemERR_MOT_MAOMODE			-5110 // Master output mode is not CW/CCW mode // Master/Slave 동작시에 Master output모드가 CW/CCW모드가 아니다.
#define cemERR_MOT_SLAVE_SET			-5120 // Slave start fail (Motion state가 "Wait for Pulsar Input"으로 변하지 않는다.
#define cemERR_SPEED_RANGE_OVER		-5130 // 
#define cemERR_INVALID_SPEED_SET		-5140 // Speed setting value is not valid
#define cemERR_ACC_LOW_LIMIT_OVER	-5142 // Acceleration setting value is too low
#define cemERR_ACC_HIGH_LIMIT_OVER	-5143 // Acceleration setting value is too high
#define cemERR_DEC_LOW_LIMIT_OVER	-5144 // Deceleration setting value is too low
#define cemERR_DEC_HIGH_LIMIT_OVER	-5145 // Deceleration setting value is too high
#define cemERR_INVALID_IXMAP			-5150 // Invalid interpolation map
#define cemERR_INVALID_LMMAP			-5160 // Invalid List-Motion Map 
#define cemERR_MOT_SEQ_SKIPPED		-5170 // Motion command is skipped because the axis is already running.  

//////////////////////////////////////////////////////////////////////////
// Process Boost Mode & Level
//////////////////////////////////////////////////////////////////////////

// MODE
#define CE_PROCESS_ONLY_BOOST	0
#define CE_SERVICE_ONLY_BOOST	1
#define CE_ALL_BOOST			2

// LEVEL
#define	CE_ABOVE_NORMAL_PRIORITY_CLASS		0x00008000
#define	CE_BELOW_NORMAL_PRIORITY_CLASS		0x00004000
#define	CE_HIGH_PRIORITY_CLASS				0x00000080
#define	CE_IDLE_PRIORITY_CLASS				0x00000040
#define	CE_NORMAL_PRIORITY_CLASS			0x00000020
#define	CE_PROCESS_MODE_BACKGROUND_BEGIN	0x00100000
#define	CE_PROCESS_MODE_BACKGROUND_END		0x00200000
#define	CE_REALTIME_PRIORITY_CLASS			0x00000100

//////////////////////////////////////////////////////////////////////////
// ceSDK Type Definition
//////////////////////////////////////////////////////////////////////////
typedef double *PDOUBLE;
typedef double DOUBLE;
typedef long   LONG;
typedef long   *PLONG;

//////////////////////////////////////////////////////////////////////////
// API Argument or Value Definition

// Motion I/O Property ID //
// MIO Property ID //
typedef enum _TCemMioPropId{
	cemALM_LOGIC, cemALM_MODE, cemCMP_LOGIC, cemDR_LOGIC, cemEL_LOGIC, cemEL_MODE, 
	cemERC_LOGIC, cemERC_OUT, cemEZ_LOGIC, cemINP_EN, cemINP_LOGIC, cemLTC_LOGIC, 
	cemLTC_LTC2SRC, cemORG_LOGIC, cemSD_EN, cemSD_LOGIC, cemSD_LATCH, cemSD_MODE, cemSTA_MODE,
	cemSTA_TRG, cemSTP_MODE, cemCLR_CNTR, cemCLR_SIGTYPE, cemCMP_PWIDTH, cemERC_ONTIME, cemSVON_LOGIC,
}TCemMioPropId;

typedef enum _TCemMioPropIdEx{
	cemMPID_ALM_LOGIC,	cemMPID_ALM_MODE,	cemMPID_CMP_LOGIC,	cemMPID_DR_LOGIC,	cemMPID_EL_LOGIC,	cemMPID_EL_MODE, 
	cemMPID_ERC_LOGIC,	cemMPID_ERC_OUT,		cemMPID_EZ_LOGIC,	cemMPID_INP_EN,		cemMPID_INP_LOGIC,	cemMPID_LTC_LOGIC, 
	cemMPID_LTC_LTC2SRC,	cemMPID_ORG_LOGIC,	cemMPID_SD_EN,		cemMPID_SD_LOGIC,	cemMPID_SD_LATCH,	cemMPID_SD_MODE, 
	cemMPID_STA_MODE,	cemMPID_STA_TRG,		cemMPID_STP_MODE,	cemMPID_CLR_CNTR,	cemMPID_CLR_SIGTYPE,	cemMPID_CMP_PWIDTH, 
	cemMPID_ERC_ONTIME,	cemMPID_SVON_LOGIC,	cemMPID_ERC_OUT_EL,	cemMPID_CNT_D_SRC,	cemMPID_CNT_G_SRC,	cemMPID_LTC_TRGMODE,
	cemMPID_SLIM_EN=100,	cemMPID_OUT_MODE,	cemMPID_IN_MODE,		cemMPID_IN_INV,		cemMPID_CEMG_EN
}TCemMioPropIdEx;

// Bit order of StReadMioStatuses() return value  //
typedef enum _TCemMioState{
	cemIOST_RDY, cemIOST_ALM,	  cemIOST_ELN,  cemIOST_ELP, cemIOST_ORG, 
	cemIOST_DIR, cemIOST_EZ,	  cemIOST_LTC,  cemIOST_SD,  cemIOST_INP, 
	cemIOST_DRN, cemIOST_DRP,	  cemIOST_STA,  cemIOST_STP, cemIOST_ALMR,
	cemIOST_EMG, cemIOST_SVON,  cemIOST_HOMS, cemIOST_PLSA
}TCemMioState;

// Motion operation status ID //
typedef enum _TCemMotionState{ 
	cemMST_STOP,			cemMST_WAIT_DR,	cemMST_WAIT_STA,		cemMST_WAIT_INSYNC,	cemMST_WAIT_OTHER, 
	cemMST_WAIT_ERC,		cemMST_WAIT_DIR, cemMST_RESERVED1,	cemMST_WAIT_PLSR,	cemMST_IN_RVSSPD, 
	cemMST_IN_INISPD,		cemMST_IN_ACC,	cemMST_IN_WORKSPD,	cemMST_IN_DEC,		cemMST_WAIT_INP, 
	cemMST_SPARE0,			cemMST_HOMMING,
}TCemMotionState;

// Signal logic definition //
typedef enum _TCemSigLogic{ 
	cemLOGIC_A=0 /*Normal open*/, cemLOGIC_B=1/*Normal close*/ 
}TCemSigLogic;

// Axis index definition //
typedef enum _TCemAxis{ 
	cemX1, cemY1, cemZ1, cemU1, cemX2, cemY2, cemZ2, cemU2 
}TCemAxis;

// Definition for axes mask  //
typedef enum _TCemAxisMask{ 
	cemX1_MASK=0x1, cemY1_MASK=0x2, cemZ1_MASK=0x4, cemU1_MASK=0x8,
	cemX2_MASK=0x10, cemY2_MASK=0x20, cemZ2_MASK=0x40, cemU2_MASK=0x80
}TCemAxisMask;

// Encoder and PA/PB input mode definition //
typedef enum _TCemInMode{ 
	cemIMODE_AB1X, cemIMODE_AB2X, cemIMODE_AB4X, cemIMODE_CWCCW, cemIMODE_STEP
}TCemInMode;

// Command output mode definition //
typedef enum _TCemOutMode{ 
	cemOMODE_PDIR0, cemOMODE_PDIR1, cemOMODE_PDIR2, cemOMODE_PDIR3,
	cemOMODE_CWCCW0, cemOMODE_CWCCW1, cemOMODE_CCWCW0, cemOMODE_CCWCW1
}TCemOutMode;

// Control Mode //
typedef enum _TCemCtrlMode{ 
	cemCTRL_OPEN, // Open loop control mode
	cemCTRL_SEMI_C, // Semi-closed loop control mode (applied only to absolute in-position commands)
	cemCTRL_FULL_C // Full-closed loop control mode (this is not supported at current version)
}TCemCtrlMode;

// (Linear)Operation direction //	
typedef enum _TCemDir{
	cemDIR_N /*(-)Dir*/, cemDIR_P /*(+)Dir*/
}TCemDir;

// Counter name //
typedef enum _TCemCntr { 
	cemCNT_COMM/*Command*/, cemCNT_FEED/*Feedback*/, cemCNT_DEV/*Deviation*/, 
	cemCNT_GEN/*General*/, cemCNT_REM/*Remained*/
}TCemCntr;

// Speed mode index definition //	
typedef enum _TCemSpeedMode{ 
	cemSMODE_KEEP=-1/* Keep previous setting*/, cemSMODE_C=0 /*Constant */, cemSMODE_T /*Trapeziodal*/, cemSMODE_S /*S-curve*/
}TCemSpeedMode;

// Arc operation direction //
typedef enum _TCemArcDir{ 
	cemARC_CW, cemARC_CCW
}TCemArcDir;

// Compare Method //
typedef enum _TCemCmpMethod{
	cemDISABLE, cemEQ_BIDIR, cemEQ_PDIR, cemEQ_NDIR, cemLESS/*Cnt<Data*/, cemGREATER/*Cnt>Data*/
}TCemCmpMethod;

// Action when general comparator met the condition //
typedef enum _TCemCmpAction{
	cemEVNT_ONLY, cemEVNT_IS, cemEVNT_DS, cemEVNT_SPDCHG
}TCemCmpAction;

// Backlash/Slip correction mode //
typedef enum _TCemCorrMode{
	cemCORR_DIS, // Disable correction 
	cemCORR_BACK, // Backlash correction mode 
	cemCORR_SLIP // Slip correction mode
}TCemCorrMode;

// Using for preregister option
typedef enum _TCemExtOptionId{
	cemEXOPT_SET_USE_PREREG
}TCemExtOptionId;

// Interrupt Handler Type //
typedef enum _TCemIntHandlerType{
	cemIHT_MESSAGE=0, cemIHT_EVENT, cemIHT_CALLBACK
}TCemIntHandlerType;

// Interrupt Handler Type //
typedef enum _TCemStringID{
	cemSTR_AXIS_NAME, cemSTR_DIST_UNIT, cemSTR_SPEED_UNIT
}TCemStringID;

// Sequence Mode //
typedef enum _TCemSeqMode{
	cemSEQM_SKIP_RUN, cemSEQM_WAIT_RUN
}TCemSeqMode;

// Map Type //
typedef enum _TCemDevMapType{
	cemDMAP_MOTION, cemDMAP_DIO, cemDMAP_ALL
}TCemDevMapType;

// SetFilterAB의 대상 //
typedef enum _TCemABFilter{
	cemAB_ENC, cemAB_PULSAR
}TCemABFilter;

// Axis Capability ID //
typedef enum _TCemAxisCapID{
	cemCAPX_CMD_DIR=0, /* Command direction change function */
	cemCAPX_EL_MAN_SET, /* -/+EL Manual control function */
	cemCAPX_CMP_HIGH /* High-speed Compare Output function */
}TCemAxisCapID;

// Axis Return to home clear mode //
typedef enum _TCemHomePosClrMode{
	cemHPCM_DISABLE=-1, // Disable HomePosClearMode
	cemHPCM_M0, // ORG(/EL/EZ) 신호가 발생할 때 COMMAND & FEEDBACK 위치를 0으로 클리어한다.
	cemHPCM_M1, // 원점복귀를 모두 완료하고 나서 COMMAND & FEEDBACK 위치를 모두 0으로 클리어한다.
	cemHPCM_M2  // 원점복귀를 모두 완료하고 나서 FEEDBACK 위치는 그대로 두고 COMMAND 위치를 FEEDBACK 위치에 일치시킨다.
}TCemHomePosClrMode;

typedef enum _TCemLatchTrgMode{
	cemLTM_LTC, // LTC 입력 신호에 의해서 포지션 래치가 수행됩니다.
	cemLTM_ORG  // ORG 입력 신호에 의해서 포지션 래치가 수행됩니다.
}TCemLatchTrgMode;

// Sync mode //
typedef enum _TCemSyncMode{
	cemSYNC_DISABLE,
	cemSYNC_INT_SYNC,
	cemSYNC_OTHER_STOP
}TCemSyncMode;

// Internal sync. conditions //
typedef enum _TCemIntSyncCond{
	cemISYNC_ACC_STA, // 0: at start of acceleration
	cemISYNC_ACC_END, // 1: at end of acceleration
	cemISYNC_DEC_STA, // 2: at start of deceleration
	cemISYNC_DEC_END, // 3: at end of deceleration
	cemISYNC_SLN, // 4: when (-)software limit met
	cemISYNC_SLP, // 5: when (+)software limit met
	cemISYNC_GCMP, // 6: when General Comparator condition is satisfied
	cemISYNC_TCMP // 7: when Trigger Comparator condition is satisfied
}TCemIntSyncCond;

// DIO Mode //
typedef enum _TCemDioMode{
	cemDIOMODE_IN /*Input Mode*/, cemDIOMODE_OUT /*Output Mode*/
}TCemDioMode;              

typedef enum _TCemLmStopMode{
 cemLM_ESTOP,
 cemLM_DSTOP,
 cemLM_CSTOP
}TCemLmStopMode;
typedef enum _TCemLmQueMode{
 cemLM_QUENCLEAR,
 cemLM_QUECLEAR
}TCemLmQueMode;

//////////////////////////////////////////////////////////////////////////
// Basic Node Information 
//////////////////////////////////////////////////////////////////////////
#define MAX_NODE				255
#define MAX_MOT_MODULE			10
#define MAX_DIO_MODULE			10
#define MAX_AI_MODULE			10
#define MAX_AO_MODULE			10
#define MAX_MDIO_MODULE			10
#define MAX_CNT_MODULE			10
#define MAX_CNET_MODULE         32
#define MAX_CNETMASTER_MODULE   1

//////////////////////////////////////////////////////////////////////////
// Sub Module Type Information 
//////////////////////////////////////////////////////////////////////////
#define MODULE_DI32_ONLY_TYPE  0x0	// DI 32ch 
#define MODULE_DO32_ONLY_TYPE  0x1  // DO 32ch
#define MODULE_MOT_TYPE        0x2
#define MODULE_AI_TYPE         0x3
#define MODULE_AO_TYPE         0x4
#define MODULE_DIO_TYPE		   0x5	// DIO bidirectional 16ch
#define MODULE_CNT_TYPE		   0x6
#define MODULE_SER_TYPE	   0x7
#define MODULE_MDIO_TYPE	   0x8

typedef struct __tagMotModule
{
	LONG nMotChannelCount;
	LONG nModuleType;
	LONG nModuleNumber;
} TMotModule, *PTMotModule;

typedef struct __tagDIOModule
{
	LONG nChannelCount;
	LONG nModuleType;
	LONG nModuleNumber;
} TDIOModule, *PTDIOModule;

typedef struct __tagAIModule
{
	LONG nChannelCount;
	LONG nModuleType;
	LONG nModuleNumber;
} TAIModule, *PTAIModule;

typedef struct __tagAOModule
{
	LONG nChannelCount;
	LONG nModuleType;
	LONG nModuleNumber;
} TAOModule, *PTAOModule;

typedef struct __tagMDIOModule
{
	LONG nChannelCount;
	LONG nModuleType;
	LONG nModuleNumber;
} TMDIOModule, *PTMDIOModule;

typedef struct __tagCNTModule
{
	LONG nChannelCount;
	LONG nModuleType;
	LONG nModuleNumber;
} TCNTModule, *PTCNTModule;

typedef struct
{
    long nChannelCount;
    long nModuleType;
    long nModuleNumber;
} TCNETModule;

typedef struct 
{
    long nTotalCNetModule;
	long nModuleNumber;
    TCNETModule CNetModule[MAX_CNET_MODULE];
} TCNETMasterModule, *PTCNETMasterModule;

typedef struct __tagNode
{
	LONG ID;
	LONG IpAddress;
	LONG UDPPort;
	LONG TCPPort;

	LONG TotalDIOModule;
	LONG TotalMotModule;
	LONG TotalAIModule;
	LONG TotalAOModule;
	LONG TotalMDIOModule;	
	LONG TotalCNTModule;

	TDIOModule  DIOModule[MAX_DIO_MODULE];
	TMotModule  MotModule[MAX_MOT_MODULE];
	TAIModule   AIModule[MAX_AI_MODULE];
	TAOModule   AOModule[MAX_AO_MODULE];
	TMDIOModule	MDIOModule[MAX_MDIO_MODULE];	
	TCNTModule  CNTModule[MAX_CNT_MODULE];

	LONG TotalCNETMasterModule;
    TCNETMasterModule   CNETMasterModule[MAX_CNETMASTER_MODULE];
} TNode, *PTNode, TCneConfigNodeEx, *PTCneConfigNodeEx;

typedef struct __tagAllNodeInformation
{
	LONG TotalNodeCount;
	TNode Node[MAX_NODE];
} TNodeInformation, *PTNodeInformation;

//////////////////////////////////////////////////////////////////////////
// Configuration I/O [cnBuilder] 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 환경설정 데이터 저장 순서 
//  1. [TCneHeader] 구조체 저장
//  2. [TCneAxis] x [TCneHeader::nNumAxis] 저장 
//  3. [TCneDio32] x [TCneHeader::nNumDioChan/32+1] 저장. 

typedef struct  
{

	//////////////////////////////////////////////////////////////////////////
	// UnitDist/UnitSpeed
	//////////////////////////////////////////////////////////////////////////
	DOUBLE fUnitDist;
	DOUBLE fUnitSpeed;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// In/Out Ratio
	//////////////////////////////////////////////////////////////////////////
	DOUBLE fInOutRatio;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Actual Speed Check
	//////////////////////////////////////////////////////////////////////////
	BOOL   nActSpdCheckEnable;
	LONG   nActSpdCheckInterval;
	//////////////////////////////////////////////////////////////////////////

} TCneLibAxis, *PTCneLibAxis;

typedef struct{
	// B0 ~ B3 //
	unsigned int AlmLogic:	1; // 0-N/O(A),  1-N/C(B)
	unsigned int AlmMode :	1; // 0-Immediate stop, 1-Decel. stop
	unsigned int ElLogic:		1; // 0-N/O(A),  1-N/C(B)
	unsigned int ElMode:		1; // 0-Immediate stop, 1-Decel. stop
	// B4 ~ B7 //
	unsigned int InpLogic:	1; // 0-N/O(A),  1-N/C(B)
	unsigned int InpEnable:	1; // 1-Enable INP
	unsigned int SvonLogic:	1; // 0-N/O(A),  1-N/C(B)
	unsigned int OrgLogic:	1; // 0-N/O(A),  1-N/C(B)
	// B8 ~ B11 //
	unsigned int EzLogic:		1; // 0-N/O(A),  1-N/C(B)
	unsigned int ErcLogic:	1; // 0-N/O(A),  1-N/C(B) 
	unsigned int ErcAtHome:	1; // 원점복귀 완료시에 ERC출력을 낼 것인지?
	unsigned int ErcAtLimit:	1; // LIMIT 감지되었을 때 ERC출력을 낼 것인지?
	// B12 ~ B15 //	
	unsigned int LtcLogic:	1; // 0-N/O(A),  1-N/C(B)
	unsigned int LtcLtc2Src:	1; // 0-Deviation counter,  1-Command speed
	unsigned int CmpLogic:	1; // 0-N/O(A),  1-N/C(B)
	unsigned int DrLogic:		1; // 0-N/O(A),  1-N/C(B)
	// B16 ~ B19 //
	unsigned int SdLogic:		1; // 0-N/O(A),  1-N/C(B)
	unsigned int SdEnable:	1; // 1-Enable SD function
	unsigned int SdLatch:		1; // 1-Latch SD
	unsigned int SdMode:		1; // 0-Decel only,  1-Decel stop
	// B20 ~ B23 //
	unsigned int StaMode:		1; // 0-Immediate stop, 1-Decel. stop
	unsigned int StaTrgType:	1; // 0-Level trigger,  1-Edge trigger
	unsigned int StpMode:		2; // 0-Ignore, 1-Immediate stop, 2-Decel stop
	// B24 ~ B31//
	unsigned int Filter:		1; // 1-Enable general filter (EL, ALM, INP, DR,...)
	unsigned int FilterAB:	1; // 1-Enable A/B filter (EA/EB, PA/PB)
	unsigned int ElnManMode:	2; // -EL의 수동입력 모드: 0=>Sensor 입력 사용, 1=>강제 OFF, 2=>강제 ON
	unsigned int ElpManMode:	2; // +EL의 수동입력 모드: 0=>Sensor 입력 사용, 1=>강제 OFF, 2=>강제 ON
	unsigned int SimulMode:	1; // 1-Mask output pulse(실제 펄스 출력되지 않음)
	unsigned int SlEnable:	1; // 1-Enable software limit
}TCneAxisProp1;

typedef struct{
	unsigned int OutputMode:	4; // Pulse output mode
	unsigned int OutputInvDir:2; // Inverse output direction(this is for future, not supported currently)
	unsigned int InputMode:	4; // Pulse output mode
	unsigned int InputInvDir:	2; // Inverse output direction(this is for future, not supported currently)
	unsigned int Cnt3Src:		2; // Counter3(deflection)의 입력 소스 설정. 0=>command&feedback,  1=>command&PA/PB, 2=>EA/EB&PA/PB
	unsigned int Cnt4Src:		2; // Counter3(deflection)의 입력 소스 설정. 0=>command,   1=>Feedback,   2=>PA/PB
	unsigned int ClrCntrMask: 4; // b0-command, b1-feedback, b2-deflection, b3-general
	unsigned int ClrSigType:	2; // 0-F/E, 1-R/E,  2-L/L(A),  3-H/L(B)
	unsigned int BlcorrMode:	2; // Backlash correction mode: 0-disable, 1-Backlash correction,  2-Slip correction
	unsigned int BlcorrCntrM:	4; // Backlash correction시의 counter mask
	unsigned int Reserved:	4; // old is 4 
	unsigned int Reserved2:  32;
}TCneAxisProp2;

typedef struct{
	unsigned int CmpPulseWidth:	16;
	unsigned int ErcOnTime:		16;
}TCneAxisProp3;

typedef struct{
	unsigned int VMode:		2; // 작업속도모드: 0-constant,  1-trapezoidal,  2-scurve
	unsigned int HomeMode:	4; // 원점복귀모드: 0 ~ 12
	unsigned int HomeVMode:	2; // 원점복귀속도모드: 0-constant,  1-trapezoidal,  2-scurve
	unsigned int HomeClrMode:	2; // 원점위치클리어모드:
	unsigned int HomeDir:     1; // 원점 복귀 방향
	unsigned int Reserved:	21;
}TCneAxisProp4;

typedef struct{
	unsigned int dwReserved;
}TCneAxisProp5;


// Configuration structure for a motion axis //
typedef struct{
	unsigned int nMaxPPS;
	unsigned int nVel, nAcc, nDec;
	unsigned int nHomeEzCnt, nHomeEscDist;
	int  nHomeOfs;
	unsigned int nHomeVel, nHomeAcc, nHomeDec, nHomeSpecVel;
	unsigned int dwIntMask;
	TCneAxisProp1 Mio1; // 32 bit 구조체 
	TCneAxisProp2 Mio2; // 32 bit 구조체 
	TCneAxisProp3 Mio3; // 32 bit 구조체 
	TCneAxisProp4 Mio4; // 32 bit 구조체 
	TCneAxisProp5 Mio5; // 32 bit 구조체 

	// [V1.1] 추가 항목들  //
	int nSlRangeN, nSlRangeP;// soft limit range.
	int nIniVel;
	unsigned int dwReserved[7];
}TCneAxis, *PTCneAxis;

///////////////////////////////////////////////////////////////////////////////
// Configuration structure for 32 DIO channels 
// : 여기서의 채널 번호는 Input/Output으로 나뉘기 전의 채널번호를 의미한다.
typedef struct{
	unsigned int dwIoMode; // 32채널의 I/O mode: 비트별로 0-Input, 1-Output
	unsigned int dwIoLogic;
	unsigned int dwReserved[8]; // Reserved for future
}TCneDio32;


// Header for configuration for a node //
typedef struct{
	unsigned int Signature; // 0x50321234
	unsigned int Version; 
	unsigned int nNumAxes;
	unsigned int nNumDioChan;
	unsigned int nNumDiChan;			// Not use for this time. For Future
	unsigned int nNumDoChan;			// Not use for this time. For Future
	unsigned int dwReserved[20];
}TCneHeader;


#define MAX_AXES_COUNT	10
#define MAX_DIO_COUNT	10

typedef struct {

	//////////////////////////////////////////////////////////////////////////
	// Node Information
	//////////////////////////////////////////////////////////////////////////
	LONG NodeID;
	LONG NodeIP;
	LONG NodeActive;        /* TRUE : Active Node , FALSE : Non-Active Node */

	//////////////////////////////////////////////////////////////////////////
	// MOTION
	//////////////////////////////////////////////////////////////////////////
	DWORD nNumAxes;					// 모션 채널의 갯수
	TCneLibAxis LibAXIS[MAX_AXES_COUNT];
	TCneAxis    NdeAXIS[MAX_AXES_COUNT];

	//////////////////////////////////////////////////////////////////////////
	// DIO
	//////////////////////////////////////////////////////////////////////////
	DWORD nNumDioChan;				// 디지털 입출력 채널의 갯수
	TCneDio32 DIO[MAX_DIO_COUNT];

	//////////////////////////////////////////////////////////////////////////
	// AIO
	//////////////////////////////////////////////////////////////////////////
	DWORD nNumAioChan;
	DWORD nNumAiChan;
	DWORD nNumAoChan;
} TCneConfigNode, *PTCneConfigNode;

typedef struct{

	LONG Version;
	LONG NumNode;
	TCneConfigNode 	  Node[MAX_NODE];	
	TCneConfigNodeEx  NodeEx[MAX_NODE];

} TCneConfig, *PTCneConfig;


// ceSDK Log Level
//
// No logging at all                                    : LL_NONE	    0
// Log server startup/shutdown                          : LL_STATE	    0
// Log connect/disconnect                               : LL_CLIENTS	1
// Log connection errors (wrong pixfmt, etc)            : LL_CONNERR	0
// Log socket errors                                    : LL_SOCKERR	4
// Log internal errors                                  : LL_INTERR	    0
// Log internal warnings                                : LL_INTWARN    8
// Log internal info						            : LL_INTINFO	9
// Log socket errors                                    : LL_SOCKINFO	10
// Log everything, including internal table setup, etc. : LL_ALL		10

#define LL_NONE		0
#define LL_STATE	9
#define LL_CLIENTS	1
#define LL_CONNERR	0
#define	LL_SOCKERR	4
#define LL_INTERR	0
#define	LL_INTWARN	8
#define LL_INTINFO	9
#define LL_SOCKINFO	10

#define LL_GENERAL	4
#define LL_MOTION	5
#define LL_DIO		6
#define LL_AIO		6
#define LL_CNT		6
#define LL_SERIAL	7
#define LL_INTLOCK	8
#define LL_UTIL		8
#define LL_CNET     6

#define LL_ALL		10

typedef enum _TBaudRate {CE_BAUD_2400, CE_BAUD_4800, CE_BAUD_9600, CE_BAUD_14400, CE_BAUD_19200, CE_BAUD_38400, CE_BAUD_57600, CE_BAUD_115200} TBaudRate;
typedef enum _TCommProtocol {CE_COMM_RS232=3, CE_COMM_RS422, CE_COMM_RS485} TCommProtocol;
typedef enum _TParityBit {CE_PARITY_NONE, CE_PARITY_ODD, CE_PARITY_EVEN} TParityBit;

#endif
