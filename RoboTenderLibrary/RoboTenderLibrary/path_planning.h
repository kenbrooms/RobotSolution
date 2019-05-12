#pragma once
#include "stdafx.h"
#include "path_point.h"

using namespace std;
using namespace log4cplus;

namespace robotender {
	class ROBOTENDERLIBRARY_API PathPlanning {
	public:
		PathPlanning();
		~PathPlanning();
	public:
		void InsertPoint(PathPoint point, long idx);
		void RemovePoint(long idx);
		void Plan(list<PathPoint> *pointList);
		void EstimateAccPoints(list<PathPoint> *viaPointList, list<PathPoint> *accPointList);
		void QuantizePoints(list<PathPoint> *accPointList, list<PathPoint> *quantizePointList, long quantizeStep);
	private:
		list<PathPoint> pointList;
		log4cplus::SharedAppenderPtr pConsoleAppender;
		log4cplus::Logger pLogger;
	};

}
