#include "stdafx.h"
#pragma once
// Controller Class
#include "csv_worker.h"
#include "path_planning.h"

using namespace log4cplus;

class PathDataManipulation
{
public:
	PathDataManipulation();
	~PathDataManipulation();
public:
	list<PathPoint> LoadFromCSV(std::string filename);
	void SaveToCSV(std::string filename, list<PathPoint> pointList);
private:
	vector<string> split(string strtem, char a);

private:
	SharedAppenderPtr pConsoleAppender;
	SharedAppenderPtr pFileRollingAppender;
	Logger pLogger;
	log4cplus::tstring pattern;
private:
	list<PathPoint> pointList;
};
