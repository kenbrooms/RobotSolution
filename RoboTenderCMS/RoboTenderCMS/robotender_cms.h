#pragma once

// Controller Class

#include "stdafx.h"
#include "ui_RoboTenderCMS.h"

#include <QFileDialog>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <Qt3DCore/qentity.h>
#include <QtGui/QScreen>
#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/qphongmaterial.h>
#include <Qt3DExtras/qorbitcameracontroller.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/qphongmaterial.h>
#include <Qt3DExtras/qorbitcameracontroller.h>


#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qcameralens.h>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DRender/qbuffer.h>
#include <Qt3DRender/qattribute.h>
#include <Qt3DRender/qpickevent.h>
#include <Qt3DRender/qobjectpicker.h>

#include "robotender_library.h"
#include "path_planning.h"
#include "path_data_manipulation.h"
#include "robotender_cms_view.h"

using namespace log4cplus;

class RoboTenderCMS : public QMainWindow
{
	Q_OBJECT

public:
	RoboTenderCMS(QWidget *parent = Q_NULLPTR);
	virtual void resizeEvent(QResizeEvent *pQEvent);

private slots:
	void handleAddButton();
	void handleRemoveButton();
	void handleSimulationButton();
	void handleLoadButton();
	void handleSaveButton();
	void handleTopViewButton();

private:
	Ui::RoboTenderCMSClass ui;
	list<PathPoint> viaPointList;
	list<PathPoint> quantizePointList;
	RoboTenderCMS_View *pCMSView;
	PathPlanning *pPathPlanning;
private:
	SharedAppenderPtr pConsoleAppender;
	SharedAppenderPtr pFileRollingAppender;
	Logger pLogger;
	log4cplus::tstring pattern;
	bool initialized;
};
