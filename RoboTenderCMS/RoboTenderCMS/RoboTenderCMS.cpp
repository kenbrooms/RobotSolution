#include "stdafx.h"
#include <memory>
#include "RoboTenderCMS.h"
#include <QtCore/QDebug>

#include <boost/algorithm/string.hpp>
using namespace log4cplus;
using namespace std;

RoboTenderCMS::RoboTenderCMS(QWidget *parent)
	: initialized(false), QMainWindow(parent)
{
	this->ui.setupUi(this);
	QMainWindow::showMaximized();
	this->pCMSView = new RoboTenderCMS_View(&this->ui);
	this->pCMSView->Init3DView();
	//  Logger Setting
	pLogger = Logger::getInstance(_T("RoboTenderCMS_Logger"));
	pattern = LOG4CPLUS_TEXT("%D{%Y/%m/%d %H:%M:%S,%Q} - %p %m\n");
	
	pConsoleAppender = new ConsoleAppender();
	pConsoleAppender->setLayout(std::auto_ptr<Layout>(new PatternLayout(pattern)));
	
	pFileRollingAppender = new RollingFileAppender(_T(".\\test.log"));

	pLogger.addAppender(pConsoleAppender);
	pLogger.addAppender(pFileRollingAppender);
	//pLogger.setLogLevel(WARN_LOG_LEVEL);
	pLogger.setLogLevel(GLOBAL_LOG_LEVEL);
	
	// Robot Controller Setting
	//RoboTender rt;
	this->pPathPlanning = new PathPlanning();

	// Event Registed
	connect(this->ui.btnAddPoint, SIGNAL(released()), this, SLOT(handleAddButton()));
	connect(this->ui.btnRemovePoint, SIGNAL(released()), this, SLOT(handleRemoveButton()));
	connect(this->ui.btnSimulation, SIGNAL(released()), this, SLOT(handleSimulationButton()));
	connect(this->ui.btnLoadPoint, SIGNAL(released()), this, SLOT(handleLoadButton()));
	connect(this->ui.btnSavePoint, SIGNAL(released()), this, SLOT(handleSaveButton()));
	
	initialized = true;
	LOG4CPLUS_DEBUG(pLogger, "RoboTenderCMS had been initialized.");
}

void RoboTenderCMS::handleAddButton()
{
	this->pCMSView->AddItem();
	LOG4CPLUS_TRACE(pLogger, "Clicked Adding Button");
}

void RoboTenderCMS::handleRemoveButton()
{
	this->pCMSView->RemoveItem();
	LOG4CPLUS_TRACE(pLogger, "Clicked Removing Button");
}

void RoboTenderCMS::handleSimulationButton()
{
	list<PathPoint> accPointList;
	this->pCMSView->GetDataFromView(&this->pointList);
	//this->pPathPlanning->EstimateAccPoints(&this->pointList, &accPointList);
	this->pPathPlanning->Plan(&this->pointList);
	this->pCMSView->Update3DView(&this->pointList);
	LOG4CPLUS_TRACE(pLogger, "Clicked Simulation Button");

}

void RoboTenderCMS::handleLoadButton()
{
	PathDataManipulation pathData;
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C:\\Users\\kenbr\\data", "csv files(*.csv)");
	this->pointList = pathData.LoadFromCSV(filename.toStdString());
	this->pCMSView->UpdateTableView(&this->pointList);
	LOG4CPLUS_TRACE(pLogger, "Load CSV");
}

void RoboTenderCMS::handleSaveButton()
{
	PathDataManipulation pathData;
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "C:\\Users\\kenbr\\data", "csv files(*.csv)");	
	this->pCMSView->GetDataFromView(&this->pointList);
	pathData.SaveToCSV(filename.toStdString(), this->pointList);
}

void RoboTenderCMS::resizeEvent(QResizeEvent *pQEvent)
{
	if (initialized)
	{
		//LOG4CPLUS_WARN(pLogger, "Resize main window to full screen");
	}
}