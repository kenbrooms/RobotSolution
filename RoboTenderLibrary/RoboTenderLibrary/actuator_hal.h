#pragma once
#ifndef _ACTUATOR_HAL
#define _ACTUATOR_HAL

#include "stdafx.h"

class ActuatorHAL
{
public:
	virtual void GoHome(DWORD homeDir, DWORD longRangeSpeed, DWORD shortRangeSpeed, DWORD pos, DWORD offset) = 0;
};

#endif
