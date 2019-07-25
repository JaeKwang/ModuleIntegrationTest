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
	// ceSDK 라이브러리 로드.
	BOOL ceLoadDll();
	// ceSDK 라이브러리 언로드.
	VOID ceUnloadDll();

	//****************************************************************************
	//*************** START OF GENERAL FUNCTION DECLARATIONS *********************
	//****************************************************************************

	// 라이브러리가 로드된 상태에서 장치를 로드.
	EXTERN LONG (__stdcall *ceGnLoad)	();

	// 라이브러리가 로드된 상태에서 장치를 언로드.
	EXTERN LONG (__stdcall *ceGnUnload)	();
	
	// 디버그 레벨 설정 
	// [LogLevel : (ceSDKDef.h) 파일을 참조합니다]
	EXTERN LONG (__stdcall *ceGnLogLevel_Set)	(__in LONG LogLevel);

	// 디버그 레벨 반환
	// [LogLevel : (ceSDKDef.h) 파일을 참조합니다]
	EXTERN LONG (__stdcall *ceGnLogLevel_Get)	(__out PLONG LogLevel);

	// 디버그 모드 설정 합니다.
	// [LogMode : 0: Disable , 1: OutputDebugString, 2 : FILE, 4: Console, szLogDir : 로그 파일이 기록될 경로]
	EXTERN LONG (__stdcall *ceGnLogMode_Set)	(__in LONG LogMode, __in CHAR * szLogDir);

	// 디버그 모드 반환 합니다.
	// [LogMode : 0: Disable , 1: OutputDebugString, 2 : FILE, 4: Console]
	EXTERN LONG (__stdcall *ceGnLogMode_Get)	(__out PLONG LogMode);
	
	// 라이브러리가 로드된 상태에서 노드를 다시 탐색합니다.
	// [RealNode: 실제 노드 정보, nTimeout: 타임 아웃, IsBlocking: 완료될때까지 메세지 블록 여부, pResultNode: 로드된 노드 수 반환]
	EXTERN LONG (__stdcall *ceGnReSearchDevice)	(__in LONG RealNode,  __in DWORD nTimeout, __in LONG IsBlocking, __out PLONG pResultNode);

	// 노드 탐색이 완료되어 있는지 확인합니다. 다중 프로세스에서 다른 프로세스에서 이미 노드가 탐색되었다면, 이 함수를 통해
	// 이미 탐색된 노드를 대상으로 재 탐색을 하거나 하지 않도록 할 수 있습니다.
	// [IsSearchedDevice: 이미 노드 탐색이 되어 있는 경우 TRUE 를 반환하며, 탐색이 되어 있지 않은 경우 FALSE 를 반환합니다]  
	EXTERN LONG (__stdcall *ceGnIsSearchedDevice)	(__out PLONG IsSearchedDevice);

	// 장치가 로드된 상태에서 장치의 환경 정보를 반환.
	// [RealNode: 실제 노드 정보, nTimeout: 타임 아웃, IsBlocking: 완료될때까지 메세지 블록 여부, pResultNode: 전체 노드 수 반환]
	EXTERN LONG (__stdcall *ceGnSearchDevice)	(__in LONG RealNode,  __in DWORD nTimeout, __in LONG IsBlocking, __out PLONG pResultNode);

	// 노드 탐색을 초기화 하며, 이 함수가 수행된 이후 ceGnSearchDevice 를 통해 노드 탐색을 할 수 있습니다.
	EXTERN LONG (__stdcall *ceGnUnSearchDevice)	();

	// 로드된 전체 노드의 개수를 반환.
	// [Node : 로드된 노드 수 반환]
	EXTERN LONG (__stdcall *ceGnTotalNode)	(__out PLONG Node);

	// 로드된 모션 제어 축 개수를 반환.
	// [Channel : 로드된 모션 제어 축 개수 반환]
	EXTERN LONG (__stdcall *ceGnTotalMotionChannel)	(__out PLONG Channel);

	// 로드된 디지털 입출력 채널 개수를 반환.
	// [Channel : 로드된 디지털 입출력 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnTotalDIOChannel)	(__out PLONG Channel);

	// 로드된 아날로그 입력 채널 개수를 반환.
	// [Channel : 로드된 아날로그 입력 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnTotalAIChannel)	(__out PLONG Channel);

	// 로드된 아날로그 출력 채널 개수를 반환.
	// [Channel : 로드된 아날로그 출력 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnTotalAOChannel)	(__out PLONG Channel);

	// 로드된 모션 디지털 입출력 채널 개수를 반환.
	// [Channel : 로드된 모션 디지털 입출력 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnTotalMDIOChannel) (__out PLONG Channel);

	// 로드된 카운터 채널 개수를 반환.
	// [Channel : 로드된 카운터 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnTotalCNTChannel) (__out PLONG Channel);

	// 해당 노드의 모션 제어 모듈 개수를 반환.
	// [NodeID : 노드 번호, ModuleCount : 해당 노드의 모션 제어 모듈 개수 반환]
	EXTERN LONG (__stdcall *ceGnModuleCount_Motion)	(__in LONG NodeID, __out PLONG ModuleCount);

	// 해당 노드의 디지털 입출력 모듈 개수를 반환.
	// [NodeID : 노드 번호, ModuleCount : 해당 노드의 디지털 입출력 모듈 개수 반환]
	EXTERN LONG (__stdcall *ceGnModuleCount_Dio)	(__in LONG NodeID, __out PLONG ModuleCount);

	// 해당 노드의 아날로그 입력 모듈 개수를 반환.
	// [NodeID : 노드 번호, ModuleCount : 해당 노드의 아날로그 입력 모듈 개수 반환]
	EXTERN LONG (__stdcall *ceGnModuleCount_Ai)	(__in LONG NodeID, __out PLONG ModuleCount);

	// 해당 노드의 아날로그 출력 모듈 개수를 반환.
	// [NodeID : 노드 번호, ModuleCount : 해당 노드의 아날로그 출력 모듈 개수 반환]
	EXTERN LONG (__stdcall *ceGnModuleCount_Ao)	(__in LONG NodeID, __out PLONG ModuleCount);

	// 해당 노드의 모션 디지털 입출력 모듈 개수를 반환.
	// [NodeID : 노드 번호, ModuleCount : 해당 노드의 모션 디지털 입출력 채널 모듈 개수 반환]
	EXTERN LONG (__stdcall *ceGnModuleCount_Mdio) (__in LONG NodeID, __out PLONG ModuleCount);

	// 해당 노드의 카운터 모듈 개수를 반환.
	// [NodeID : 노드 번호, ModuleCount : 해당 노드의 카운터 모듈 개수 반환]
	EXTERN LONG (__stdcall *ceGnModuleCount_Cnt) (__in LONG NodeID, __out PLONG ModuleCount);

	// 해당 노드의 모션 모듈에 대한 모션 제어 축 수를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 모션 모듈 번호, ChannelCount : 모션 제어 축 개수 반환]
	EXTERN LONG (__stdcall *ceGnChannelCount_Motion)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// 해당 노드의 디지털 입출력 모듈에 대한 채널 개수를 반환 .
	// [NodeID : 노드 번호, ModuleIdx : 디지털 입출력 모듈 번호, ChannelCount : 디지털 입출력 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnChannelCount_Dio)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// 해당 노드의 아날로그 입력 모듈에 대한 채널 개수를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 아날로그 입력 모듈 번호, ChannelCount : 아날로그 입력 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnChannelCount_Ai)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// 해당 노드의 아날로그 출력 모듈에 대한 채널 개수를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 아날로그 출력 모듈 번호, ChannelCount : 아날로그 출력 채널 개수 반환]
	EXTERN LONG (__stdcall *ceGnChannelCount_Ao)	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// 해당 노드의 모션 디지털 입출력 모듈에 대한 채널 개수를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 모션 디지털 입출력 모듈 번호, ChannelCount : 모션 디지털 입출력 채널 개수 반환
	EXTERN LONG (__stdcall *ceGnChannelCount_Mdio) 	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// 해당 노드의 카운터 모듈에 대한 채널 개수를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 카운터 모듈 번호, ChannelCount : 카운터 채널 개수 반환
	EXTERN LONG (__stdcall *ceGnChannelCount_Cnt) 	(__in LONG NodeID, __in LONG ModuleIdx, __out PLONG ChannelCount);

	// 해당 노드에 소프트웨어 적으로 Emergency 상황을 설정하거나 해제 합니다.
	// [NodeID : 노드 번호, State : Emergency 상태에 대해서 설정합니다]
	EXTERN LONG (__stdcall *ceGnEmergency_Set)  (__in LONG NodeID, __in LONG State);

	// 해당 노드의 소프트웨어 적으로 Emergency 상황에 대해 반환합니다.
	// [NodeID : 노드 번호, State : Emergency 상태에 대해서 반환합니다]
	EXTERN LONG (__stdcall *ceGnEmergency_Get)  (__in LONG NodeID, __out PLONG State);

	// 해당 노드의 모듈을 초기화.
	// [NodeID : 노드 번호, ResetMode : 초기화 모드]
	EXTERN LONG (__stdcall *ceGnResetNode)	(__in LONG NodeID, __in LONG ResetMode);

	// 해당 프로세스와 서비스 프로세스의 프로세스 우선순위를 제어
	// [BoostLevel : 우선 순위, BoostMode : 모드]
	EXTERN LONG (__stdcall *ceGnCtrlBoost_Set)	(__in LONG BoostLevel,	__in LONG BoostMode);

	// 해당 프로세스와 서비스 프로세스의 프로세스 우선순위를 반환
	// [BoostLevel : 우선 순위, BoostMode : 모드]
	EXTERN LONG (__stdcall *ceGnCtrlBoost_Get)	(__out PLONG BoostLevel, __out PLONG BoostMode);

	// 해당 노드가 연결되어 있는지 단절되어 있는지 확인하는 함수
	// [NodeID : 대상 노드, IsActive : 연결 혹은 단절 상태]
	EXTERN LONG (__stdcall *ceGnNodeIsActive)		(__in LONG NodeID, __out PLONG IsActive);

	// 해당 노드의 Flash Memory에 환경 설정 데이터 기록을 시작.
	// [NodeID : 노드 번호]
	EXTERN LONG (__stdcall *ceGnBeginSerialize)	(__in LONG NodeID);

	// 해당 노드에 Flash Memory에 환경 설정 데이터 기록을 종료.
	// [NodeID : 노드 번호]
	EXTERN LONG (__stdcall *ceGnEndSerialize)	(__in LONG NodeID);

	// 해당 모션 제어 축에 대한 노드 및 모듈 정보를 반환.
	// [Axis : 통합 모션 제어 축 번호, NodeIP : 노드 IP 주소 반환, NodeID : 노드 번호 반환, NodeInGlobal : 해당 노드의 통합 모션 제어 축 번호 반환,
	// ModuleIdx : 해당 노드의 모듈 번호 반환, ModuleInCh : 모듈 내 모션 제어 축 번호 반환]
	EXTERN LONG (__stdcall *ceGnLocalAxis_Get)	(__in LONG Axis,  __out PLONG NodeIP, __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// 해당 디지털 I/O 채널에 대한 노드 및 모듈 정보를 반환.
	// [Channel : 통합 디지털 입출력 채널 번호, NodeIP : 노드 IP 주소 반환, NodeID : 노드 번호 반환, NodeInGlobal : 해당 노드의 통합 디지털 입출력 채널 번호 반환, ModuleIdx : 해당 노드의 모듈 번호 반환, ModuleInCh : 모듈 내 디지털 입출력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnLocalDIO_Get)	(__in LONG Channel,  __out PLONG NodeIP, __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// 해당 아날로그 입력 채널에 대한 노드 및 모듈 정보를 반환.
	// [Channel: 통합 아날로그 입력 채널 번호, NodeIP : 노드 IP 주소 반환, NodeID : 노드 번호 반환, NodeInGlobal : 해당 노드의 통합 아날로그 입력 채널 번호 반환, ModuleIdx : 해당 노드의 모듈 번호 반환, ModuleInCh : 모듈 내 아날로그 입력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnLocalAI_Get)	(__in LONG Channel,  __out PLONG NodeIP, __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// 해당 아날로그 출력 채널에 대한 노드 및 모듈 정보를 반환.
	// [Channel: 통합 아날로그 출력 채널 번호, NodeIP : 노드 IP 주소 반환, NodeID : 노드 번호 반환, NodeInGlobal : 해당 노드의 통합 아날로그 출력 채널 번호 반환, ModuleIdx : 해당 노드의 모듈 번호 반환, ModuleInCh : 모듈 내 아날로그 출력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnLocalAO_Get)	(__in LONG Channel, __out PLONG NodeIP,  __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// 해당 모션 디지털 입출력 채널에 대한 노드 및 모듈 정보를 반환.
	// [Channel: 통합 카운터 채널 번호, NodeIP : 노드 IP 주소 반환, NodeID : 노드 번호 반환, NodeInGlobal : 해당 노드의 통합 모션 디지털 입출력 채널 번호 반환, ModuleIdx : 해당 노드의 모듈 번호 반환, ModuleInCh : 모듈 내 모션 디지털 입 출력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnLocalMDIO_Get)   (__in LONG Channel, __out PLONG NodeIP,  __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// 해당 카운터 채널에 대한 노드 및 모듈 정보를 반환.
	// [Channel: 통합 카운터 채널 번호, NodeIP : 노드 IP 주소 반환, NodeID : 노드 번호 반환, NodeInGlobal : 해당 노드의 통합 카운터 채널 번호 반환, ModuleIdx : 해당 노드의 모듈 번호 반환, ModuleInCh : 모듈 내 카운터 출력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnLocalCNT_Get)   (__in LONG Channel, __out PLONG NodeIP,  __out PLONG NodeID, __out PLONG NodeInGlobal, __out PLONG ModuleIdx, __out PLONG ModuleInCh);

	// 해당 노드 모션 모듈의 로컬 축 번호를 통하여 통합 축 번호를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 해당 노드의 모듈 번호, ModuleInCh : 모듈 내 모션 제어 축 번호, GlobalAxis : 통합 모션 제어 축 번호 반환]
	EXTERN LONG (__stdcall *ceGnGlobalAxis_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalAxis);

	// 해당 노드 디지털 입출력 모듈의 로컬 채널 번호를 통하여 통합 채널 번호를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 해당 노드의 모듈 번호, ModuleInCh : 모듈 내 디지털 입출력 채널 번호, GlobalDIO : 통합 디지털 입출력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnGlobalDIO_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalDIO);

	// 해당 노드 아날로그 입력 모듈의 로컬 채널 번호를 통하여 통합 채널 번호를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 해당 노드의 모듈 번호, ModuleInCh : 모듈 내 아날로그 입력 채널 번호, GlobalAI : 통합 아날로그 입력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnGlobalAI_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalAI);

	// 해당 노드 아날로그 출력 모듈의 로컬 채널 번호를 통하여 통합 채널 번호를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 해당 노드의 모듈 번호, ModuleInCh : 모듈 내 아날로그 출력 채널 번호, GlobalAO : 통합 아날로그 출력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnGlobalAO_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalAO);

	// 해당 노드 모션 디지털 입 출력 모듈의 로컬 채널 번호를 통하여 통합 채널 번호를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 해당 노드의 모듈 번호, ModuleInCh : 모듈 내 모션 디지털 입 출력 채널 번호, GlobalAO : 통합 모션 디지털 입 출력 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnGlobalMDIO_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalMDIO);

	// 해당 노드 카운터 모듈의 로컬 채널 번호를 통하여 통합 채널 번호를 반환.
	// [NodeID : 노드 번호, ModuleIdx : 해당 노드의 모듈 번호, ModuleInCh : 모듈 내 카운터 채널 번호, GlobalAO : 통합 카운터 채널 번호 반환]
	EXTERN LONG (__stdcall *ceGnGlobalCNT_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __in  LONG ModuleInCh, __out PLONG GlobalCNT);
	
	EXTERN LONG (__stdcall *ceGnModuleTrType_Get)	(__in LONG NodeID, __in  LONG ModuleIdx, __out PLONG Type);


	//****************************************************************************
	//*************** START OF GENERAL MOTION FUNCTION DECLARATIONS **************
	//****************************************************************************

	// SERVO-ON 신호 출력을 인가 혹은 차단.
	// [Channel : 통합 축 번호, Enable : SERVO-ON 신호 출력 ON/OFF]
	EXTERN LONG (__stdcall *cemGnServoOn_Set)	(__in LONG Channel, __in LONG Enable);

	// SERVO-ON 신호의 출력 상태를 반환.
	// [Channel: 통합 축 번호, Enable: SERVO-ON 신호의 출력 상태를 반환]
	EXTERN LONG (__stdcall *cemGnServoOn_Get)	(__in LONG Channel, __in PLONG Enable);

	// 해당 모션 축의 알람 리셋 신호 출력 제어.
	// [Axis : 통합 모션 제어 축 번호, IsReset: 알람 리셋 신호 출력 여부]
	EXTERN LONG (__stdcall *cemGnAlarmReset) (__in LONG Axis, __in LONG IsReset);

	//****************************************************************************
	//*************** START OF CONFIGURATION FUNCTION DECLARATIONS ***************
	//****************************************************************************

	// 모션 입출력 신호의 환경 설정 구성. PropId는 ceSDKDef.h 파일에 정의된 enum _TCmMioPropId 값 리스트를 참고.
	// [Axis : 통합 축 번호, PropId : 환경 설정 매개 변수, PropVal : PropId로 지정된 환경에 대한 설정값]
	EXTERN LONG (__stdcall *cemCfgMioProperty_Set)	(__in LONG Axis, __in  LONG PropId, __in  LONG PropVal);

	// 모션 입출력 신호의 환경 설정 구성 반환. PropId는 ceSDKDef.h 파일에 정의된 enum _TCmMioPropId 값 리스트를 참고.
	// [Axis : 통합 축 번호, PropId : 환경 설정 매개 변수, PropVal : PropId로 지정된 환경에 대한 반환값]
	EXTERN LONG (__stdcall *cemCfgMioProperty_Get)	(__in LONG Axis, __in  LONG PropId, __out PLONG PropVal);

	// 각종 I/O(Input/Output) 신호에 대해 노이즈 대응 필터 기능 설정.
	// [Axis : 통합 축 번호, IsEnable : 필터 로직 적용 여부]
	EXTERN LONG (__stdcall *cemCfgFilter_Set)	(__in LONG Axis, __in LONG IsEnable);

	// 각종 I/O(Input/Output) 신호에 대해 노이즈 대응 필터 기능 설정 상태를 반환.
	// [Axis : 통합 축 번호, IsEnabled : 필터 로직 적용 여부 반환]
	EXTERN LONG (__stdcall *cemCfgFilter_Get)	(__in LONG Axis, __out PLONG IsEnabled);

	// EA/EB 또는 PA/PB 신호 입력 회로에 노이즈 필터를 적용할 지를 설정.
	// [Channel : 통합 축 번호, Target : 함수의 적용 대상(EA/EB or PA/PB), IsEnable : 필터 로직의 적용 여부]
	EXTERN LONG (__stdcall *cemCfgFilterAB_Set)	(__in LONG Channel, __in LONG Target, __in LONG IsEnable);

	// EA/EB 또는 PA/PB 신호 입력 회로에 노이즈 필터를 적용할 지에 대한 설정 상태를 반환
	// [Channel : 통합 축 번호, Target : 함수의 적용 대상(EA/EB or PA/PB), IsEnabled : 필터 로직 적용 여부 반환]
	EXTERN LONG (__stdcall *cemCfgFilterAB_Get)	(__in LONG Channel, __in LONG Target, __out PLONG IsEnabled);

	// 인코더 펄스(Feedback Pulse) 신호의 입력 모드 설정.
	// [Axis : 통합 축 번호, InputMode : Feedback Pulse 입력 모드, IsReverse : Feedback Count 값의 UP/DOWN 방향을 반대로 할 것인지 여부]
	EXTERN LONG (__stdcall *cemCfgInMode_Set)	(__in LONG Axis, __in LONG InputMode, __in LONG IsReverse);

	// 인코더 펄스(Feedback Pulse) 신호의 입력 모드 설정 상태를 반환.
	// [Axis : 통합 축 번호, InputMode: Feedback Pulse 입력 모드, IsReverse : Feedback Count 값의 UP/DOWN 방향을 반대로 할 것인지 여부 반환]
	EXTERN LONG (__stdcall *cemCfgInMode_Get)	(__in LONG Axis, __out PLONG InputMode, __out PLONG IsReverse);

	// 지령 펄스(Command Pulse) 신호 출력 모드 설정.
	// [Axis : 통합 축 번호, OutputMode : Command Pulse 출력 모드]
	EXTERN LONG (__stdcall *cemCfgOutMode_Set)	(__in LONG Axis, __in LONG OutputMode);

	// 지령 펄스(Command Pulse) 신호 출력 모드 설정 상태를 반환.
	// [Axis : 통합 축 번호, OutputMode: Command 펄스의 출력 모드 반환]
	EXTERN LONG (__stdcall *cemCfgOutMode_Get)	(__in LONG Axis, __out PLONG OutputMode);

	// 이송 목표 좌표의 기준을 커맨드 위치로 할지 피드백 위치로 할지를 설정.
	// [Axis : 통합 축 번호, CtrlMode : 제어 모드]
	EXTERN LONG (__stdcall *cemCfgCtrlMode_Set)	(__in LONG Axis, __in LONG CtrlMode);

	// 이송 목표 좌표의 기준을 커맨드 위치로 할지 피드백 위치로 할지에 대한 설정 상태를 반환.
	// [Axis : 통합 축 번호, CtrlMode : 제어 모드]
	EXTERN LONG (__stdcall *cemCfgCtrlMode_Get)	(__in LONG Axis, __out PLONG CtrlMode);

	// 입력 펄스(Feedback Pulse)와 출력 펄스(Command Pulse)의 분해능율 설정.
	// [Axis : 통합 축 번호, Ratio : Feedback Pulse와 Command Pulse의 분해능 비율]
	EXTERN LONG (__stdcall *cemCfgInOutRatio_Set)	(__in LONG Axis, __in DOUBLE Ratio);

	// 입력 펄스(Feedback Pulse)와 출력 펄스(Command Pulse)의 분해능 설정 상태를 반환.
	// [Axis : 통합 축 번호, Ratio : Feedback Pulse와 Command Pulse의 분해능 비율을 반환]
	EXTERN LONG (__stdcall *cemCfgInOutRatio_Get)	(__in LONG Axis, __out PDOUBLE Ratio);

	// 논리적 거리 단위를 설정.
	// [Axis : 통합 축 번호, UnitDist : 논리적 거리 1을 이동하기 위한 출력 펄스 수]
	EXTERN LONG (__stdcall *cemCfgUnitDist_Set)	(__in LONG Axis, __in DOUBLE UnitDist);

	// 논리적 거리 단위를 반환.
	// [Axis : 통합 축 번호, UnitDist : 논리적 거리 1을 이동하기 위한 출력 펄스 수를 반환]
	EXTERN LONG (__stdcall *cemCfgUnitDist_Get)	(__in LONG Axis, __out PDOUBLE UnitDist);

	// 논리적 속도 단위를 설정.
	// [Axis : 통합 축 번호, UnitSpeed : 단위 속도에 대한 펄스 출력 속도(PPS)]
	EXTERN LONG (__stdcall *cemCfgUnitSpeed_Set)	(__in LONG Axis, __in DOUBLE UnitSpeed);

	// 논리적 속도 단위를 반환.
	// [Axis : 통합 축 번호, UnitSpeed : 단위 속도에 대한 펄스 출력 속도(PPS)를 반환]
	EXTERN LONG (__stdcall *cemCfgUnitSpeed_Get)	(__in LONG Axis, __out PDOUBLE UnitSpeed);

	// 모션 속도 제한범위를 설정.
	// [Axis : 통합 축 번호, MaxPPS : 모션 최고 속도(PPS)]
	EXTERN LONG (__stdcall *cemCfgSpeedRange_Set)	(__in LONG Axis, __in  DOUBLE MaxPPS);

	// 모션 속도 제한범위 설정 상태를 반환.
	// [Axis : 통합 축 번호, MinPPS : 모션 최저 속도(PPS) 반환, MaxPPS : 모션 최고 속도(PPS) 반환]
	EXTERN LONG (__stdcall *cemCfgSpeedRange_Get)	(__in LONG Axis, __out PDOUBLE MinPPS, __out PDOUBLE MaxPPS);

	// 모션 이송 기준 속도 설정.
	// [Axis : 통합 축 번호, SpeedMode : 속도 모드, WorkSpeed : 작업 속도, Accel : 가속도, Decel : 감속도]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_Set)	(__in LONG Axis, __in  LONG SpeedMode, __in  DOUBLE  WorkSpeed, __in  DOUBLE Accel,  __in  DOUBLE Decel);

	// 모션 이송 기준 속도 설정 상태를 반환.
	// [Axis : 통합 축 번호, SpeedMode : 속도 모드 반환, WorkSpeed : 작업 속도 반환, Accel : 가속도 반환, Decel : 감속도 반환]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_Get)	(__in LONG Axis, __out PLONG SpeedMode,__out PDOUBLE WorkSpeed, __out PDOUBLE Accel, __out PDOUBLE Decel);

	// 모션 이송 기준 속도 설정.
	// [Axis : 통합 축 번호, SpeedMode : 속도 모드, WorkSpeed : 작업 속도, AccelTime : 가속도시간, DecelTime : 감속도시간]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_T_Set)	(__in LONG Axis, __in  LONG SpeedMode, __in  DOUBLE  WorkSpeed, __in  DOUBLE AccelTime,  __in  DOUBLE DecelTime);

	// 모션 이송 기준 속도 설정 상태를 반환.
	// [Axis : 통합 축 번호, SpeedMode : 속도 모드 반환, WorkSpeed : 작업 속도 반환, AccelTime : 가속도 시간 반환, DecelTime : 감속도 시간 반환]
	EXTERN LONG (__stdcall *cemCfgSpeedPattern_T_Get)	(__in LONG Axis, __out PLONG SpeedMode,__out PDOUBLE WorkSpeed, __out PDOUBLE AccelTime, __out PDOUBLE DecelTime);

	// 입력 펄스(Feedback Pulse)를 통해 모션의 실제속도 검출 설정.
	// [Axis : 통합 축 번호, IsEnable : Feedback 속도 확인 기능 활성 여부, Interval : Feedback 펄스 수 확인 주기(ms)]
	EXTERN LONG (__stdcall *cemCfgActSpdCheck_Set)	(__in LONG Axis, __in LONG IsEnable, __in LONG Interval);

	// 입력 펄스(Feedback Pulse)를 통한 모션 실제속도 검출 설정 상태를 반환.
	// [Axis : 통합 축 번호, IsEnable : Feedback 속도 확인 기능 활성여부를 반환, Interval : Feedback 펄스 수 확인 주기(ms) 반환]
	EXTERN LONG (__stdcall *cemCfgActSpdCheck_Get)	(__in LONG Axis, __out PLONG IsEnable, __out PLONG Interval);

	// 모션의 이송 범위를 소프트웨어적인 이송제한범위를 설정하여 제한.
	// [Axis : 통합 축 번호, IsEnable : 소프트웨어 리밋 기능 활성 여부, LimitN : (-)방향 Limit값, LimitP : (+)방향 Limit값]
	EXTERN LONG (__stdcall *cemCfgSoftLimit_Set)	(__in LONG Axis, __in LONG IsEnable, __in DOUBLE LimitN, __in DOUBLE LimitP);

	// 모션의 소프트웨어적인 이송제한범위에 대한 설정을 반환.
	// [Axis : 통합 축 번호, IsEnable : 소프트웨어 리밋 기능 활성 여부 반환, LimitN : (-)방향 Limit값 반환, LimitP : (+)방향 Limit값 반환]
	EXTERN LONG (__stdcall *cemCfgSoftLimit_Get)	(__in LONG Axis, __out PLONG IsEnable, __out PDOUBLE LimitN, __out PDOUBLE LimitP);

	// 링카운터(Ring-Counter) 기능 설정.
	// [Channel : 통합 축 번호, TargCntr : 함수의 적용 대상(Command or Feedback Counter), IsEnable : Ring-Counter 기능 활성 여부, CntMax: 카운터 범위]
	EXTERN LONG (__stdcall *cemCfgRingCntr_Set)	(__in LONG Channel, __in LONG TargCntr, __in LONG IsEnable, __in DOUBLE CntMax);

	// 링카운터(Ring-Counter) 기능 설정 상태를 반환.
	// [Channel: 통합 축 번호, TargCntr: 함수의 적용 대상(Command or Feedback Counter) 선택, IsEnable: Ring-Counter 기능 활성 여부 반환, CntMax: 카운터 범위 반환]
	EXTERN LONG (__stdcall *cemCfgRingCntr_Get)	(__in LONG Channel, __in LONG TargCntr, __out PLONG IsEnable, __out PDOUBLE CntMax);

	// 작업속도 보정 시 보정된 작업속도를 산출하는 비례 값 설정.
	// [Axis: 통합 축 번호, fCorrRatio: 속도 보정 비율값(%)]
	EXTERN LONG (__stdcall *cemCfgVelCorrRatio_Set)	(__in LONG Axis, __in DOUBLE fCorrRatio);

	// 작업속도 보정 시 보정된 작업속도를 산출하는 비례 값을 반환.
	// [Axis: 통합 축 번호, fCorrRatio: 속도 보정 비율값(%) 반환]
	EXTERN LONG (__stdcall *cemCfgVelCorrRatio_Get)	(__in LONG Axis, __out PDOUBLE fCorrRatio);

	// 이전의 이송 작업이 완료되지 않은 축에 새로운 이송 명령이 하달되었을 때의 처리 정책을 설정.
	// [seqMode: 시퀀스(Sequence) 모드]
	EXTERN LONG (__stdcall *cemCfgSeqMode_Set)	(__in LONG SeqMode);

	// 이전의 이송 작업이 완료되지 않은 축에 새로운 이송 명령이 하달되었을 때의 처리 정책에 대한 설정을 반환.
	// [seqMode: 시퀀스(Sequence) 모드 반환]
	EXTERN LONG (__stdcall *cemCfgSeqMode_Get)	(__out PLONG SeqMode);

	//****************************************************************************
	//*************** START OF HOME RETURN FUNCTION DECLARATIONS *****************
	//****************************************************************************

	// 원점복귀 환경 설정.
	// [Axis: 통합 축 번호, HomeMode: 원점복귀 모드(0~12), Dir: 원점복귀 모션 수행 방향 EzCount: EzCount 값(0~15), EscDist: 원점탈출 거리, Offset: 원점복귀 종료 위치를 기준으로 추가 모션 이동값(상대좌표 이송)]
	EXTERN LONG (__stdcall *cemHomeConfig_Set)	(__in LONG Axis, __in  LONG HomeMode,  __in  LONG Dir,  __in LONG EzCount,  __in  DOUBLE EscDist,  __in  DOUBLE Offset);

	// 원점복귀 환경 설정 상태를 반환.
	// [Axis: 통합 축 번호, HomeMode: 원점복귀 모드(0~12) 반환, Dir: 원점복귀 모션 수행 방향 반환, EzCount: EzCount 값(0~15) 반환, EscDist: 원점탈출 거리 반환, Offset: 원점복귀 종료 위치를 기준으로 추가 모션 이동값 반환]
	EXTERN LONG (__stdcall *cemHomeConfig_Get)	(__in LONG Axis, __out PLONG HomeMode, __out PLONG Dir, __out PLONG EzCount, __out PDOUBLE EscDist, __out PDOUBLE Offset);

	// 원점복귀 완료 후 발생하는 모션 컨트롤러와 서보 드라이브간의 제어 편차에 의해 발생한 입력 펄스(Feedback Pulse) 처리에 대한 설정.
	// [Axis: 통합 축 번호, PosClrMode: Command 및 Feedback 위치가 클리어되는 모드]
	EXTERN LONG (__stdcall *cemHomePosClrMode_Set)	(__in LONG Axis, __in LONG PosClrMode);

	// 원점복귀 완료 후 발생하는 모션 컨트롤러와 서보 드라이브간의 제어 편차에 의해 발생한 입력 펄스(Feedback Pulse) 처리에 대한 설정 상태를 반환.
	//[Axis: 통합 축 번호, PosClrMode: Command 및 Feedback 위치가 클리어 되는 모드 반환]
	EXTERN LONG (__stdcall *cemHomePosClrMode_Get)	(__in LONG Axis, __out PLONG PosClrMode);

	// 원점 복귀 속도 설정.
	// [Axis: 통합 축 번호, SpeedMode: 원점복귀 속도 모드, Vel: 원점복귀 작업 속도, Accel: 원점복귀 가속도, Decel: 원점복귀 감속도, RevVel: Revers Speed]
	EXTERN LONG (__stdcall *cemHomeSpeedPattern_Set)	(__in LONG Axis, __in LONG SpeedMode, __in DOUBLE Vel, __in DOUBLE Accel, __in DOUBLE Decel, __in DOUBLE RevVel);

	// 원점 복귀 속도 설정 상태를 반환.
	// [Axis: 통합 축 번호, SpeedMode: 원점복귀 속도 모드 반환, Vel: 원점복귀 작업 속도 반환, Accel:원점복귀 가속도 반환, Decel:원점복귀 감속도 반환, RevVel: Revers Speed 반환]
	EXTERN LONG (__stdcall *cemHomeSpeedPattern_Get)	(__in LONG Axis, __out PLONG SpeedMode, __out PDOUBLE Vel, __out PDOUBLE Accel, __out PDOUBLE Decel, __out PDOUBLE RevVel);

	// 단축 원점 복귀 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [Axis: 통합 축 번호, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemHomeMove)	(__in LONG Axis, __in LONG IsBlocking);

	// 단축 원점 복귀 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Axis: 통합 축 번호]
	EXTERN LONG (__stdcall *cemHomeMoveStart)	(__in LONG Axis);

	// 다축 원점 복귀 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [NumAxes: 작업 대상 축 수, AxisList: 대상 축의 배열 주소, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemHomeMoveAll)	(__in LONG NumAxes, __in PLONG AxisList, __in LONG IsBlocking);

	// 다축 원점 복귀 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	//[NumAxes: 작업 대상 축 수, AxisList: 대상 축의 배열 주소]
	EXTERN LONG (__stdcall *cemHomeMoveAllStart)	(__in LONG NumAxes, __in PLONG AxisList);

	// 이전에 실행된 원점복귀 구동 완료 상태를 확인.
	// [Axis: 통합 축 번호, IsSuccess: 이전에 실행된 원점 복귀 구동 완료 여부 반환]
	EXTERN LONG (__stdcall *cemHomeSuccess_Get)	(__in LONG Axis, __out PLONG IsSuccess);

	// 이전에 실행된 원점복귀 구동 완료 상태를 강제로 설정.
	// [Axis: 통합 축 번호, IsSuccess: 원점 복귀의 성공 여부를 강제로 설정]
	EXTERN LONG (__stdcall *cemHomeSuccess_Set)	(__in LONG Axis, __in LONG IsSuccess);

	// 원점복귀 구동 상태를 반환.
	// [Axis: 통합 축 번호, IsBusy: 현재 원점복귀 진행 여부 반환]
	EXTERN LONG (__stdcall *cemHomeIsBusy)	(__in LONG Axis, __out PLONG IsBusy);

	// 원점복귀 완료 시까지 대기.
	// [Channel: 통합 축 번호, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemHomeWaitDone)	(__in LONG Axis, __in LONG IsBlocking);


	//****************************************************************************
	//*************** START OF SINGLE AXIS CONTROL FUNCTION DECLARATIONS *********
	//****************************************************************************

	// 단축 구동 시 해당 축에 대한 속도방식 및 속도비율 설정.
	// [Axis: 통합 축 번호, SpeedMode: 속도 모드, VelRatio: 작업속도 비율(%), AccRatio: 가속도 비율(%), DecRatio: 감속도 비율(%)]
	EXTERN LONG (__stdcall *cemSxSpeedRatio_Set)	(__in LONG Axis, __in LONG SpeedMode, __in DOUBLE VelRatio, __in DOUBLE AccRatio, __in DOUBLE DecRatio);

	// 단축 구동 시 해당 축에 대한 속도방식 및 속도비율 설정 상태를 반환.
	// [Axis: 통합 축 번호, SpeedMode: 속도 모드 반환, VelRatio: 작업속도 비율(%) 반환, AccRatio: 가속도 비율(%) 반환, DecRatio: 감속도 비율(%) 반환]
	EXTERN LONG (__stdcall *cemSxSpeedRatio_Get)	(__in LONG Axis, __out PLONG SpeedMode, __out PDOUBLE VelRatio, __out PDOUBLE AccRatio, __out PDOUBLE DecRatio);

	// 단축 상대 좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [Axis: 통합 축 번호, Distance: 이동할 거리, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemSxMove)	(__in LONG Axis, __in DOUBLE Distance, __in LONG IsBlocking);

	// 단축 상대 좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Axis: 통합 축 번호, Distance: 이동할 거리]
	EXTERN LONG (__stdcall *cemSxMoveStart)	(__in LONG Axis, __in DOUBLE Distance);

	// 단축 절대 좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [Axis: 통합 축 번호, Distance: 이동할 절대 좌표값, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemSxMoveTo)	(__in LONG Axis, __in DOUBLE Position, __in LONG IsBlocking);

	// 단축 절대 좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Axis: 통합 축 번호, Distance: 이동할 절대 좌표 값]
	EXTERN LONG (__stdcall *cemSxMoveToStart)	(__in LONG Axis, __in DOUBLE Position);	

	// 단축 연속 속도 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Axis: 통합 축 번호, Direction: 모션 이송 방향]
	EXTERN LONG (__stdcall *cemSxVMoveStart)	(__in LONG Axis, __in LONG Direction);

	// 단축 이송 감속 후 정지.
	// [Axis: 통합 축 번호, IsWaitComplete: 동작 완료될때까지 함수 반환 여부, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemSxStop)	(__in LONG Axis, __in LONG IsWaitComplete, __in LONG IsBlocking);

	// 단축 이송 비상 정지.
	// [Axis: 통합 축 번호]
	EXTERN LONG (__stdcall *cemSxStopEmg)	(__in LONG Axis);

	// 단축 이송 완료 확인.
	// [Axis: 통합 축 번호, IsDone: 모션 작업 완료 여부 반환]
	EXTERN LONG (__stdcall *cemSxIsDone)	(__in LONG Axis, __out PLONG IsDone);

	// 단축 이송 완료 시점까지 대기.
	// [Axis: 통합 축 번호, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemSxWaitDone)	(__in LONG Axis, __in LONG IsBlocking);

	// 해당 통합 축에 대해 마지막으로 이송한(상대 or 절대 좌표) 위치를 반환.
	// [Channel: 통합 축 번호, Position: 마지막으로 이송한 위치 값 반환]
	EXTERN LONG (__stdcall *cemSxTargetPos_Get)	(__in LONG Channel, __out PDOUBLE Position);

	// 단축 모션의 초기 속도 설정.
	// [Axis: 통합 축 번호, IniSpeed: 초기 속도]
	EXTERN LONG (__stdcall *cemSxOptIniSpeed_Set)	(__in LONG Axis, __in DOUBLE IniSpeed);

	// 단축 모션의 초기 속도 설정을 반환.
	// [Axis: 통합 축 번호, IniSpeed: 초기 속도 반환]
	EXTERN LONG (__stdcall *cemSxOptIniSpeed_Get)	(__in LONG Axis, __out PDOUBLE IniSpeed);

	// 단축 모션의 RDP 오프셋 설정 
	// [Axis: 통합 축(채널)번호, OffsetDist:RDP 위치]
	EXTERN LONG (__stdcall *cemSxOptRdpOffset_Set)(__in LONG Axis, __in DOUBLE OffsetDist);

	// 단축 모션의 RDP 오프셋 반환
	// [Axis: 통합 축(채널)번호, OffsetDist:RDP 위치 반환]
	EXTERN LONG (__stdcall *cemSxOptRdpOffset_Get)(__in LONG Axis, __in PDOUBLE OffsetDist);
	
	// 단축 모션 상대 좌표 2단계 속도 이송 기능. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Axis: 통합 축 번호, Distance: 이동할 거리(상대 좌표 값), Vel2: 2단계 작업 속도]
	EXTERN LONG (__stdcall *cemSxMoveStart2V)	(__in LONG Axis, __in  DOUBLE Distance, __in DOUBLE Vel2);

	// 단축 모션 절대 좌표 2단계 속도 이송 기능. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Axis: 통합 태널 번호, Position: 이동할 위치 (절대 좌표 값), Vel2: 2단계 작업 속도]
	EXTERN LONG (__stdcall *cemSxMoveToStart2V)	(__in LONG Axis, __in  DOUBLE Position, __in DOUBLE Vel2);

	// 단축 모션의 백래쉬 혹은 슬립 보정을 위해 설정.
	// [Axis: 통합 축 번호, CorrMode: 보정 모드, CorrAmount: 보정 펄스 수, CorrVel: 보정 펄스의 출력 주파수, CntrMask: 보정 펄스 출력시 카운터의 동작 여부]
	EXTERN LONG (__stdcall *cemSxCorrection_Set)	(__in LONG Axis, __in LONG CorrMode, __in DOUBLE CorrAmount, __in DOUBLE CorrVel, __in LONG CntrMask);

	// 단축 모션의 백래쉬 혹은 슬립 보정의 설정을 반환.
	// [Axis: 통합 축 번호, CorrMode: 보정 모드 반환, CorrAmount: 보정 펄스 수 반환, CorrVel: 보정 펄스의 출력 주파수 반환, CntrMask: 보정 펄스 출력시 카운터의 동작 여부 반환]
	EXTERN LONG (__stdcall *cemSxCorrection_Get)	(__in LONG Axis, __out PLONG CorrMode, __out PDOUBLE CorrAmount, __out PDOUBLE CorrVel, __out PLONG CntrMask);

	// 지정한 다른 축과 동기 시작 환경 설정.
	// [Axis: 통합 축 번호, Mode: 동기 모드, RefAxis: 내부 동기 신호를 발생할때 참조할 축 혹은 마스크, Condition: 내부 동기 신호 발생 조건]
	EXTERN LONG (__stdcall *cemSxOptSyncMode_Set)	(__in LONG Axis, __in LONG Mode, __in LONG RefAxis, __in LONG Condition);

	// 지정한 다른 축과 동기 시작에 대한 설정 반환.
	// [Axis: 통합 축 번호, Mode: 동기 모드 반환, RefAxis: 내부 동기 신호를 발생할때 참조할 축 혹은 마스크를 반환, Condition: 내부 동기 신호 발생 조건 반환]
	EXTERN LONG (__stdcall *cemSxOptSyncMode_Get)	(__in LONG Axis, __out PLONG Mode, __out PLONG RefAxis, __out PLONG Condition);

	// 모션 속도 구간 별 디지털 출력 설정.
	// [Axis: 통합 축 번호, Mode: 고속 디지털 출력 발생 모드, DoChan_local: 디지털 출력 채널 번호, DoLogic: 디지털 출력 채널의 로직]
	//EXTERN LONG (__stdcall *cemSxOptSyncOut_Set)	(__in LONG Axis, __in LONG Mode, __in LONG DoChan_local, __in LONG DoLogic);

	// 모션 속도 구간 별 디지털 출력 설정 반환.
	// [Axis: 통합 축 번호, Mode: 고속 디지털 출력 발생 모드 반환, DoChan_local: 디지털 출력 채널 번호 반환, DoLogic: 디지털 출력 채널의 로직 반환]
	//EXTERN LONG (__stdcall *cemSxOptSyncOut_Get)	(__in LONG Axis, __out PLONG Mode, __out PLONG DoChan_local, __out PLONG DoLogic);

	// RDP(Ramping Down Point)의 오프셋 설정. (감속 시작의 상대 위치 설정.)
	// [Axis: 통합 축 번호, OffsetDist: RDP Offset 적용 거리]
	//EXTERN LONG (__stdcall *cemSxOptRdpOffset_Set)	(__in LONG Axis, __in DOUBLE OffsetDist);

	// RDP(Ramping Down Point)의 오프셋 반환. (감속 시작의 상대 위치 반환.)
	// [Axis: 통합 축 번호, OffsetDist: RDP Offset 적용 거리 반환]
	//EXTERN LONG (__stdcall *cemSxOptRdpOffset_Get)	(__in LONG Axis, __out PDOUBLE OffsetDist);


	//****************************************************************************
	//*************** START OF MULTIPLE AXES CONTROL FUNCTION DECLARATIONS *******
	//****************************************************************************

	// 다축 상대 좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, DistList: 이동할 거리값의 배열 주소, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemMxMove)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE DistList, __in LONG IsBlocking);

	// 다축 상대 좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	//[NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, DistList: 이동할 거리의(상대좌표) 배열 주소]
	EXTERN LONG (__stdcall *cemMxMoveStart)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE DistList);

	// 다축 절대 좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, PosList: 이동할 위치의(절대좌표) 배열 주소, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemMxMoveTo)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE PosList, __in LONG IsBlocking);

	// 다축 절대 좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, PosList: 이동할 위치의(절대좌표) 배열 주소]
	EXTERN LONG (__stdcall *cemMxMoveToStart)	(__in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE PosList);

	// 다축 연속속도 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, DirList: 방향을 지시하는 값의 배열 주소]
	EXTERN LONG (__stdcall *cemMxVMoveStart)	(__in LONG NumAxes, __in PLONG AxisList, __in PLONG DirList);

	// 다축 이송 감혹 후 정지.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, IsWaitComplete: 동작 완료될때까지 함수 반환 여부, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemMxStop)	(__in LONG NumAxes, __in PLONG AxisList, __in LONG IsWaitComplete, __in LONG IsBlocking);

	// 다축 이송 비상 정지.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소]
	EXTERN LONG (__stdcall *cemMxStopEmg)	(__in LONG NumAxes, __in PLONG AxisList);

	// 다축 이송 완료 확인.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, IsDone: 모션작업 완료 여부 반환]
	EXTERN LONG (__stdcall *cemMxIsDone)	(__in LONG NumAxes, __in PLONG AxisList, __out PLONG IsDone);

	// 다축 이송 완료 시점까지 대기.
	// [NumAxes: 대상 축 수, AxisList: 대상 축의 배열 주소, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemMxWaitDone)	(__in LONG NumAxes, __in PLONG AxisList, __in LONG IsBlocking);

	//****************************************************************************
	//*************** START OF INTERPOLATION CONTROL FUNCTION DECLARATIONS *******
	//****************************************************************************

	// 보간 대상 축 그룹 설정.
	// [MapIndex: 맵 번호(0~7), NodeID: 노드 번호, MapMask1: 축 맵에 포함할 축들을 지정할 마스크값(하위 32비트, BIT0~BIT31),
	// MapMask2: 축 맵에 포함할 축들을 지정할 마스크값(상위 32비트, BIT32~BIT63)]
	EXTERN LONG (__stdcall *cemIxMapAxes)	(__in LONG MapIndex,__in LONG NodeID, __in LONG MapMask1, __in LONG MapMask2);

	// 보간 속도 보정모드 설정 [MapIndex: 맵 번호, 옵션1: VelCorrOpt1, 옵션2: VelCorrOpt2] 
	EXTERN LONG (__stdcall *cemIxVelCorrMode_Set)	(__in LONG MapIndex, __in LONG VelCorrOpt1, __in LONG VelCorrOpt2);

	// 보간 속도 보정모드 반환 [MapIndex: 맵 번호, 옵션1: VelCorrOpt1, 옵션2: VelCorrOpt2]
	EXTERN LONG (__stdcall *cemIxVelCorrMode_Get)	(__in LONG MapIndex, __out PLONG VelCorrOpt1, __out PLONG VelCorrOpt2);

	// 보간 대상 축 그룹 설정 해제.
	// [MapIndex: 맵 번호]
	EXTERN LONG (__stdcall *cemIxUnMap)	(__in LONG MapIndex);

	// 보간 이송 속도 설정.
	// [MapIndex: 맵 번호, IsVectorSpeed: 벡터 혹은 마스터 스피드 모드 설정, SpeedMode: 속도 모드, Vel: 작업 속도, Acc: 가속도, Dec: 감속도]
	EXTERN LONG (__stdcall *cemIxSpeedPattern_Set)	(__in LONG MapIndex, __in LONG IsVectorSpeed, __in LONG SpeedMode, __in DOUBLE Vel, __in DOUBLE Acc, __in DOUBLE Dec);

	// 보간 이속 속도 설정을 반환.
	// [MapIndex: 맵 번호, IsVectorSpeed: 벡터 혹은 마스터 스피드 모드 설정 반환, SpeedMode: 속도 모드 반환, Vel: 작업 속도 반환, Acc: 가속도 반환, Dec: 감속도 반환]
	EXTERN LONG (__stdcall *cemIxSpeedPattern_Get)	(__in LONG MapIndex, __out PLONG IsVectorSpeed, __out PLONG SpeedMode, __out PDOUBLE Vel, __out PDOUBLE Acc, __out PDOUBLE Dec);

	// 직선 보간 상대좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, DistList: 이동할 거리의(상대좌표) 배열 주소, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxLine)	(__in LONG MapIndex, __in PDOUBLE DistList, __in LONG IsBlocking);

	// 직선 보간 상대좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, DistList: 이동할 거리의(상대좌표) 배열 주소]
	EXTERN LONG (__stdcall *cemIxLineStart)	(__in LONG MapIndex, __in PDOUBLE DistList);

	// 직선 보간 절대좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, PosList: 이동할 위치의(절대좌표) 배열 주소, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxLineTo)	(__in LONG MapIndex, __in PDOUBLE PosList, __in LONG IsBlocking);

	// 직선 보간 절대좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, PosList: 이동할 위치의(절대좌표) 배열 주소]
	EXTERN LONG (__stdcall *cemIxLineToStart)	(__in LONG MapIndex, __in PDOUBLE PosList);
	
	EXTERN LONG (__stdcall *cemIxLineStart_Fx)	(__in LONG MapIndex, __in PDOUBLE DistList);
	EXTERN LONG (__stdcall *cemIxLineToStart_Fx)	(__in LONG MapIndex, __in PDOUBLE PosList);

	// 원호 보간 상대좌표(상대적 중심좌표와 각도) 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, XCentOffset: 현재 위치로부터 원의 중심까지 X축 상대좌표, YCentOffset: 현재 위치에서 원의 중심까지 Y축 상대좌표,
	// EndAngle: 원호 보간을 완료할 목표지점의 현재 위치에 대한 각도(Degree), IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxArcA)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// 원호 보간 상대좌표(상대적 중심좌표와 각도) 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, XCentOffset: 현재 위치로부터 원의 중심까지 X축 상대좌표, YCentOffset: 현재 위치로부터 원의 중심까지 Y축 상대좌표,
	// EndAngle: 원호 보간을 완료할 목표 지점의 현재 위치에 대한 각도(Degree)]
	EXTERN LONG (__stdcall *cemIxArcAStart)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE EndAngle);

	// 원호 보간 절대좌표(절대적 중심좌표와 각도) 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, XCent: 중심점의 X축 절대좌표, YCent: 중심점의 Y축 절대좌표,
	// EndAngle: 원호 보간을 완료할 목표 지점의 현재 위치에 대한 각도(Degree), IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxArcATo)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// 원호 보간 절대좌표(절대적 중심좌표와 각도) 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, XCent: 중심점의 X축 절대좌표, YCent: 중심점의 Y축 절대좌표, EndAngle: 원호 보간을 완료할 목표 지점의 현재 위치에 대한 각도(Degree)]
	EXTERN LONG (__stdcall *cemIxArcAToStart)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE EndAngle);

	// 원호보간 상대좌표(상대적 중심좌표와 종점좌표) 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, XCentOffset: 현재 위치에서 원 중심까지 X축상의 거리, YCentOffset: 현재 위치에서 원 중심까지 Y축상의 거리,
	// XEndPointDist: 원호보간 이동을 완료할 목표지점의 현재 위치로부터 X축상 거리, YEndPointDist: 원호 보간 이동을 완료할 목표지점의 현재위치로 부터의 Y축상 거리, Direction: 회전 방향, IsBlocking: 완료될때까지 메세지 블록 여부 ]
	EXTERN LONG (__stdcall *cemIxArcP)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction, __in LONG IsBlocking);

	// 원호보간 상대좌표(상대적 중심좌표와 종점좌표) 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, XCentOffset: 현 위치에서 원 중심까지 X축상의 거리, YCentOffset: 현 위치에서 원 중심까지 Y축상의 거리,
	// XEndPointDist: 원호 보간 이동을 완료할 목표지점의 현재위치로 부터의 X축상 거리, YEndPointDist: 원호 보간 이동을 완료할 목표지점의 현재위치로 부터의 Y축상 거리, Direction: 회전 방향]
	EXTERN LONG (__stdcall *cemIxArcPStart)	(__in LONG MapIndex, __in DOUBLE XCentOffset, __in DOUBLE YCentOffset, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction);

	// 원호보간 절대좌표(절대적 중심좌표와 종점좌표) 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, XCent: 중심점의 X축 절대좌표, YCent: 중심점의 Y축 절대좌표, XEndPointDist: 원호보간 이동을 완료할 목표지점의 X축 절대좌표,
	// YEndPointDist: 원호보간 이동을 완료할 목표지점의 Y축 절대좌표, Direction: 회전 방향, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxArcPTo)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction, __in LONG IsBlocking);

	// 원호보간 절대좌표(절대적 중심좌표와 종점좌표) 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, XCent: 중심점의 X축 절대좌표, YCent: 중심점의 Y축 절대좌표, XEndPointDist: 원호보간 이동을 완료할 목표지점의 X축 절대좌표,
	// YEndPointDist: 원호보간 이동을 완료할 목표지점의 Y축 절대좌표, Direction: 회전 방향]
	EXTERN LONG (__stdcall *cemIxArcPToStart)	(__in LONG MapIndex, __in DOUBLE XCent, __in DOUBLE YCent, __in DOUBLE XEndPointDist, __in DOUBLE YEndPointDist, __in LONG Direction);

	// 3점(Point)을 통한 원호보간 상대좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, P2X: 현재 위치에서 2번째 점까지 X축 상대좌표, P2Y: 현재 위치에서 2번째 점까지 Y축 상대좌표,
	// P3X: 2번째 점에서 3번째 점까지 X축 상대좌표, P3Y: 2번째 점에서 3번째 점까지 Y축 상대좌표, EndAngle: 각도값, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxArc3P)	(__in LONG MapIndex, __in DOUBLE P2X,__in  DOUBLE P2Y,__in  DOUBLE P3X, __in DOUBLE P3Y, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// 3점(Point)을 통한 원호보간 상대좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, P2X: 현재 위치에서 2번째 점까지 X축 상대좌표, P2Y: 현재 위치에서 2번째 점까지 Y축 상대좌표,
	// P3X: 2번째 점에서 3번째 점까지 X축 상대좌표, P3Y: 2번째 점에서 3번째 점까지 Y축 상대좌표, EndAngle: 각도값]
	EXTERN LONG (__stdcall *cemIxArc3PStart)	(__in LONG MapIndex, __in DOUBLE P2X, __in DOUBLE P2Y, __in DOUBLE P3X,__in  DOUBLE P3Y,__in  DOUBLE EndAngle);

	// 3점(Point)을 통한 원호보간 절대좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [MapIndex: 맵 번호, P2X: 2번째 점의 X축 절대좌표, P2Y: 2번째 점의 Y축 절대좌표,
	// P3X: 3번째 점의 X축 절대좌표, P3Y: 3번째 점의 Y축 절대좌표, EndAngle: 각도값, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxArc3PTo)	(__in LONG MapIndex, __in DOUBLE P2X,__in  DOUBLE P2Y,__in  DOUBLE P3X, __in DOUBLE P3Y, __in DOUBLE EndAngle, __in LONG IsBlocking);

	// 3점(Point)을 통한 원호보간 절대좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [MapIndex: 맵 번호, P2X: 2번째 점의 X축 절대좌표, P2Y: 2번째 점의 Y축 절대좌표, P3X: 3번째 점의 X축 절대좌표, P3Y: 3번째 점의 Y축 절대좌표, EndAngle: 각도값]
	EXTERN LONG (__stdcall *cemIxArc3PToStart)	(__in LONG MapIndex, __in DOUBLE P2X, __in DOUBLE P2Y, __in DOUBLE P3X, __in DOUBLE P3Y, __in DOUBLE EndAngle);

	// 보간 제어 구동 이송 감속 후 정지.
	// [MapIndex: 맵 번호]
	EXTERN LONG (__stdcall *cemIxStop)	(__in LONG MapIndex);

	// 보간 제어 구동 이송 비상정지.
	// [MapIndex: 맵 번호]
	EXTERN LONG (__stdcall *cemIxStopEmg)	(__in LONG MapIndex);

	// 보간 제어 구동 이송의 보간 완료 확인.
	// [MapIndex: 맵 번호, IsDone: 보간 제어 구동 이송의 보간 완료 여부]
	EXTERN LONG (__stdcall *cemIxIsDone)	(__in LONG MapIndex, __out PLONG IsDone);

	// 보간 제어 구동 이송의 보간 완료 시점까지 대기.
	// [MapIndex: 맵 번호, IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemIxWaitDone)	(__in LONG MapIndex, __in LONG IsBlocking);

	EXTERN LONG (__stdcall *cemIxMasterAxis_Set)	(__in LONG nAxis, __in LONG bSetValue);
	EXTERN LONG (__stdcall *cemIxMasterAxis_Get)	(__in LONG nAxis, __out PLONG bSetValue);
	EXTERN LONG (__stdcall *cemIxSmartDecel_Set)	(__in LONG nAxis, __in LONG bSetValue);
	EXTERN LONG (__stdcall *cemIxSmartDecel_Get)	(__in LONG nAxis, __out PLONG bSetValue);
	EXTERN LONG (__stdcall *cemIxSmartStop)	(__in LONG nIxMapIndex, __in DOUBLE decelTimeSec);

	// 헬리컬 보간 이송 속도 패턴 및 관련 환경 설정.
	// [HelId: 헬리컬 보간 이송 작업의 ID, Master: 마스터 속도 설정 , SpeedMode: 속도 모드, WorkSpeed: 작업 속도, Acc:가속도, Dec:감속도]
	// EXTERN LONG (__stdcall *cemIxxHelOnceSpeed_Set)	(__in LONG HelId, __in LONG Master, __in LONG SpeedMode, __in DOUBLE WorkSpeed, __in DOUBLE Acc, __in DOUBLE Dec);

	// 헬리컬 보간 이송 속도 패턴 및 관련 환경 설정 반환.
	// [HelId: 헬리컬 보간 이송 작업의 ID, Master: 마스터 속도 설정 반환, SpeedMode: 속도 모드 반환, WorkSpeed: 작업 속도 반환, Acc:가속도 반환, Dec:감속도 반환]
	// EXTERN LONG (__stdcall *cemIxxHelOnceSpeed_Get)	(__in LONG HelId, __out PLONG SpeedMaster, __out PLONG SpeedMode, __out PDOUBLE WorkSpeed, __out PDOUBLE Acc, __out PDOUBLE Dec);

	// 헬리컬 보간이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [HelId: 헬리컬 보간 이송 작업의 ID, NumAxes: 헬리컬 보간에 사용되는 축 수(3 or 4), AxisList: 대상 축 배열 주소,
	// CoordList: 좌표 배열 주소, ArcAngle: 원호 보간 이동 각도, DistU: U축 이송 거리 반환, IsBlocking: 완료될때까지 메세지 블록 여부]
	// EXTERN LONG (__stdcall *cemIxxHelOnce)	(__in LONG HelId, __in LONG NumAxes, __in PLONG AxisList, __in PDOUBLE CoordList, __in DOUBLE ArcAngle, __out PDOUBLE DistU, __in LONG IsBlocking);

	// 헬리컬 보간이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [HelId: 헬리컬 보간 이송 작업의 ID, NumAxes: 헬리컬 보간에 사용되는 축 수(3 or 4), AxisList: 대상 축 배열 주소,
	// CoordList: 좌표 배열 주소, ArcAngle: 원호 보간 이동 각도, DistU: U축 이송 거리 반환]
	// EXTERN LONG (__stdcall *cemIxxHelOnceStart)	(__in LONG HelId, __in Long NumAxes, __in PLONG AxisList, __in PDOUBLE CoordList, __in DOUBLE ArcAngle, __out PDOUBLE DistU);

	// Cubic Spline 보간 구동의 목표 좌표 생성.
	// [InArray: 스플라인 보간을 수행할 샘플 데이터 포인트 배열, NumInArray: 샘플 데이터의 수,
	// OutArray: 스플라인 보간을 수행하여 자동 생성된 자유곡선 데이터를 전달할 배열의 주소, NumOutArray: 스플라인 보간을 수행하여 자동 생성할 데이터 수]
	// EXTERN LONG (__stdcall *cemIxxSplineBuild)	(__in PDOUBLE InArray, __in LONG NumInArray, __out PDOUBLE OutArray, __in LONG NumOutArray);

	//****************************************************************************
	//*************** START OF MASTER/SLAVE CONTROL FUNCTION DECLARATIONS ********
	//****************************************************************************

	// 대상 모션 축에 대해서, Master/Slave 동기 구동의 Slave 축으로 등록.
	// [Axis: Slave 축으로 지정할 통합 축 번호, MaxSpeed: Slave축 구동 최대 속도, IsInverse: Slave축 과 Master축의 구동방향을 반대로 할것인지 여부]
	EXTERN LONG (__stdcall *cemMsRegisterSlave)	(__in LONG Axis, __in DOUBLE MaxSpeed, __in LONG IsInverse);

	// 대상 모션 축에 대해서, Master/Slave 동기 구동의 Slave 축 해제.
	// [Axis: Slave 축에서 해제할 통합 축 번호]
	EXTERN LONG (__stdcall *cemMsUnregisterSlave)	(__in LONG Axis);

	// 대상 모션 축에 대해서, Master/Slave 동기 구동의 Slave 축 등록 여부 환인.
	// [SlaveAxis: Slave 상태를 확인할 대상 통합 축 번호, SlaveState: Slave 축 상태 반환]
	EXTERN LONG (__stdcall *cemMsCheckSlaveState)	(__in LONG SlaveAxis, __out PLONG SlaveState);

	// 대상 모션 축에 대해서, Master/Slave 동기 구동의 Master 축의 통합 축 번호를 확인.
	// [SlaveAxis: Slave 통합 축 번호, MasterAxis: Master 통합 축 번호]
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

	// Manual Pulsar 입력 신호에 대한 환경설정.
	// [Channel: 통합 축 번호, InputMode: Pulsar 입력 신호의 입력 모드, IsInverse: Pulsar 입력 신호가 나타내는 방향과 모션의 방향 일치 여부]
	EXTERN LONG (__stdcall *cemPlsrInMode_Set)	(__in LONG Channel, __in  LONG InputMode,   __in  LONG IsInverse);

	// Manual Pulsar 입력 신호에 대한 환경설정 반환.
	// [Channel: 통합 축 번호, InputMode: Pulsar 입력 신호의 입력 모드 반환, Pulsar 입력 신호가 나타내는 방향과 모션의 방향 일치 여부 반환]
	EXTERN LONG (__stdcall *cemPlsrInMode_Get)	(__in LONG Channel, __out PLONG InputMode, __out  PLONG IsInverse);

	// Manual Pulsar의 PA/PB 입력펄스 대비, 출력펄스 수에 대한 비율 설정.
	// [Channel: 통합 축 번호, GainFactor: PMG 회로에 설정되는 사용자 정수(1~32), DivFactor: PDIV 회로에 설정되는 사용자 정수(1~2048)]
	EXTERN LONG (__stdcall *cemPlsrGain_Set)	(__in LONG Channel, __in  LONG GainFactor,  __in  LONG DivFactor);

	// Manual Pulsar의 PA/PB 입력펄스 대비, 출력펄스 수에 대한 비율 설정 반환.
	// [Channel: 통합 축 번호, GainFactor: PMG 회로에 설정되는 사용자 정수 반환, DivFactor: PDIV 회로에 설정되는 사용자 정수 반환]
	EXTERN LONG (__stdcall *cemPlsrGain_Get)	(__in LONG Channel, __out  PLONG GainFactor, __out PLONG DivFactor);
	//
	// Manual Pulsar 입력 신호에 의한 원점복귀 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Channel: 통합 축 번호, HomeType: Pulsar Input에 의한 원점 복귀 수행 모드]
	EXTERN LONG (__stdcall *cemPlsrHomeMoveStart)	(__in LONG Channel, __in  LONG  HomeType);

	// Manual Pulsar 입력 신호에 의한 상대좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [Channel: 통합 축 번호, Distance: 이동할 거리(상대좌표), IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemPlsrMove)	(__in LONG Channel, __in DOUBLE Distance, __in LONG IsBlocking);

	// Manual Pulsar 입력 신호에 의한 상대좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Channel: 통합 축 번호, Distance: 이동할 거리(상대좌표)]
	EXTERN LONG (__stdcall *cemPlsrMoveStart)	(__in LONG Channel, __in DOUBLE Distance);

	// Manual Pulsar 입력 신호에 의한 절대좌표 이송. 이 함수는 모션이 완료되기 전까지 반환되지 않습니다.
	// [Channel: 통합 축 번호, Position: 이동할 위치(절대좌표), IsBlocking: 완료될때까지 메세지 블록 여부]
	EXTERN LONG (__stdcall *cemPlsrMoveTo)         (__in LONG Channel, __in DOUBLE Position, __in LONG IsBlocking);

	// Manual Pulsar 입력 신호에 의한 절대좌표 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Channel: 통합 축 번호, Position: 이동할 위치(절대좌표)]
	EXTERN LONG (__stdcall *cemPlsrMoveToStart)    (__in LONG Channel, __in DOUBLE Position);

	// Manual Pulsar 입력 신호에 의한 연속속도 이송. 이 함수는 모션을 시작시킨 후에 바로 반환됩니다.
	// [Channel: 통합 축 번호]
	EXTERN LONG (__stdcall *cemPlsrVMoveStart)	(__in LONG Channel);

	//****************************************************************************
	//*************** START OF OVERRIDE FUNCTION DECLARATIONS ********************
	//****************************************************************************

	// 단축 이송 작업 중에 속도를 변경.
	// [Axis: 통합 축 번호]
	EXTERN LONG (__stdcall *cemOverrideSpeedSet)	(__in LONG Axis);

	// 다축 이송 작업 중에 대상 축들에 대하여 동시에 속도를 변경.
	// [NumAxes : 동시에 작업을 수행할 대상 축의 수, AxisList : 동시에 작업을 수행할 대상 축의 배열 주소]
	// EXTERN LONG (__stdcall *cemOverrideSpeedSetAll)	(__in LONG NumAxes, __in LONG AxisList);

	// 단축상대좌표 이송 중에, 상대좌표상의 목표 논리 거리값을 수정.
	// [Axis: 통합 축 번호, NewDistance: 새로운 목표 거리(상대좌표), IsHardApply: Override 불가 시점에서, Override 설정을 강제로 적용 여부, AppliedState: Override 적용 성공 여부 반환]
	EXTERN LONG (__stdcall *cemOverrideMove)	(__in LONG Axis, __in DOUBLE NewDistance, __in LONG IsHardApply, __out PLONG AppliedState);

	// 단축절대좌표 이송 중에, 절대좌표상의 목표 놀리 거리값을 수정.
	// [Axis: 통합 축 번호, NewPosition: 새로운 목표 거리(절대좌표), IsHardApply: Override 불가 시점에서, Override 설정을 강제로 적용 여부, AppliedState: Override 적용 성공 여부 반환]
	EXTERN LONG (__stdcall *cemOverrideMoveTo)	(__in LONG Axis, __in DOUBLE NewPosition, __in LONG IsHardApply, __out PLONG AppliedState);

	//****************************************************************************
	//*************** START OF MONITORING FUNCTION DECLARATIONS ******************
	//****************************************************************************

	// 대상 축의 지정한 하드웨어 카운터 값(펄스수) 설정. Target 값은 ceSDKDef.h 파일에 정의된 enum _TCnmCntr 값 리스트를 참고.
	// [Axis: 통합 축 번호, Target: 설정할 카운터 번호, Count: 대상 카운터 값(PPS)]
	EXTERN LONG (__stdcall *cemStCount_Set)	(__in LONG Axis, __in LONG Target, __in LONG Count);

	// 대상 축의 지정한 하드웨어 카운터 값(펄스수) 반환. Target 값은 ceSDKDef.h 파일에 정의된 enum _TCnmCntr 값 리스트를 참고.
	// [Axis: 통합 축 번호, Source: 값을 읽을 카운터 번호, Count: 대상 카운터 값(PPS) 반환]
	EXTERN LONG (__stdcall *cemStCount_Get)	(__in LONG Axis, __in LONG Source, __out PLONG Count);

	// 대상 축의 지정한 논리적 카운터 값(논리적 거리) 설정. Target 값은 ceSDKDef.h 파일에 정의된 enum _TCnmCntr 값 리스트를 참고.
	// [Axis: 통합 축 번호, Target: 설정할 카운터 번호, Position: 대상 카운터 값(논리적 거리)]
	EXTERN LONG (__stdcall *cemStPosition_Set)	(__in LONG Axis, __in LONG Target, __in DOUBLE Position);

	// 대상 축의 지정한 논리적 카운터 값(논리적 거리) 반환. Target 값은 ceSDKDef.h 파일에 정의된 enum _TCnmCntr 값 리스트를 참고.
	// [Axis: 통합 축 번호, Source: 값을 읽을 카운터 번호, Position: 대상 카운터 값(논리적 거리) 반환]
	EXTERN LONG (__stdcall *cemStPosition_Get)	(__in LONG Axis, __in LONG Source, __out PDOUBLE Position);

	// 대상 축의 논리적 속도 반환. Target 값은 ceSDKDef.h 파일에 정의된 enum _TCnmCntr 값 리스트를 참고.
	// [Axis: 통합 축 번호, Source: 속도 반환대상이 되는 카운터 번호, Speed: 지정한 Source의 속도(논리적 속도) 반환]
	EXTERN LONG (__stdcall *cemStSpeed_Get)		(__in LONG Axis, __in LONG Source, __out PDOUBLE Speed);

	// 대상 축의 모션 동작 상태 반환.
	// [Axis: 통합 축 번호, MotStates: 모션 상태 반환]
	EXTERN LONG (__stdcall *cemStReadMotionState)	(__in LONG Axis, __out PLONG MotStates);

	// 대상 축의 모션 관련 I/O 상태 반환.
	// [Axis: 통합 축 번호, MiotStates: Machine I/O 상태 반환]
	EXTERN LONG (__stdcall *cemStReadMioStatuses)	(__in LONG Axis, __out PLONG MioStates);

	// 모션 동작상태와 관련된 문자열 반환. cemStReadMotionState() 함수를 통해 얻어온 모션 상태.
	// [MstCode: 모션 동작 상태 값, Buffer: 모션 동작상태를 담은 문자열 버퍼의 주소 반환, Bufferlen: 문자열 버퍼의 길이]
	EXTERN LONG (__stdcall *cemStGetMstString)	(__in LONG MstCode, __out PCHAR Buffer, __in LONG BufferLen);

	// 수신된 I/O 메시지 개수 반환.
	// [IOMessageCount: I/O 메시지 수]
	EXTERN LONG (__stdcall *cemStReadIOMessageCount)	(__out PDWORD IOMessageCount);

	//****************************************************************************
	//*************** START OF LTC FUNCTION DECLARATIONS *************************
	//****************************************************************************

	// 해당축의 LTC 카운터 활성화 여부 확인 [Axis: 축(채널)번호, IsLatched: 카운터 활성화 여부 반환]
	EXTERN LONG (__stdcall *cemLtcIsLatched)	(__in LONG Axis, __out PLONG IsLatched);

	// 해당축의 LTC 카운터 값을 확인 [Axis: 축(채널)번호, Counter: 대상 카운터, LatchedPos: 지정한 축의 래치된 카운트 값 반환]
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

	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cemAdvGetNodeInformation)	(__in LONG nNode, __out PTNode pTargetNode);

	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cemAdvGetAllNodeInformation)	(__out PTNodeInformation pTargetNodes);

