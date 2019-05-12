// stdafx.h: 包含標準系統 Include 檔案的檔案，
// 或經常使用但經常變更的
// 專案專屬 include 檔案
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 從 Windows 標頭排除不常使用的項目
// Windows 標頭檔
#include <windows.h>

#ifdef ROBOTENDERLIBRARY_EXPORTS
#define ROBOTENDERLIBRARY_API  __declspec(dllexport)   // export DLL information
#else
#define ROBOTENDERLIBRARY_API  __declspec(dllimport)   // import DLL information
#endif

// 在此參考您的程式所需的其他標頭

#include <list>
#include <sstream>
#include <iomanip>

#include <math.h>
#include <iostream>
#include <Tchar.h>

#include <boost/algorithm/string.hpp>

#include <log4cplus\consoleappender.h>
#include <log4cplus\loggingmacros.h>
#include <log4cplus\fileappender.h>

#include <rl/math/Transform.h>
#include <rl/math/Unit.h>

// Headers of RoboTender Library
#include "math_common.h"
#include "dh_table.h"
#include "joint.h"
#include "path_point.h"
#include "algebra_data.h"
#include "path_planning.h"

#define GLOBAL_LOG_LEVEL WARN_LOG_LEVEL