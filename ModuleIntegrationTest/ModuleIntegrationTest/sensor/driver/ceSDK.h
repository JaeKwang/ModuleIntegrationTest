/*******************************************************************************
* [ ceSDK.h ]
* Header file for definitions of constants and data in ceSDK library
* - Update Date: 2008/03/26
* - Provider: COMIZOA Co., Ltd.
* - Phone: +82-42-936-6500~6
* - Fax  : +82-42-936-6507
* - URL  : http://www.comizoa.co.kr,  http://www.comizoa.com
********************************************************************************/

#ifndef __CESDK_H__
#define __CESDK_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ceSDKDef.h"


typedef DOUBLE *PDOUBLE;

#if !defined(__in)
#define __in
#endif

#if !defined(__out)
#define __out
#endif

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _DLL_MAIN_CPP_
#define EXTERN
#else
#define EXTERN extern
#endif
	//
	//****************************************************************************
	//*************** START OF Load/Unload DLL FUNCTION DECLARATIONS *************
	//****************************************************************************
	// ceSDK ���̺귯�� �ε�.
	BOOL ceLoadDll();
	// ceSDK ���̺귯�� ��ε�.
	VOID ceUnloadDll();

	//****************************************************************************
	//*************** START OF GENERAL FUNCTION DECLARATIONS *********************
	//****************************************************************************

	// ���̺귯���� �ε�� ���¿��� ��ġ�� �ε�.
	EXTERN LONG (__stdcall *ceGnLoad)	();

	// ���̺귯���� �ε�� ���¿��� ��ġ�� ��ε�.
	EXTERN LONG (__stdcall *ceGnUnload)	();
	
	// ����� ���� ���� 
	// [LogLevel : (ceSDKDef.h) ������ �����մϴ�]
	EXTERN LONG (__stdcall *ceGnLogLevel_Set)	(__in LONG LogLevel);

	// ����� ���� ��ȯ
	// [LogLevel : (ceSDKDef.h) ������ �����մϴ�]
	EXTERN LONG (__stdcall *ceGnLogLevel_Get)	(__out PLONG LogLevel);

	// ����� ��� ���� �մϴ�.
	// [LogMode : 0: Disable , 1: OutputDebugString, 2 : FILE, 4: Console, szLogDir : �α� ������ ��ϵ� ���]
	EXTERN LONG (__stdcall *ceGnLogMode_Set)	(__in LONG LogMode, __in CHAR * szLogDir);

	// ����� ��� ��ȯ �մϴ�.
	// [LogMode : 0: Disable , 1: OutputDebugString, 2 : FILE, 4: Console]
	EXTERN LONG (__stdcall *ceGnLogMode_Get)	(__out PLONG LogMode);
	
	// ���̺귯���� �ε�� ���¿��� ��带 �ٽ� Ž���մϴ�.
	// [RealNode: ���� ��� ����, nTimeout: Ÿ�� �ƿ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����, pResultNode: �ε�� ��� �� ��ȯ]
	EXTERN LONG (__stdcall *ceGnReSearchDevice)	(__in LONG RealNode,  __in DWORD nTimeout, __in LONG IsBlocking, __out PLONG pResultNode);

	// ��� Ž���� �Ϸ�Ǿ� �ִ��� Ȯ���մϴ�. ���� ���μ������� �ٸ� ���μ������� �̹� ��尡 Ž���Ǿ��ٸ�, �� �Լ��� ����
	// �̹� Ž���� ��带 ������� �� Ž���� �ϰų� ���� �ʵ��� �� �� �ֽ��ϴ�.
	// [IsSearchedDevice: �̹� ��� Ž���� �Ǿ� �ִ� ��� TRUE �� ��ȯ�ϸ�, Ž���� �Ǿ� ���� ���� ��� FALSE �� ��ȯ�մϴ�]  
	EXTERN LONG (__stdcall *ceGnIsSearchedDevice)	(__out PLONG IsSearchedDevice);

	// ��ġ�� �ε�� ���¿��� ��ġ�� ȯ�� ������ ��ȯ.
	// [RealNode: ���� ��� ����, nTimeout: Ÿ�� �ƿ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����, pResultNode: ��ü ��� �� ��ȯ]
	EXTERN LONG (__stdcall *ceGnSearchDevice)	(__in LONG RealNode,  __in DWORD nTimeout, __in LONG IsBlocking, __out PLONG pResultNode);

	// ��� Ž���� �ʱ�ȭ �ϸ�, �� �Լ��� ����� ���� ceGnSearchDevice �� ���� ��� Ž���� �� �� �ֽ��ϴ�.
	EXTERN LONG (__stdcall *ceGnUnSearchDevice)	();

	// �ε�� ��ü ����� ������ ��ȯ.
	// [Node : �ε�� ��� �� ��ȯ]
	EXTERN LONG (__stdcall *ceGnTotalNode)	(__out PLONG Node);

	// �ε�� ��� ���� �� ������ ��ȯ.
	// [Channel : �ε�� ��� ���� �� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnTotalMotionChannel)	(__out PLONG Channel);

	// �ε�� ������ ����� ä�� ������ ��ȯ.
	// [Channel : �ε�� ������ ����� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnTotalDIOChannel)	(__out PLONG Channel);

	// �ε�� �Ƴ��α� �Է� ä�� ������ ��ȯ.
	// [Channel : �ε�� �Ƴ��α� �Է� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnTotalAIChannel)	(__out PLONG Channel);

	// �ε�� �Ƴ��α� ��� ä�� ������ ��ȯ.
	// [Channel : �ε�� �Ƴ��α� ��� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnTotalAOChannel)	(__out PLONG Channel);

	// �ε�� ��� ������ ����� ä�� ������ ��ȯ.
	// [Channel : �ε�� ��� ������ ����� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnTotalMDIOChannel) (__out PLONG Channel);

	// �ε�� ī���� ä�� ������ ��ȯ.
	// [Channel : �ε�� ī���� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnTotalCNTChannel) (__out PLONG Channel);

	// �ش� ����� ��� ���� ��� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleCount : �ش� ����� ��� ���� ��� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnModuleCount_Motion)	(__in LONG NodeID, __out PLONG ModuleCount);

	// �ش� ����� ������ ����� ��� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleCount : �ش� ����� ������ ����� ��� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnModuleCount_Dio)	(__in LONG NodeID, __out PLONG ModuleCount);

	// �ش� ����� �Ƴ��α� �Է� ��� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleCount : �ش� ����� �Ƴ��α� �Է� ��� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnModuleCount_Ai)	(__in LONG NodeID, __out PLONG ModuleCount);

	// �ش� ����� �Ƴ��α� ��� ��� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleCount : �ش� ����� �Ƴ��α� ��� ��� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnModuleCount_Ao)	(__in LONG NodeID, __out PLONG ModuleCount);

	// �ش� ����� ��� ������ ����� ��� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleCount : �ش� ����� ��� ������ ����� ä�� ��� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnModuleCount_Mdio) (__in LONG NodeID, __out PLONG ModuleCount);

	// �ش� ����� ī���� ��� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleCount : �ش� ����� ī���� ��� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnModuleCount_Cnt) (__in LONG NodeID, __out PLONG ModuleCount);

	// �ش� ����� ��� ��⿡ ���� ��� ���� �� ���� ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : ��� ��� ��ȣ, ChannelCount : ��� ���� �� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnChannelCount_Motion)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// �ش� ����� ������ ����� ��⿡ ���� ä�� ������ ��ȯ .
	// [NodeID : ��� ��ȣ, ModuleIdx : ������ ����� ��� ��ȣ, ChannelCount : ������ ����� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnChannelCount_Dio)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// �ش� ����� �Ƴ��α� �Է� ��⿡ ���� ä�� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �Ƴ��α� �Է� ��� ��ȣ, ChannelCount : �Ƴ��α� �Է� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnChannelCount_Ai)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// �ش� ����� �Ƴ��α� ��� ��⿡ ���� ä�� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �Ƴ��α� ��� ��� ��ȣ, ChannelCount : �Ƴ��α� ��� ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceGnChannelCount_Ao)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// �ش� ����� ��� ������ ����� ��⿡ ���� ä�� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : ��� ������ ����� ��� ��ȣ, ChannelCount : ��� ������ ����� ä�� ���� ��ȯ
	EXTERN LONG (__stdcall *ceGnChannelCount_Mdio) 	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// �ش� ����� ī���� ��⿡ ���� ä�� ������ ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : ī���� ��� ��ȣ, ChannelCount : ī���� ä�� ���� ��ȯ
	EXTERN LONG (__stdcall *ceGnChannelCount_Cnt) 	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// �ش� ��忡 ����Ʈ���� ������ Emergency ��Ȳ�� �����ϰų� ���� �մϴ�.
	// [NodeID : ��� ��ȣ, State : Emergency ���¿� ���ؼ� �����մϴ�]
	EXTERN LONG (__stdcall *ceGnEmergency_Set)  (__in LONG NodeID, __in LONG State);

	// �ش� ����� ����Ʈ���� ������ Emergency ��Ȳ�� ���� ��ȯ�մϴ�.
	// [NodeID : ��� ��ȣ, State : Emergency ���¿� ���ؼ� ��ȯ�մϴ�]
	EXTERN LONG (__stdcall *ceGnEmergency_Get)  (__in LONG NodeID, __out PLONG State);

	// �ش� ����� ����� �ʱ�ȭ.
	// [NodeID : ��� ��ȣ, ResetMode : �ʱ�ȭ ���]
	EXTERN LONG (__stdcall *ceGnResetNode)	(__in LONG NodeID, __in LONG ResetMode);

	// �ش� ���μ����� ���� ���μ����� ���μ��� �켱������ ����
	// [BoostLevel : �켱 ����, BoostMode : ���]
	EXTERN LONG (__stdcall *ceGnCtrlBoost_Set)	(__in LONG BoostLevel,	__in LONG BoostMode);

	// �ش� ���μ����� ���� ���μ����� ���μ��� �켱������ ��ȯ
	// [BoostLevel : �켱 ����, BoostMode : ���]
	EXTERN LONG (__stdcall *ceGnCtrlBoost_Get)	(__out PLONG BoostLevel, __out PLONG BoostMode);

	// �ش� ��尡 ����Ǿ� �ִ��� �����Ǿ� �ִ��� Ȯ���ϴ� �Լ�
	// [NodeID : ��� ���, IsActive : ���� Ȥ�� ���� ����]
	EXTERN LONG (__stdcall *ceGnNodeIsActive)		(__in LONG NodeID, __out PLONG IsActive);

	// �ش� ����� Flash Memory�� ȯ�� ���� ������ ����� ����.
	// [NodeID : ��� ��ȣ]
	EXTERN LONG (__stdcall *ceGnBeginSerialize)	(__in LONG NodeID);

	// �ش� ��忡 Flash Memory�� ȯ�� ���� ������ ����� ����.
	// [NodeID : ��� ��ȣ]
	EXTERN LONG (__stdcall *ceGnEndSerialize)	(__in LONG NodeID);

	// �ش� ��� ���� �࿡ ���� ��� �� ��� ������ ��ȯ.
	// [Axis : ���� ��� ���� �� ��ȣ, NodeIP : ��� IP �ּ� ��ȯ, NodeID : ��� ��ȣ ��ȯ, NodeInGlobal : �ش� ����� ���� ��� ���� �� ��ȣ ��ȯ,
	// ModuleIdx : �ش� ����� ��� ��ȣ ��ȯ, ModuleInCh : ��� �� ��� ���� �� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnLocalAxis_Get)	(__in LONG Axis,  __out PLONG NodeIP, __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// �ش� ������ I/O ä�ο� ���� ��� �� ��� ������ ��ȯ.
	// [Channel : ���� ������ ����� ä�� ��ȣ, NodeIP : ��� IP �ּ� ��ȯ, NodeID : ��� ��ȣ ��ȯ, NodeInGlobal : �ش� ����� ���� ������ ����� ä�� ��ȣ ��ȯ, ModuleIdx : �ش� ����� ��� ��ȣ ��ȯ, ModuleInCh : ��� �� ������ ����� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnLocalDIO_Get)	(__in LONG Channel,  __out PLONG NodeIP, __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// �ش� �Ƴ��α� �Է� ä�ο� ���� ��� �� ��� ������ ��ȯ.
	// [Channel: ���� �Ƴ��α� �Է� ä�� ��ȣ, NodeIP : ��� IP �ּ� ��ȯ, NodeID : ��� ��ȣ ��ȯ, NodeInGlobal : �ش� ����� ���� �Ƴ��α� �Է� ä�� ��ȣ ��ȯ, ModuleIdx : �ش� ����� ��� ��ȣ ��ȯ, ModuleInCh : ��� �� �Ƴ��α� �Է� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnLocalAI_Get)	(__in LONG Channel,  __out PLONG NodeIP, __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// �ش� �Ƴ��α� ��� ä�ο� ���� ��� �� ��� ������ ��ȯ.
	// [Channel: ���� �Ƴ��α� ��� ä�� ��ȣ, NodeIP : ��� IP �ּ� ��ȯ, NodeID : ��� ��ȣ ��ȯ, NodeInGlobal : �ش� ����� ���� �Ƴ��α� ��� ä�� ��ȣ ��ȯ, ModuleIdx : �ش� ����� ��� ��ȣ ��ȯ, ModuleInCh : ��� �� �Ƴ��α� ��� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnLocalAO_Get)	(__in LONG Channel, __out PLONG NodeIP,  __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// �ش� ��� ������ ����� ä�ο� ���� ��� �� ��� ������ ��ȯ.
	// [Channel: ���� ī���� ä�� ��ȣ, NodeIP : ��� IP �ּ� ��ȯ, NodeID : ��� ��ȣ ��ȯ, NodeInGlobal : �ش� ����� ���� ��� ������ ����� ä�� ��ȣ ��ȯ, ModuleIdx : �ش� ����� ��� ��ȣ ��ȯ, ModuleInCh : ��� �� ��� ������ �� ��� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnLocalMDIO_Get)   (__in LONG Channel, __out PLONG NodeIP,  __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// �ش� ī���� ä�ο� ���� ��� �� ��� ������ ��ȯ.
	// [Channel: ���� ī���� ä�� ��ȣ, NodeIP : ��� IP �ּ� ��ȯ, NodeID : ��� ��ȣ ��ȯ, NodeInGlobal : �ش� ����� ���� ī���� ä�� ��ȣ ��ȯ, ModuleIdx : �ش� ����� ��� ��ȣ ��ȯ, ModuleInCh : ��� �� ī���� ��� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnLocalCNT_Get)   (__in LONG Channel, __out PLONG NodeIP,  __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// �ش� ��� ��� ����� ���� �� ��ȣ�� ���Ͽ� ���� �� ��ȣ�� ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �ش� ����� ��� ��ȣ, ModuleInCh : ��� �� ��� ���� �� ��ȣ, GlobalAxis : ���� ��� ���� �� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnGlobalAxis_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalAxis);

	// �ش� ��� ������ ����� ����� ���� ä�� ��ȣ�� ���Ͽ� ���� ä�� ��ȣ�� ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �ش� ����� ��� ��ȣ, ModuleInCh : ��� �� ������ ����� ä�� ��ȣ, GlobalDIO : ���� ������ ����� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnGlobalDIO_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalDIO);

	// �ش� ��� �Ƴ��α� �Է� ����� ���� ä�� ��ȣ�� ���Ͽ� ���� ä�� ��ȣ�� ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �ش� ����� ��� ��ȣ, ModuleInCh : ��� �� �Ƴ��α� �Է� ä�� ��ȣ, GlobalAI : ���� �Ƴ��α� �Է� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnGlobalAI_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalAI);

	// �ش� ��� �Ƴ��α� ��� ����� ���� ä�� ��ȣ�� ���Ͽ� ���� ä�� ��ȣ�� ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �ش� ����� ��� ��ȣ, ModuleInCh : ��� �� �Ƴ��α� ��� ä�� ��ȣ, GlobalAO : ���� �Ƴ��α� ��� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnGlobalAO_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalAO);

	// �ش� ��� ��� ������ �� ��� ����� ���� ä�� ��ȣ�� ���Ͽ� ���� ä�� ��ȣ�� ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �ش� ����� ��� ��ȣ, ModuleInCh : ��� �� ��� ������ �� ��� ä�� ��ȣ, GlobalAO : ���� ��� ������ �� ��� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnGlobalMDIO_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalMDIO);

	// �ش� ��� ī���� ����� ���� ä�� ��ȣ�� ���Ͽ� ���� ä�� ��ȣ�� ��ȯ.
	// [NodeID : ��� ��ȣ, ModuleIdx : �ش� ����� ��� ��ȣ, ModuleInCh : ��� �� ī���� ä�� ��ȣ, GlobalAO : ���� ī���� ä�� ��ȣ ��ȯ]
	EXTERN LONG (__stdcall *ceGnGlobalCNT_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalCNT);
	
	EXTERN LONG (__stdcall *ceGnModuleTrType_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __out PLONG Type);


	//****************************************************************************
	//*************** START OF GENERAL MOTION FUNCTION DECLARATIONS **************
	//****************************************************************************

	// SERVO-ON ��ȣ ����� �ΰ� Ȥ�� ����.
	// [Channel : ���� �� ��ȣ, Enable : SERVO-ON ��ȣ ��� ON/OFF]
	EXTERN LONG (__stdcall *cemGnServoOn_Set)	(__in LONG Channel, __in LONG Enable);

	// SERVO-ON ��ȣ�� ��� ���¸� ��ȯ.
	// [Channel: ���� �� ��ȣ, Enable: SERVO-ON ��ȣ�� ��� ���¸� ��ȯ]
	EXTERN LONG (__stdcall *cemGnServoOn_Get)	(__in LONG Channel, __in PLONG Enable);

	// �ش� ��� ���� �˶� ���� ��ȣ ��� ����.
	// [Axis : ���� ��� ���� �� ��ȣ, IsReset: �˶� ���� ��ȣ ��� ����]
	EXTERN LONG (__stdcall *cemGnAlarmReset) (__in LONG Axis, __in LONG IsReset);

	//****************************************************************************
	//*************** START OF CONFIGURATION FUNCTION DECLARATIONS ***************
	//****************************************************************************

	// ��� ����� ��ȣ�� ȯ�� ���� ����. PropId�� ceSDKDef.h ���Ͽ� ���ǵ� enum _TCmMioPropId �� ����Ʈ�� ����.
	// [Axis : ���� �� ��ȣ, PropId : ȯ�� ���� �Ű� ����, PropVal : PropId�� ������ ȯ�濡 ���� ������]
	EXTERN LONG (__stdcall *cemCfgMioProperty_Set)	(__in LONG Axis, __in  LONG PropId, __in  LONG PropVal);

	// ��� ����� ��ȣ�� ȯ�� ���� ���� ��ȯ. PropId�� ceSDKDef.h ���Ͽ� ���ǵ� enum _TCmMioPropId �� ����Ʈ�� ����.
	// [Axis : ���� �� ��ȣ, PropId : ȯ�� ���� �Ű� ����, PropVal : PropId�� ������ ȯ�濡 ���� ��ȯ��]
	EXTERN LONG (__stdcall *cemCfgMioProperty_Get)	(__in LONG Axis, __in  LONG PropId, __out PLONG PropVal);

	// ���� I/O(Input/Output) ��ȣ�� ���� ������ ���� ���� ��� ����.
	// [Axis : ���� �� ��ȣ, IsEnable : ���� ���� ���� ����]
	EXTERN LONG (__stdcall *cemCfgFilter_Set)	(__in LONG Axis, __in LONG IsEnable);

	// ���� I/O(Input/Output) ��ȣ�� ���� ������ ���� ���� ��� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, IsEnabled : ���� ���� ���� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgFilter_Get)	(__in LONG Axis, __out PLONG IsEnabled);

	// EA/EB �Ǵ� PA/PB ��ȣ �Է� ȸ�ο� ������ ���͸� ������ ���� ����.
	// [Channel : ���� �� ��ȣ, Target : �Լ��� ���� ���(EA/EB or PA/PB), IsEnable : ���� ������ ���� ����]
	EXTERN LONG (__stdcall *cemCfgFilterAB_Set)	(__in LONG Channel, __in LONG Target, __in LONG IsEnable);

	// EA/EB �Ǵ� PA/PB ��ȣ �Է� ȸ�ο� ������ ���͸� ������ ���� ���� ���� ���¸� ��ȯ
	// [Channel : ���� �� ��ȣ, Target : �Լ��� ���� ���(EA/EB or PA/PB), IsEnabled : ���� ���� ���� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgFilterAB_Get)	(__in LONG Channel, __in LONG Target, __out PLONG IsEnabled);

	// ���ڴ� �޽�(Feedback Pulse) ��ȣ�� �Է� ��� ����.
	// [Axis : ���� �� ��ȣ, InputMode : Feedback Pulse �Է� ���, IsReverse : Feedback Count ���� UP/DOWN ������ �ݴ�� �� ������ ����]
	EXTERN LONG (__stdcall *cemCfgInMode_Set)	(__in LONG Axis, __in LONG InputMode, __in LONG IsReverse);

	// ���ڴ� �޽�(Feedback Pulse) ��ȣ�� �Է� ��� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, InputMode: Feedback Pulse �Է� ���, IsReverse : Feedback Count ���� UP/DOWN ������ �ݴ�� �� ������ ���� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgInMode_Get)	(__in LONG Axis, __out PLONG InputMode, __out PLONG IsReverse);

	// ���� �޽�(Command Pulse) ��ȣ ��� ��� ����.
	// [Axis : ���� �� ��ȣ, OutputMode : Command Pulse ��� ���]
	EXTERN LONG (__stdcall *cemCfgOutMode_Set)	(__in LONG Axis, __in LONG OutputMode);

	// ���� �޽�(Command Pulse) ��ȣ ��� ��� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, OutputMode: Command �޽��� ��� ��� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgOutMode_Get)	(__in LONG Axis, __out PLONG OutputMode);

	// �̼� ��ǥ ��ǥ�� ������ Ŀ�ǵ� ��ġ�� ���� �ǵ�� ��ġ�� ������ ����.
	// [Axis : ���� �� ��ȣ, CtrlMode : ���� ���]
	EXTERN LONG (__stdcall *cemCfgCtrlMode_Set)	(__in LONG Axis, __in LONG CtrlMode);

	// �̼� ��ǥ ��ǥ�� ������ Ŀ�ǵ� ��ġ�� ���� �ǵ�� ��ġ�� ������ ���� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, CtrlMode : ���� ���]
	EXTERN LONG (__stdcall *cemCfgCtrlMode_Get)	(__in LONG Axis, __out PLONG CtrlMode);

	// �Է� �޽�(Feedback Pulse)�� ��� �޽�(Command Pulse)�� ���ش��� ����.
	// [Axis : ���� �� ��ȣ, Ratio : Feedback Pulse�� Command Pulse�� ���ش� ����]
	EXTERN LONG (__stdcall *cemCfgInOutRatio_Set)	(__in LONG Axis, __in DOUBLE Ratio);

	// �Է� �޽�(Feedback Pulse)�� ��� �޽�(Command Pulse)�� ���ش� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, Ratio : Feedback Pulse�� Command Pulse�� ���ش� ������ ��ȯ]
	EXTERN LONG (__stdcall *cemCfgInOutRatio_Get)	(__in LONG Axis, __out PDOUBLE Ratio);

	// ���� �Ÿ� ������ ����.
	// [Axis : ���� �� ��ȣ, UnitDist : ���� �Ÿ� 1�� �̵��ϱ� ���� ��� �޽� ��]
	EXTERN LONG (__stdcall *cemCfgUnitDist_Set)	(__in LONG Axis, __in DOUBLE UnitDist);

	// ���� �Ÿ� ������ ��ȯ.
	// [Axis : ���� �� ��ȣ, UnitDist : ���� �Ÿ� 1�� �̵��ϱ� ���� ��� �޽� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgUnitDist_Get)	(__in LONG Axis, __out PDOUBLE UnitDist);

	// ���� �ӵ� ������ ����.
	// [Axis : ���� �� ��ȣ, UnitSpeed : ���� �ӵ��� ���� �޽� ��� �ӵ�(PPS)]
	EXTERN LONG (__stdcall *cemCfgUnitSpeed_Set)	(__in LONG Axis, __in DOUBLE UnitSpeed);

	// ���� �ӵ� ������ ��ȯ.
	// [Axis : ���� �� ��ȣ, UnitSpeed : ���� �ӵ��� ���� �޽� ��� �ӵ�(PPS)�� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgUnitSpeed_Get)	(__in LONG Axis, __out PDOUBLE UnitSpeed);

	// ��� �ӵ� ���ѹ����� ����.
	// [Axis : ���� �� ��ȣ, MaxPPS : ��� �ְ� �ӵ�(PPS)]
	EXTERN LONG (__stdcall *cemCfgSpeedRange_Set)	(__in LONG Axis, __in  DOUBLE MaxPPS);

	// ��� �ӵ� ���ѹ��� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, MinPPS : ��� ���� �ӵ�(PPS) ��ȯ, MaxPPS : ��� �ְ� �ӵ�(PPS) ��ȯ]
	EXTERN LONG (__stdcall *cemCfgSpeedRange_Get)	(__in LONG Axis, __out PDOUBLE MinPPS, __out PDOUBLE MaxPPS);

	// ��� �̼� ���� �ӵ� ����.
	// [Axis : ���� �� ��ȣ, SpeedMode : �ӵ� ���, WorkSpeed : �۾� �ӵ�, Accel : ���ӵ�, Decel : ���ӵ�]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_Set)	(__in LONG Axis, __in  LONG SpeedMode, __in  DOUBLE  WorkSpeed, __in  DOUBLE Accel,  __in  DOUBLE Decel);

	// ��� �̼� ���� �ӵ� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, SpeedMode : �ӵ� ��� ��ȯ, WorkSpeed : �۾� �ӵ� ��ȯ, Accel : ���ӵ� ��ȯ, Decel : ���ӵ� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_Get)	(__in LONG Axis, __out PLONG SpeedMode,__out PDOUBLE WorkSpeed, __out PDOUBLE Accel, __out PDOUBLE Decel);

	// ��� �̼� ���� �ӵ� ����.
	// [Axis : ���� �� ��ȣ, SpeedMode : �ӵ� ���, WorkSpeed : �۾� �ӵ�, AccelTime : ���ӵ��ð�, DecelTime : ���ӵ��ð�]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_T_Set)	(__in LONG Axis, __in  LONG SpeedMode, __in  DOUBLE  WorkSpeed, __in  DOUBLE AccelTime,  __in  DOUBLE DecelTime);

	// ��� �̼� ���� �ӵ� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, SpeedMode : �ӵ� ��� ��ȯ, WorkSpeed : �۾� �ӵ� ��ȯ, AccelTime : ���ӵ� �ð� ��ȯ, DecelTime : ���ӵ� �ð� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_T_Get)	(__in LONG Axis, __out PLONG SpeedMode,__out PDOUBLE WorkSpeed, __out PDOUBLE AccelTime, __out PDOUBLE DecelTime);

	// �Է� �޽�(Feedback Pulse)�� ���� ����� �����ӵ� ���� ����.
	// [Axis : ���� �� ��ȣ, IsEnable : Feedback �ӵ� Ȯ�� ��� Ȱ�� ����, Interval : Feedback �޽� �� Ȯ�� �ֱ�(ms)]
	EXTERN LONG (__stdcall *cemCfgActSpdCheck_Set)	(__in LONG Axis, __in LONG IsEnable, __in LONG Interval);

	// �Է� �޽�(Feedback Pulse)�� ���� ��� �����ӵ� ���� ���� ���¸� ��ȯ.
	// [Axis : ���� �� ��ȣ, IsEnable : Feedback �ӵ� Ȯ�� ��� Ȱ�����θ� ��ȯ, Interval : Feedback �޽� �� Ȯ�� �ֱ�(ms) ��ȯ]
	EXTERN LONG (__stdcall *cemCfgActSpdCheck_Get)	(__in LONG Axis, __out PLONG IsEnable, __out PLONG Interval);

	// ����� �̼� ������ ����Ʈ�������� �̼����ѹ����� �����Ͽ� ����.
	// [Axis : ���� �� ��ȣ, IsEnable : ����Ʈ���� ���� ��� Ȱ�� ����, LimitN : (-)���� Limit��, LimitP : (+)���� Limit��]
	EXTERN LONG (__stdcall *cemCfgSoftLimit_Set)	(__in LONG Axis, __in LONG IsEnable, __in DOUBLE LimitN, __in DOUBLE LimitP);

	// ����� ����Ʈ�������� �̼����ѹ����� ���� ������ ��ȯ.
	// [Axis : ���� �� ��ȣ, IsEnable : ����Ʈ���� ���� ��� Ȱ�� ���� ��ȯ, LimitN : (-)���� Limit�� ��ȯ, LimitP : (+)���� Limit�� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgSoftLimit_Get)	(__in LONG Axis, __out PLONG IsEnable, __out PDOUBLE LimitN, __out PDOUBLE LimitP);

	// ��ī����(Ring-Counter) ��� ����.
	// [Channel : ���� �� ��ȣ, TargCntr : �Լ��� ���� ���(Command or Feedback Counter), IsEnable : Ring-Counter ��� Ȱ�� ����, CntMax: ī���� ����]
	EXTERN LONG (__stdcall *cemCfgRingCntr_Set)	(__in LONG Channel, __in LONG TargCntr, __in LONG IsEnable, __in DOUBLE CntMax);

	// ��ī����(Ring-Counter) ��� ���� ���¸� ��ȯ.
	// [Channel: ���� �� ��ȣ, TargCntr: �Լ��� ���� ���(Command or Feedback Counter) ����, IsEnable: Ring-Counter ��� Ȱ�� ���� ��ȯ, CntMax: ī���� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgRingCntr_Get)	(__in LONG Channel, __in LONG TargCntr, __out PLONG IsEnable, __out PDOUBLE CntMax);

	// �۾��ӵ� ���� �� ������ �۾��ӵ��� �����ϴ� ��� �� ����.
	// [Axis: ���� �� ��ȣ, fCorrRatio: �ӵ� ���� ������(%)]
	EXTERN LONG (__stdcall *cemCfgVelCorrRatio_Set)	(__in LONG Axis, __in DOUBLE fCorrRatio);

	// �۾��ӵ� ���� �� ������ �۾��ӵ��� �����ϴ� ��� ���� ��ȯ.
	// [Axis: ���� �� ��ȣ, fCorrRatio: �ӵ� ���� ������(%) ��ȯ]
	EXTERN LONG (__stdcall *cemCfgVelCorrRatio_Get)	(__in LONG Axis, __out PDOUBLE fCorrRatio);

	// ������ �̼� �۾��� �Ϸ���� ���� �࿡ ���ο� �̼� ����� �ϴ޵Ǿ��� ���� ó�� ��å�� ����.
	// [seqMode: ������(Sequence) ���]
	EXTERN LONG (__stdcall *cemCfgSeqMode_Set)	(__in LONG SeqMode);

	// ������ �̼� �۾��� �Ϸ���� ���� �࿡ ���ο� �̼� ����� �ϴ޵Ǿ��� ���� ó�� ��å�� ���� ������ ��ȯ.
	// [seqMode: ������(Sequence) ��� ��ȯ]
	EXTERN LONG (__stdcall *cemCfgSeqMode_Get)	(__out PLONG SeqMode);

	//****************************************************************************
	//*************** START OF HOME RETURN FUNCTION DECLARATIONS *****************
	//****************************************************************************

	// �������� ȯ�� ����.
	// [Axis: ���� �� ��ȣ, HomeMode: �������� ���(0~12), Dir: �������� ��� ���� ���� EzCount: EzCount ��(0~15), EscDist: ����Ż�� �Ÿ�, Offset: �������� ���� ��ġ�� �������� �߰� ��� �̵���(�����ǥ �̼�)]
	EXTERN LONG (__stdcall *cemHomeConfig_Set)	(__in LONG Axis, __in  LONG HomeMode,  __in  LONG Dir,  __in LONG EzCount,  __in  DOUBLE EscDist,  __in  DOUBLE Offset);

	// �������� ȯ�� ���� ���¸� ��ȯ.
	// [Axis: ���� �� ��ȣ, HomeMode: �������� ���(0~12) ��ȯ, Dir: �������� ��� ���� ���� ��ȯ, EzCount: EzCount ��(0~15) ��ȯ, EscDist: ����Ż�� �Ÿ� ��ȯ, Offset: �������� ���� ��ġ�� �������� �߰� ��� �̵��� ��ȯ]
	EXTERN LONG (__stdcall *cemHomeConfig_Get)	(__in LONG Axis, __out PLONG HomeMode, __out PLONG Dir, __out PLONG EzCount, __out PDOUBLE EscDist, __out PDOUBLE Offset);

	// �������� �Ϸ� �� �߻��ϴ� ��� ��Ʈ�ѷ��� ���� ����̺갣�� ���� ������ ���� �߻��� �Է� �޽�(Feedback Pulse) ó���� ���� ����.
	// [Axis: ���� �� ��ȣ, PosClrMode: Command �� Feedback ��ġ�� Ŭ����Ǵ� ���]
	EXTERN LONG (__stdcall *cemHomePosClrMode_Set)	(__in LONG Axis, __in LONG PosClrMode);

	// �������� �Ϸ� �� �߻��ϴ� ��� ��Ʈ�ѷ��� ���� ����̺갣�� ���� ������ ���� �߻��� �Է� �޽�(Feedback Pulse) ó���� ���� ���� ���¸� ��ȯ.
	//[Axis: ���� �� ��ȣ, PosClrMode: Command �� Feedback ��ġ�� Ŭ���� �Ǵ� ��� ��ȯ]
	EXTERN LONG (__stdcall *cemHomePosClrMode_Get)	(__in LONG Axis, __out PLONG PosClrMode);

	// ���� ���� �ӵ� ����.
	// [Axis: ���� �� ��ȣ, SpeedMode: �������� �ӵ� ���, Vel: �������� �۾� �ӵ�, Accel: �������� ���ӵ�, Decel: �������� ���ӵ�, RevVel: Revers Speed]
	EXTERN LONG (__stdcall *cemHomeSpeedPattern_Set)	(__in LONG Axis, __in LONG SpeedMode, __in DOUBLE Vel, __in DOUBLE Accel, __in DOUBLE Decel, __in DOUBLE RevVel);

	// ���� ���� �ӵ� ���� ���¸� ��ȯ.
	// [Axis: ���� �� ��ȣ, SpeedMode: �������� �ӵ� ��� ��ȯ, Vel: �������� �۾� �ӵ� ��ȯ, Accel:�������� ���ӵ� ��ȯ, Decel:�������� ���ӵ� ��ȯ, RevVel: Revers Speed ��ȯ]
	EXTERN LONG (__stdcall *cemHomeSpeedPattern_Get)	(__in LONG Axis, __out PLONG SpeedMode, __out PDOUBLE Vel, __out PDOUBLE Accel, __out PDOUBLE Decel, __out PDOUBLE RevVel);

	// ���� ���� ���� �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [Axis: ���� �� ��ȣ, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemHomeMove)	(__in LONG Axis, __in LONG IsBlocking);

	// ���� ���� ���� �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Axis: ���� �� ��ȣ]
	EXTERN LONG (__stdcall *cemHomeMoveStart)	(__in LONG Axis);

	// ���� ���� ���� �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [NumAxes: �۾� ��� �� ��, AxisList: ��� ���� �迭 �ּ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemHomeMoveAll)	(__in LONG NumAxes, __in PLONG AxisList, __in LONG IsBlocking);

	// ���� ���� ���� �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	//[NumAxes: �۾� ��� �� ��, AxisList: ��� ���� �迭 �ּ�]
	EXTERN LONG (__stdcall *cemHomeMoveAllStart)	(__in LONG NumAxes, __in PLONG AxisList);

	// ������ ����� �������� ���� �Ϸ� ���¸� Ȯ��.
	// [Axis: ���� �� ��ȣ, IsSuccess: ������ ����� ���� ���� ���� �Ϸ� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemHomeSuccess_Get)	(__in LONG Axis, __out PLONG IsSuccess);

	// ������ ����� �������� ���� �Ϸ� ���¸� ������ ����.
	// [Axis: ���� �� ��ȣ, IsSuccess: ���� ������ ���� ���θ� ������ ����]
	EXTERN LONG (__stdcall *cemHomeSuccess_Set)	(__in LONG Axis, __in LONG IsSuccess);

	// �������� ���� ���¸� ��ȯ.
	// [Axis: ���� �� ��ȣ, IsBusy: ���� �������� ���� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemHomeIsBusy)	(__in LONG Axis, __out PLONG IsBusy);

	// �������� �Ϸ� �ñ��� ���.
	// [Channel: ���� �� ��ȣ, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemHomeWaitDone)	(__in LONG Axis, __in LONG IsBlocking);


	//****************************************************************************
	//*************** START OF SINGLE AXIS CONTROL FUNCTION DECLARATIONS *********
	//****************************************************************************

	// ���� ���� �� �ش� �࿡ ���� �ӵ���� �� �ӵ����� ����.
	// [Axis: ���� �� ��ȣ, SpeedMode: �ӵ� ���, VelRatio: �۾��ӵ� ����(%), AccRatio: ���ӵ� ����(%), DecRatio: ���ӵ� ����(%)]
	EXTERN LONG (__stdcall *cemSxSpeedRatio_Set)	(__in LONG Axis, __in LONG SpeedMode, __in DOUBLE VelRatio, __in DOUBLE AccRatio, __in DOUBLE DecRatio);

	// ���� ���� �� �ش� �࿡ ���� �ӵ���� �� �ӵ����� ���� ���¸� ��ȯ.
	// [Axis: ���� �� ��ȣ, SpeedMode: �ӵ� ��� ��ȯ, VelRatio: �۾��ӵ� ����(%) ��ȯ, AccRatio: ���ӵ� ����(%) ��ȯ, DecRatio: ���ӵ� ����(%) ��ȯ]
	EXTERN LONG (__stdcall *cemSxSpeedRatio_Get)	(__in LONG Axis, __out PLONG SpeedMode, __out PDOUBLE VelRatio, __out PDOUBLE AccRatio, __out PDOUBLE DecRatio);

	// ���� ��� ��ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [Axis: ���� �� ��ȣ, Distance: �̵��� �Ÿ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemSxMove)	(__in LONG Axis, __in DOUBLE Distance, __in LONG IsBlocking);

	// ���� ��� ��ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Axis: ���� �� ��ȣ, Distance: �̵��� �Ÿ�]
	EXTERN LONG (__stdcall *cemSxMoveStart)	(__in LONG Axis, __in DOUBLE Distance);

	// ���� ���� ��ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [Axis: ���� �� ��ȣ, Distance: �̵��� ���� ��ǥ��, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemSxMoveTo)	(__in LONG Axis, __in DOUBLE Position, __in LONG IsBlocking);

	// ���� ���� ��ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Axis: ���� �� ��ȣ, Distance: �̵��� ���� ��ǥ ��]
	EXTERN LONG (__stdcall *cemSxMoveToStart)	(__in LONG Axis, __in DOUBLE Position);	

	// ���� ���� �ӵ� �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Axis: ���� �� ��ȣ, Direction: ��� �̼� ����]
	EXTERN LONG (__stdcall *cemSxVMoveStart)	(__in LONG Axis, __in LONG Direction);

	// ���� �̼� ���� �� ����.
	// [Axis: ���� �� ��ȣ, IsWaitComplete: ���� �Ϸ�ɶ����� �Լ� ��ȯ ����, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemSxStop)	(__in LONG Axis, __in LONG IsWaitComplete, __in LONG IsBlocking);

	// ���� �̼� ��� ����.
	// [Axis: ���� �� ��ȣ]
	EXTERN LONG (__stdcall *cemSxStopEmg)	(__in LONG Axis);

	// ���� �̼� �Ϸ� Ȯ��.
	// [Axis: ���� �� ��ȣ, IsDone: ��� �۾� �Ϸ� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemSxIsDone)	(__in LONG Axis, __out PLONG IsDone);

	// ���� �̼� �Ϸ� �������� ���.
	// [Axis: ���� �� ��ȣ, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemSxWaitDone)	(__in LONG Axis, __in LONG IsBlocking);

	// �ش� ���� �࿡ ���� ���������� �̼���(��� or ���� ��ǥ) ��ġ�� ��ȯ.
	// [Channel: ���� �� ��ȣ, Position: ���������� �̼��� ��ġ �� ��ȯ]
	EXTERN LONG (__stdcall *cemSxTargetPos_Get)	(__in LONG Channel, __out PDOUBLE Position);

	// ���� ����� �ʱ� �ӵ� ����.
	// [Axis: ���� �� ��ȣ, IniSpeed: �ʱ� �ӵ�]
	EXTERN LONG (__stdcall *cemSxOptIniSpeed_Set)	(__in LONG Axis, __in DOUBLE IniSpeed);

	// ���� ����� �ʱ� �ӵ� ������ ��ȯ.
	// [Axis: ���� �� ��ȣ, IniSpeed: �ʱ� �ӵ� ��ȯ]
	EXTERN LONG (__stdcall *cemSxOptIniSpeed_Get)	(__in LONG Axis, __out PDOUBLE IniSpeed);

	// ���� ����� RDP ������ ���� 
	// [Axis: ���� ��(ä��)��ȣ, OffsetDist:RDP ��ġ]
	EXTERN LONG (__stdcall *cemSxOptRdpOffset_Set)(__in LONG Axis, __in DOUBLE OffsetDist);

	// ���� ����� RDP ������ ��ȯ
	// [Axis: ���� ��(ä��)��ȣ, OffsetDist:RDP ��ġ ��ȯ]
	EXTERN LONG (__stdcall *cemSxOptRdpOffset_Get)(__in LONG Axis, __in PDOUBLE OffsetDist);
	
	// ���� ��� ��� ��ǥ 2�ܰ� �ӵ� �̼� ���. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Axis: ���� �� ��ȣ, Distance: �̵��� �Ÿ�(��� ��ǥ ��), Vel2: 2�ܰ� �۾� �ӵ�]
	EXTERN LONG (__stdcall *cemSxMoveStart2V)	(__in LONG Axis, __in  DOUBLE Distance, __in DOUBLE Vel2);

	// ���� ��� ���� ��ǥ 2�ܰ� �ӵ� �̼� ���. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Axis: ���� �³� ��ȣ, Position: �̵��� ��ġ (���� ��ǥ ��), Vel2: 2�ܰ� �۾� �ӵ�]
	EXTERN LONG (__stdcall *cemSxMoveToStart2V)	(__in LONG Axis, __in  DOUBLE Position, __in DOUBLE Vel2);

	// ���� ����� �鷡�� Ȥ�� ���� ������ ���� ����.
	// [Axis: ���� �� ��ȣ, CorrMode: ���� ���, CorrAmount: ���� �޽� ��, CorrVel: ���� �޽��� ��� ���ļ�, CntrMask: ���� �޽� ��½� ī������ ���� ����]
	EXTERN LONG (__stdcall *cemSxCorrection_Set)	(__in LONG Axis, __in LONG CorrMode, __in DOUBLE CorrAmount, __in DOUBLE CorrVel, __in LONG CntrMask);

	// ���� ����� �鷡�� Ȥ�� ���� ������ ������ ��ȯ.
	// [Axis: ���� �� ��ȣ, CorrMode: ���� ��� ��ȯ, CorrAmount: ���� �޽� �� ��ȯ, CorrVel: ���� �޽��� ��� ���ļ� ��ȯ, CntrMask: ���� �޽� ��½� ī������ ���� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemSxCorrection_Get)	(__in LONG Axis, __out PLONG CorrMode, __out PDOUBLE CorrAmount, __out PDOUBLE CorrVel, __out PLONG CntrMask);

	// ������ �ٸ� ��� ���� ���� ȯ�� ����.
	// [Axis: ���� �� ��ȣ, Mode: ���� ���, RefAxis: ���� ���� ��ȣ�� �߻��Ҷ� ������ �� Ȥ�� ����ũ, Condition: ���� ���� ��ȣ �߻� ����]
	EXTERN LONG (__stdcall *cemSxOptSyncMode_Set)	(__in LONG Axis, __in LONG Mode, __in LONG RefAxis, __in LONG Condition);

	// ������ �ٸ� ��� ���� ���ۿ� ���� ���� ��ȯ.
	// [Axis: ���� �� ��ȣ, Mode: ���� ��� ��ȯ, RefAxis: ���� ���� ��ȣ�� �߻��Ҷ� ������ �� Ȥ�� ����ũ�� ��ȯ, Condition: ���� ���� ��ȣ �߻� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemSxOptSyncMode_Get)	(__in LONG Axis, __out PLONG Mode, __out PLONG RefAxis, __out PLONG Condition);

	// ��� �ӵ� ���� �� ������ ��� ����.
	// [Axis: ���� �� ��ȣ, Mode: ��� ������ ��� �߻� ���, DoChan_local: ������ ��� ä�� ��ȣ, DoLogic: ������ ��� ä���� ����]
	//EXTERN LONG (__stdcall *cemSxOptSyncOut_Set)	(__in LONG Axis, __in LONG Mode, __in LONG DoChan_local, __in LONG DoLogic);

	// ��� �ӵ� ���� �� ������ ��� ���� ��ȯ.
	// [Axis: ���� �� ��ȣ, Mode: ��� ������ ��� �߻� ��� ��ȯ, DoChan_local: ������ ��� ä�� ��ȣ ��ȯ, DoLogic: ������ ��� ä���� ���� ��ȯ]
	//EXTERN LONG (__stdcall *cemSxOptSyncOut_Get)	(__in LONG Axis, __out PLONG Mode, __out PLONG DoChan_local, __out PLONG DoLogic);

	// RDP(Ramping Down Point)�� ������ ����. (���� ������ ��� ��ġ ����.)
	// [Axis: ���� �� ��ȣ, OffsetDist: RDP Offset ���� �Ÿ�]
	//EXTERN LONG (__stdcall *cemSxOptRdpOffset_Set)	(__in LONG Axis, __in DOUBLE OffsetDist);

	// RDP(Ramping Down Point)�� ������ ��ȯ. (���� ������ ��� ��ġ ��ȯ.)
	// [Axis: ���� �� ��ȣ, OffsetDist: RDP Offset ���� �Ÿ� ��ȯ]
	//EXTERN LONG (__stdcall *cemSxOptRdpOffset_Get)	(__in LONG Axis, __out PDOUBLE OffsetDist);


	//****************************************************************************
	//*************** START OF MULTIPLE AXES CONTROL FUNCTION DECLARATIONS *******
	//****************************************************************************

	// ���� ��� ��ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, DistList: �̵��� �Ÿ����� �迭 �ּ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemMxMove)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE DistList, __in LONG IsBlocking);

	// ���� ��� ��ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	//[NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, DistList: �̵��� �Ÿ���(�����ǥ) �迭 �ּ�]
	EXTERN LONG (__stdcall *cemMxMoveStart)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE DistList);

	// ���� ���� ��ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, PosList: �̵��� ��ġ��(������ǥ) �迭 �ּ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemMxMoveTo)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE PosList, __in LONG IsBlocking);

	// ���� ���� ��ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, PosList: �̵��� ��ġ��(������ǥ) �迭 �ּ�]
	EXTERN LONG (__stdcall *cemMxMoveToStart)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE PosList);

	// ���� ���Ӽӵ� �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, DirList: ������ �����ϴ� ���� �迭 �ּ�]
	EXTERN LONG (__stdcall *cemMxVMoveStart)	(__in LONG NumAxes, __in PLONG AxisList, __in PLONG DirList);

	// ���� �̼� ��Ȥ �� ����.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, IsWaitComplete: ���� �Ϸ�ɶ����� �Լ� ��ȯ ����, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemMxStop)	(__in LONG NumAxes, __in PLONG AxisList, __in LONG IsWaitComplete, __in LONG IsBlocking);

	// ���� �̼� ��� ����.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�]
	EXTERN LONG (__stdcall *cemMxStopEmg)	(__in LONG NumAxes, __in PLONG AxisList);

	// ���� �̼� �Ϸ� Ȯ��.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, IsDone: ����۾� �Ϸ� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemMxIsDone)	(__in LONG NumAxes, __in PLONG AxisList, __out PLONG IsDone);

	// ���� �̼� �Ϸ� �������� ���.
	// [NumAxes: ��� �� ��, AxisList: ��� ���� �迭 �ּ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemMxWaitDone)	(__in LONG NumAxes, __in PLONG AxisList, __in LONG IsBlocking);

	//****************************************************************************
	//*************** START OF INTERPOLATION CONTROL FUNCTION DECLARATIONS *******
	//****************************************************************************

	// ���� ��� �� �׷� ����.
	// [MapIndex: �� ��ȣ(0~7), NodeID: ��� ��ȣ, MapMask1: �� �ʿ� ������ ����� ������ ����ũ��(���� 32��Ʈ, BIT0~BIT31),
	// MapMask2: �� �ʿ� ������ ����� ������ ����ũ��(���� 32��Ʈ, BIT32~BIT63)]
	EXTERN LONG (__stdcall *cemIxMapAxes)	(__in LONG MapIndex,__in LONG NodeID, __in LONG MapMask1, __in LONG MapMask2);

	// ���� �ӵ� ������� ���� [MapIndex: �� ��ȣ, �ɼ�1: VelCorrOpt1, �ɼ�2: VelCorrOpt2] 
	EXTERN LONG (__stdcall *cemIxVelCorrMode_Set)	(__in LONG MapIndex, __in LONG VelCorrOpt1, __in LONG VelCorrOpt2);

	// ���� �ӵ� ������� ��ȯ [MapIndex: �� ��ȣ, �ɼ�1: VelCorrOpt1, �ɼ�2: VelCorrOpt2]
	EXTERN LONG (__stdcall *cemIxVelCorrMode_Get)	(__in LONG MapIndex, __out PLONG VelCorrOpt1, __out PLONG VelCorrOpt2);

	// ���� ��� �� �׷� ���� ����.
	// [MapIndex: �� ��ȣ]
	EXTERN LONG (__stdcall *cemIxUnMap)	(__in LONG MapIndex);

	// ���� �̼� �ӵ� ����.
	// [MapIndex: �� ��ȣ, IsVectorSpeed: ���� Ȥ�� ������ ���ǵ� ��� ����, SpeedMode: �ӵ� ���, Vel: �۾� �ӵ�, Acc: ���ӵ�, Dec: ���ӵ�]
	EXTERN LONG (__stdcall *cemIxSpeedPattern_Set)	(__in LONG MapIndex, __in LONG IsVectorSpeed, __in LONG SpeedMode, __in DOUBLE Vel, __in DOUBLE Acc, __in DOUBLE Dec);

	// ���� �̼� �ӵ� ������ ��ȯ.
	// [MapIndex: �� ��ȣ, IsVectorSpeed: ���� Ȥ�� ������ ���ǵ� ��� ���� ��ȯ, SpeedMode: �ӵ� ��� ��ȯ, Vel: �۾� �ӵ� ��ȯ, Acc: ���ӵ� ��ȯ, Dec: ���ӵ� ��ȯ]
	EXTERN LONG (__stdcall *cemIxSpeedPattern_Get)	(__in LONG MapIndex, __out PLONG IsVectorSpeed, __out PLONG SpeedMode, __out PDOUBLE Vel, __out PDOUBLE Acc, __out PDOUBLE Dec);

	// ���� ���� �����ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, DistList: �̵��� �Ÿ���(�����ǥ) �迭 �ּ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxLine)	(__in LONG MapIndex, __in PDOUBLE DistList, __in LONG IsBlocking);

	// ���� ���� �����ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, DistList: �̵��� �Ÿ���(�����ǥ) �迭 �ּ�]
	EXTERN LONG (__stdcall *cemIxLineStart)	(__in LONG MapIndex, __in PDOUBLE DistList);

	// ���� ���� ������ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, PosList: �̵��� ��ġ��(������ǥ) �迭 �ּ�, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxLineTo)	(__in LONG MapIndex, __in PDOUBLE PosList, __in LONG IsBlocking);

	// ���� ���� ������ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, PosList: �̵��� ��ġ��(������ǥ) �迭 �ּ�]
	EXTERN LONG (__stdcall *cemIxLineToStart)	(__in LONG MapIndex, __in PDOUBLE PosList);
	
	EXTERN LONG (__stdcall *cemIxLineStart_Fx)	(__in LONG MapIndex, __in PDOUBLE DistList);
	EXTERN LONG (__stdcall *cemIxLineToStart_Fx)	(__in LONG MapIndex, __in PDOUBLE PosList);

	// ��ȣ ���� �����ǥ(����� �߽���ǥ�� ����) �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, XCentOffset: ���� ��ġ�κ��� ���� �߽ɱ��� X�� �����ǥ, YCentOffset: ���� ��ġ���� ���� �߽ɱ��� Y�� �����ǥ,
	// EndAngle: ��ȣ ������ �Ϸ��� ��ǥ������ ���� ��ġ�� ���� ����(Degree), IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxArcA)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// ��ȣ ���� �����ǥ(����� �߽���ǥ�� ����) �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, XCentOffset: ���� ��ġ�κ��� ���� �߽ɱ��� X�� �����ǥ, YCentOffset: ���� ��ġ�κ��� ���� �߽ɱ��� Y�� �����ǥ,
	// EndAngle: ��ȣ ������ �Ϸ��� ��ǥ ������ ���� ��ġ�� ���� ����(Degree)]
	EXTERN LONG (__stdcall *cemIxArcAStart)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE EndAngle);

	// ��ȣ ���� ������ǥ(������ �߽���ǥ�� ����) �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, XCent: �߽����� X�� ������ǥ, YCent: �߽����� Y�� ������ǥ,
	// EndAngle: ��ȣ ������ �Ϸ��� ��ǥ ������ ���� ��ġ�� ���� ����(Degree), IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxArcATo)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// ��ȣ ���� ������ǥ(������ �߽���ǥ�� ����) �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, XCent: �߽����� X�� ������ǥ, YCent: �߽����� Y�� ������ǥ, EndAngle: ��ȣ ������ �Ϸ��� ��ǥ ������ ���� ��ġ�� ���� ����(Degree)]
	EXTERN LONG (__stdcall *cemIxArcAToStart)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE EndAngle);

	// ��ȣ���� �����ǥ(����� �߽���ǥ�� ������ǥ) �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, XCentOffset: ���� ��ġ���� �� �߽ɱ��� X����� �Ÿ�, YCentOffset: ���� ��ġ���� �� �߽ɱ��� Y����� �Ÿ�,
	// XEndPointDist: ��ȣ���� �̵��� �Ϸ��� ��ǥ������ ���� ��ġ�κ��� X��� �Ÿ�, YEndPointDist: ��ȣ ���� �̵��� �Ϸ��� ��ǥ������ ������ġ�� ������ Y��� �Ÿ�, Direction: ȸ�� ����, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ���� ]
	EXTERN LONG (__stdcall *cemIxArcP)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction, __in LONG IsBlocking);

	// ��ȣ���� �����ǥ(����� �߽���ǥ�� ������ǥ) �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, XCentOffset: �� ��ġ���� �� �߽ɱ��� X����� �Ÿ�, YCentOffset: �� ��ġ���� �� �߽ɱ��� Y����� �Ÿ�,
	// XEndPointDist: ��ȣ ���� �̵��� �Ϸ��� ��ǥ������ ������ġ�� ������ X��� �Ÿ�, YEndPointDist: ��ȣ ���� �̵��� �Ϸ��� ��ǥ������ ������ġ�� ������ Y��� �Ÿ�, Direction: ȸ�� ����]
	EXTERN LONG (__stdcall *cemIxArcPStart)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction);

	// ��ȣ���� ������ǥ(������ �߽���ǥ�� ������ǥ) �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, XCent: �߽����� X�� ������ǥ, YCent: �߽����� Y�� ������ǥ, XEndPointDist: ��ȣ���� �̵��� �Ϸ��� ��ǥ������ X�� ������ǥ,
	// YEndPointDist: ��ȣ���� �̵��� �Ϸ��� ��ǥ������ Y�� ������ǥ, Direction: ȸ�� ����, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxArcPTo)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction, __in LONG IsBlocking);

	// ��ȣ���� ������ǥ(������ �߽���ǥ�� ������ǥ) �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, XCent: �߽����� X�� ������ǥ, YCent: �߽����� Y�� ������ǥ, XEndPointDist: ��ȣ���� �̵��� �Ϸ��� ��ǥ������ X�� ������ǥ,
	// YEndPointDist: ��ȣ���� �̵��� �Ϸ��� ��ǥ������ Y�� ������ǥ, Direction: ȸ�� ����]
	EXTERN LONG (__stdcall *cemIxArcPToStart)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction);

	// 3��(Point)�� ���� ��ȣ���� �����ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, P2X: ���� ��ġ���� 2��° ������ X�� �����ǥ, P2Y: ���� ��ġ���� 2��° ������ Y�� �����ǥ,
	// P3X: 2��° ������ 3��° ������ X�� �����ǥ, P3Y: 2��° ������ 3��° ������ Y�� �����ǥ, EndAngle: ������, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxArc3P)	(__in LONG MapIndex, __in DOUBLE P2X,__in  DOUBLE P2Y,__in  DOUBLE P3X, __in DOUBLE P3Y, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// 3��(Point)�� ���� ��ȣ���� �����ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, P2X: ���� ��ġ���� 2��° ������ X�� �����ǥ, P2Y: ���� ��ġ���� 2��° ������ Y�� �����ǥ,
	// P3X: 2��° ������ 3��° ������ X�� �����ǥ, P3Y: 2��° ������ 3��° ������ Y�� �����ǥ, EndAngle: ������]
	EXTERN LONG (__stdcall *cemIxArc3PStart)	(__in LONG MapIndex, __in DOUBLE P2X, __in DOUBLE P2Y, __in DOUBLE P3X,__in  DOUBLE P3Y,__in  DOUBLE EndAngle);

	// 3��(Point)�� ���� ��ȣ���� ������ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [MapIndex: �� ��ȣ, P2X: 2��° ���� X�� ������ǥ, P2Y: 2��° ���� Y�� ������ǥ,
	// P3X: 3��° ���� X�� ������ǥ, P3Y: 3��° ���� Y�� ������ǥ, EndAngle: ������, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxArc3PTo)	(__in LONG MapIndex, __in DOUBLE P2X,__in  DOUBLE P2Y,__in  DOUBLE P3X, __in DOUBLE P3Y, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// 3��(Point)�� ���� ��ȣ���� ������ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [MapIndex: �� ��ȣ, P2X: 2��° ���� X�� ������ǥ, P2Y: 2��° ���� Y�� ������ǥ, P3X: 3��° ���� X�� ������ǥ, P3Y: 3��° ���� Y�� ������ǥ, EndAngle: ������]
	EXTERN LONG (__stdcall *cemIxArc3PToStart)	(__in LONG MapIndex, __in DOUBLE P2X, __in DOUBLE P2Y, __in DOUBLE P3X, __in DOUBLE P3Y, __in DOUBLE EndAngle);

	// ���� ���� ���� �̼� ���� �� ����.
	// [MapIndex: �� ��ȣ]
	EXTERN LONG (__stdcall *cemIxStop)	(__in LONG MapIndex);

	// ���� ���� ���� �̼� �������.
	// [MapIndex: �� ��ȣ]
	EXTERN LONG (__stdcall *cemIxStopEmg)	(__in LONG MapIndex);

	// ���� ���� ���� �̼��� ���� �Ϸ� Ȯ��.
	// [MapIndex: �� ��ȣ, IsDone: ���� ���� ���� �̼��� ���� �Ϸ� ����]
	EXTERN LONG (__stdcall *cemIxIsDone)	(__in LONG MapIndex, __out PLONG IsDone);

	// ���� ���� ���� �̼��� ���� �Ϸ� �������� ���.
	// [MapIndex: �� ��ȣ, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemIxWaitDone)	(__in LONG MapIndex, __in LONG IsBlocking);

	EXTERN LONG (__stdcall *cemIxMasterAxis_Set)	(__in LONG nAxis, __in LONG bSetValue);
	EXTERN LONG (__stdcall *cemIxMasterAxis_Get)	(__in LONG nAxis, __out PLONG bSetValue);
	EXTERN LONG (__stdcall *cemIxSmartDecel_Set)	(__in LONG nAxis, __in LONG bSetValue);
	EXTERN LONG (__stdcall *cemIxSmartDecel_Get)	(__in LONG nAxis, __out PLONG bSetValue);
	EXTERN LONG (__stdcall *cemIxSmartStop)	(__in LONG nIxMapIndex, __in DOUBLE decelTimeSec);

	// �︮�� ���� �̼� �ӵ� ���� �� ���� ȯ�� ����.
	// [HelId: �︮�� ���� �̼� �۾��� ID, Master: ������ �ӵ� ���� , SpeedMode: �ӵ� ���, WorkSpeed: �۾� �ӵ�, Acc:���ӵ�, Dec:���ӵ�]
	// EXTERN LONG (__stdcall *cemIxxHelOnceSpeed_Set)	(__in LONG HelId, __in LONG Master, __in LONG SpeedMode, __in DOUBLE WorkSpeed, __in DOUBLE Acc, __in DOUBLE Dec);

	// �︮�� ���� �̼� �ӵ� ���� �� ���� ȯ�� ���� ��ȯ.
	// [HelId: �︮�� ���� �̼� �۾��� ID, Master: ������ �ӵ� ���� ��ȯ, SpeedMode: �ӵ� ��� ��ȯ, WorkSpeed: �۾� �ӵ� ��ȯ, Acc:���ӵ� ��ȯ, Dec:���ӵ� ��ȯ]
	// EXTERN LONG (__stdcall *cemIxxHelOnceSpeed_Get)	(__in LONG HelId, __out PLONG SpeedMaster, __out PLONG SpeedMode, __out PDOUBLE WorkSpeed, __out PDOUBLE Acc, __out PDOUBLE Dec);

	// �︮�� �����̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [HelId: �︮�� ���� �̼� �۾��� ID, NumAxes: �︮�� ������ ���Ǵ� �� ��(3 or 4), AxisList: ��� �� �迭 �ּ�,
	// CoordList: ��ǥ �迭 �ּ�, ArcAngle: ��ȣ ���� �̵� ����, DistU: U�� �̼� �Ÿ� ��ȯ, IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	// EXTERN LONG (__stdcall *cemIxxHelOnce)	(__in LONG HelId, __in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE CoordList, __in DOUBLE ArcAngle, __out PDOUBLE DistU, __in LONG IsBlocking);

	// �︮�� �����̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [HelId: �︮�� ���� �̼� �۾��� ID, NumAxes: �︮�� ������ ���Ǵ� �� ��(3 or 4), AxisList: ��� �� �迭 �ּ�,
	// CoordList: ��ǥ �迭 �ּ�, ArcAngle: ��ȣ ���� �̵� ����, DistU: U�� �̼� �Ÿ� ��ȯ]
	// EXTERN LONG (__stdcall *cemIxxHelOnceStart)	(__in LONG HelId, __in Long NumAxes, __in PLONG AxisList, __in PDOUBLE CoordList, __in DOUBLE ArcAngle, __out PDOUBLE DistU);

	// Cubic Spline ���� ������ ��ǥ ��ǥ ����.
	// [InArray: ���ö��� ������ ������ ���� ������ ����Ʈ �迭, NumInArray: ���� �������� ��,
	// OutArray: ���ö��� ������ �����Ͽ� �ڵ� ������ ����� �����͸� ������ �迭�� �ּ�, NumOutArray: ���ö��� ������ �����Ͽ� �ڵ� ������ ������ ��]
	// EXTERN LONG (__stdcall *cemIxxSplineBuild)	(__in PDOUBLE InArray, __in LONG NumInArray, __out PDOUBLE OutArray, __in LONG NumOutArray);

	//****************************************************************************
	//*************** START OF MASTER/SLAVE CONTROL FUNCTION DECLARATIONS ********
	//****************************************************************************

	// ��� ��� �࿡ ���ؼ�, Master/Slave ���� ������ Slave ������ ���.
	// [Axis: Slave ������ ������ ���� �� ��ȣ, MaxSpeed: Slave�� ���� �ִ� �ӵ�, IsInverse: Slave�� �� Master���� ���������� �ݴ�� �Ұ����� ����]
	EXTERN LONG (__stdcall *cemMsRegisterSlave)	(__in LONG Axis, __in DOUBLE MaxSpeed, __in LONG IsInverse);

	// ��� ��� �࿡ ���ؼ�, Master/Slave ���� ������ Slave �� ����.
	// [Axis: Slave �࿡�� ������ ���� �� ��ȣ]
	EXTERN LONG (__stdcall *cemMsUnregisterSlave)	(__in LONG Axis);

	// ��� ��� �࿡ ���ؼ�, Master/Slave ���� ������ Slave �� ��� ���� ȯ��.
	// [SlaveAxis: Slave ���¸� Ȯ���� ��� ���� �� ��ȣ, SlaveState: Slave �� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemMsCheckSlaveState)	(__in LONG SlaveAxis, __out PLONG SlaveState);

	// ��� ��� �࿡ ���ؼ�, Master/Slave ���� ������ Master ���� ���� �� ��ȣ�� Ȯ��.
	// [SlaveAxis: Slave ���� �� ��ȣ, MasterAxis: Master ���� �� ��ȣ]
	EXTERN LONG (__stdcall *cemMsMasterAxis_Get)	(__in LONG SlaveAxis, __out PLONG MasterAxis);

	//****************************************************************************
	//*************** START OF LISTMOTION FUNCTION DECLARATIONS ******************
	//****************************************************************************

	EXTERN LONG (__stdcall *cemLmBeginList)	(__in LONG LmMapIndex, __in LONG NodeID, __in LONG MapMask);

	EXTERN LONG (__stdcall *cemLmEndList)	(__in LONG LmMapIndex);

	EXTERN LONG (__stdcall *cemLmStart)	(__in LONG LmMapIndex);

	EXTERN LONG (__stdcall *cemLmStop)	(__in LONG LmMapIndex, __in LONG StopMode, __in LONG DecTime_ms, __in LONG IsClearQue);

	EXTERN LONG (__stdcall *cemLmIsDone) (__in LONG LmMapIndex, __out PLONG IsDone);

	EXTERN LONG (__stdcall *cemLmSetStepID_Reg)	(__in LONG LmMapIndex, __in LONG nStepId);

	EXTERN LONG (__stdcall *cemLmGetStepID_Reg)	(__in LONG LmMapIndex, __out PLONG nStepId);

	EXTERN LONG (__stdcall *cemLmGetInfo)	(__in LONG LmMapIndex, __out PLONG LmFlag, __out PLONG QueFreeSpace,__out PLONG RunStepCnt, __out PLONG RunStepId);

	EXTERN LONG (__stdcall *cemLmSetUserPara_Reg)	(__in LONG LmMapIndex, __in LONG nParamIndex, __in LONG nParamVal);

	EXTERN LONG (__stdcall *cemLmGetUserPara_Reg)	(__in LONG LmMapIndex, __in LONG nParamIndex, __in PLONG nParamVal);

	EXTERN LONG (__stdcall *cemLmGetUserPara_Run)	(__in LONG LmMapIndex, __in LONG nParamIndex, __in PLONG nParamVal);

	//****************************************************************************
	//*************** START OF Manual Pulsar FUNCTION SECTION ********************
	//****************************************************************************

	// Manual Pulsar �Է� ��ȣ�� ���� ȯ�漳��.
	// [Channel: ���� �� ��ȣ, InputMode: Pulsar �Է� ��ȣ�� �Է� ���, IsInverse: Pulsar �Է� ��ȣ�� ��Ÿ���� ����� ����� ���� ��ġ ����]
	EXTERN LONG (__stdcall *cemPlsrInMode_Set)	(__in LONG Channel, __in  LONG InputMode,   __in  LONG IsInverse);

	// Manual Pulsar �Է� ��ȣ�� ���� ȯ�漳�� ��ȯ.
	// [Channel: ���� �� ��ȣ, InputMode: Pulsar �Է� ��ȣ�� �Է� ��� ��ȯ, Pulsar �Է� ��ȣ�� ��Ÿ���� ����� ����� ���� ��ġ ���� ��ȯ]
	EXTERN LONG (__stdcall *cemPlsrInMode_Get)	(__in LONG Channel, __out PLONG InputMode, __out  PLONG IsInverse);

	// Manual Pulsar�� PA/PB �Է��޽� ���, ����޽� ���� ���� ���� ����.
	// [Channel: ���� �� ��ȣ, GainFactor: PMG ȸ�ο� �����Ǵ� ����� ����(1~32), DivFactor: PDIV ȸ�ο� �����Ǵ� ����� ����(1~2048)]
	EXTERN LONG (__stdcall *cemPlsrGain_Set)	(__in LONG Channel, __in  LONG GainFactor,  __in  LONG DivFactor);

	// Manual Pulsar�� PA/PB �Է��޽� ���, ����޽� ���� ���� ���� ���� ��ȯ.
	// [Channel: ���� �� ��ȣ, GainFactor: PMG ȸ�ο� �����Ǵ� ����� ���� ��ȯ, DivFactor: PDIV ȸ�ο� �����Ǵ� ����� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemPlsrGain_Get)	(__in LONG Channel, __out  PLONG GainFactor, __out PLONG DivFactor);
	//
	// Manual Pulsar �Է� ��ȣ�� ���� �������� �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Channel: ���� �� ��ȣ, HomeType: Pulsar Input�� ���� ���� ���� ���� ���]
	EXTERN LONG (__stdcall *cemPlsrHomeMoveStart)	(__in LONG Channel, __in  LONG  HomeType);

	// Manual Pulsar �Է� ��ȣ�� ���� �����ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [Channel: ���� �� ��ȣ, Distance: �̵��� �Ÿ�(�����ǥ), IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemPlsrMove)	(__in LONG Channel, __in DOUBLE Distance, __in LONG IsBlocking);

	// Manual Pulsar �Է� ��ȣ�� ���� �����ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Channel: ���� �� ��ȣ, Distance: �̵��� �Ÿ�(�����ǥ)]
	EXTERN LONG (__stdcall *cemPlsrMoveStart)	(__in LONG Channel, __in DOUBLE Distance);

	// Manual Pulsar �Է� ��ȣ�� ���� ������ǥ �̼�. �� �Լ��� ����� �Ϸ�Ǳ� ������ ��ȯ���� �ʽ��ϴ�.
	// [Channel: ���� �� ��ȣ, Position: �̵��� ��ġ(������ǥ), IsBlocking: �Ϸ�ɶ����� �޼��� ��� ����]
	EXTERN LONG (__stdcall *cemPlsrMoveTo)         (__in LONG Channel, __in DOUBLE Position, __in LONG IsBlocking);

	// Manual Pulsar �Է� ��ȣ�� ���� ������ǥ �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Channel: ���� �� ��ȣ, Position: �̵��� ��ġ(������ǥ)]
	EXTERN LONG (__stdcall *cemPlsrMoveToStart)    (__in LONG Channel, __in DOUBLE Position);

	// Manual Pulsar �Է� ��ȣ�� ���� ���Ӽӵ� �̼�. �� �Լ��� ����� ���۽�Ų �Ŀ� �ٷ� ��ȯ�˴ϴ�.
	// [Channel: ���� �� ��ȣ]
	EXTERN LONG (__stdcall *cemPlsrVMoveStart)	(__in LONG Channel);

	//****************************************************************************
	//*************** START OF OVERRIDE FUNCTION DECLARATIONS ********************
	//****************************************************************************

	// ���� �̼� �۾� �߿� �ӵ��� ����.
	// [Axis: ���� �� ��ȣ]
	EXTERN LONG (__stdcall *cemOverrideSpeedSet)	(__in LONG Axis);

	// ���� �̼� �۾� �߿� ��� ��鿡 ���Ͽ� ���ÿ� �ӵ��� ����.
	// [NumAxes : ���ÿ� �۾��� ������ ��� ���� ��, AxisList : ���ÿ� �۾��� ������ ��� ���� �迭 �ּ�]
	// EXTERN LONG (__stdcall *cemOverrideSpeedSetAll)	(__in LONG NumAxes, __in LONG AxisList);

	// ��������ǥ �̼� �߿�, �����ǥ���� ��ǥ �� �Ÿ����� ����.
	// [Axis: ���� �� ��ȣ, NewDistance: ���ο� ��ǥ �Ÿ�(�����ǥ), IsHardApply: Override �Ұ� ��������, Override ������ ������ ���� ����, AppliedState: Override ���� ���� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemOverrideMove)	(__in LONG Axis, __in DOUBLE NewDistance, __in LONG IsHardApply, __out PLONG AppliedState);

	// ����������ǥ �̼� �߿�, ������ǥ���� ��ǥ � �Ÿ����� ����.
	// [Axis: ���� �� ��ȣ, NewPosition: ���ο� ��ǥ �Ÿ�(������ǥ), IsHardApply: Override �Ұ� ��������, Override ������ ������ ���� ����, AppliedState: Override ���� ���� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemOverrideMoveTo)	(__in LONG Axis, __in DOUBLE NewPosition, __in LONG IsHardApply, __out PLONG AppliedState);

	//****************************************************************************
	//*************** START OF MONITORING FUNCTION DECLARATIONS ******************
	//****************************************************************************

	// ��� ���� ������ �ϵ���� ī���� ��(�޽���) ����. Target ���� ceSDKDef.h ���Ͽ� ���ǵ� enum _TCnmCntr �� ����Ʈ�� ����.
	// [Axis: ���� �� ��ȣ, Target: ������ ī���� ��ȣ, Count: ��� ī���� ��(PPS)]
	EXTERN LONG (__stdcall *cemStCount_Set)	(__in LONG Axis, __in LONG Target, __in LONG Count);

	// ��� ���� ������ �ϵ���� ī���� ��(�޽���) ��ȯ. Target ���� ceSDKDef.h ���Ͽ� ���ǵ� enum _TCnmCntr �� ����Ʈ�� ����.
	// [Axis: ���� �� ��ȣ, Source: ���� ���� ī���� ��ȣ, Count: ��� ī���� ��(PPS) ��ȯ]
	EXTERN LONG (__stdcall *cemStCount_Get)	(__in LONG Axis, __in LONG Source, __out PLONG Count);

	// ��� ���� ������ ���� ī���� ��(���� �Ÿ�) ����. Target ���� ceSDKDef.h ���Ͽ� ���ǵ� enum _TCnmCntr �� ����Ʈ�� ����.
	// [Axis: ���� �� ��ȣ, Target: ������ ī���� ��ȣ, Position: ��� ī���� ��(���� �Ÿ�)]
	EXTERN LONG (__stdcall *cemStPosition_Set)	(__in LONG Axis, __in LONG Target, __in DOUBLE Position);

	// ��� ���� ������ ���� ī���� ��(���� �Ÿ�) ��ȯ. Target ���� ceSDKDef.h ���Ͽ� ���ǵ� enum _TCnmCntr �� ����Ʈ�� ����.
	// [Axis: ���� �� ��ȣ, Source: ���� ���� ī���� ��ȣ, Position: ��� ī���� ��(���� �Ÿ�) ��ȯ]
	EXTERN LONG (__stdcall *cemStPosition_Get)	(__in LONG Axis, __in LONG Source, __out PDOUBLE Position);

	// ��� ���� ���� �ӵ� ��ȯ. Target ���� ceSDKDef.h ���Ͽ� ���ǵ� enum _TCnmCntr �� ����Ʈ�� ����.
	// [Axis: ���� �� ��ȣ, Source: �ӵ� ��ȯ����� �Ǵ� ī���� ��ȣ, Speed: ������ Source�� �ӵ�(���� �ӵ�) ��ȯ]
	EXTERN LONG (__stdcall *cemStSpeed_Get)		(__in LONG Axis, __in LONG Source, __out PDOUBLE Speed);

	// ��� ���� ��� ���� ���� ��ȯ.
	// [Axis: ���� �� ��ȣ, MotStates: ��� ���� ��ȯ]
	EXTERN LONG (__stdcall *cemStReadMotionState)	(__in LONG Axis, __out PLONG MotStates);

	// ��� ���� ��� ���� I/O ���� ��ȯ.
	// [Axis: ���� �� ��ȣ, MiotStates: Machine I/O ���� ��ȯ]
	EXTERN LONG (__stdcall *cemStReadMioStatuses)	(__in LONG Axis, __out PLONG MioStates);

	// ��� ���ۻ��¿� ���õ� ���ڿ� ��ȯ. cemStReadMotionState() �Լ��� ���� ���� ��� ����.
	// [MstCode: ��� ���� ���� ��, Buffer: ��� ���ۻ��¸� ���� ���ڿ� ������ �ּ� ��ȯ, Bufferlen: ���ڿ� ������ ����]
	EXTERN LONG (__stdcall *cemStGetMstString)	(__in LONG MstCode, __out PCHAR Buffer, __in LONG BufferLen);

	// ���ŵ� I/O �޽��� ���� ��ȯ.
	// [IOMessageCount: I/O �޽��� ��]
	EXTERN LONG (__stdcall *cemStReadIOMessageCount)	(__out PDWORD IOMessageCount);

	//****************************************************************************
	//*************** START OF LTC FUNCTION DECLARATIONS *************************
	//****************************************************************************

	// �ش����� LTC ī���� Ȱ��ȭ ���� Ȯ�� [Axis: ��(ä��)��ȣ, IsLatched: ī���� Ȱ��ȭ ���� ��ȯ]
	EXTERN LONG (__stdcall *cemLtcIsLatched)	(__in LONG Axis, __out PLONG IsLatched);

	// �ش����� LTC ī���� ���� Ȯ�� [Axis: ��(ä��)��ȣ, Counter: ��� ī����, LatchedPos: ������ ���� ��ġ�� ī��Ʈ �� ��ȯ]
	EXTERN LONG (__stdcall *cemLtcReadLatch)	(__in LONG Axis, __in LONG Counter, __out PDOUBLE LatchedPos);

	//****************************************************************************
	//*************** START OF CMP FUNCTION DECLARATIONS *************************
	//****************************************************************************

	EXTERN LONG (__stdcall *cemCmpGenConfig_Set)		(__in LONG Axis, __in  LONG CmpSrc, __in  LONG  CmpMethod, __in  LONG CmpAction,  __in  DOUBLE CmpData);

	EXTERN LONG (__stdcall *cemCmpGenConfig_Get)		(__in LONG Axis, __out PLONG CmpSrc,__out PLONG CmpMethod, __out PLONG CmpAction, __out PDOUBLE CmpData);

	EXTERN LONG (__stdcall *cemCmpTrgConfig_Set)		(__in LONG Axis, __in  LONG CmpSrc, __in  LONG CmpMethod);

	EXTERN LONG (__stdcall *cemCmpTrgConfig_Get)		(__in LONG Axis, __out PLONG CmpSrc, __out  PLONG CmpMethod);
	
	EXTERN LONG (__stdcall *cemCmpTrgOneData_Set)		(__in LONG Axis, __in  DOUBLE DataVal);
	
	EXTERN LONG (__stdcall *cemCmpTrgCurData_Get)		(__in LONG Axis, __out PDOUBLE DataVal);

	//****************************************************************************
	//*************** START OF ADVANCED FUNCTION DECLARATIONS ********************
	//****************************************************************************

	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cemAdvGetNodeInformation)	(__in LONG nNode, __out PTNode pTargetNode);

	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cemAdvGetAllNodeInformation)	(__out PTNodeInformation pTargetNodes);

