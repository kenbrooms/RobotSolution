#include "stdafx.h"
#include "scenemodifier.h"
#include <QtCore/QDebug>

using namespace std;

SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity, Qt3DRender::QCamera *cameraEntity) : m_rootEntity(rootEntity), m_cameraEntity(cameraEntity)
{

	// Torus shape data
	m_torus = new Qt3DExtras::QTorusMesh();
	m_torus->setRadius(1.0f);
	m_torus->setMinorRadius(0.4f);
	m_torus->setRings(100);
	m_torus->setSlices(20);

	// TorusMesh Transform
	Qt3DCore::QTransform *torusTransform = new Qt3DCore::QTransform();
	torusTransform->setScale(2.0f);
	torusTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), 25.0f));
	torusTransform->setTranslation(QVector3D(5.0f, 4.0f, 0.0f));

	Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial();
	torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));

	// Torus
	m_torusEntity = new Qt3DCore::QEntity(m_rootEntity);
	m_torusEntity->addComponent(m_torus);
	m_torusEntity->addComponent(torusMaterial);
	m_torusEntity->addComponent(torusTransform);

	// Cone shape data
	Qt3DExtras::QConeMesh *cone = new Qt3DExtras::QConeMesh();
	cone->setTopRadius(0.5);
	cone->setBottomRadius(1);
	cone->setLength(3);
	cone->setRings(50);
	cone->setSlices(20);

	// ConeMesh Transform
	Qt3DCore::QTransform *coneTransform = new Qt3DCore::QTransform();
	coneTransform->setScale(1.5f);
	coneTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
	coneTransform->setTranslation(QVector3D(0.0f, 4.0f, -1.5));

	Qt3DExtras::QPhongMaterial *coneMaterial = new Qt3DExtras::QPhongMaterial();
	coneMaterial->setDiffuse(QColor(QRgb(0x928327)));

	// Cone
	m_coneEntity = new Qt3DCore::QEntity(m_rootEntity);
	m_coneEntity->addComponent(cone);
	m_coneEntity->addComponent(coneMaterial);
	m_coneEntity->addComponent(coneTransform);

	// Cylinder shape data
	Qt3DExtras::QCylinderMesh *cylinder = new Qt3DExtras::QCylinderMesh();
	cylinder->setRadius(1);
	cylinder->setLength(3);
	cylinder->setRings(100);
	cylinder->setSlices(20);

	// CylinderMesh Transform
	Qt3DCore::QTransform *cylinderTransform = new Qt3DCore::QTransform();
	cylinderTransform->setScale(1.5f);
	cylinderTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
	cylinderTransform->setTranslation(QVector3D(-5.0f, 4.0f, -1.5));

	Qt3DExtras::QPhongMaterial *cylinderMaterial = new Qt3DExtras::QPhongMaterial();
	cylinderMaterial->setDiffuse(QColor(QRgb(0x928327)));

	// Cylinder
	m_cylinderEntity = new Qt3DCore::QEntity(m_rootEntity);
	m_cylinderEntity->addComponent(cylinder);
	m_cylinderEntity->addComponent(cylinderMaterial);
	m_cylinderEntity->addComponent(cylinderTransform);

	// Cuboid shape data
	Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();

	// CuboidMesh Transform
	cuboidTransform = new Qt3DCore::QTransform();
	cuboidTransform->setScale(1.0f);
	cuboidTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

	Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
	cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));

	//Cuboid
	m_cuboidEntity = new Qt3DCore::QEntity(m_rootEntity);
	m_cuboidEntity->addComponent(cuboid);
	m_cuboidEntity->addComponent(cuboidMaterial);
	m_cuboidEntity->addComponent(cuboidTransform);

	// Plane shape data
	Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh();
	planeMesh->setWidth(2);
	planeMesh->setHeight(2);

	// Plane mesh transform
	Qt3DCore::QTransform *planeTransform = new Qt3DCore::QTransform();
	planeTransform->setScale(1.3f);
	planeTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), 45.0f));
	planeTransform->setTranslation(QVector3D(0.0f, -4.0f, 0.0f));

	Qt3DExtras::QPhongMaterial *planeMaterial = new Qt3DExtras::QPhongMaterial();
	planeMaterial->setDiffuse(QColor(QRgb(0xa69929)));

	// Plane
	m_planeEntity = new Qt3DCore::QEntity(m_rootEntity);
	m_planeEntity->addComponent(planeMesh);
	m_planeEntity->addComponent(planeMaterial);
	m_planeEntity->addComponent(planeTransform);

	// Sphere shape data
	Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
	sphereMesh->setRings(20);
	sphereMesh->setSlices(20);
	sphereMesh->setRadius(2);

	// Sphere mesh transform
	Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();

	sphereTransform->setScale(1.3f);
	sphereTransform->setTranslation(QVector3D(-5.0f, -4.0f, 0.0f));

	Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
	sphereMaterial->setDiffuse(QColor(QRgb(0xa69929)));



	// Sphere
	m_sphereEntity = new Qt3DCore::QEntity(m_rootEntity);

	//m_picker = new Qt3DRender::QObjectPicker(m_sphereEntity);
	//m_picker->setHoverEnabled(true);
	//m_picker->setEnabled(true);

	m_sphereEntity->addComponent(sphereMesh);
	m_sphereEntity->addComponent(sphereMaterial);
	m_sphereEntity->addComponent(sphereTransform);
	m_sphereEntity->setObjectName("Sphere");
	//m_sphereEntity->addComponent(m_picker);

	//QObject::connect(m_picker, &Qt3DRender::QObjectPicker::clicked, this, &SceneModifier::mouseClicked);

	m_rootEntity->setObjectName("rootEntity");
	m_picker1 = new Qt3DRender::QObjectPicker(m_rootEntity);
	m_picker1->setHoverEnabled(true);
	m_picker1->setEnabled(true);
	QObject::connect(m_picker1, &Qt3DRender::QObjectPicker::clicked, this, &SceneModifier::mouseClicked);
	m_rootEntity->addComponent(m_picker1);

	Qt3DCore::QTransform *rootTransform = new Qt3DCore::QTransform();
	rootTransform->setScale(1.0f);
	rootTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
	m_rootEntity->addComponent(rootTransform);

}

