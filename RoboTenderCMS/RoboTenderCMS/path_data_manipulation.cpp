#include <QDebug>
#include "path_data_manipulation.h"

PathDataManipulation::PathDataManipulation()
{
	pLogger = Logger::getInstance(_T("PathDataManipulationLogger"));
	pattern = LOG4CPLUS_TEXT("%D{%Y/%m/%d %H:%M:%S,%Q} - %p %m\n");
	
	pConsoleAppender = new ConsoleAppender();
	pConsoleAppender->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
	
	pFileRollingAppender = new RollingFileAppender(_T(".\\test.log"));

	pLogger.addAppender(pConsoleAppender);
	pLogger.addAppender(pFileRollingAppender);
	//pLogger.setLogLevel(WARN_LOG_LEVEL);
	pLogger.setLogLevel(GLOBAL_LOG_LEVEL);
}

PathDataManipulation::~PathDataManipulation()
{

}

list<PathPoint> PathDataManipulation::LoadFromCSV(std::string filename)
{
	CsvWorker csv(';');
	PathPoint pathPoint;
	std::vector<string> ret_field;
	std::string csv_str;
	double x, y, z;
	long time;

	csv.loadFromFile(filename);
	
	this->pointList.clear();
	for (auto rowIdx = 0; rowIdx < csv.getRowsCount(); rowIdx++)
	{
		csv_str.clear();
		for (auto colIdx = 0; colIdx < csv.getColumnsCount(); colIdx++)
		{
			csv_str = csv.getField(rowIdx, colIdx);
			if (colIdx == 0 || colIdx == 1)
			{
				ret_field = this->split(csv_str, ',');
				x = std::stod(ret_field.at(0));
				y = std::stod(ret_field.at(1));
				z = std::stod(ret_field.at(2));
				if (colIdx == 0)
				{
					pathPoint.SetPosition(x, y, z);
				}
				else {
					pathPoint.SetRotation(x, y, z);
				}
			}
			else if(colIdx == 2 || colIdx == 3){
				time = std::stol(csv_str);
				if (colIdx == 2)
				{
					pathPoint.SetDurationTime(time);
				}
				else if(colIdx == 3) {
					pathPoint.SetAccelearationTime(time);
				}
			}
			else {
				pathPoint.SetAttr((char)(*csv_str.c_str()));
			}
		}
		this->pointList.push_back(pathPoint);
	}
	
	//LOG4CPLUS_WARN(pLogger, this->pointList);
	return this->pointList;
}
	
void PathDataManipulation::SaveToCSV(std::string filename, list<PathPoint> pointList)
{
	CsvWorker csv(';');
	list<PathPoint>::iterator it;
	std::string position_field, rotation_field, dt_field, at_field, attr_field;
	double x, y, z;
	long time;
	char attr;

	std::string item_str;
	std::ostringstream streamObj;
	std::string str_x, str_y, str_z;

	streamObj << std::fixed;
	streamObj << std::setprecision(2);
	this->pointList = pointList;
	item_str.clear();
	for (it = this->pointList.begin(); it != this->pointList.end(); it++)
	{
		it->GetPosition(&x, &y, &z);
		streamObj << x;	
		str_x = streamObj.str();
		streamObj.str("");
		streamObj << y;
		str_y = streamObj.str();
		streamObj.str("");
		streamObj << z;
		str_z = streamObj.str();
		streamObj.str("");
		item_str = item_str + str_x + "," + str_y + "," + str_z + ";";
		
		it->GetRotation(&x, &y, &z);
		streamObj << x;	
		str_x = streamObj.str();
		streamObj.str("");
		streamObj << y;
		str_y = streamObj.str();
		streamObj.str("");
		streamObj << z;
		str_z = streamObj.str();
		streamObj.str("");
		item_str = item_str + str_x + "," + str_y + "," + str_z + ";";
		
		it->GetDurationTime(&time);
		item_str = item_str + std::to_string(time) + ";";
		
		it->GetAccelerationTime(&time);
		item_str = item_str + std::to_string(time) + ";";
		
		it->GetAttr(&attr);
		item_str = item_str + attr + ";\n";
	}
	
	qDebug() << item_str.c_str();
	FILE *fin;
	int ok = fopen_s(&fin, filename.c_str(), "wb");
	if (!ok) {
		int len = item_str.length();
		fwrite(item_str.c_str(), 1, len, fin);
		fclose(fin);
	}
	else {
		cout << "Can't open file \"" << filename.c_str() << '\"' << endl;
		throw;
	}
		
}

vector<string> PathDataManipulation::split(string strtem, char a)
{
	vector<string> strvec;

	string::size_type pos1, pos2;
	pos2 = strtem.find(a);
	pos1 = 0;
	while (string::npos != pos2)
	{
		strvec.push_back(strtem.substr(pos1, pos2 - pos1));

		pos1 = pos2 + 1;
		pos2 = strtem.find(a, pos1);
	}
	strvec.push_back(strtem.substr(pos1));
	return strvec;
}