#if 0
	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cmnAdvDownloadDefaultConfigure)	();

	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cemAdvUploadConfigure)	(__in LONG FileType, __in const PCHAR szFileName);

	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cemAdvDownloadConfigure)	(__in LONG FileType, __in const PCHAR szFileName);

	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cemAdvActiveNodeCount_Get)	(__out PLONG NumNode);

	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cemAdvActiveNodeID_Get)	(__in  LONG ArraySize, __out PLONG lArray, __out PLONG NumNode);
#endif

	// �ش� �࿡ ERC ��ȣ�� ����մϴ�.
	EXTERN LONG (__stdcall *cemAdvErcOut)				      (__in LONG Axis);

	// �ش� �࿡ ERC ��ȣ�� ����� �����մϴ�.
	EXTERN LONG (__stdcall *cemAdvErcReset)				  (__in LONG Axis);

	// Undocument Function �Դϴ�. �� �Լ��� ��� �����̳� �� ���������� ���˴ϴ�.
	EXTERN LONG (__stdcall *cemAdvManualPacket)			  (__in LONG NodeID, __in LONG CommandNo, __in PDOUBLE SendBuffer, __in LONG NumSendData, __out PDOUBLE RecvBuffer, __out LONG NumRecvData, __in LONG SendFlag, __in LONG RecvFlag);

	//****************************************************************************
	//*************** START OF SYSTEM DIO CONFIGURATION FUNCTION DECLARATIONS ****
	//****************************************************************************
	// �ý��� ������ ������� �����Ǵ� ��ǰ���� ���� ä�ο� ���ؼ� �Է��� Ȯ���մϴ�.
	EXTERN LONG (__stdcall *cemDiOne_Get)       (__in LONG Channel,     __out PLONG State);

	// �ý��� ������ ������� �����Ǵ� ��ǰ���� ���� ä�ο� ���ؼ� �Է��� Ȯ���մϴ�.
	EXTERN LONG (__stdcall *cemDiMulti_Get)		(__in LONG IniChannel,	__in LONG NumChannels, __out PLONG InputState);

	// �ý��� ������ ������� �����Ǵ� ��ǰ���� ���� ä�ο� ���ؼ� ����� �߻��մϴ�.
	EXTERN LONG (__stdcall *cemDoOne_Put)		(__in LONG Channel,		__in LONG OutState);

	// �ý��� ������ ������� �����Ǵ� ��ǰ���� ���� ä�ο� ���ؼ� ����� Ȯ���մϴ�.
	EXTERN LONG (__stdcall *cemDoOne_Get)		(__in LONG Channel,		__in PLONG OutState);

	// �ý��� ������ ������� �����Ǵ� ��ǰ���� ���� ä�ο� ���ؼ� ����� �߻��մϴ�.
	EXTERN LONG (__stdcall *cemDoMulti_Put)		(__in LONG IniChannel,	__in LONG NumChannels, __in LONG OutStates);

	// �ý��� ������ ������� �����Ǵ� ��ǰ���� ���� ä�ο� ���ؼ� ����� Ȯ���մϴ�.
	EXTERN LONG (__stdcall *cemDoMulti_Get)		(__in LONG IniChannel,	__in LONG NumChannels, __out PLONG OutStates);


	//****************************************************************************
	//*************** START OF INTERLOCK FUNCTION DECLARATIONS *******************
	//****************************************************************************
	EXTERN LONG (__stdcall *ceil_Set)						(__in LONG NodeID, __in LONG Interlock_Type, __in LONG bEnable);

	EXTERN LONG (__stdcall *ceil_Get)						(__in LONG NodeID, __in LONG Interlock_Type, __out PLONG bIsEnabled);

	EXTERN LONG (__stdcall *ceilDisconnectTimeout_Set)		(__in LONG NodeID, __in LONG Interlock_Type, __in LONG dwTimeOut);

	EXTERN LONG (__stdcall *ceilDisconnectTimeout_Get)		(__in LONG NodeID, __in LONG Interlock_Type, __out PLONG pdwTimeOut);

	EXTERN LONG (__stdcall *ceilActionModeOne_Set)			(__in LONG NodeID, __in LONG ModuleType, __in LONG Channel, __in LONG ActionMode);

	EXTERN LONG (__stdcall *ceilActionModeOne_Get)			(__in LONG NodeID, __in LONG ModuleType, __in LONG Channel, __out PLONG pdwActionMode);

	EXTERN LONG (__stdcall *ceilActionModeMulti_Set)		(__in LONG NodeID, __in LONG ModuleType, __in LONG IniChan, __in LONG NumChan, __in LONG ActionModes);

	EXTERN LONG (__stdcall *ceilActionModeMulti_Get)		(__in LONG NodeID, __in LONG ModuleType, __in LONG IniChan, __in LONG NumChan, __out PLONG pdwActionModes);

	//****************************************************************************
	//*************** START OF DIO CONFIGURATION FUNCTION DECLARATIONS ***********
	//****************************************************************************

	// ��� ������ ����� ä���� ����� ���(Input/Output) ����.
	// [Channel: ���� ä�� ��ȣ, InOutMode: ����� ���]
	EXTERN LONG (__stdcall *cedioMode_Set)	(__in LONG Channel, __in LONG InOutMode);

	// ��� ������ ����� ä���� ����� ���(Input/Output) ���� ���� ��ȯ.
	// [Channel: ���� ä�� ��ȣ, InOutMode: ����� ��� ��ȯ]
	EXTERN LONG (__stdcall *cedioMode_Get)	(__in LONG Channel, __out PLONG InOutMode);

	// ��� ������ ����� ä�� ������ ���� ����� ä�ο� ���� ���ÿ� ����� ���(Input/Output) ����.
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ��� ä�� ����, InOutModeMask: ����� ��� ����ũ��]
	EXTERN LONG (__stdcall *cedioModeMulti_Set) (__in LONG IniChan, __in LONG NumChan, __in LONG InOutModeMask);

	// ��� ������ ����� ä�� ������ ���� ����� ä�ο� ���� ���ÿ� ����� ���(Input/Output) ���� ���� ��ȯ.
	// [IniCahn: ���� ���� ä�� ��ȣ, NumChan: ��� ä�� ����, InOutModeMask: ����� ��� ����ũ�� ��ȯ]
	EXTERN LONG (__stdcall *cedioModeMulti_Get) (__in LONG IniChan, __in LONG NumChan, __out PLONG InOutModeMask);

	// ��� ������ ����� ä���� ����� ��(Logic) ����.
	// [Channel: ���� ä�� ��ȣ, InputLogic: ����� ����]
	EXTERN LONG (__stdcall *cedioLogicOne_Set)	(__in LONG Channel, __in  LONG Logic);

	// ��� ������ ����� ä���� ����� ��(Logic) ���� ���� ��ȯ.
	// [Channel: ���� ä�� ��ȣ, InputLogic: ����� ���� ��ȯ]
	EXTERN LONG (__stdcall *cedioLogicOne_Get)	(__in LONG Channel, __out PLONG Logic);

	// ��� ������ ����� ä�� ������ ���� ����� ä�ο� ���� ���ÿ� ����� ��(Logic) ����.
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ��� ä�� ����, LogicMask: ����� ��(Logic) ����ũ]
	EXTERN LONG (__stdcall *cedioLogicMulti_Set)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  LogicMask);

	// ��� ������ ����� ä�� ������ ���� ����� ä�ο� ���� ���ÿ� ����� ��(Logic) ���� ���� ��ȯ
	// ������ ����� ä���� ����³� �������� ��ȯ [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, LogicMask: ���� ����ũ]
	EXTERN LONG (__stdcall *cedioLogicMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG LogicMask);

	// ��� ������ ����� ä���� �Է� �Ǵ� ��� ���� ��ȯ.
	// [Channel: ���� ä�� ��ȣ, OutState: ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *cedioOne_Get)	(__in LONG Channel, __out PLONG State);

	// ��� ������ ����� ä���� �Է� �Ǵ� ��� ���� ����.
	// [Channel: ���� ä�� ��ȣ, OutState: ä�� ����]
	EXTERN LONG (__stdcall *cedioOne_Put)	(__in LONG Channel, __in  LONG  State);

	// ��� ������ ����� ä�� ������ ���� ����� ä�ο� ���� ���ÿ� �Է� �Ǵ� ��� ���¸� ��ȯ.
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ��� ä�� ����, States: ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *cedioMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG States);

	// ��� ������ ����� ä�� ������ ���� ����� ä�ο� ���� ���ÿ� �Է� �Ǵ� ��� ���¸� ����.
	// [ IniChan: ���� ���� ä�� ��ȣ, NumChan: ��� ä�� ����, States: ä�� ����]
	EXTERN LONG (__stdcall *cedioMulti_Put)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  States);

	// ��� ������ ����� ä���� ������ ���� ����� Ȱ��ȭ �Ͽ� ������ �Է� �Ǵ� ��� ���¸� ��ȯ.
	// [Channel: ���� ä�� ��ȣ, CutoffTime_us: ������ �Է� ��ȣ ���� �ð�(us), State: ä�� ���� ��ȯ]
	EXTERN LONG (__stdcall *cedioOneF_Get)	(__in LONG Channel,    __in LONG CutoffTime_us, __out PLONG State);

	// ��� ������ ����� ä�� ������
	// ���� ������ ����� ä���� ������ ���� ���
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ��, CutoffTime_us: ������ �Է� ��ȣ ���� �ð�(us), InputStates: �ش� ä���� ������ �Է� ����]
	EXTERN LONG (__stdcall *cedioMultiF_Get)	(__in LONG IniChan, __in LONG NumChan, __in LONG CutoffTime_us, __out PLONG States);

	// ��� ������ ����� ä���� ���� ������ ä���� ���� ���� �޽� ����� �߻�
	// [Channel: ���� ä�� ��ȣ, IsOnPulse: ������ ������ ��� ���� ���� �ʱ� �޽� ����� ���¸� ����, Duration: �޽� ��� �ð� ����,
	// IsWaitPulseEnd: �޽� ��� ���۽ÿ� �Լ��� �ٷ� ��ȯ�� ������, �ƴϸ� �޽� ��� �ð����� �Լ� ��ȯ�� ����� ������ ����]
	EXTERN LONG (__stdcall *cedioPulseOne)	(__in LONG Channel, __in LONG IsOnPulse, __in LONG Duration,  __in LONG IsWaitPulseEnd);

	// ������ ��� ��ä�� ������ ������ ���� ������ ä���� ���� ���� �޽� ����� �߻�
	// [IniChan: ���� ä��, NumChan: ä�� ��, OutStates: ������ ��� ����, Duration: �޽� ��� �ð� ����,
	// IsWaitPulseEnd: �޽� ��� ���۽ÿ� �Լ��� �ٷ� ��ȯ�� ������, �ƴϸ� �޽� ��� �ð����� �Լ� ��ȯ�� ����� ������ ����]
	EXTERN LONG (__stdcall *cedioPulseMulti)	(__in LONG IniChan, __in LONG NumChan,   __in LONG OutStates, __in LONG Duration, __in LONG IsWaitPulseEnd);

