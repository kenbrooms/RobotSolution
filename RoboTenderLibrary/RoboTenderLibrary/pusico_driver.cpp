#include "pch.h"
#include <iostream>
#include <windows.h>
#include "pusico_driver.h"

DWORD PusicoDriver::actuatorOpenes = 0;
HANDLE PusicoDriver::g_hSlaveOnline = NULL;
HANDLE PusicoDriver::g_hSlaveIdle = NULL;


PusicoDriver::PusicoDriver(DWORD dwNodeID, DWORD dwHomeDir)
{
	PCANResult result = PCAN_SUCCESS;
	BOOL bOnline = 0;

	this->g_dwNodeID = dwNodeID;
	this->g_dwHomeDir = dwHomeDir;

	if (actuatorOpenes == 0) {
		PusicoDriver::g_hSlaveOnline = CreateEvent(NULL, FALSE, FALSE, NULL);
		PusicoDriver::g_hSlaveIdle = CreateEvent(NULL, FALSE, FALSE, NULL);
		result = PCAN_Init(CX_CANALYST_II, PMC007C6SE, TRACE_LEVEL1);
		if (PCAN_SUCCESS != result)
		{
			std::cout << "PCAN_Init fail!" << std::endl;
			throw std::runtime_error("PCAN_Init fail!");
		}
		PCAN_SetEventCallback(PusicoDriver::slaveChangeCallback, PusicoDriver::traceCallback, PusicoDriver::tpdoCallback);
		
		result = PCAN_OpenPort(BR_125KBPS);//打开适配器端口
		if (PCAN_SUCCESS != result)  //打开适配器端口
		{
			printf("PCAN_OpenPort fail!\n");
			throw std::runtime_error("PCAN_OpenPort fail!");
		}
		else {
			printf("PCAN_OpenPort success!\n");
		}
		Sleep(3000);
		WaitForSingleObject(PusicoDriver::g_hSlaveOnline, INFINITE); //等待从站上线
		PCAN_IsSlaveOnline(this->g_dwNodeID, &bOnline);
		cout << "Online status: " << bOnline << endl;
	}
	actuatorOpenes++;

	this->initActuator();
}


PCANResult PusicoDriver::initActuator(DWORD microStep, DWORD maxSpeed, DWORD workMode)
{
	PCANResult result = PCAN_SUCCESS;
	
	result = PCAN_SetMaxSpeed(this->g_dwNodeID, maxSpeed);
	if (result != PCAN_SUCCESS)
	{
		cout << "SetMaxSpeed: " << maxSpeed << " Result: " << result << endl;
		return result;
	}

	result = PCAN_SetMicroStep(this->g_dwNodeID, microStep);
	if (result != PCAN_SUCCESS)
	{
		cout << "SetMicroStep: " << microStep << " Result: " << result << endl;
		return result;
	}
	
	result = PCAN_SetAccel(this->g_dwNodeID, 8);
	if (result != PCAN_SUCCESS)
	{
		cout << "SetAccel: " << 8 << " Result: " << result << endl;
		return result;
	}
	
	result = PCAN_SetDecel(this->g_dwNodeID, 8);
	if (result != PCAN_SUCCESS)
	{
		cout << "SetDecel: " << 8 << " Result: " << result << endl;
		return result;
	}
	
	result = PCAN_SetWorkMode(this->g_dwNodeID, workMode);
	if (result != PCAN_SUCCESS)
	{
		cout << "SetWorkMode: " << workMode << " Result: " << result << endl;
		return result;
	}
	
	result = PCAN_SetExtStopEnable(this->g_dwNodeID, 2);
	if (result != PCAN_SUCCESS)
	{
		cout << "SetExtStopEnable: " << "2" << " Result: " << result << endl;
		return result;
	}
	
	result = PCAN_SetExtStopTrigger(this->g_dwNodeID, 0);
	if (result != PCAN_SUCCESS)
	{
		cout << "SetExtStopTrigger: " << "0" << " Result: " << result << endl;
		return result;
	}
	
	return PCAN_SUCCESS;
}

