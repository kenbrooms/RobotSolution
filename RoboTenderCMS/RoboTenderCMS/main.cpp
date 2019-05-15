#include "robotender_cms.h"
#include <QtWidgets/QApplication>
#include <windows.h>	
#include <iostream>

#define DEBUG

int main(int argc, char *argv[])
{

#ifdef DEBUG
	//FreeConsole();
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
	freopen("CON", "r", stdin);
#endif
	
	QApplication a(argc, argv);
	// create a separate new console window
	
	RoboTenderCMS w;
	w.show();
	return a.exec();
}