#ifdef __DI_DO_SUPPORT__
	//****************************************************************************
	//*************** START OF DI CONTROL FUNCTION DECLARATIONS ******************
	//****************************************************************************

	// ��� ������ �Է� ä���� �Է³� ����
	// [Channel: ���� ä�� ��ȣ, InputLogic: �Է� ����]
	EXTERN LONG (__stdcall *cediLogicOne_Set)	(__in LONG Channel, __in  LONG  InputLogic);

	// ��� ������ �Է� ä���� �Է³� �������� ��ȯ
	// [Channel: ���� ä�� ��ȣ, InputLogic: �Է� ����]
	EXTERN LONG (__stdcall *cediLogicOne_Get)	(__in LONG Channel, __out PLONG InputLogic);

	// ������ �Է� ä���� �Է³� ����
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, LogicMask: ���� ����ũ]
	EXTERN LONG (__stdcall *cediLogicMulti_Set)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  LogicMask);

	// ������ �Է� ä���� �Է³� �������� ��ȯ
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, LogicMask: ���� ����ũ]
	EXTERN LONG (__stdcall *cediLogicMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG LogicMask);

	// ��� ������ �Է�ä���� ���� ������ �Է� ä���� ���¸� ��ȯ
	// [Channel: ���� ä�� ��ȣ, InputState: ������ �Է� ����]
	EXTERN LONG (__stdcall *cediOne_Get)	(__in LONG Channel, __out PLONG InputState);

	// ��� ������ �Է� ä�� ������ ���� ������ �Է� ä���� ���¸� ��ȯ
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, InputStates: ������ �Է� ����]
	EXTERN LONG (__stdcall *cediMulti_Get)	(__in LONG IniChan, __in  LONG NumChan, __out PLONG InputStates);

	// ��� ������ �Է� ä���� ���� ä���� ������� ������ ���� ����� Ȱ��ȭ �Ͽ� ������ �Է� ���¸� ��ȯ
	// [Channel: ���� ä�� ��ȣ, CutoffTime_us: ������ �Է� ��ȣ ���� �ð�(us), InputState: �ش� ä���� ������ �Է� ����]
	EXTERN LONG (__stdcall *cediOneF_Get)	(__in LONG Channel, __in LONG CutoffTime_us, __out PLONG InputState);

	// ���� ������ �Է� ä���� ������ ���� ���
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ��, CutoffTime_us: ������ �Է� ��ȣ ���� �ð�(us), InputStates: �ش� ä���� ������ �Է� ����]
	EXTERN LONG (__stdcall *cediMultiF_Get)	(__in LONG IniChan, __in LONG NumChan, __in LONG CutoffTime_us, __out PLONG InputStates);

	//****************************************************************************
	//*************** START OF DO CONTROL FUNCTION DECLARATIONS ******************
	//****************************************************************************

	// ��� ������ ��� ä���� ��³� ����
	// [Channel: ���� ä�� ��ȣ, OutputLogic: ��� ����]
	EXTERN LONG (__stdcall *cedoLogicOne_Set)	(__in LONG Channel, __in  LONG  OutputLogic);

	// ��� ������ ��� ä���� ��³� ���� ������ ��ȯ
	// [Channel: ���� ä�� ��ȣ, OutputLogic:��� ����]
	EXTERN LONG (__stdcall *cedoLogicOne_Get)	(__in LONG Channel, __out PLONG OutputLogic);

	// ������ ��� ä�� ������ ���� ������ ��� ä���� ���� ���ÿ� ������ ����� �߻�
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, LogicMask: ���� ����ũ]
	EXTERN LONG (__stdcall *cedoLogicMulti_Set)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  LogicMask);

	// ������ ��� ä�� ������ ���� ������ ��� ä���� ���¸� Ȯ��
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, LogicMask: ���� ����ũ]
	EXTERN LONG (__stdcall *cedoLogicMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG LogicMask);

	// ��� ������ ��� ä���� ���� ������ ä���� ���� ������ ����� �߻�
	// [Channel: ���� ä�� ��ȣ, OutState: ��� ����]
	EXTERN LONG (__stdcall *cedoOne_Put)	(__in LONG Channel, __in  LONG  OutState);

	// ��� ������ ��� ä���� ���� ������ ä���� ���� ������ ��� ���¸� ��ȯ
	// [Channel: ���� ä�� ��ȣ, OutState: ��� ���� ]
	EXTERN LONG (__stdcall *cedoOne_Get)	(__in LONG Channel, __out PLONG OutState);

	// ������ ��� ä�� ������ ���� ������ ��� ä���� ���� ���ÿ� ������ ����� �߻�
	// [ IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, OutStates: ������ ��� ����]
	EXTERN LONG (__stdcall *cedoMulti_Put)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  OutStates);

	// ������ ��� ä�� ������ ���� ������ ��� ä���� ���� ���ÿ� ������ ��� ���¸� Ȯ��
	// [IniChannel: ���� ���� ä�� ��ȣ, NumChan: ä�� ����, OutStates: ������ ��� ����]
	EXTERN LONG (__stdcall *cedoMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG OutStates);

	// ��� ������ ��� ä���� ���� ������ ä���� ���� ���� �޽� ����� �߻�
	// [Channel: ���� ä�� ��ȣ, IsOnPulse: ������ ������ ��� ���� ���� �ʱ� �޽� ����� ���¸� ����,
	// IsWaitPulseEnd: �޽� ��� ���۽ÿ� �Լ��� �ٷ� ��ȯ�� ������, �ƴϸ� �޽� ��� �ð����� �Լ� ��ȯ�� ����� ������ ����]
	EXTERN LONG (__stdcall *cedoPulseOne)	(__in LONG Channel, __in LONG IsOnPulse, __in LONG Duration,  __in LONG IsWaitPulseEnd);

	// ������ ��� ä�� ������ ������ ���� ������ ä���� ���� ���� �޽� ����� �߻�
	// [IniChan: ���� ���� ä�� ��ȣ, NumChan: ä�� ��, OutStates: ������ ��� ����, Duration: �޽� ��� �ð� ����,
	// IsWaitPulseEnd: �޽� ��� ���۽ÿ� �Լ��� �ٷ� ��ȯ�� ������, �ƴϸ� �޽� ��� �ð����� �Լ� ��ȯ�� ����� ������ ����]
	EXTERN LONG (__stdcall *cedoPulseMulti)	(__in LONG IniChan, __in LONG NumChan,   __in LONG OutStates, __in LONG Duration, __in LONG IsWaitPulseEnd);