PusicoDriver::~PusicoDriver()
{
	PCANResult result = PCAN_SUCCESS;
	actuatorOpenes--;
	if (actuatorOpenes == 0)
	{
		result = PCAN_ClosePort();//Close Port	
		std::cout << "CloseUSB: " << std::endl;
	}
}


void PusicoDriver::GoHome(DWORD homeDir, DWORD longRangeSpeed, DWORD shortRangeSpeed, DWORD pos, DWORD offset)
{
	int stage = 0;
	DWORD pControlStatus=0;
	PCANResult result = PCAN_SUCCESS;
	cout << "Starting Go Gome" << endl;
	while (stage <= 3)
	{
		result = PCAN_GetControlStatus(this->g_dwNodeID, &pControlStatus);
		//cout << "Get Control Status: " << result << endl;
		if ((pControlStatus & 0x0002) != 0)
		{
			stage++;
			result = PCAN_ClearExtStopFlag(this->g_dwNodeID, 1);
			//pControlStatus = 6;
			//result = PCAN_GetControlStatus(this->g_dwNodeID, &pControlStatus);
			pControlStatus = 0;

		}
		else if (pControlStatus == 0)
		{
			switch (stage) 
			{
				case 0:
					//result = PCAN_SetWorkMode(this->g_dwNodeID, WM_VELOCITY);
					result = PCAN_SetMaxSpeed(this->g_dwNodeID, longRangeSpeed);
					//cout << "SeMaxSpeed: " << longRangeSpeed << " Result: " << result << endl;
					
					result = PCAN_SetWorkMode(g_dwNodeID, WM_VELOCITY);//设置工作模式为速度模式
					//cout << "SetWorkMode: " << "WM_VELOCITY" << " Result: " << result << endl;
					
					result = PCAN_SetDir(this->g_dwNodeID, homeDir); // 0: は锣 1:タ锣
					//result = PCAN_SetDir(this->g_dwNodeID, MOTOR_FORWARD); // 0: は锣 1:タ锣
					//cout << "SetDir: " << MOTOR_REVERSE << " Result: " << result << endl;
					ResetEvent(PusicoDriver::g_hSlaveIdle);
					result = PCAN_StartRelStep(this->g_dwNodeID, longRangeSpeed);
					cout << "Go Home and Speed " << longRangeSpeed << " Result: " << result << endl;
					WaitForSingleObject(PusicoDriver::g_hSlaveIdle, INFINITE); //等待从站上线
					cout << "Stage << " << stage << " was finished" << endl;
					//Sleep(500);
					break;
				case 1:
					result = PCAN_SetWorkMode(this->g_dwNodeID, WM_POS);
					//cout << "SetWorkMode: " << "WM_VELOCITY" << " Result: " << result << endl;
					
					result = PCAN_SetMaxSpeed(this->g_dwNodeID, shortRangeSpeed);
					//cout << "SeMaxSpeed: " << longRangeSpeed << " Result: " << result << endl;
					if (homeDir == MOTOR_REVERSE)
					{
						result = PCAN_SetDir(this->g_dwNodeID, MOTOR_FORWARD); // 0: は锣 1:タ锣
						//cout << "SetDir: " << MOTOR_FORWARD << " Result: " << result << endl;
					}
					else 
					{
						result = PCAN_SetDir(this->g_dwNodeID, MOTOR_REVERSE); // 0: は锣 1:タ锣
						//cout << "SetDir: " << MOTOR_REVERSE << " Result: " << result << endl;
					}
					
					ResetEvent(PusicoDriver::g_hSlaveIdle);
					result = PCAN_StartRelStep(this->g_dwNodeID, pos*2);
					cout << "Leave Home and Speed 400" << " Result: " << result << endl;
					WaitForSingleObject(PusicoDriver::g_hSlaveIdle, INFINITE); //等待从站上线
					cout << "Stage << " << stage << " was finished" << endl;
					stage++;
					break;
				case 2:
					result = PCAN_SetMaxSpeed(this->g_dwNodeID, shortRangeSpeed);
					cout << "SeMaxSpeed: " << shortRangeSpeed << " Result: " << result << endl;
					
					result = PCAN_SetWorkMode(g_dwNodeID, WM_VELOCITY);//设置工作模式为速度模式
					cout << "SetWorkMode: " << "WM_VELOCITY" << " Result: " << result << endl;
					
					result = PCAN_SetDir(this->g_dwNodeID, homeDir); // 0: は锣 1:タ锣
					cout << "SetDir: " << homeDir << " Result: " << result << endl;
					
					ResetEvent(PusicoDriver::g_hSlaveIdle);
					result = PCAN_StartRelStep(this->g_dwNodeID, shortRangeSpeed);
					cout << "Go Home and Speed 400 Result: " << result << endl;
					WaitForSingleObject(PusicoDriver::g_hSlaveIdle, INFINITE); //等待从站上线
					cout << "Stage << " << stage << " was finished" << endl;
					Sleep(1000);
					result = PCAN_SetMotorPos(g_dwNodeID, offset);
					break;
				case 3:
					result = PCAN_SetWorkMode(this->g_dwNodeID, WM_POS);
					//cout << "SetWorkMode: " << "WM_POS" << " Result: " << result << endl;
					result = PCAN_SetMaxSpeed(this->g_dwNodeID, shortRangeSpeed);
					//cout << "SeMaxSpeed: " << shortRangeSpeed << " Result: " << result << endl;
					if (homeDir == MOTOR_REVERSE)
					{
						result = PCAN_SetDir(this->g_dwNodeID, MOTOR_FORWARD); // 0: は锣 1:タ锣
						//cout << "SetDir: " << MOTOR_FORWARD << " Result: " << result << endl;
					}
					else 
					{
						result = PCAN_SetDir(this->g_dwNodeID, MOTOR_REVERSE); // 0: は锣 1:タ锣
						//cout << "SetDir: " << MOTOR_REVERSE << " Result: " << result << endl;
					}
					
					ResetEvent(PusicoDriver::g_hSlaveIdle);
					result = PCAN_StartRelStep(this->g_dwNodeID, pos);
					cout << "Go Home and Speed 400 Result: " << result << endl;
					WaitForSingleObject(PusicoDriver::g_hSlaveIdle, INFINITE); //等待从站上线
					cout << "Stage << " << stage << " was finished" << endl;
					
					//result = PCAN_SetMotorPos(g_dwNodeID, 0);
					stage++;
					break;
			}
		}
	}
}