SceneModifier::~SceneModifier()
{
}

void SceneModifier::enableTorus(bool enabled)
{
	m_torusEntity->setEnabled(enabled);
}

void SceneModifier::enableCone(bool enabled)
{
	m_coneEntity->setEnabled(enabled);
}

void SceneModifier::enableCylinder(bool enabled)
{
	m_cylinderEntity->setEnabled(enabled);
}

void SceneModifier::enableCuboid(bool enabled)
{
	m_cuboidEntity->setEnabled(enabled);
}

void SceneModifier::enablePlane(bool enabled)
{
	m_planeEntity->setEnabled(enabled);
}

void SceneModifier::enableSphere(bool enabled)
{
	m_sphereEntity->setEnabled(enabled);
	qDebug("enableSphere");
}

void SceneModifier::mouseClicked(Qt3DRender::QPickEvent *pick)
{

	std::cout << "mouseClicked" << std::endl;
	qDebug("mouseCliecked");
	//m_sphereEntity->setEnabled(false);
	QVector4D vt = pick->worldIntersection().toVector4D();
	QVector4D vt1 = pick->localIntersection().toVector4D();
	QPoint pt1 = pick->worldIntersection().toPoint();

	QMatrix4x4 view_matrix = m_cameraEntity->viewMatrix();
	QMatrix4x4 projection_matrix = m_cameraEntity->projectionMatrix();
	QMatrix4x4 projection_view = projection_matrix * view_matrix;
	QMatrix4x4 inv_projection_view = projection_view.inverted();
	float mouse_x = 650.0;
	float mouse_y = 450.0;
	//float screen_x = ((2.0f * mouse_x) / 800.0) - 1.0;
	//float screen_x = (mouse_x - 400.0) / 400.0;
	float screen_x = mouse_x;
	//float screen_y = 1.0 - ((2.0f * mouse_y) / 600.0);
	//float screen_y = (300.0 - mouse_y) / 300.0;
	float screen_y = mouse_y;

	QVector4D screen_pos = QVector4D({ screen_x, screen_y, -1.0f, 1.0f });
	QVector4D ray_eye = projection_matrix.inverted() * screen_pos;
	ray_eye = QVector4D({ ray_eye.x(), ray_eye.y(), -1.0, 0.0 });

	QVector4D ray_world_4d = (view_matrix.inverted() * ray_eye);
	QVector3D ray_world_3d = QVector3D(ray_world_4d.x(), ray_world_4d.y(), ray_world_4d.z());
	ray_world_3d.normalize();
	QVector4D world_pos = screen_pos * m_cameraEntity->transform()->matrix().inverted() * projection_matrix.inverted() * view_matrix.inverted();
	//QVector4D world_pos = screen_pos * inv_projection_view;
	world_pos.normalize();
	qDebug() << "projection: " << projection_matrix << endl;
	qDebug() << "view: " << view_matrix << endl;
	qDebug() << "projection_view: " << projection_view << endl;
	qDebug() << "inv_projection_view: " << inv_projection_view << endl;
	qDebug() << "Indetifi matrix: " << inv_projection_view * projection_view << endl;
	qDebug() << "screen : " << screen_x << " " << screen_y << endl;
	qDebug() << "screen pos: " << screen_pos << endl;
	qDebug() << "world pos: " << world_pos << endl;
	qDebug() << "ray_world_3d: " << ray_world_3d << endl;
	//this->cuboidTransform->setTranslation(QVector3D(ray_world_3d.x(), ray_world_3d.y(), ray_world_3d.z()));
	this->cuboidTransform->setTranslation(QVector3D(world_pos.x(), world_pos.y(), world_pos.z()));
	//qDebug() << pick->objectName() << endl;
	//qDebug() << "RX: " << vt1.x() << " RY: " << vt1.y() << " RZ: " << vt1.z() << " RW: " << vt1.w() << endl;
	//qDebug("X: %d\n", pick->worldIntersection().toPoint().x());
}