#endif

	//****************************************************************************
	//*************** START OF COUNTER MODULE FUNCTION DECLARATIONS **************
	//****************************************************************************
	// ī���ʹ� ���� 8ä���� ���� �ֽ��ϴ�. (��⺰�� ���� Channel 0 ~ Channel 7)

	// ��� ī���� ä���� Edge Mode �� �����մϴ�.
	// [Channel: ī���� ä�ι�ȣ, EdgeMode: Edge��� 0(falling edge) 1(rising edge) Default:falling edge]
	EXTERN LONG (__stdcall *cecEdgeOne_Set)       (__in LONG Channel, __in DWORD EdgeMode);

	// ��� ī���� ä���� Edge Mode �������� �����ɴϴ�
	// [Channel: ī���� ä�ι�ȣ, EdgeMode: Edge��� ��ȯ�� 0(falling edge) 1(rising edge)]
	EXTERN LONG (__stdcall *cecEdgeOne_Get)       (__in LONG Channel, __out PDWORD EdgeMode);

	// ��� ī���� ä�� ������ ���Ե� ä�ε��� Edge Mode �� ��Ƽ�� �����մϴ�.
	// [IniChannel:ä�� Range ���� ä�� ��ȣ, NumChannels:ä�� Range ũ��, EdgeModeMask:���� ä�ι�ȣ ���� ��ä�� ��ȣ���� �� ä�κ� Edge Mode �� �ش� ��Ʈ�� 0/1 �� ���� 0(falling edge) 1(rising edge)]
	EXTERN LONG (__stdcall *cecEdgeMulti_Set)     (__in LONG IniChannel, __in LONG NumChannels, __in DWORD EdgeModeMask);

	// ��� ī���� ä�� ������ ���Ե� ä�ε��� Edge Mode �������� ��Ƽ�� �����ɴϴ�. ��Ʈ ����ũ�� ���� �� ��ƮShift ������ ���� ä�κ��� 0 �Ǵ� 1 ���� (Edge Mode) �� ���� �� �ֽ��ϴ�.
	// [IniChannel:ä�� Range ���� ä�� ��ȣ, NumChannels:ä�� Range ũ��, EdgeModeMask:���� ä�ι�ȣ ���� ��ä�� ��ȣ���� �� ä�κ� Edge Mode �� �ش� ��Ʈ�� 0/1 �� ������ �� ��ȯ 0(falling edge) 1(rising edge)]
	EXTERN LONG (__stdcall *cecEdgeMulti_Get)     (__in LONG IniChannel, __in LONG NumChannels, __out PDWORD EdgeModeMask);

	// ��� ī���� ä���� ī��Ʈ ���� Clear (0 ���� ����) ��ŵ�ϴ�.
	// [Channel: ī���� ä�ι�ȣ]
	EXTERN LONG (__stdcall *cecClearOne)         (__in LONG Channel);

	// ��� ī���� ä�� ������ ���Ե� ä�ε��� ī��Ʈ ���� ��� Clear (0 ���� ����) ��ŵ�ϴ�.
	// [IniChannel:ä�� Range ���� ä�� ��ȣ, NumChannels:ä�� Range ũ��]
	EXTERN LONG (__stdcall *cecClearMulti)       (__in LONG IniChannel, __in LONG NumChannels);

	// ��� ī���� ä���� ī��Ʈ ���� Clear (0 ���� ����) ��ŵ�ϴ�.
	// [NodeID: ��� ID - ���IP(192.168.1.x) �� 4��° �ڸ���(x)]
	EXTERN LONG (__stdcall *cecClearAll)         (__in LONG NodeID);

	// ��� ī���� ä���� ī��Ʈ ���� ��� �ɴϴ�.
	// [Channel: ī���� ä�ι�ȣ, Count: ī��Ʈ ��]
	EXTERN LONG (__stdcall *cec_Get)                (__in LONG Channel, __out PDWORD Count);

	// ��� ī���� ä���� ī��Ʈ�� �����ϵ��� �����մϴ�. Enable: true (1) or false (0)
	// [Channel: ī���� ä�ι�ȣ, Enable: Count Enable ���°� 0: Diable 1: Enable]
	EXTERN LONG (__stdcall *cecEnableOne_Set)     (__in LONG Channel, __in DWORD Enable);

	// ��� ī���� ä���� ī��Ʈ�� ������ �������� Counter Enable ���¸� ��� �ɴϴ�.
	// [Channel: ī���� ä�ι�ȣ, IsEnabled: Count Enable ���°� 0: Diable 1: Enable]
	EXTERN LONG (__stdcall *cecEnableOne_Get)     (__in LONG Channel, __out PDWORD IsEnabled);

	// ��� ī���� ä�� ������ ���Ե� ä�ε��� ī��Ʈ�� �����ϵ��� Counter Enable ���¸� ��� true(1) �� �����մϴ�.
	// [IniChannel:ä�� Range ���� ä�� ��ȣ, NumChannels:ä�� Range ũ��, EnableMask: ��Ƽä�ο� ���� Counter Enable ���¸���ũ ��]
	EXTERN LONG (__stdcall *cecEnableMulti_Set)   (__in LONG IniChannel, __in LONG NumChannels, __in DWORD EnableMask);

	// ��� ī���� ä�� ������ ���Ե� ä�ε��� ī��Ʈ�� ������ �������� Counter Enable ���¸� ���ɴϴ�. ��Ƽ ä�ο� ���� EnabledMask �� ���� �� ��ƮShift ������ ���� ä�κ��� Enable ���¸� ���� �� �ֽ��ϴ�.
	// [IniChannel:ä�� Range ���� ä�� ��ȣ, NumChannels:ä�� Range ũ��, EnabledMask: ��Ƽä�ο� ���� Counter Enable ���¸���ũ ��]
	EXTERN LONG (__stdcall *cecEnableMulti_Get)   (__in LONG IniChannel, __in LONG NumChannels, __out PDWORD EnabledMask);

	// ��� ī���� ä���� Overflow (24��Ʈ:0~2^24-1 ���� �ʰ�) ���¸� ��� �ɴϴ�. 1:overflow
	// [Channel: ī���� ä�ι�ȣ, OverflowStatus: Count Overflow ���°� 0: Overflow �߻� ���� 1: Overflow �߻� ��]
	EXTERN LONG (__stdcall *cecOverflowFlagGetOne)   (__in LONG Channel, __out PDWORD OverflowStatus);

	// ��� ī���� ä�ι����� Overflow (24��Ʈ ���� �ʰ�) ���¸� ��� �ɴϴ�.
	// [IniChannel:ä�� Range ���� ä�� ��ȣ, NumChannels:ä�� Range ũ��, OverflowStates: ��Ƽä�ο� ���� Overflow ���¸���ũ ��]
	EXTERN LONG (__stdcall *cecOverflowFlagGetMulti)   (__in LONG IniChannel, __in LONG NumChannels, __out PDWORD OverflowStates);

	// ��� ī���� ä�ο� �ش��ϴ� Overflow Flag �� 0 ���� Clear ��ŵ�ϴ�.
	// [Channel: ī���� ä�ι�ȣ]
	EXTERN LONG (__stdcall *cecOverflowFlagClearOne)    (__in LONG Channel);

	// ��� ī���� ä�ι��� �� �ش��ϴ� ä�κ� Overflow Flag �� 0 ���� Clear ��ŵ�ϴ�.
	// [IniChannel:ä�� Range ���� ä�� ��ȣ, NumChannels:ä�� Range ũ��]
	EXTERN LONG (__stdcall *cecOverflowFlagClearMulti)  (__in LONG IniChannel, __in LONG NumChannels);

	// ��� ī���� ä���� overflow flag �� 0 ���� Clear ��ŵ�ϴ�.
	// [NodeID: ��� ID - ���IP(192.168.1.x) �� 4��° �ڸ���(x)]
	EXTERN LONG (__stdcall *cecOverflowFlagClearAll)    (__in LONG NodeID);

	// ��� ī���� ä�κ� ���� Cutoff ���ļ� ����: FilterFreq: 0~2 ���� ��� ����.
	// [Channel: ī���� ä�ι�ȣ, FilterFreq: ä�κ� ���� Cutoff ���ļ�]
	//A	B	���� ���ļ�		Cutoff ���ļ� (50duty)	Filter�� pass�ϱ� ���� �ּҽð�
	//0	0	10Mhz (default)	500Khz					1usec
	//0	1	312Khz			20Khz					25usec
	//1	0	39Khz			4Khz					125usec
	EXTERN LONG (__stdcall *cecFilterFreq_Set)           (__in LONG Channel, __in LONG FilterFreq);

	// ��� ī���� ä�κ� ���� Cutoff ���ļ� ������ ��� �Լ� => �� �Լ��� �ɼ��Դϴ�. ���� ���̺귯������ ���ܵ� �� �ֽ��ϴ�.
	// [Channel: ī���� ä�ι�ȣ, FilterFreq: ä�κ� ���� Cutoff ���ļ�]
	EXTERN LONG (__stdcall *cecFilterFreq_Get)           (__in LONG Channel, __out PLONG FilterFreq);

	//****************************************************************************
	//*************** START OF ANALOG INPUT FUNCTION DECLARATIONS ****************
	//****************************************************************************

	// �Ƴ��α� �Է¿� ���� ���� ������ ������ ��带 ���� �����մϴ�.
	// [Channel: �Ƴ��α� �Է� ä�� ��ȣ, RangeMode: ���� ���� ���� ���]
	//RangeMode (0~3)
	//A	B	�Է¹���
	//0	0	+10V ~ -10V
	//0	1	+5V ~ -5V
	//1	0	+2.5V ~ -2.5V
	//1	1	0V ~ +10V (0~20mA)
	EXTERN LONG (__stdcall *ceaiVoltRangeMode_Set)		(__in LONG Channel, __in  LONG  RangeMode);

	// �Ƴ��α� �Է¿� ���� ������ ���� ������ �ش��ϴ� ��带 ��ȯ�մϴ�.
	// [Channel: �Ƴ��α� �Է� ä�� ��ȣ, RangeMode: ���� ���� ���� ���]
	EXTERN LONG (__stdcall *ceaiVoltRangeMode_Get)		(__in LONG Channel, __out PLONG RangeMode);

	// �Ƴ��α� �Է¿� ���� ������ �Է� Range �� Digit ������ ��ȯ�մϴ� => �� �Լ��� ���Ŀ� ������� ���� �� �ֽ��ϴ�.
	// [Channel: �Ƴ��α� �Է� ä�� ��ȣ, DigitMin: �ּ� �Է� Digit ��, DigitMax: �ִ� �Է� Digit ��]
	EXTERN LONG (__stdcall *ceaiRangeDigit_Get)         (__in LONG Channel, __out PLONG DigitMin, __out PLONG DigitMax);

	// �ش� �Ƴ��α� �Է� ä���� �Է� Digit ���� ��ȯ�մϴ�.
	// [Channel: �Ƴ��α� �Է� ä�� ��ȣ, Digit: �Էµ� Digit ��]
	EXTERN LONG (__stdcall *ceaiDigit_Get)              (__in LONG Channel, __out PLONG Digit);

	// �ش� �Ƴ��α� �Է� ä���� �Է� ���� ���� ��ȯ�մϴ�.
	// [Channel: �Ƴ��α� �Է� ä�� ��ȣ, fVolt: �Էµ� ���� ��]
	EXTERN LONG (__stdcall *ceaiVolt_Get)               (__in LONG Channel, __out PDOUBLE fVolt);

	// �ش� �Ƴ��α� �Է� ä���� �Է� ���� ���� ��ȯ�մϴ�.
	// [Channel: �Ƴ��α� �Է� ä�� ��ȣ, fCurrent: �Էµ� ���� ��]
	EXTERN LONG (__stdcall *ceaiCurrent_Get)            (__in LONG Channel, __out PDOUBLE fCurrent);

	//****************************************************************************
	//*************** START OF ANALOG OUTPUT FUNCTION DECLARATIONS ***************
	//****************************************************************************

	// �ش� �Ƴ��α� ��� ä���� ���� Digit ���� ����մϴ�.
	// [Channel: �Ƴ��α� ��� ä�� ��ȣ, Digit: ��� Digit ��]
	EXTERN LONG (__stdcall *ceaoDigit_Out)              (__in LONG Channel, __in LONG Digit);

	// �ش� �Ƴ��α� ��� ä���� ���� ���� ���� ����մϴ�.
	// [Channel: �Ƴ��α� ��� ä�� ��ȣ, fVolt: ��� ���� ��]
	EXTERN LONG (__stdcall *ceaoVolt_Out)               (__in LONG Channel, __in DOUBLE fVolt);

	// �ش� �Ƴ��α� ��� ä���� ���� ���� ���� ����մϴ�.
	// [Channel: �Ƴ��α� ��� ä�� ��ȣ, fCurrent: ��� ���� ��]
	EXTERN LONG (__stdcall *ceaoCurrent_Out)            (__in LONG Channel, __in DOUBLE fCurrent);

	//****************************************************************************
	//*************** START OF UTILITY FUNCTION DECLARATIONS *********************
	//****************************************************************************

	// �ִ� 32����Ʈ�� ������ ���ڿ��� ����� ���� ���� ��ġ�� ����մϴ�.
	// [NodeID : ��� ��� ��ȣ]
	// [NumByte: ����� ������ ����(����Ʈ ����)]
	// [szText : ����� ���ڿ�]
	EXTERN LONG (__stdcall *ceutlUserData_Set)		(__in LONG NodeID, __in  LONG NumByte,  __in  PCHAR szText);

	// �ִ� 32����Ʈ�� ������ ���ڿ��� ����� ���� ���� ��ġ���� �о�ɴϴ�.
	// [NodeID : ��� ��� ��ȣ]
	// [NumByte: �о�� ������ ����(����Ʈ ����)]
	// [szText : �о�� ���ڿ� ��ȯ]
	EXTERN LONG (__stdcall *ceutlUserData_Get)		(__in LONG NodeID, __out PLONG NumByte, __out PCHAR szText);

	// ��� ���� ��忡 ����� ���� ������ ����մϴ�.
	// [NodeID : ��� ��� ��ȣ]
	// [Version: ����� ����]
	EXTERN LONG (__stdcall *ceutlUserVersion_Set)	(__in LONG NodeID, __in  LONG Version);

	// ��� ���� ����� ����� ���� ������ �о�ɴϴ�.
	// [NodeID : ��� ��� ��ȣ]
	// [Version: ��ϵ� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceutlUserVersion_Get)	(__in LONG NodeID, __out PLONG pVersion);

	// ��� ���� ����� �߿��� ������ �о�ɴϴ�.
	// [NodeID : ��� ��� ��ȣ]
	// [Version: ��ϵ� �߿��� ���� ��ȯ]
	EXTERN LONG (__stdcall *ceutlNodeVersion_Get)	(__in LONG NodeID, __out PLONG pVersion);

	// �� ���̺귯���� ������ �����ɴϴ�. ���� �� ���� 4����Ʈ�� �ּҿ� �� 2����Ʈ�� ������ �Ҵ��մϴ�. ������ �ڸ����� �� 4�ڸ��Դϴ�.
	// ���̺귯�� ������ ��� ����� ������ �����ϴ�.
	// [pVersionMS : ���� ��Ʈ ���� ���� ��ȯ]
	// [pVersionLS : ���� ��Ʈ ���� ���� ��ȯ]

	// printf("Dynamic Link Library Version = [%d].[%d].[%d].[%d]"
	//	_X(pVersionMS >> 16 & 0xFF)
	//	_X(pVersionMS >> 0 & 0xFF)
	//	_X(pVersionLS >> 16 & 0xFF)
	//	_X(pVersionLS >> 0 & 0xFF));
	EXTERN LONG (__stdcall *ceutlLibVersion_Get)		(__out PLONG pVersionMS, __out PLONG pVersionLS);

	// ���� ������ �޼����� ó���մϴ�.
	EXTERN LONG (__stdcall *ceutlPumpSingleMessage)     ();

	// ���� ������ �޼����� ó���մϴ�. ���ڷ� ������ nTimeout �� ������ �ð����� ������ �޼����� ó���ϰ� �˴ϴ�.
	// ���� nTimeout�� CN_INFINITE �� �����ϰԵǸ�, ��� ������ �޼����� ó���� �� ��ȯ�˴ϴ�.
	// nTimeout �� ������ ms �Դϴ�
	// [nTimeout : ������ �ð����� ������ �޼����� ó���մϴ�.]
	EXTERN LONG (__stdcall *ceutlPumpMultiMessage)      (__in LONG nTimeout);

	// ��� ����� ����ȭ �ϱ� ���� ���� ī��Ʈ�� ��ȯ
	// [NodeID : ��� ���, pSyncCount : ��� ����� ���� ī��Ʈ ��ȯ]
	EXTERN LONG (__stdcall *ceutlSyncCount_Get)		(__in LONG NodeID, __out PLONG pSyncCount);

	// ��� ����� ����ȭ �ϱ� ���� I/O �޼��� ���� ī��Ʈ�� ��ȯ
	// [NodeID : ��� ���, pSyncCount : ��� ����� ���� ī��Ʈ ��ȯ]
	EXTERN LONG (__stdcall *ceutlIOSyncCount_Get)		(__in LONG NodeID, __out PLONG pSyncCount);

	// ���� ���� �������α׷��� ��� ����ȭ�� ���� ó���մϴ�. 
	// ���� ��ɵ� ��� ����� �ֱ����� �޼����� ����ȭ�� ���� ����մϴ�.
	// [NodeID : ��� ���, IsBlocking : ���⸦ ���� ����ϴ� ���� ������ �޼��� Blocking ����]
	EXTERN LONG (__stdcall *ceutlSyncWait)		   (__in LONG NodeID, __in LONG IsBlocking);

	// ��忡 �ֱ��� �޼����� ���� Ÿ�� �������� ��ȯ�մϴ�.
	// [NodeID : ��� ���, pTimeStamp : ��� ����� Ÿ�� ������]
	EXTERN LONG (__stdcall * ceutlTimeStamp_Get)	(__in LONG NodeID, __out PLONG pTimeStamp);

	//****************************************************************************
	//*************** START OF CNET FUNCTION DECLARATIONS *********************
	//****************************************************************************
	EXTERN LONG (__stdcall *cecnetLogicOne_Set)     (__in LONG nChannel, __in  LONG  bInputLogic);
	EXTERN LONG (__stdcall *cecnetLogicOne_Get)     (__in LONG nChannel, __out LONG* pbInputLogic);

	EXTERN LONG (__stdcall *cecnetLogicMulti_Set)   (__in LONG nInitChannel, __in LONG nChannel, __in LONG  LogicMask);
	EXTERN LONG (__stdcall *cecnetLogicMulti_Get)   (__in LONG nInitChannel, __in LONG nChannel, __in LONG* pLogicMask);

	EXTERN LONG (__stdcall *cecnetOne_Put)          (__in LONG nChannel, __in  LONG  State);
	EXTERN LONG (__stdcall *cecnetDOOne_Get)        (__in LONG nChannel, __out LONG* pState);
	EXTERN LONG (__stdcall *cecnetDIOne_Get)        (__in LONG nChannel, __out LONG* pState);

	EXTERN LONG (__stdcall *cecnetMulti_Put)        (__in LONG nInitChannel, __in LONG nChannel, __in  LONG  StateMask);
	EXTERN LONG (__stdcall *cecnetDOMulti_Get)      (__in LONG nInitChannel, __in LONG nChannel, __out LONG* pStateMask);
	EXTERN LONG (__stdcall *cecnetDIMulti_Get)      (__in LONG nInitChannel, __in LONG nChannel, __out LONG* pStateMask);
	
	//****************************************************************************
	//*************** START OF SERIAL FUNCTION DECLARATIONS *********************
	//****************************************************************************
	EXTERN LONG (__stdcall *cesOpenPort)			(__in LONG nNodeID, __in LONG nChannel, __in LONG nSerType, __in LONG nBaudId, __in LONG nDataBits, __in LONG nStopBits, __in LONG nParity);
	EXTERN LONG (__stdcall *cesClosePort)			(__in LONG nNodeID, __in LONG nChannel);
	EXTERN LONG (__stdcall *cesIsDataReady)			(__in LONG nNodeID, __in LONG nChannel, __out PLONG bIsReady);
	EXTERN LONG (__stdcall *cesSetTimeOut)			(__in LONG nNodeID, __in LONG nChannel, __in ULONG nTimeOut);
	EXTERN LONG (__stdcall *cesGetTimeOut)			(__in LONG nNodeID, __in LONG nChannel, __in PULONG nTimeOut);
	EXTERN LONG (__stdcall *cesRxReset)			(__in LONG nNodeID, __in LONG nChannel);
	EXTERN LONG (__stdcall *cesTxReset)			(__in LONG nNodeID, __in LONG nChannel);
	EXTERN LONG (__stdcall *cesGetUnreadDataSize)	(__in LONG nNodeID, __in LONG nChannel, __out PULONG nSize);
	EXTERN LONG (__stdcall *cesPeekByte)			(__in LONG nNodeID, __in LONG nChannel, __out PBYTE byRetVal, __out PBOOL bIsSuccess);
	EXTERN LONG (__stdcall *cesPeekByteEx)			(__in LONG nNodeID, __in LONG nChannel, __in LONG nIndex, __out PBYTE byRetVal, __out PBOOL bIsSuccess);
	EXTERN LONG (__stdcall *cesReadByte)			(__in LONG nNodeID, __in LONG nChannel, __out PBYTE byRetVal, __out PBOOL bIsSuccess);
	EXTERN LONG (__stdcall *cesWriteByte)			(__in LONG nNodeID, __in LONG nChannel, __in BYTE byVal, __out PBOOL bIsSuccess);
	EXTERN LONG (__stdcall *cesPeekString)			(__in LONG nNodeID, __in LONG nChannel, __in LONG nNumBufSize, __out PCHAR aRetBuf, __out PLONG nNumRetBytes);
	EXTERN LONG (__stdcall *cesReadString)			(__in LONG nNodeID, __in LONG nChannel, __in LONG nNumBufSize, __out PCHAR aRetBuf, __out PLONG nNumRetBytes);
	EXTERN LONG (__stdcall *cesWriteString)			(__in LONG nNodeID, __in LONG nChannel, __in LONG nNumBytes, __in PCHAR aWriteBuf, __out PLONG nNumRetWriteBytes);
	EXTERN LONG (__stdcall *cesReadDword)			(__in LONG nNodeID, __in LONG nChannel, __in LONG nNumBufSize, __out PDWORD aRetBuf, __out PLONG nNumRetDwords);
	EXTERN LONG (__stdcall *cesWriteDword)			(__in LONG nNodeID, __in LONG nChannel, __in LONG nNumWriteSize, __out PDWORD aWriteBuf, __out PLONG nNumRetWriteDwords);
	EXTERN LONG (__stdcall *cesCommCommit)			(__in LONG nNodeID, __in LONG nChannel, __out PLONG nNumRetSendSize);

	//****************************************************************************
	//************************ ACTUAL FEEDBACK SPEED *****************************
	//****************************************************************************
	EXTERN LONG (__stdcall *cemCfgActSpdFilter_Set)		(__in LONG nAxis, __in LONG nAvrFilterNum);
	EXTERN LONG (__stdcall *cemCfgActSpdFilter_Get)		(__in LONG nAxis, __out PLONG nAvrFilterNum);
#ifdef __cplusplus
}
#endif


#endif
