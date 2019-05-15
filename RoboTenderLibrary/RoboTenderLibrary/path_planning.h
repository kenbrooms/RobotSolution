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
		void insertPoint(PathPoint point, long idx);
		void removePoint(long idx);
		void plan(list<PathPoint> *viaPointList, list<PathPoint> *quantizePointList);
		void estimateAccPoints(list<PathPoint> *viaPointList, list<PathPoint> *accPointList);
		void quantizePoints(list<PathPoint> *accPointList, list<PathPoint> *quantizePointList, long quantizeStep);
	private:
		list<PathPoint> _point_list;
		log4cplus::SharedAppenderPtr _console_appender;
		log4cplus::Logger _logger;
	};

}
