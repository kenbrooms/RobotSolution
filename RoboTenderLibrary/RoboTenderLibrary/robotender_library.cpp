// RoboTenderLibrary.cpp : 定義 DLL 應用程式的匯出函式。
//

#include "stdafx.h"
#include <iostream>
#include "robotender_library.h"
//#include "RoboTenderLibrary.h"

using namespace robotender;
using namespace log4cplus;

RoboTender::RoboTender()
{
	pConsoleAppender = new ConsoleAppender();
	pLogger = Logger::getInstance(_T("LoggerName"));
	pLogger.addAppender(pConsoleAppender);
	pLogger.setLogLevel(WARN_LOG_LEVEL);
}

std::string RoboTender::test()
{
	//LOG4CPLUS_WARN(pLogger, "We Can Do It!");
	return "output test from RoboTender Library";
}

void RoboTender::test2()
{
	std::cout << "output test2 from RoboTender Library";
}



