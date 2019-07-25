/*******************************************************************************
* [ ceSDK.cpp ]
* CPP file for definitions of constants and data in cnSDK library
* - Update Data: 2008/03/26
* - Provider: COMIZOA Co., Ltd.
* - Phone: +82-42-936-6500~6
* - Fax  : +82-42-936-6507
* - URL  : http://www.comizoa.co.kr,  http://www.comizoa.com
********************************************************************************/

#include "stdafx.h"

#if defined(__BCPLUSPLUS__)  // Borland C++ Builder specific
#include <vcl.h>
#pragma hdrstop
#endif

#include <windows.h>
#include <stdio.h>

#define _DLL_MAIN_CPP_
#include "ceSDK.h"

typedef struct{
	char *name;
	FARPROC* ptr;
}LIB_FUNCT;

//#if defined(UNICODE)
//
//	#error No unicode support in ceSDK
//
//#endif

static HINSTANCE hLibrary=NULL;
#define __DLL_FILE_FULL_PATH__ _T("ceSDKDLL.dll")

BOOL ceLoadDll(void)
{
	
	LIB_FUNCT Func[] = {
	
		//****************************************************************************
		//*************** START OF General FUNCTION DECLARATIONS *********************
		//****************************************************************************
		{"ceGnLoad", 			  (FARPROC*)&ceGnLoad},
		{"ceGnUnload", 			  (FARPROC*)&ceGnUnload},
		
		{"ceGnLogLevel_Set",	  (FARPROC*)&ceGnLogLevel_Set},
		{"ceGnLogLevel_Get",	  (FARPROC*)&ceGnLogLevel_Get},

		{"ceGnLogMode_Set",       (FARPROC*)&ceGnLogMode_Set},
		{"ceGnLogMode_Get",		  (FARPROC*)&ceGnLogMode_Get},

		{"ceGnReSearchDevice",	  (FARPROC*)&ceGnReSearchDevice},

		{"ceGnIsSearchedDevice",  (FARPROC*)&ceGnIsSearchedDevice},
		{"ceGnSearchDevice",	  (FARPROC*)&ceGnSearchDevice},
		{"ceGnUnSearchDevice",    (FARPROC*)&ceGnUnSearchDevice},

		{"ceGnTotalNode",         (FARPROC*)&ceGnTotalNode },

		{"ceGnTotalMotionChannel",(FARPROC*)&ceGnTotalMotionChannel},
		{"ceGnTotalDIOChannel",   (FARPROC*)&ceGnTotalDIOChannel},
		{"ceGnTotalAIChannel",    (FARPROC*)&ceGnTotalAIChannel},
		{"ceGnTotalAOChannel",    (FARPROC*)&ceGnTotalAOChannel},
		{"ceGnTotalMDIOChannel",   (FARPROC*)&ceGnTotalMDIOChannel},
		{"ceGnTotalCNTChannel",   (FARPROC*)&ceGnTotalCNTChannel},

		{"ceGnModuleCount_Motion",(FARPROC*)&ceGnModuleCount_Motion},
		{"ceGnModuleCount_Dio",   (FARPROC*)&ceGnModuleCount_Dio},
		{"ceGnModuleCount_Ai",    (FARPROC*)&ceGnModuleCount_Ai},
		{"ceGnModuleCount_Ao",    (FARPROC*)&ceGnModuleCount_Ao},
		{"ceGnModuleCount_Mdio",   (FARPROC*)&ceGnModuleCount_Mdio},
		{"ceGnModuleCount_Cnt",   (FARPROC*)&ceGnModuleCount_Cnt},

		{"ceGnChannelCount_Motion", (FARPROC*)&ceGnChannelCount_Motion},
		{"ceGnChannelCount_Dio",    (FARPROC*)&ceGnChannelCount_Dio},
		{"ceGnChannelCount_Ai",     (FARPROC*)&ceGnChannelCount_Ai},
		{"ceGnChannelCount_Ao",     (FARPROC*)&ceGnChannelCount_Ao},
		{"ceGnChannelCount_Mdio",    (FARPROC*)&ceGnChannelCount_Mdio},
		{"ceGnChannelCount_Cnt",    (FARPROC*)&ceGnChannelCount_Cnt},

		{"ceGnEmergency_Set",		(FARPROC*)&ceGnEmergency_Set},
		{"ceGnEmergency_Get",		(FARPROC*)&ceGnEmergency_Get},

		{"ceGnResetNode",		(FARPROC*)&ceGnResetNode},
		
		{"ceGnCtrlBoost_Set",	(FARPROC*)&ceGnCtrlBoost_Set},
		{"ceGnCtrlBoost_Get",	(FARPROC*)&ceGnCtrlBoost_Get},
	
		{"ceGnNodeIsActive",    (FARPROC*)&ceGnNodeIsActive},

		{"ceGnBeginSerialize",  (FARPROC*)&ceGnBeginSerialize},
		{"ceGnEndSerialize",    (FARPROC*)&ceGnEndSerialize},

		{"ceGnLocalAxis_Get",	(FARPROC*)&ceGnLocalAxis_Get},
		{"ceGnLocalDIO_Get",	(FARPROC*)&ceGnLocalDIO_Get},
		{"ceGnLocalAI_Get",		(FARPROC*)&ceGnLocalAI_Get},
		{"ceGnLocalAO_Get",		(FARPROC*)&ceGnLocalAO_Get},
		{"ceGnLocalMDIO_Get",    (FARPROC*)&ceGnLocalMDIO_Get},
		{"ceGnLocalCNT_Get",    (FARPROC*)&ceGnLocalCNT_Get},

		{"ceGnGlobalAxis_Get",  (FARPROC*)&ceGnGlobalAxis_Get},
		{"ceGnGlobalDIO_Get",   (FARPROC*)&ceGnGlobalDIO_Get},
		{"ceGnGlobalAI_Get",    (FARPROC*)&ceGnGlobalAI_Get},
		{"ceGnGlobalAO_Get",    (FARPROC*)&ceGnGlobalAO_Get},
		{"ceGnGlobalMDIO_Get",   (FARPROC*)&ceGnGlobalMDIO_Get},
		{"ceGnGlobalCNT_Get",   (FARPROC*)&ceGnGlobalCNT_Get},
		{"ceGnModuleTrType_Get",   (FARPROC*)&ceGnModuleTrType_Get},

		//****************************************************************************
		//*************** START OF GENERAL MOTION FUNCTION DECLARATIONS **************
		//****************************************************************************
		{"cemGnAlarmReset",		    (FARPROC*)&cemGnAlarmReset},
		{"cemGnServoOn_Set", 	    (FARPROC*)&cemGnServoOn_Set},
		{"cemGnServoOn_Get", 		(FARPROC*)&cemGnServoOn_Get},

		//****************************************************************************
		//*************** START OF CONFIGURATION FUNCTION DECLARATIONS ***************
		//****************************************************************************
		{"cemCfgMioProperty_Set", 	(FARPROC*)&cemCfgMioProperty_Set},
		{"cemCfgMioProperty_Get",   (FARPROC*)&cemCfgMioProperty_Get},
		{"cemCfgFilter_Set",		(FARPROC*)&cemCfgFilter_Set},
		{"cemCfgFilter_Get",		(FARPROC*)&cemCfgFilter_Get},
		{"cemCfgFilterAB_Set",		(FARPROC*)&cemCfgFilterAB_Set},
		{"cemCfgFilterAB_Get",		(FARPROC*)&cemCfgFilterAB_Get},
		{"cemCfgInMode_Set",		(FARPROC*)&cemCfgInMode_Set},
		{"cemCfgInMode_Get",		(FARPROC*)&cemCfgInMode_Get},
		{"cemCfgOutMode_Set",		(FARPROC*)&cemCfgOutMode_Set},
		{"cemCfgOutMode_Get",		(FARPROC*)&cemCfgOutMode_Get},  
		{"cemCfgCtrlMode_Set",		(FARPROC*)&cemCfgCtrlMode_Set},
		{"cemCfgCtrlMode_Get",		(FARPROC*)&cemCfgCtrlMode_Get},
		{"cemCfgInOutRatio_Set",	(FARPROC*)&cemCfgInOutRatio_Set},
		{"cemCfgInOutRatio_Get",	(FARPROC*)&cemCfgInOutRatio_Get},
		{"cemCfgUnitDist_Set",		(FARPROC*)&cemCfgUnitDist_Set},
		{"cemCfgUnitDist_Get",		(FARPROC*)&cemCfgUnitDist_Get},
		{"cemCfgUnitSpeed_Set",		(FARPROC*)&cemCfgUnitSpeed_Set},
		{"cemCfgUnitSpeed_Get",		(FARPROC*)&cemCfgUnitSpeed_Get},
		{"cemCfgSpeedRange_Set",	(FARPROC*)&cemCfgSpeedRange_Set},
		{"cemCfgSpeedRange_Get",	(FARPROC*)&cemCfgSpeedRange_Get},
		{"cemCfgSpeedPattern_Set",	(FARPROC*)&cemCfgSpeedPattern_Set},
		{"cemCfgSpeedPattern_Get",	(FARPROC*)&cemCfgSpeedPattern_Get},
		{"cemCfgSpeedPattern_T_Set",	(FARPROC*)&cemCfgSpeedPattern_T_Set},
		{"cemCfgSpeedPattern_T_Get",	(FARPROC*)&cemCfgSpeedPattern_T_Get},
		{"cemCfgActSpdCheck_Set",	(FARPROC*)&cemCfgActSpdCheck_Set},
		{"cemCfgActSpdCheck_Get",	(FARPROC*)&cemCfgActSpdCheck_Get},
		{"cemCfgSoftLimit_Set",		(FARPROC*)&cemCfgSoftLimit_Set},
		{"cemCfgSoftLimit_Get",		(FARPROC*)&cemCfgSoftLimit_Get},
		{"cemCfgRingCntr_Set",		(FARPROC*)&cemCfgRingCntr_Set},
		{"cemCfgRingCntr_Get",		(FARPROC*)&cemCfgRingCntr_Get},
		{"cemCfgVelCorrRatio_Set",	(FARPROC*)&cemCfgVelCorrRatio_Set},
		{"cemCfgVelCorrRatio_Get",	(FARPROC*)&cemCfgVelCorrRatio_Get},
		{"cemCfgSeqMode_Set",		(FARPROC*)&cemCfgSeqMode_Set},
		{"cemCfgSeqMode_Get",		(FARPROC*)&cemCfgSeqMode_Get},

		//{"cemCfgManExtLimit_Set",		(FARPROC*)&cemCfgManExtLimit_Set},
		//{"cemCfgManExtLimit_Get",		(FARPROC*)&cemCfgManExtLimit_Get},

		//****************************************************************************
		//*************** START OF HOME RETURN FUNCTION DECLARATIONS *****************
		//****************************************************************************
		{"cemHomeConfig_Set",		(FARPROC*)&cemHomeConfig_Set},
		{"cemHomeConfig_Get",		(FARPROC*)&cemHomeConfig_Get},
		{"cemHomePosClrMode_Set",	(FARPROC*)&cemHomePosClrMode_Set},
		{"cemHomePosClrMode_Get",	(FARPROC*)&cemHomePosClrMode_Get},
		{"cemHomeSpeedPattern_Set",	(FARPROC*)&cemHomeSpeedPattern_Set},
		{"cemHomeSpeedPattern_Get",	(FARPROC*)&cemHomeSpeedPattern_Get},
		{"cemHomeMoveStart",		(FARPROC*)&cemHomeMoveStart},
		{"cemHomeMove",			    (FARPROC*)&cemHomeMove},
		{"cemHomeMoveAll",		(FARPROC*)&cemHomeMoveAll},
		{"cemHomeMoveAllStart",	(FARPROC*)&cemHomeMoveAllStart},
		{"cemHomeSuccess_Get",	(FARPROC*)&cemHomeSuccess_Get},
		{"cemHomeSuccess_Set",	(FARPROC*)&cemHomeSuccess_Set},

		{"cemHomeIsBusy",		    (FARPROC*)&cemHomeIsBusy},
		{"cemHomeWaitDone",		    (FARPROC*)&cemHomeWaitDone},

		//****************************************************************************
		//*************** START OF SINGLE AXIS CONTROL FUNCTION DECLARATIONS *********
		//****************************************************************************
		{"cemSxSpeedRatio_Set",		(FARPROC*)&cemSxSpeedRatio_Set},
		{"cemSxSpeedRatio_Get",		(FARPROC*)&cemSxSpeedRatio_Get},
		{"cemSxMoveStart",		    (FARPROC*)&cemSxMoveStart},
		{"cemSxMove",			    (FARPROC*)&cemSxMove},
		{"cemSxMoveToStart",		(FARPROC*)&cemSxMoveToStart},
		{"cemSxMoveTo",			    (FARPROC*)&cemSxMoveTo},
		{"cemSxVMoveStart",		    (FARPROC*)&cemSxVMoveStart},
		{"cemSxStop",			    (FARPROC*)&cemSxStop},
		{"cemSxStopEmg",		    (FARPROC*)&cemSxStopEmg},
		{"cemSxIsDone",			    (FARPROC*)&cemSxIsDone},
		{"cemSxWaitDone",		    (FARPROC*)&cemSxWaitDone},
		{"cemSxTargetPos_Get",		(FARPROC*)&cemSxTargetPos_Get},
		{"cemSxOptIniSpeed_Set",	(FARPROC*)&cemSxOptIniSpeed_Set},
		{"cemSxOptIniSpeed_Get",	(FARPROC*)&cemSxOptIniSpeed_Get},
		{"cemSxOptRdpOffset_Set",	(FARPROC*)&cemSxOptRdpOffset_Set},
		{"cemSxOptRdpOffset_Get",	(FARPROC*)&cemSxOptRdpOffset_Get},
		{"cemSxMoveStart2V",        (FARPROC*)&cemSxMoveStart2V},
		{"cemSxMoveToStart2V",      (FARPROC*)&cemSxMoveToStart2V},


		{"cemSxCorrection_Set",		(FARPROC*)&cemSxCorrection_Set},
		{"cemSxCorrection_Get",		(FARPROC*)&cemSxCorrection_Get},
		{"cemSxOptSyncMode_Set",	(FARPROC*)&cemSxOptSyncMode_Set},
		{"cemSxOptSyncMode_Get",	(FARPROC*)&cemSxOptSyncMode_Get},
		/*
		{"cemSxOptSyncOut_Set",		(FARPROC*)&cemSxOptSyncOut_Set},
		{"cemSxOptSyncOut_Get",		(FARPROC*)&cemSxOptSyncOut_Get},
		{"cemSxOptRdpOffset_Set",	(FARPROC*)&cemSxOptRdpOffset_Set},
		{"cemSxOptRdpOffset_Get",	(FARPROC*)&cemSxOptRdpOffset_Get},
		*/

		//****************************************************************************
		//*************** START OF MULTIPLE AXES CONTROL FUNCTION DECLARATIONS *******
		//****************************************************************************
		/*
		{"cemMxMove",			(FARPROC*)&cemMxMove},
		{"cemMxVMoveStart",		(FARPROC*)&cemMxVMoveStart},
		{"cemMxMoveStart",		(FARPROC*)&cemMxMoveStart},
		{"cemMxMoveTo",			(FARPROC*)&cemMxMoveTo},
		{"cemMxMoveToStart",	(FARPROC*)&cemMxMoveToStart},
		{"cemMxStop",			(FARPROC*)&cemMxStop},
		{"cemMxStopEmg",		(FARPROC*)&cemMxStopEmg},
		{"cemMxIsDone",			(FARPROC*)&cemMxIsDone},
		{"cemMxWaitDone",		(FARPROC*)&cemMxWaitDone},
		*/

		//****************************************************************************
		//*************** START OF INTERPOLATION CONTROL FUNCTION DECLARATIONS *******
		//****************************************************************************
		{"cemIxMapAxes",			(FARPROC*)&cemIxMapAxes},
		
		{"cemIxVelCorrMode_Set",	(FARPROC*)&cemIxVelCorrMode_Set},
		{"cemIxVelCorrMode_Get",	(FARPROC*)&cemIxVelCorrMode_Get},
		
		{"cemIxUnMap",				(FARPROC*)&cemIxUnMap},
		{"cemIxSpeedPattern_Set",	(FARPROC*)&cemIxSpeedPattern_Set},
		{"cemIxSpeedPattern_Get",	(FARPROC*)&cemIxSpeedPattern_Get},
		{"cemIxLine",				(FARPROC*)&cemIxLine},
		{"cemIxLineStart",			(FARPROC*)&cemIxLineStart},
		{"cemIxLineTo",				(FARPROC*)&cemIxLineTo},
		{"cemIxLineToStart",		(FARPROC*)&cemIxLineToStart},
		{"cemIxLineStart_Fx",			(FARPROC*)&cemIxLineStart_Fx},
		{"cemIxLineToStart_Fx",		(FARPROC*)&cemIxLineToStart_Fx},


		//////////////////////////////////////////////////////////////////////////

		{"cemIxArcA",				(FARPROC*)&cemIxArcA},
		{"cemIxArcAStart",			(FARPROC*)&cemIxArcAStart},
		{"cemIxArcATo",				(FARPROC*)&cemIxArcATo},
		{"cemIxArcAToStart",		(FARPROC*)&cemIxArcAToStart},

		{"cemIxArcP",				(FARPROC*)&cemIxArcP},
		{"cemIxArcPStart",			(FARPROC*)&cemIxArcPStart},
		{"cemIxArcPTo",				(FARPROC*)&cemIxArcPTo},
		{"cemIxArcPToStart",		(FARPROC*)&cemIxArcPToStart},

		{"cemIxArc3P",				(FARPROC*)&cemIxArc3P},
		{"cemIxArc3PStart",			(FARPROC*)&cemIxArc3PStart},
		{"cemIxArc3PTo",			(FARPROC*)&cemIxArc3PTo},
		{"cemIxArc3PToStart",		(FARPROC*)&cemIxArc3PToStart},


		//////////////////////////////////////////////////////////////////////////


		{"cemIxStop",				(FARPROC*)&cemIxStop},
		{"cemIxStopEmg",			(FARPROC*)&cemIxStopEmg},
		{"cemIxIsDone",				(FARPROC*)&cemIxIsDone},
		{"cemIxWaitDone",			(FARPROC*)&cemIxWaitDone},
		{"cemIxMasterAxis_Set",			(FARPROC*)&cemIxMasterAxis_Set},
		{"cemIxMasterAxis_Get",			(FARPROC*)&cemIxMasterAxis_Get},
		{"cemIxSmartDecel_Set",			(FARPROC*)&cemIxSmartDecel_Set},
		{"cemIxSmartDecel_Get",			(FARPROC*)&cemIxSmartDecel_Get},
		{"cemIxSmartStop",			(FARPROC*)&cemIxSmartStop},
		/*
		{"cemIxxHelOnceSpeed_Set",	(FARPROC*)&cemIxxHelOnceSpeed_Set},
		{"cemIxxHelOnceSpeed_Get",	(FARPROC*)&cemIxxHelOnceSpeed_Get},
		{"cemIxxHelOnce",			(FARPROC*)&cemIxxHelOnce},
		{"cemIxxHelOnceStart",		(FARPROC*)&cemIxxHelOnceStart},
		{"cemIxxSplineBuild",		(FARPROC*)&cemIxxSplineBuild},
		*/

		//****************************************************************************
		//*************** START OF MASTER/SLAVE CONTROL FUNCTION DECLARATIONS ********
		//****************************************************************************
		{"cemMsRegisterSlave",		(FARPROC*)&cemMsRegisterSlave},
		{"cemMsUnregisterSlave",	(FARPROC*)&cemMsUnregisterSlave},
		{"cemMsCheckSlaveState",	(FARPROC*)&cemMsCheckSlaveState},
		{"cemMsMasterAxis_Get",		(FARPROC*)&cemMsMasterAxis_Get},

		//****************************************************************************
		//*************** START OF LISTMOTION FUNCTION DECLARATIONS ******************
		//****************************************************************************
		{"cemLmBeginList",			(FARPROC*)&cemLmBeginList},
		{"cemLmEndList",			(FARPROC*)&cemLmEndList},
		{"cemLmStart",				(FARPROC*)&cemLmStart},
		{"cemLmStop",				(FARPROC*)&cemLmStop},
		{"cemLmIsDone",				(FARPROC*)&cemLmIsDone},
		{"cemLmSetStepID_Reg",		(FARPROC*)&cemLmSetStepID_Reg},
		{"cemLmGetStepID_Reg",		(FARPROC*)&cemLmGetStepID_Reg},
		{"cemLmGetInfo",			(FARPROC*)&cemLmGetInfo},
		{"cemLmSetUserPara_Reg",	(FARPROC*)&cemLmSetUserPara_Reg},
		{"cemLmGetUserPara_Reg",	(FARPROC*)&cemLmGetUserPara_Reg},
		{"cemLmGetUserPara_Run",	(FARPROC*)&cemLmGetUserPara_Run},
		//****************************************************************************
		//*************** START OF MONITORING FUNCTION DECLARATIONS ******************
		//****************************************************************************
		{"cemStCount_Set",		(FARPROC*)&cemStCount_Set},
		{"cemStCount_Get",		(FARPROC*)&cemStCount_Get},
		{"cemStPosition_Set",		(FARPROC*)&cemStPosition_Set},
		{"cemStPosition_Get",		(FARPROC*)&cemStPosition_Get},
		{"cemStSpeed_Get",		(FARPROC*)&cemStSpeed_Get},
		{"cemStReadMotionState",	(FARPROC*)&cemStReadMotionState},
		{"cemStReadMioStatuses",	(FARPROC*)&cemStReadMioStatuses},
		{"cemStGetMstString",		(FARPROC*)&cemStGetMstString},
		{"cemStReadIOMessageCount", (FARPROC*)&cemStReadIOMessageCount},

		//****************************************************************************
		//*************** START OF LTC FUNCTION SECTION ******************************
		//****************************************************************************
		{"cemLtcIsLatched",			(FARPROC*)&cemLtcIsLatched},
		{"cemLtcReadLatch",			(FARPROC*)&cemLtcReadLatch},

		//****************************************************************************
		//*************** START OF CMP FUNCTION SECTION ******************************
		//****************************************************************************
		
		{"cemCmpGenConfig_Set",			(FARPROC*)&cemCmpGenConfig_Set},
		{"cemCmpGenConfig_Get",			(FARPROC*)&cemCmpGenConfig_Get},
		{"cemCmpTrgConfig_Set",			(FARPROC*)&cemCmpTrgConfig_Set},
		{"cemCmpTrgConfig_Get",			(FARPROC*)&cemCmpTrgConfig_Get},
		{"cemCmpTrgOneData_Set",			(FARPROC*)&cemCmpTrgOneData_Set},
		{"cemCmpTrgCurData_Get",			(FARPROC*)&cemCmpTrgCurData_Get},

		//****************************************************************************
		//*************** START OF Manual Pulsar FUNCTION SECTION ********************
		//****************************************************************************
		{"cemPlsrInMode_Set",        (FARPROC*)&cemPlsrInMode_Set},
		{"cemPlsrInMode_Get",        (FARPROC*)&cemPlsrInMode_Get},
		{"cemPlsrGain_Set",          (FARPROC*)&cemPlsrGain_Set},
		{"cemPlsrGain_Get",          (FARPROC*)&cemPlsrGain_Get},
		{"cemPlsrHomeMoveStart",     (FARPROC*)&cemPlsrHomeMoveStart},
		{"cemPlsrVMoveStart",        (FARPROC*)&cemPlsrVMoveStart},
		{"cemPlsrMove",              (FARPROC*)&cemPlsrMove},
		{"cemPlsrMoveStart",         (FARPROC*)&cemPlsrMoveStart},
		{"cemPlsrMoveToStart",       (FARPROC*)&cemPlsrMoveToStart},
		{"cemPlsrMoveTo",            (FARPROC*)&cemPlsrMoveTo},

		//****************************************************************************
		//*************** START OF Override FUNCTION SECTION *************************
		//****************************************************************************
		{"cemOverrideSpeedSet",		(FARPROC*)&cemOverrideSpeedSet},
		{"cemOverrideMove",			(FARPROC*)&cemOverrideMove},
		{"cemOverrideMoveTo",		(FARPROC*)&cemOverrideMoveTo},

		//****************************************************************************
		//*************** START OF ADVANCED FUNCTION SECTION *************************
		//****************************************************************************

		{"cemAdvGetNodeInformation", 	(FARPROC*)&cemAdvGetNodeInformation},
		{"cemAdvGetAllNodeInformation", (FARPROC*)&cemAdvGetAllNodeInformation},

#if 0
		{"cmnAdvDownloadDefaultConfigure",(FARPROC*)&cmnAdvDownloadDefaultConfigure},
		{"cemAdvUploadConfigure",         (FARPROC*)&cemAdvUploadConfigure},
		{"cemAdvDownloadConfigure",       (FARPROC*)&cemAdvDownloadConfigure},


		{"cemAdvActiveNodeCount_Get",     (FARPROC*)&cemAdvActiveNodeCount_Get},
		{"cemAdvActiveNodeID_Get",        (FARPROC*)&cemAdvActiveNodeID_Get},
#endif
		{"cemAdvErcOut",				(FARPROC*)&cemAdvErcOut},
		{"cemAdvErcReset",				(FARPROC*)&cemAdvErcReset},
		{"cemAdvManualPacket",			(FARPROC*)&cemAdvManualPacket},

		//****************************************************************************
		//*************** START OF SYSTEM DIO CONFIGURATION FUNCTION DECLARATIONS ****
		//****************************************************************************
		{"cemDiOne_Get",					(FARPROC*)&cemDiOne_Get},
		{"cemDiMulti_Get",					(FARPROC*)&cemDiMulti_Get},
		{"cemDoOne_Put",					(FARPROC*)&cemDoOne_Put},
		{"cemDoOne_Get",					(FARPROC*)&cemDoOne_Get},
		{"cemDoMulti_Put",					(FARPROC*)&cemDoMulti_Put},
		{"cemDoMulti_Get",					(FARPROC*)&cemDoMulti_Get},

		//****************************************************************************
		//*************** START OF INTERLOCK CONFIGURATION FUNCTION DECLARATIONS *****
		//****************************************************************************
		{"ceil_Set",						(FARPROC*)&ceil_Set},
		{"ceil_Get",						(FARPROC*)&ceil_Get},
		{"ceilDisconnectTimeout_Set",		(FARPROC*)&ceilDisconnectTimeout_Set},
		{"ceilDisconnectTimeout_Get",		(FARPROC*)&ceilDisconnectTimeout_Get},
		{"ceilActionModeOne_Set",			(FARPROC*)&ceilActionModeOne_Set},
		{"ceilActionModeOne_Get",			(FARPROC*)&ceilActionModeOne_Get},
		{"ceilActionModeMulti_Set",			(FARPROC*)&ceilActionModeMulti_Set},
		{"ceilActionModeMulti_Get",			(FARPROC*)&ceilActionModeMulti_Get},

		/************************************************************************/
		/* DIO Control Function                                                 */
		/************************************************************************/
		{"cedioMode_Set",				(FARPROC*)&cedioMode_Set},
		{"cedioMode_Get",				(FARPROC*)&cedioMode_Get},
		{"cedioModeMulti_Set",			(FARPROC*)&cedioModeMulti_Set},
		{"cedioModeMulti_Get",			(FARPROC*)&cedioModeMulti_Get},

		//////////////////////////////////////////////////////////////////////////
		// DIO 변경 추가된 함수
		{"cedioLogicOne_Set",			(FARPROC*)&cedioLogicOne_Set},
		{"cedioLogicOne_Get",			(FARPROC*)&cedioLogicOne_Get},

		{"cedioLogicMulti_Set",			(FARPROC*)&cedioLogicMulti_Set},
		{"cedioLogicMulti_Get",			(FARPROC*)&cedioLogicMulti_Get},

		{"cedioOne_Get",				(FARPROC*)&cedioOne_Get},
		{"cedioOne_Put",				(FARPROC*)&cedioOne_Put},

		{"cedioMulti_Get",				(FARPROC*)&cedioMulti_Get},
		{"cedioMulti_Put",				(FARPROC*)&cedioMulti_Put},


		{"cedioOneF_Get",				(FARPROC*)&cedioOneF_Get},
		{"cedioMultiF_Get",				(FARPROC*)&cedioMultiF_Get},

		{"cedioPulseOne",				(FARPROC*)&cedioPulseOne},
		{"cedioPulseMulti",				(FARPROC*)&cedioPulseMulti},
		//////////////////////////////////////////////////////////////////////////

#ifdef __DI_DO_SUPPORT__
		/************************************************************************/
		/* DI Control Function                                                  */
		/************************************************************************/
		{"cediLogicOne_Set",			(FARPROC*)&cediLogicOne_Set},
		{"cediLogicOne_Get",			(FARPROC*)&cediLogicOne_Get},

		{"cediLogicMulti_Set",			(FARPROC*)&cediLogicMulti_Set},
		{"cediLogicMulti_Get",			(FARPROC*)&cediLogicMulti_Get},
		{"cediOne_Get",					(FARPROC*)&cediOne_Get},
		{"cediMulti_Get",				(FARPROC*)&cediMulti_Get},
		{"cediOneF_Get",				(FARPROC*)&cediOneF_Get},
		{"cediMultiF_Get",				(FARPROC*)&cediMultiF_Get},

		/************************************************************************/
		/* DO Control Function                                                  */
		/************************************************************************/
		{"cedoLogicOne_Set",			(FARPROC*)&cedoLogicOne_Set},
		{"cedoLogicOne_Get",			(FARPROC*)&cedoLogicOne_Get},

		{"cedoLogicMulti_Set",			(FARPROC*)&cedoLogicMulti_Set},
		{"cedoLogicMulti_Get",			(FARPROC*)&cedoLogicMulti_Get},
		{"cedoOne_Put",					(FARPROC*)&cedoOne_Put},
		{"cedoOne_Get",					(FARPROC*)&cedoOne_Get},
		{"cedoMulti_Put",				(FARPROC*)&cedoMulti_Put},
		{"cedoMulti_Get",				(FARPROC*)&cedoMulti_Get},
		{"cedoPulseOne",				(FARPROC*)&cedoPulseOne},
		{"cedoPulseMulti",				(FARPROC*)&cedoPulseMulti},
#endif

		//****************************************************************************
		//*************** START OF COUNTER MODULE FUNCTION DECLARATIONS **************
		//****************************************************************************
		{"cecEdgeOne_Set",				(FARPROC*)&cecEdgeOne_Set},
		{"cecEdgeOne_Get",				(FARPROC*)&cecEdgeOne_Get},
		{"cecEdgeMulti_Set",			(FARPROC*)&cecEdgeMulti_Set},
		{"cecEdgeMulti_Get",			(FARPROC*)&cecEdgeMulti_Get},
		{"cecClearOne",					(FARPROC*)&cecClearOne},
		{"cecClearMulti",				(FARPROC*)&cecClearMulti},
		{"cecClearAll",					(FARPROC*)&cecClearAll},
		{"cec_Get",						(FARPROC*)&cec_Get},
		{"cecEnableOne_Set",			(FARPROC*)&cecEnableOne_Set},
		{"cecEnableOne_Get",			(FARPROC*)&cecEnableOne_Get},
		{"cecEnableMulti_Set",			(FARPROC*)&cecEnableMulti_Set},
		{"cecEnableMulti_Get",			(FARPROC*)&cecEnableMulti_Get},
		{"cecOverflowFlagGetOne",		(FARPROC*)&cecOverflowFlagGetOne},
		{"cecOverflowFlagGetMulti",		(FARPROC*)&cecOverflowFlagGetMulti},
		{"cecOverflowFlagClearOne",		(FARPROC*)&cecOverflowFlagClearOne},
		{"cecOverflowFlagClearMulti",	(FARPROC*)&cecOverflowFlagClearMulti},
		{"cecOverflowFlagClearAll",		(FARPROC*)&cecOverflowFlagClearAll},
		{"cecFilterFreq_Set",			(FARPROC*)&cecFilterFreq_Set},
		{"cecFilterFreq_Get",			(FARPROC*)&cecFilterFreq_Get},


		//****************************************************************************
		//*************** START OF ANALOG INPUT FUNCTION DECLARATIONS ****************
		//****************************************************************************
		{"ceaiVoltRangeMode_Set",		(FARPROC*)&ceaiVoltRangeMode_Set},
		{"ceaiVoltRangeMode_Get",		(FARPROC*)&ceaiVoltRangeMode_Get},
		{"ceaiRangeDigit_Get",			(FARPROC*)&ceaiRangeDigit_Get},
		{"ceaiDigit_Get",				(FARPROC*)&ceaiDigit_Get},
		{"ceaiVolt_Get",				(FARPROC*)&ceaiVolt_Get},
		{"ceaiCurrent_Get",				(FARPROC*)&ceaiCurrent_Get},

		//****************************************************************************
		//*************** START OF ANALOG OUTPUT FUNCTION DECLARATIONS ***************
		//****************************************************************************
		{"ceaoDigit_Out",				(FARPROC*)&ceaoDigit_Out}, 
		{"ceaoVolt_Out",				(FARPROC*)&ceaoVolt_Out},
		{"ceaoCurrent_Out",				(FARPROC*)&ceaoCurrent_Out},

		/************************************************************************/
		/* Utility Function				                                        */
		/************************************************************************/
		{"ceutlUserData_Set",			(FARPROC*)&ceutlUserData_Set},
		{"ceutlUserData_Get",			(FARPROC*)&ceutlUserData_Get},

		{"ceutlUserVersion_Set",		(FARPROC*)&ceutlUserVersion_Set},
		{"ceutlUserVersion_Get",		(FARPROC*)&ceutlUserVersion_Get},

		{"ceutlNodeVersion_Get",		(FARPROC*)&ceutlNodeVersion_Get},
		{"ceutlLibVersion_Get",			(FARPROC*)&ceutlLibVersion_Get},

		{"ceutlPumpSingleMessage",      (FARPROC*)&ceutlPumpSingleMessage},
		{"ceutlPumpMultiMessage",       (FARPROC*)&ceutlPumpMultiMessage},

		{"ceutlSyncCount_Get",			(FARPROC*)&ceutlSyncCount_Get},
		{"ceutlIOSyncCount_Get",		(FARPROC*)&ceutlIOSyncCount_Get},
		{"ceutlSyncWait",				(FARPROC*)&ceutlSyncWait},

		{"ceutlTimeStamp_Get",			(FARPROC*)&ceutlTimeStamp_Get},
        ///////////////////////////////////////////////////////////////////////
        // C-NET
        ///////////////////////////////////////////////////////////////////////
        {"cecnetLogicOne_Set",          (FARPROC*)&cecnetLogicOne_Set}, 
        {"cecnetLogicOne_Get",          (FARPROC*)&cecnetLogicOne_Get}, 
        {"cecnetLogicMulti_Set",        (FARPROC*)&cecnetLogicMulti_Set}, 
        {"cecnetLogicMulti_Get",        (FARPROC*)&cecnetLogicMulti_Get}, 
        {"cecnetOne_Put",               (FARPROC*)&cecnetOne_Put}, 
        {"cecnetDOOne_Get",             (FARPROC*)&cecnetDOOne_Get}, 
		{"cecnetDIOne_Get",             (FARPROC*)&cecnetDIOne_Get},
        {"cecnetMulti_Put",             (FARPROC*)&cecnetMulti_Put}, 
        {"cecnetDOMulti_Get",           (FARPROC*)&cecnetDOMulti_Get}, 
		{"cecnetDIMulti_Get",           (FARPROC*)&cecnetDIMulti_Get},
		
		///////////////////////////////////////////////////////////////////////
        // SERIAL
        ///////////////////////////////////////////////////////////////////////
		{"cesOpenPort",           		(FARPROC*)&cesOpenPort},
		{"cesClosePort",           		(FARPROC*)&cesClosePort},
		{"cesIsDataReady",           	(FARPROC*)&cesIsDataReady},
		{"cesSetTimeOut",           	(FARPROC*)&cesSetTimeOut},
		{"cesGetTimeOut",           	(FARPROC*)&cesGetTimeOut},
		{"cesRxReset",           		(FARPROC*)&cesRxReset},
		{"cesTxReset",           		(FARPROC*)&cesTxReset},
		{"cesGetUnreadDataSize",        (FARPROC*)&cesGetUnreadDataSize},
		{"cesPeekByte",           		(FARPROC*)&cesPeekByte},
		{"cesPeekByteEx",           	(FARPROC*)&cesPeekByteEx},
		{"cesReadByte",           		(FARPROC*)&cesReadByte},
		{"cesWriteByte",           		(FARPROC*)&cesWriteByte},
		{"cesPeekString",           	(FARPROC*)&cesPeekString},
		{"cesReadString",           	(FARPROC*)&cesReadString},
		{"cesWriteString",           	(FARPROC*)&cesWriteString},
		{"cesReadDword",           		(FARPROC*)&cesReadDword},
		{"cesWriteDword",           	(FARPROC*)&cesWriteDword},
		{"cesCommCommit",           	(FARPROC*)&cesCommCommit},
		{"cemCfgActSpdFilter_Set",		(FARPROC*)&cemCfgActSpdFilter_Set},
		{"cemCfgActSpdFilter_Get",		(FARPROC*)&cemCfgActSpdFilter_Get},
		
		{NULL, NULL}
		};


	LIB_FUNCT *f;

	char szBuffer[MAX_PATH + _MAX_FNAME] = "";

	if((hLibrary = LoadLibrary (__DLL_FILE_FULL_PATH__)) == NULL)
		return FALSE;

	f = &Func[0];
	while(f->ptr != NULL)
	{
		*(f->ptr) = GetProcAddress ((HMODULE)hLibrary, f->name);
		if(*(f->ptr) == NULL){
//			sprintf(szBuffer,"\nFUNCTION FAIL [%20s],[0x%04x]\n",f->name,f->ptr);
//			OutputDebugString(szBuffer);
		}

		f++;
	}
	return TRUE;
}

void ceUnloadDll(void)
{
	if(hLibrary){
		FreeLibrary(hLibrary);
		hLibrary = NULL;
	}
}

