#pragma once
#ifndef _PUSICO_DRIVER
#define _PUSICO_DRIVER
#include "pch.h"
#include <iostream>
#include <string>
#include <PUSICANControlLib.h>
#include <pusico.h>
#include <synchapi.h>

#include "actuator_hal.h"

typedef void *HANDLE;
using namespace std;

class PusicoDriver : public ActuatorHAL
{
public:
	PusicoDriver(DWORD dwNodeID, DWORD dwHomeDir);
	~PusicoDriver();
	void GoHome(DWORD homeDir, DWORD lonRangeSpeed, DWORD shortRangeSpeed, DWORD pos, DWORD offset);
	PCANResult SetMaxSpeed(DWORD maxSpeed);
	PCANResult SetMicroStep(DWORD microStep);
	PCANResult GetMicroStep(DWORD *microStep);
	PCANResult SetDir(DWORD dir);
	PCANResult SetWorkMode(DWORD workMode);
	PCANResult SetGroupID(DWORD groupID);
	PCANResult SetPVTMode(DWORD pvtMode);
	PCANResult SetMaxPVTNum(DWORD point_num);
	PCANResult SetPVTPara(DWORD startIndex, DWORD endIndex);
	PCANResult WritePVT(DWORD pos, DWORD velocity, DWORD time);
	PCANResult StartPVTStep(DWORD groupID);
	PCANResult GetMotorPos(int* pos);
	PCANResult SetVelocityMode();
	PCANResult SetPosMode();
	PCANResult ClearExtStopFlag();
	PCANResult SetMotorPos(int pos);
	PCANResult SetMotorEnable(BOOL pos);
	PCANResult SetExtStopEnable(DWORD extStopEnable);

	PCANResult StartRelStep(int pos, BOOL nonBlock=FALSE);
	PCANResult StartAbsStep(int pos, BOOL nonBlock=FALSE);
	PCANResult GoPosition(const double degree, const double reduce_ratio, const int clockwise_dir, DWORD speed=6000);
private:
	PCANResult initActuator(DWORD microStep=32, DWORD maxSpeed=6400, DWORD workMode=WM_POS);
private:
	string actuatorName;
	DWORD g_dwNodeID;
	DWORD g_dwHomeDir;
	DWORD g_dwLongRangeSpeed;
	DWORD g_dwshortRangeSpeed;
	DWORD g_dwPos;
private:
	static PCANResult __stdcall slaveChangeCallback(DWORD dwNodeID, BOOL bOnline);
	static PCANResult __stdcall traceCallback(char* szTrace);
	static PCANResult __stdcall tpdoCallback(DWORD dwNodeID, DWORD dwTPDOChannel, BYTE* pTPDOData, DWORD dwLen);
	static HANDLE g_hSlaveOnline;
	static HANDLE g_hSlaveIdle;
	static DWORD actuatorOpenes;
};

#endif