PCANResult __stdcall PusicoDriver::slaveChangeCallback(DWORD dwNodeID, BOOL bOnline)
{
	if (TRUE == bOnline) {
		SetEvent(PusicoDriver::g_hSlaveOnline);
	}
	return PCAN_SUCCESS;
}


PCANResult __stdcall PusicoDriver::traceCallback(char* szTrace)
{
	//std::cout << "TraceMsg: " << szTrace << std::endl;
	return PCAN_SUCCESS;
}


PCANResult __stdcall PusicoDriver::tpdoCallback(DWORD dwNodeID, DWORD dwTPDOChannel, BYTE* pTPDOData, DWORD dwLen)
{
	if (TPDO_CH1 == dwTPDOChannel) {
		if ((pTPDOData[1] & (1 << CS_BUSY)) == 0) {
			std::cout << dwNodeID << " enter idle." << std::endl;
			SetEvent(PusicoDriver::g_hSlaveIdle);
		}
		else {
			std::cout << dwNodeID << " enter busy." << std::endl;
		}
	}
	return PCAN_SUCCESS;
}

PCANResult PusicoDriver::SetMaxSpeed(DWORD maxSpeed)
{
	return PCAN_SetMaxSpeed(this->g_dwNodeID, maxSpeed);
}


PCANResult PusicoDriver::SetMicroStep(DWORD microStep)
{
	return PCAN_SetMicroStep(this->g_dwNodeID, microStep);
}

PCANResult PusicoDriver::GetMicroStep(DWORD *microStep)
{
	return PCAN_GetMicroStep(this->g_dwNodeID, microStep);
}


