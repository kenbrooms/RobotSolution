#pragma once
#include "stdafx.h"
#include <QtWidgets/QMainWindow>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/qphongmaterial.h>
#include <Qt3DExtras/qorbitcameracontroller.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/qphongmaterial.h>
#include <Qt3DExtras/qorbitcameracontroller.h>
#include <Qt3DExtras/qcylindermesh.h>

#include <Qt3DInput/QInputAspect>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qcamera.h>
#include <Qt3DRender/qcameralens.h>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DRender/qbuffer.h>
#include <Qt3DRender/qattribute.h>
#include <Qt3DRender/qpickevent.h>
#include <Qt3DRender/qobjectpicker.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>
#include "ui_RoboTenderCMS.h"

class RoboTenderCMS_View
{
	public:
		RoboTenderCMS_View(Ui::RoboTenderCMSClass* ui):ui(ui)
		{
				this->m_view = new Qt3DExtras::Qt3DWindow();
				this->m_view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
				
				
				this->m_container = QWidget::createWindowContainer(m_view);
				this->m_container->setMaximumWidth(160000);
				this->m_container->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
				this->pTableWidget = ui->tableWidget;
				//pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
				this->pTableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
				this->pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
				QHeaderView* header = pTableWidget->horizontalHeader();
				header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
				header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
				header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
				header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
				header->setSectionResizeMode(4, QHeaderView::Stretch);

				ui->horizontalLayout->addWidget(m_container, 1);
				ui->horizontalLayout->addWidget(pTableWidget, 2);
		};
		~RoboTenderCMS_View();
		void UpdateTableView(std::list<PathPoint> *pointList);
		void GetDataFromView(std::list<PathPoint> *pointList);
		void Init3DView();
		void Update3DView(std::list<PathPoint> *viaPointList, std::list<PathPoint> *quantizePointList);
		shared_ptr<Qt3DCore::QEntity> DrawLine(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity *_rootEntity);
		void DrawAxis();
		void RemoveItem();
		void AddItem();
		void GoToTopView();
		void UpdateRobotArm();
	private:
		Ui::RoboTenderCMSClass *ui;
		QMainWindow* parent;
		Qt3DExtras::Qt3DWindow *m_view;
		QWidget *m_container;
		QTableWidget* pTableWidget;
		Qt3DCore::QEntity *rootEntity;
		std::list<shared_ptr<Qt3DCore::QEntity>> entityList;
		std::list<shared_ptr<Qt3DCore::QEntity>> axisEntityList;
		std::list<shared_ptr<Qt3DCore::QEntity>> pathEntityList;
};