#if 0
	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cmnAdvDownloadDefaultConfigure)	();

	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cemAdvUploadConfigure)	(__in LONG FileType, __in const PCHAR szFileName);

	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cemAdvDownloadConfigure)	(__in LONG FileType, __in const PCHAR szFileName);

	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cemAdvActiveNodeCount_Get)	(__out PLONG NumNode);

	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cemAdvActiveNodeID_Get)	(__in  LONG ArraySize, __out PLONG lArray, __out PLONG NumNode);
#endif

	// 해당 축에 ERC 신호를 출력합니다.
	EXTERN LONG (__stdcall *cemAdvErcOut)				      (__in LONG Axis);

	// 해당 축에 ERC 신호를 출력을 리셋합니다.
	EXTERN LONG (__stdcall *cemAdvErcReset)				  (__in LONG Axis);

	// Undocument Function 입니다. 이 함수는 기술 지원이나 고객 지원용으로 사용됩니다.
	EXTERN LONG (__stdcall *cemAdvManualPacket)			  (__in LONG NodeID, __in LONG CommandNo, __in PDOUBLE SendBuffer, __in LONG NumSendData, __out PDOUBLE RecvBuffer, __out LONG NumRecvData, __in LONG SendFlag, __in LONG RecvFlag);

	//****************************************************************************
	//*************** START OF SYSTEM DIO CONFIGURATION FUNCTION DECLARATIONS ****
	//****************************************************************************
	// 시스템 디지털 입출력이 지원되는 제품에서 단일 채널에 대해서 입력을 확인합니다.
	EXTERN LONG (__stdcall *cemDiOne_Get)       (__in LONG Channel,     __out PLONG State);

	// 시스템 디지털 입출력이 지원되는 제품에서 다중 채널에 대해서 입력을 확인합니다.
	EXTERN LONG (__stdcall *cemDiMulti_Get)		(__in LONG IniChannel,	__in LONG NumChannels, __out PLONG InputState);

	// 시스템 디지털 입출력이 지원되는 제품에서 단일 채널에 대해서 출력을 발생합니다.
	EXTERN LONG (__stdcall *cemDoOne_Put)		(__in LONG Channel,		__in LONG OutState);

	// 시스템 디지털 입출력이 지원되는 제품에서 단일 채널에 대해서 출력을 확인합니다.
	EXTERN LONG (__stdcall *cemDoOne_Get)		(__in LONG Channel,		__in PLONG OutState);

	// 시스템 디지털 입출력이 지원되는 제품에서 다중 채널에 대해서 출력을 발생합니다.
	EXTERN LONG (__stdcall *cemDoMulti_Put)		(__in LONG IniChannel,	__in LONG NumChannels, __in LONG OutStates);

	// 시스템 디지털 입출력이 지원되는 제품에서 다중 채널에 대해서 출력을 확인합니다.
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

	// 대상 디지털 입출력 채널의 입출력 모드(Input/Output) 설정.
	// [Channel: 통합 채널 번호, InOutMode: 입출력 모드]
	EXTERN LONG (__stdcall *cedioMode_Set)	(__in LONG Channel, __in LONG InOutMode);

	// 대상 디지털 입출력 채널의 입출력 모드(Input/Output) 설정 상태 반환.
	// [Channel: 통합 채널 번호, InOutMode: 입출력 모드 반환]
	EXTERN LONG (__stdcall *cedioMode_Get)	(__in LONG Channel, __out PLONG InOutMode);

	// 대상 디지털 입출력 채널 범위의 다중 입출력 채널에 대해 동시에 입출력 모드(Input/Output) 설정.
	// [IniChan: 시작 통합 채널 번호, NumChan: 대상 채널 개수, InOutModeMask: 입출력 모드 마스크값]
	EXTERN LONG (__stdcall *cedioModeMulti_Set) (__in LONG IniChan, __in LONG NumChan, __in LONG InOutModeMask);

	// 대상 디지털 입출력 채널 범위의 다중 입출력 채널에 대해 동시에 입출력 모드(Input/Output) 설정 상태 반환.
	// [IniCahn: 시작 통합 채널 번호, NumChan: 대상 채널 개수, InOutModeMask: 입출력 모드 마스크값 반환]
	EXTERN LONG (__stdcall *cedioModeMulti_Get) (__in LONG IniChan, __in LONG NumChan, __out PLONG InOutModeMask);

	// 대상 디지털 입출력 채널의 입출력 논리(Logic) 설정.
	// [Channel: 통합 채널 번호, InputLogic: 입출력 로직]
	EXTERN LONG (__stdcall *cedioLogicOne_Set)	(__in LONG Channel, __in  LONG Logic);

	// 대상 디지털 입출력 채널의 입출력 논리(Logic) 설정 상태 반환.
	// [Channel: 통합 채널 번호, InputLogic: 입출력 로직 반환]
	EXTERN LONG (__stdcall *cedioLogicOne_Get)	(__in LONG Channel, __out PLONG Logic);

	// 대상 디지털 입출력 채널 범위의 다중 입출력 채널에 대해 동시에 입출력 논리(Logic) 설정.
	// [IniChan: 시작 통합 채널 번호, NumChan: 대상 채널 개수, LogicMask: 입출력 논리(Logic) 마스크]
	EXTERN LONG (__stdcall *cedioLogicMulti_Set)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  LogicMask);

	// 대상 디지털 입출력 채널 범위의 다중 입출력 채널에 대해 동시에 입출력 논리(Logic) 설정 상태 반환
	// 디지털 입출력 채널의 입출력논리 설정상태 반환 [IniChan: 시작 통합 채널 번호, NumChan: 채널 개수, LogicMask: 로직 마스크]
	EXTERN LONG (__stdcall *cedioLogicMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG LogicMask);

	// 대상 디지털 입출력 채널의 입력 또는 출력 상태 반환.
	// [Channel: 통합 채널 번호, OutState: 채널 상태 반환]
	EXTERN LONG (__stdcall *cedioOne_Get)	(__in LONG Channel, __out PLONG State);

	// 대상 디지털 입출력 채널의 입력 또는 출력 상태 설정.
	// [Channel: 통합 채널 번호, OutState: 채널 상태]
	EXTERN LONG (__stdcall *cedioOne_Put)	(__in LONG Channel, __in  LONG  State);

	// 대상 디지털 입출력 채널 범위의 다중 입출력 채널에 대해 동시에 입력 또는 출력 상태를 반환.
	// [IniChan: 시작 통합 채널 번호, NumChan: 대상 채널 개수, States: 채널 상태 반환]
	EXTERN LONG (__stdcall *cedioMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG States);

	// 대상 디지털 입출력 채널 범위의 다중 입출력 채널에 대해 동시에 입력 또는 출력 상태를 설정.
	// [ IniChan: 시작 통합 채널 번호, NumChan: 대상 채널 개수, States: 채널 상태]
	EXTERN LONG (__stdcall *cedioMulti_Put)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  States);

	// 대상 디지털 입출력 채널의 노이즈 필터 기능을 활성화 하여 디지털 입력 또는 출력 상태를 반환.
	// [Channel: 통합 채널 번호, CutoffTime_us: 디지털 입력 신호 유지 시간(us), State: 채널 상태 반환]
	EXTERN LONG (__stdcall *cedioOneF_Get)	(__in LONG Channel,    __in LONG CutoffTime_us, __out PLONG State);

	// 대상 디지털 입출력 채널 범위의
	// 다중 디지털 입출력 채널의 노이즈 필터 기능
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 수, CutoffTime_us: 디지털 입력 신호 유지 시간(us), InputStates: 해당 채널의 디지털 입력 상태]
	EXTERN LONG (__stdcall *cedioMultiF_Get)	(__in LONG IniChan, __in LONG NumChan, __in LONG CutoffTime_us, __out PLONG States);

	// 대상 디지털 입출력 채널의 단일 디지털 채널을 통해 단일 펄스 출력을 발생
	// [Channel: 통합 채널 번호, IsOnPulse: 설정된 디지털 출력 논리에 따라 초기 펄스 출력의 형태를 결정, Duration: 펄스 출력 시간 설정,
	// IsWaitPulseEnd: 펄스 출력 동작시에 함수를 바로 반환할 것인지, 아니면 펄스 출력 시간동안 함수 반환을 대기할 것인지 여부]
	EXTERN LONG (__stdcall *cedioPulseOne)	(__in LONG Channel, __in LONG IsOnPulse, __in LONG Duration,  __in LONG IsWaitPulseEnd);

	// 디지털 출력 입채널 범위의 지정한 다중 디지털 채널을 통해 단일 펄스 출력을 발생
	// [IniChan: 시작 채널, NumChan: 채널 수, OutStates: 디지털 출력 상태, Duration: 펄스 출력 시간 설정,
	// IsWaitPulseEnd: 펄스 출력 동작시에 함수를 바로 반환할 것인지, 아니면 펄스 출력 시간동안 함수 반환을 대기할 것인지 여부]
	EXTERN LONG (__stdcall *cedioPulseMulti)	(__in LONG IniChan, __in LONG NumChan,   __in LONG OutStates, __in LONG Duration, __in LONG IsWaitPulseEnd);

