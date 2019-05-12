#pragma once
#include "stdafx.h"
#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/qpickingsettings.h>
#include <Qt3DRender/qpickevent.h>

#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <Qt3DRender/qbuffer.h>
#include <Qt3DRender/qattribute.h>

#include <Qt3DExtras/qphongmaterial.h>
#include <Qt3DExtras/qorbitcameracontroller.h>

#include <Qt3DRender/qpickevent.h>
#include <Qt3DRender/qobjectpicker.h>

class SceneModifier : public QObject
{
	Q_OBJECT

public:
	explicit SceneModifier(Qt3DCore::QEntity *rootEntity, Qt3DRender::QCamera *cameraEntity);
	~SceneModifier();

public slots:
	void enableTorus(bool enabled);
	void enableCone(bool enabled);
	void enableCylinder(bool enabled);
	void enableCuboid(bool enabled);
	void enablePlane(bool enabled);
	void enableSphere(bool enabled);
	void mouseClicked(Qt3DRender::QPickEvent *pick);

private:
	Qt3DCore::QEntity *m_rootEntity;
	Qt3DExtras::QTorusMesh *m_torus;
	Qt3DCore::QEntity *m_coneEntity;
	Qt3DCore::QEntity *m_cylinderEntity;
	Qt3DCore::QEntity *m_torusEntity;
	Qt3DCore::QEntity *m_cuboidEntity;
	Qt3DCore::QEntity *m_planeEntity;
	Qt3DCore::QEntity *m_sphereEntity;
	Qt3DRender::QCamera *m_cameraEntity;
	Qt3DCore::QTransform *cuboidTransform;

	Qt3DRender::QObjectPicker *m_picker;
	Qt3DRender::QObjectPicker *m_picker1;
};

