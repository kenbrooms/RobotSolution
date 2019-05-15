#pragma once
#include "stdafx.h"


using namespace log4cplus;

namespace robotender {
	class ROBOTENDERLIBRARY_API RoboTender {
	public:
		RoboTender();

	public:
		std::string test();
		void test2();
	private:
		log4cplus::SharedAppenderPtr pConsoleAppender;
		log4cplus::Logger pLogger;
	};
};