#ifdef __DI_DO_SUPPORT__
	//****************************************************************************
	//*************** START OF DI CONTROL FUNCTION DECLARATIONS ******************
	//****************************************************************************

	// 대상 디지털 입력 채널의 입력논리 설정
	// [Channel: 통합 채널 번호, InputLogic: 입력 로직]
	EXTERN LONG (__stdcall *cediLogicOne_Set)	(__in LONG Channel, __in  LONG  InputLogic);

	// 대상 디지털 입력 채널의 입력논리 설정상태 반환
	// [Channel: 통합 채널 번호, InputLogic: 입력 로직]
	EXTERN LONG (__stdcall *cediLogicOne_Get)	(__in LONG Channel, __out PLONG InputLogic);

	// 디지털 입력 채널의 입력논리 설정
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 개수, LogicMask: 로직 마스크]
	EXTERN LONG (__stdcall *cediLogicMulti_Set)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  LogicMask);

	// 디지털 입력 채널의 입력논리 설정상태 반환
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 개수, LogicMask: 로직 마스크]
	EXTERN LONG (__stdcall *cediLogicMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG LogicMask);

	// 대상 디지털 입력채널의 단일 디지털 입력 채널의 상태를 반환
	// [Channel: 통합 채널 번호, InputState: 디지털 입력 상태]
	EXTERN LONG (__stdcall *cediOne_Get)	(__in LONG Channel, __out PLONG InputState);

	// 대상 디지털 입력 채널 범위의 다중 디지털 입력 채널의 상태를 반환
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 개수, InputStates: 디지털 입력 상태]
	EXTERN LONG (__stdcall *cediMulti_Get)	(__in LONG IniChan, __in  LONG NumChan, __out PLONG InputStates);

	// 대상 디지털 입력 채널의 단일 채널을 대상으로 노이즈 필터 기능을 활성화 하여 디지털 입력 상태를 반환
	// [Channel: 통합 채널 번호, CutoffTime_us: 디지털 입력 신호 유지 시간(us), InputState: 해당 채널의 디지털 입력 상태]
	EXTERN LONG (__stdcall *cediOneF_Get)	(__in LONG Channel, __in LONG CutoffTime_us, __out PLONG InputState);

	// 다중 디지털 입력 채널의 노이즈 필터 기능
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 수, CutoffTime_us: 디지털 입력 신호 유지 시간(us), InputStates: 해당 채널의 디지털 입력 상태]
	EXTERN LONG (__stdcall *cediMultiF_Get)	(__in LONG IniChan, __in LONG NumChan, __in LONG CutoffTime_us, __out PLONG InputStates);

	//****************************************************************************
	//*************** START OF DO CONTROL FUNCTION DECLARATIONS ******************
	//****************************************************************************

	// 대상 디지털 출력 채널의 출력논리 설정
	// [Channel: 통합 채널 번호, OutputLogic: 출력 로직]
	EXTERN LONG (__stdcall *cedoLogicOne_Set)	(__in LONG Channel, __in  LONG  OutputLogic);

	// 대상 디지털 출력 채널의 출력논리 설정 상태의 반환
	// [Channel: 통합 채널 번호, OutputLogic:출력 로직]
	EXTERN LONG (__stdcall *cedoLogicOne_Get)	(__in LONG Channel, __out PLONG OutputLogic);

	// 디지털 출력 채널 범위의 다중 디지털 출력 채널을 통해 동시에 디지털 출력을 발생
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 개수, LogicMask: 로직 마스크]
	EXTERN LONG (__stdcall *cedoLogicMulti_Set)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  LogicMask);

	// 디지털 출력 채널 범위의 다중 디지털 출력 채널의 상태를 확인
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 개수, LogicMask: 로직 마스크]
	EXTERN LONG (__stdcall *cedoLogicMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG LogicMask);

	// 대상 디지털 출력 채널의 단일 디지털 채널을 통해 디지털 출력을 발생
	// [Channel: 통합 채널 번호, OutState: 출력 상태]
	EXTERN LONG (__stdcall *cedoOne_Put)	(__in LONG Channel, __in  LONG  OutState);

	// 대상 디지털 출력 채널의 단일 디지털 채널을 통해 디지털 출력 상태를 반환
	// [Channel: 통합 채널 번호, OutState: 출력 상태 ]
	EXTERN LONG (__stdcall *cedoOne_Get)	(__in LONG Channel, __out PLONG OutState);

	// 디지털 출력 채널 범위의 다중 디지털 출력 채널을 통해 동시에 디지털 출력을 발생
	// [ IniChan: 시작 통합 채널 번호, NumChan: 채널 개수, OutStates: 디지털 출력 상태]
	EXTERN LONG (__stdcall *cedoMulti_Put)	(__in LONG IniChan, __in LONG NumChan, __in  LONG  OutStates);

	// 디지털 출력 채널 범위의 다중 디지털 출력 채널을 통해 동시에 디지털 출력 상태를 확인
	// [IniChannel: 시작 통합 채널 번호, NumChan: 채널 개수, OutStates: 디지털 출력 상태]
	EXTERN LONG (__stdcall *cedoMulti_Get)	(__in LONG IniChan, __in LONG NumChan, __out PLONG OutStates);

	// 대상 디지털 출력 채널의 단일 디지털 채널을 통해 단일 펄스 출력을 발생
	// [Channel: 통합 채널 번호, IsOnPulse: 설정된 디지털 출력 논리에 따라 초기 펄스 출력의 형태를 결정,
	// IsWaitPulseEnd: 펄스 출력 동작시에 함수를 바로 반환할 것인지, 아니면 펄스 출력 시간동안 함수 반환을 대기할 것인지 여부]
	EXTERN LONG (__stdcall *cedoPulseOne)	(__in LONG Channel, __in LONG IsOnPulse, __in LONG Duration,  __in LONG IsWaitPulseEnd);

	// 디지털 출력 채널 범위의 지정한 다중 디지털 채널을 통해 단일 펄스 출력을 발생
	// [IniChan: 시작 통합 채널 번호, NumChan: 채널 수, OutStates: 디지털 출력 상태, Duration: 펄스 출력 시간 설정,
	// IsWaitPulseEnd: 펄스 출력 동작시에 함수를 바로 반환할 것인지, 아니면 펄스 출력 시간동안 함수 반환을 대기할 것인지 여부]
	EXTERN LONG (__stdcall *cedoPulseMulti)	(__in LONG IniChan, __in LONG NumChan,   __in LONG OutStates, __in LONG Duration, __in LONG IsWaitPulseEnd);