PCANResult PusicoDriver::SetDir(DWORD dir)
{
	return PCAN_SetDir(this->g_dwNodeID, dir);
}


PCANResult PusicoDriver::SetWorkMode(DWORD workMode)
{
	return PCAN_SetWorkMode(this->g_dwNodeID, workMode);
}

PCANResult PusicoDriver::SetVelocityMode()
{
	return PCAN_SetWorkMode(this->g_dwNodeID, WM_VELOCITY);
}

PCANResult PusicoDriver::SetPosMode()
{
	return PCAN_SetWorkMode(this->g_dwNodeID, WM_POS);
}

PCANResult PusicoDriver::SetGroupID(DWORD groupID)
{
	return PCAN_SetGroupID(this->g_dwNodeID, groupID);
}


PCANResult PusicoDriver::SetPVTMode(DWORD pvtMode)
{
	return PCAN_SetPVTMode(this->g_dwNodeID, pvtMode);
}


PCANResult PusicoDriver::SetMaxPVTNum(DWORD point_num)
{
	return PCAN_SetMaxPVTNum(this->g_dwNodeID, point_num);
}
	

PCANResult PusicoDriver::SetPVTPara(DWORD startIndex, DWORD endIndex)
{
	return PCAN_SetPVT1Para(this->g_dwNodeID, startIndex, endIndex);
}


PCANResult PusicoDriver::StartPVTStep(DWORD groupID)
{
	return PCAN_StartPVTStep(groupID);
}


PCANResult PusicoDriver::WritePVT(DWORD pos, DWORD velocity, DWORD time)
{
	return PCAN_WritePVT(this->g_dwNodeID, pos, velocity, time);
}
	
PCANResult PusicoDriver::GetMotorPos(int* pos)
{
	return PCAN_GetMotorPos(this->g_dwNodeID, pos);
}
	
PCANResult PusicoDriver::ClearExtStopFlag()
{
	return PCAN_ClearExtStopFlag(this->g_dwNodeID, 1);
}


PCANResult PusicoDriver::SetMotorPos(int pos)
{
	return PCAN_SetMotorPos(this->g_dwNodeID, pos);
}

PCANResult PusicoDriver::SetMotorEnable(BOOL enable)
{
	return PCAN_SetMotorEnable(this->g_dwNodeID, enable);
}

PCANResult PusicoDriver::StartRelStep(int pos, BOOL nonBlock)
{
	PCANResult result;
	if (nonBlock == TRUE)
	{
		return PCAN_StartRelStep(this->g_dwNodeID, pos);
	}
	else {
		ResetEvent(PusicoDriver::g_hSlaveIdle);
		result = PCAN_StartRelStep(this->g_dwNodeID, pos);
		WaitForSingleObject(PusicoDriver::g_hSlaveIdle, INFINITE);
		return result;
	}
}


PCANResult PusicoDriver::StartAbsStep(int pos, BOOL nonBlock)
{
	PCANResult result;
	if (nonBlock == TRUE)
	{
		return PCAN_StartAbsStep(this->g_dwNodeID, pos);
	}
	else {
		ResetEvent(PusicoDriver::g_hSlaveIdle);
		result = PCAN_StartAbsStep(this->g_dwNodeID, pos);
		WaitForSingleObject(PusicoDriver::g_hSlaveIdle, INFINITE);
		return result;
	}
}

PCANResult PusicoDriver::SetExtStopEnable(DWORD extStopEnable)
{
	return PCAN_SetExtStopEnable(this->g_dwNodeID, extStopEnable);
}

PCANResult PusicoDriver::GoPosition(const double degree, const double reduce_ratio, const int clockwise_dir, DWORD speed)
{
	DWORD microStep = 0;
	PCANResult result;
	
	this->SetMaxSpeed(speed);
	
	double totalStep = ((degree/360.0)*4000.0) * reduce_ratio;
	if (clockwise_dir)
		totalStep = -totalStep;
	cout << "TotalStep: " << totalStep << endl;
	return this->StartAbsStep(totalStep);
}