#endif

	//****************************************************************************
	//*************** START OF COUNTER MODULE FUNCTION DECLARATIONS **************
	//****************************************************************************
	// 카운터는 모듈당 8채널을 갖고 있습니다. (모듈별로 로컬 Channel 0 ~ Channel 7)

	// 대상 카운터 채널의 Edge Mode 를 설정합니다.
	// [Channel: 카운터 채널번호, EdgeMode: Edge모드 0(falling edge) 1(rising edge) Default:falling edge]
	EXTERN LONG (__stdcall *cecEdgeOne_Set)       (__in LONG Channel, __in DWORD EdgeMode);

	// 대상 카운터 채널의 Edge Mode 설정값을 가져옵니다
	// [Channel: 카운터 채널번호, EdgeMode: Edge모드 반환값 0(falling edge) 1(rising edge)]
	EXTERN LONG (__stdcall *cecEdgeOne_Get)       (__in LONG Channel, __out PDWORD EdgeMode);

	// 대상 카운터 채널 범위에 포함된 채널들의 Edge Mode 를 멀티로 설정합니다.
	// [IniChannel:채널 Range 시작 채널 번호, NumChannels:채널 Range 크기, EdgeModeMask:시작 채널번호 부터 끝채널 번호까지 각 채널별 Edge Mode 를 해당 비트별 0/1 로 설정 0(falling edge) 1(rising edge)]
	EXTERN LONG (__stdcall *cecEdgeMulti_Set)     (__in LONG IniChannel, __in LONG NumChannels, __in DWORD EdgeModeMask);

	// 대상 카운터 채널 범위에 포함된 채널들의 Edge Mode 설정값을 멀티로 가져옵니다. 비트 마스크를 얻은 뒤 비트Shift 연산을 통해 채널별로 0 또는 1 상태 (Edge Mode) 를 얻을 수 있습니다.
	// [IniChannel:채널 Range 시작 채널 번호, NumChannels:채널 Range 크기, EdgeModeMask:시작 채널번호 부터 끝채널 번호까지 각 채널별 Edge Mode 를 해당 비트별 0/1 로 설정된 값 반환 0(falling edge) 1(rising edge)]
	EXTERN LONG (__stdcall *cecEdgeMulti_Get)     (__in LONG IniChannel, __in LONG NumChannels, __out PDWORD EdgeModeMask);

	// 대상 카운터 채널의 카운트 값을 Clear (0 으로 리셋) 시킵니다.
	// [Channel: 카운터 채널번호]
	EXTERN LONG (__stdcall *cecClearOne)         (__in LONG Channel);

	// 대상 카운터 채널 범위에 포함된 채널들의 카운트 값을 모두 Clear (0 으로 리셋) 시킵니다.
	// [IniChannel:채널 Range 시작 채널 번호, NumChannels:채널 Range 크기]
	EXTERN LONG (__stdcall *cecClearMulti)       (__in LONG IniChannel, __in LONG NumChannels);

	// 모든 카운터 채널의 카운트 값을 Clear (0 으로 리셋) 시킵니다.
	// [NodeID: 노드 ID - 노드IP(192.168.1.x) 의 4번째 자리값(x)]
	EXTERN LONG (__stdcall *cecClearAll)         (__in LONG NodeID);

	// 대상 카운터 채널의 카운트 값을 얻어 옵니다.
	// [Channel: 카운터 채널번호, Count: 카운트 값]
	EXTERN LONG (__stdcall *cec_Get)                (__in LONG Channel, __out PDWORD Count);

	// 대상 카운터 채널의 카운트를 가능하도록 설정합니다. Enable: true (1) or false (0)
	// [Channel: 카운터 채널번호, Enable: Count Enable 상태값 0: Diable 1: Enable]
	EXTERN LONG (__stdcall *cecEnableOne_Set)     (__in LONG Channel, __in DWORD Enable);

	// 대상 카운터 채널의 카운트가 가능한 상태인지 Counter Enable 상태를 얻어 옵니다.
	// [Channel: 카운터 채널번호, IsEnabled: Count Enable 상태값 0: Diable 1: Enable]
	EXTERN LONG (__stdcall *cecEnableOne_Get)     (__in LONG Channel, __out PDWORD IsEnabled);

	// 대상 카운터 채널 범위에 포함된 채널들의 카운트를 가능하도록 Counter Enable 상태를 모두 true(1) 로 설정합니다.
	// [IniChannel:채널 Range 시작 채널 번호, NumChannels:채널 Range 크기, EnableMask: 멀티채널에 대한 Counter Enable 상태마스크 값]
	EXTERN LONG (__stdcall *cecEnableMulti_Set)   (__in LONG IniChannel, __in LONG NumChannels, __in DWORD EnableMask);

	// 대상 카운터 채널 범위에 포함된 채널들의 카운트가 가능한 상태인지 Counter Enable 상태를 얻어옵니다. 멀티 채널에 대한 EnabledMask 를 얻은 뒤 비트Shift 연산을 통해 채널별로 Enable 상태를 얻을 수 있습니다.
	// [IniChannel:채널 Range 시작 채널 번호, NumChannels:채널 Range 크기, EnabledMask: 멀티채널에 대한 Counter Enable 상태마스크 값]
	EXTERN LONG (__stdcall *cecEnableMulti_Get)   (__in LONG IniChannel, __in LONG NumChannels, __out PDWORD EnabledMask);

	// 대상 카운터 채널의 Overflow (24비트:0~2^24-1 범위 초과) 상태를 얻어 옵니다. 1:overflow
	// [Channel: 카운터 채널번호, OverflowStatus: Count Overflow 상태값 0: Overflow 발생 안함 1: Overflow 발생 함]
	EXTERN LONG (__stdcall *cecOverflowFlagGetOne)   (__in LONG Channel, __out PDWORD OverflowStatus);

	// 대상 카운터 채널범위의 Overflow (24비트 범위 초과) 상태를 얻어 옵니다.
	// [IniChannel:채널 Range 시작 채널 번호, NumChannels:채널 Range 크기, OverflowStates: 멀티채널에 대한 Overflow 상태마스크 값]
	EXTERN LONG (__stdcall *cecOverflowFlagGetMulti)   (__in LONG IniChannel, __in LONG NumChannels, __out PDWORD OverflowStates);

	// 대상 카운터 채널에 해당하는 Overflow Flag 를 0 으로 Clear 시킵니다.
	// [Channel: 카운터 채널번호]
	EXTERN LONG (__stdcall *cecOverflowFlagClearOne)    (__in LONG Channel);

	// 대상 카운터 채널범위 에 해당하는 채널별 Overflow Flag 를 0 으로 Clear 시킵니다.
	// [IniChannel:채널 Range 시작 채널 번호, NumChannels:채널 Range 크기]
	EXTERN LONG (__stdcall *cecOverflowFlagClearMulti)  (__in LONG IniChannel, __in LONG NumChannels);

	// 모든 카운터 채널의 overflow flag 를 0 으로 Clear 시킵니다.
	// [NodeID: 노드 ID - 노드IP(192.168.1.x) 의 4번째 자리값(x)]
	EXTERN LONG (__stdcall *cecOverflowFlagClearAll)    (__in LONG NodeID);

	// 대상 카운터 채널별 필터 Cutoff 주파수 설정: FilterFreq: 0~2 까지 모드 가능.
	// [Channel: 카운터 채널번호, FilterFreq: 채널별 필터 Cutoff 주파수]
	//A	B	필터 주파수		Cutoff 주파수 (50duty)	Filter를 pass하기 위한 최소시간
	//0	0	10Mhz (default)	500Khz					1usec
	//0	1	312Khz			20Khz					25usec
	//1	0	39Khz			4Khz					125usec
	EXTERN LONG (__stdcall *cecFilterFreq_Set)           (__in LONG Channel, __in LONG FilterFreq);

	// 대상 카운터 채널별 필터 Cutoff 주파수 설정값 얻는 함수 => 이 함수는 옵션입니다. 추후 라이브러리에서 제외될 수 있습니다.
	// [Channel: 카운터 채널번호, FilterFreq: 채널별 필터 Cutoff 주파수]
	EXTERN LONG (__stdcall *cecFilterFreq_Get)           (__in LONG Channel, __out PLONG FilterFreq);

	//****************************************************************************
	//*************** START OF ANALOG INPUT FUNCTION DECLARATIONS ****************
	//****************************************************************************

	// 아날로그 입력에 대한 전압 범위를 지정된 모드를 통해 설정합니다.
	// [Channel: 아날로그 입력 채널 번호, RangeMode: 전압 범위 설정 모드]
	//RangeMode (0~3)
	//A	B	입력범위
	//0	0	+10V ~ -10V
	//0	1	+5V ~ -5V
	//1	0	+2.5V ~ -2.5V
	//1	1	0V ~ +10V (0~20mA)
	EXTERN LONG (__stdcall *ceaiVoltRangeMode_Set)		(__in LONG Channel, __in  LONG  RangeMode);

	// 아날로그 입력에 대해 설정된 전압 범위에 해당하는 모드를 반환합니다.
	// [Channel: 아날로그 입력 채널 번호, RangeMode: 전압 범위 설정 모드]
	EXTERN LONG (__stdcall *ceaiVoltRangeMode_Get)		(__in LONG Channel, __out PLONG RangeMode);

	// 아날로그 입력에 대해 설정된 입력 Range 를 Digit 값으로 반환합니다 => 이 함수는 추후에 사용하지 않을 수 있습니다.
	// [Channel: 아날로그 입력 채널 번호, DigitMin: 최소 입력 Digit 값, DigitMax: 최대 입력 Digit 값]
	EXTERN LONG (__stdcall *ceaiRangeDigit_Get)         (__in LONG Channel, __out PLONG DigitMin, __out PLONG DigitMax);

	// 해당 아날로그 입력 채널의 입력 Digit 값을 반환합니다.
	// [Channel: 아날로그 입력 채널 번호, Digit: 입력된 Digit 값]
	EXTERN LONG (__stdcall *ceaiDigit_Get)              (__in LONG Channel, __out PLONG Digit);

	// 해당 아날로그 입력 채널의 입력 전압 값을 반환합니다.
	// [Channel: 아날로그 입력 채널 번호, fVolt: 입력된 전압 값]
	EXTERN LONG (__stdcall *ceaiVolt_Get)               (__in LONG Channel, __out PDOUBLE fVolt);

	// 해당 아날로그 입력 채널의 입력 전류 값을 반환합니다.
	// [Channel: 아날로그 입력 채널 번호, fCurrent: 입력된 전류 값]
	EXTERN LONG (__stdcall *ceaiCurrent_Get)            (__in LONG Channel, __out PDOUBLE fCurrent);

	//****************************************************************************
	//*************** START OF ANALOG OUTPUT FUNCTION DECLARATIONS ***************
	//****************************************************************************

	// 해당 아날로그 출력 채널을 통해 Digit 값을 출력합니다.
	// [Channel: 아날로그 출력 채널 번호, Digit: 출력 Digit 값]
	EXTERN LONG (__stdcall *ceaoDigit_Out)              (__in LONG Channel, __in LONG Digit);

	// 해당 아날로그 출력 채널을 통해 전압 값을 출력합니다.
	// [Channel: 아날로그 출력 채널 번호, fVolt: 출력 전압 값]
	EXTERN LONG (__stdcall *ceaoVolt_Out)               (__in LONG Channel, __in DOUBLE fVolt);

	// 해당 아날로그 출력 채널을 통해 전류 값을 출력합니다.
	// [Channel: 아날로그 출력 채널 번호, fCurrent: 출력 전류 값]
	EXTERN LONG (__stdcall *ceaoCurrent_Out)            (__in LONG Channel, __in DOUBLE fCurrent);

	//****************************************************************************
	//*************** START OF UTILITY FUNCTION DECLARATIONS *********************
	//****************************************************************************

	// 최대 32바이트의 임의의 문자열을 노드의 영구 저장 장치에 기록합니다.
	// [NodeID : 대상 노드 번호]
	// [NumByte: 기록할 데이터 길이(바이트 단위)]
	// [szText : 기록할 문자열]
	EXTERN LONG (__stdcall *ceutlUserData_Set)		(__in LONG NodeID, __in  LONG NumByte,  __in  PCHAR szText);

	// 최대 32바이트의 임의의 문자열을 노드의 영구 저장 장치에서 읽어옵니다.
	// [NodeID : 대상 노드 번호]
	// [NumByte: 읽어온 데이터 길이(바이트 단위)]
	// [szText : 읽어온 문자열 반환]
	EXTERN LONG (__stdcall *ceutlUserData_Get)		(__in LONG NodeID, __out PLONG NumByte, __out PCHAR szText);

	// 대상 원격 노드에 사용자 정의 버전을 기록합니다.
	// [NodeID : 대상 노드 번호]
	// [Version: 기록할 버전]
	EXTERN LONG (__stdcall *ceutlUserVersion_Set)	(__in LONG NodeID, __in  LONG Version);

	// 대상 원격 노드의 사용자 정의 버전을 읽어옵니다.
	// [NodeID : 대상 노드 번호]
	// [Version: 기록된 버전 반환]
	EXTERN LONG (__stdcall *ceutlUserVersion_Get)	(__in LONG NodeID, __out PLONG pVersion);

	// 대상 원격 노드의 펌웨어 버전을 읽어옵니다.
	// [NodeID : 대상 노드 번호]
	// [Version: 기록된 펌웨어 버전 반환]
	EXTERN LONG (__stdcall *ceutlNodeVersion_Get)	(__in LONG NodeID, __out PLONG pVersion);

	// 본 라이브러리의 버젼을 가져옵니다. 상위 및 하위 4바이트의 주소에 각 2바이트씩 버전을 할당합니다. 버전의 자리수는 총 4자리입니다.
	// 라이브러리 버전을 얻는 방법은 다음과 같습니다.
	// [pVersionMS : 상위 비트 버전 정보 반환]
	// [pVersionLS : 하위 비트 버전 정보 반환]

	// printf("Dynamic Link Library Version = [%d].[%d].[%d].[%d]"
	//	_X(pVersionMS >> 16 & 0xFF)
	//	_X(pVersionMS >> 0 & 0xFF)
	//	_X(pVersionLS >> 16 & 0xFF)
	//	_X(pVersionLS >> 0 & 0xFF));
	EXTERN LONG (__stdcall *ceutlLibVersion_Get)		(__out PLONG pVersionMS, __out PLONG pVersionLS);

	// 단일 윈도우 메세지를 처리합니다.
	EXTERN LONG (__stdcall *ceutlPumpSingleMessage)     ();

	// 다중 윈도우 메세지를 처리합니다. 인자로 설정된 nTimeout 은 설정된 시간동안 윈도우 메세지를 처리하게 됩니다.
	// 만약 nTimeout을 CN_INFINITE 로 설정하게되면, 모든 윈도우 메세지를 처리한 후 반환됩니다.
	// nTimeout 의 단위는 ms 입니다
	// [nTimeout : 설정된 시간동안 윈도우 메세지를 처리합니다.]
	EXTERN LONG (__stdcall *ceutlPumpMultiMessage)      (__in LONG nTimeout);

	// 노드 명령을 동기화 하기 위한 동기 카운트를 반환
	// [NodeID : 대상 노드, pSyncCount : 대상 노드의 현재 카운트 반환]
	EXTERN LONG (__stdcall *ceutlSyncCount_Get)		(__in LONG NodeID, __out PLONG pSyncCount);

	// 노드 명령을 동기화 하기 위한 I/O 메세지 동기 카운트를 반환
	// [NodeID : 대상 노드, pSyncCount : 대상 노드의 현재 카운트 반환]
	EXTERN LONG (__stdcall *ceutlIOSyncCount_Get)		(__in LONG NodeID, __out PLONG pSyncCount);

	// 노드와 상위 응용프로그램의 명령 동기화에 대해 처리합니다. 
	// 실제 명령된 명령 계수와 주기적인 메세지의 동기화를 위해 대기합니다.
	// [NodeID : 대상 노드, IsBlocking : 동기를 위해 대기하는 동안 윈도우 메세지 Blocking 여부]
	EXTERN LONG (__stdcall *ceutlSyncWait)		   (__in LONG NodeID, __in LONG IsBlocking);

	// 노드에 주기적 메세지에 대한 타임 스탬프를 반환합니다.
	// [NodeID : 대상 노드, pTimeStamp : 대상 노드의 타임 스탬프]
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
