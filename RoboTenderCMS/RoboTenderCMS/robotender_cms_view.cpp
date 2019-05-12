#include "stdafx.h"
#include "robotender_cms_view.h"
#include "scenemodifier.h"
using namespace std;

RoboTenderCMS_View::~RoboTenderCMS_View()
{

}

void RoboTenderCMS_View::UpdateTableView(list<PathPoint> *pointList)
{
	list<PathPoint>::iterator it;
	std::string item_str;
	double x, y, z;
	long time;
	char attr;
	std::ostringstream streamObj;
	std::string str_x, str_y, str_z;

	streamObj << std::fixed;
	streamObj << std::setprecision(2);
	
	this->pTableWidget->setRowCount(0);
	for (it = pointList->begin(); it != pointList->end(); it++)
	{
		pTableWidget->insertRow(pTableWidget->rowCount());
		
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
		item_str = str_x + "," + str_y + "," + str_z;
		pTableWidget->setItem(pTableWidget->rowCount()-1, 0, new QTableWidgetItem(item_str.c_str()));
		
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
		item_str = str_x + "," + str_y + "," + str_z;
		pTableWidget->setItem(pTableWidget->rowCount()-1, 1, new QTableWidgetItem(item_str.c_str()));
	
		it->GetDurationTime(&time);
		item_str = std::to_string(time);
		pTableWidget->setItem(pTableWidget->rowCount()-1, 2, new QTableWidgetItem(item_str.c_str()));
		
		it->GetAccelerationTime(&time);
		item_str = std::to_string(time);
		pTableWidget->setItem(pTableWidget->rowCount()-1, 3, new QTableWidgetItem(item_str.c_str()));
		
		it->GetAttr(&attr);
		item_str = attr;
		pTableWidget->setItem(pTableWidget->rowCount()-1, 4, new QTableWidgetItem(item_str.c_str()));

	}

}


void RoboTenderCMS_View::GetDataFromView(list<PathPoint> *pointList)
{
	QString item_str;
	vector<string> strs;
	PathPoint point;
	double x, y, z;
	long time;
	char attr;
	
	pointList->clear();
	
	for (auto rowIdx = 0; rowIdx < this->pTableWidget->rowCount(); rowIdx++)
	{
		item_str = this->pTableWidget->item(rowIdx, 0)->text();
		boost::split(strs, item_str.toStdString(),boost::is_any_of(","));
		x = std::stod(strs.at(0)); y = std::stod(strs.at(1)); z = std::stod(strs.at(2));
		point.SetPosition(x, y, z);
		strs.clear();

		item_str = this->pTableWidget->item(rowIdx, 1)->text();
		boost::split(strs, item_str.toStdString(),boost::is_any_of(","));
		x = std::stod(strs.at(0)); y = std::stod(strs.at(1)); z = std::stod(strs.at(2));
		point.SetRotation(x, y, z);
		strs.clear();
			
		item_str = this->pTableWidget->item(rowIdx, 2)->text();
		time = std::stol(item_str.toStdString());
		point.SetDurationTime(time);
		
		item_str = this->pTableWidget->item(rowIdx, 3)->text();
		time = std::stol(item_str.toStdString());
		point.SetAccelearationTime(time);
		
		item_str = this->pTableWidget->item(rowIdx, 4)->text();
		attr = (*item_str.toStdString().c_str());
		point.SetAttr(attr);
		pointList->push_back(point);
	}
}


void RoboTenderCMS_View::RemoveItem()
{	
		QModelIndexList selection = pTableWidget->selectionModel()->selectedIndexes();
		if (selection.count() == 1)
		{
			int idx = selection.at(0).row();
			this->pTableWidget->removeRow(idx);
		}
}

void RoboTenderCMS_View::AddItem()
{
	QModelIndexList selection = this->pTableWidget->selectionModel()->selectedIndexes();

	std::string item_str;
	int rowIdx;

	if (selection.count() == 1)
	{
		rowIdx = selection.at(0).row() + 1;
		pTableWidget->insertRow(rowIdx);
		for (auto colIdx = 0; colIdx < pTableWidget->columnCount(); colIdx++)
		{
			item_str = pTableWidget->item(rowIdx - 1, colIdx)->text().toStdString();
			pTableWidget->setItem(rowIdx, colIdx, new QTableWidgetItem(item_str.c_str()));
		}
	}else {
		if (pTableWidget->rowCount() == 0)
		{
			// There are no any row in the table.	
			rowIdx = 0;
			pTableWidget->insertRow(rowIdx);
			pTableWidget->setItem(rowIdx, 0, new QTableWidgetItem("0,0,0"));
			pTableWidget->setItem(rowIdx, 1, new QTableWidgetItem("0,0,0"));
			pTableWidget->setItem(rowIdx, 2, new QTableWidgetItem("10"));
			pTableWidget->setItem(rowIdx, 3, new QTableWidgetItem("20"));
			pTableWidget->setItem(rowIdx, 4, new QTableWidgetItem(""));
		}
		else 
		{
			// There are have a rows in the table at least.	Append the new row after the latest row.
			rowIdx = pTableWidget->rowCount();
			pTableWidget->insertRow(rowIdx);
			for (auto colIdx = 0; colIdx < pTableWidget->columnCount(); colIdx++)
			{
				item_str = pTableWidget->item(rowIdx - 1, colIdx)->text().toStdString();
				pTableWidget->setItem(rowIdx, colIdx, new QTableWidgetItem(item_str.c_str()));
			}
		}
	}
}

void RoboTenderCMS_View::Update3DView(std::list<PathPoint> *viaPointList)
{
	std::list<PathPoint>::iterator it;
	std::list<PathPoint>::iterator prevIt;
	std::list<Qt3DCore::QTransform*> transformList;
	shared_ptr<Qt3DCore::QEntity> smallGreenSphere;
	Qt3DCore::QTransform* transform;
	Qt3DExtras::QPhongMaterial* greenMaterial;
	Qt3DExtras::QSphereMesh* smallMesh;
	double px, py, pz;
	double ppx, ppy, ppz;

	this->entityList.clear();
	this->pathEntityList.clear();
	
	for (it = viaPointList->begin(); it != viaPointList->end(); it++)
	{
		it->GetPosition(&px, &py, &pz);
		transform = new Qt3DCore::QTransform();
		transform->setTranslation(QVector3D(px, py, pz));
		transform->setScale(1.0f);
		smallMesh = new Qt3DExtras::QSphereMesh;
		smallMesh->setRings(10);
		smallMesh->setSlices(10);
		smallMesh->setRadius(5);

		greenMaterial = new Qt3DExtras::QPhongMaterial;
		greenMaterial->setSpecular(Qt::white);
		greenMaterial->setShininess(10);
		greenMaterial->setAmbient(Qt::green);

		smallGreenSphere = shared_ptr<Qt3DCore::QEntity>(new Qt3DCore::QEntity(this->rootEntity));
		smallGreenSphere->addComponent(greenMaterial);
		smallGreenSphere->addComponent(smallMesh);
		smallGreenSphere->addComponent(transform);
		
		this->entityList.push_back(smallGreenSphere);

		if (it != viaPointList->begin())
		{
			it->GetPosition(&px, &py, &pz);
			prevIt->GetPosition(&ppx, &ppy, &ppz);
			this->pathEntityList.push_back(this->DrawLine({ (float)ppx, (float)ppy, (float)ppz }, { (float)px, (float)py, (float)pz }, Qt::black, this->rootEntity));
			prevIt = it;
		}
		else {
			prevIt = it;
		}
	}
}

void RoboTenderCMS_View::DrawAxis()
{
	this->axisEntityList.clear();
	this->axisEntityList.push_back(this->DrawLine({ 0, 0, 0 }, { 600, 0, 0 }, Qt::red, this->rootEntity)); // X
	this->axisEntityList.push_back(this->DrawLine({ 0, 0, 0 }, { 0, 600, 0 }, Qt::green, this->rootEntity)); // Y
	this->axisEntityList.push_back(this->DrawLine({ 0, 0, 0 }, { 0, 0, 600 }, Qt::blue, this->rootEntity)); // Z
}

void RoboTenderCMS_View::Init3DView()
{
	Qt3DInput::QInputAspect *input = new Qt3DInput::QInputAspect;
	this->m_view->registerAspect(input);

	this->rootEntity = new Qt3DCore::QEntity();
	
	// Camera
	Qt3DRender::QCamera *cameraEntity = this->m_view->camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 2000.0f);
	cameraEntity->setPosition(QVector3D(0, 0, 1000.0f));
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));
	
	Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(this->rootEntity);
	Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
	light->setColor("white");
	light->setIntensity(1);
	lightEntity->addComponent(light);
	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	lightTransform->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform);

	// For camera controls
	//Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
	//camController->setCamera(cameraEntity);
	Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(this->rootEntity);
	camController->setCamera(cameraEntity);
	float linearSpeed = camController->linearSpeed();
	camController->setLinearSpeed(200);
	 float lookSpeed = camController->lookSpeed(); 
	// Scenemodifier
	//SceneModifier *modifier = new SceneModifier(rootEntity, cameraEntity);

	// Set root object of the scene
	this->m_view->setRootEntity(this->rootEntity);
	this->DrawAxis();
}

shared_ptr<Qt3DCore::QEntity> RoboTenderCMS_View::DrawLine(const QVector3D& start, const QVector3D& end, const QColor& color, Qt3DCore::QEntity *_rootEntity)
{
	auto *geometry = new Qt3DRender::QGeometry(_rootEntity);

	// position vertices (start and end)
	QByteArray bufferBytes;
	bufferBytes.resize(3 * 2 * sizeof(float)); // start.x, start.y, start.end + end.x, end.y, end.z
	float *positions = reinterpret_cast<float*>(bufferBytes.data());
	*positions++ = start.x();
	*positions++ = start.y();
	*positions++ = start.z();
	*positions++ = end.x();
	*positions++ = end.y();
	*positions++ = end.z();

	auto *buf = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, geometry);
	buf->setData(bufferBytes);

	auto *positionAttribute = new Qt3DRender::QAttribute(geometry);
	positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
	positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
	positionAttribute->setVertexSize(3);
	positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
	positionAttribute->setBuffer(buf);
	positionAttribute->setByteStride(3 * sizeof(float));
	positionAttribute->setCount(2);
	geometry->addAttribute(positionAttribute); // We add the vertices in the geometry

	// connectivity between vertices
	QByteArray indexBytes;
	indexBytes.resize(2 * sizeof(unsigned int)); // start to end
	unsigned int *indices = reinterpret_cast<unsigned int*>(indexBytes.data());
	*indices++ = 0;
	*indices++ = 1;

	auto *indexBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::IndexBuffer, geometry);
	indexBuffer->setData(indexBytes);

	auto *indexAttribute = new Qt3DRender::QAttribute(geometry);
	indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
	indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
	indexAttribute->setBuffer(indexBuffer);
	indexAttribute->setCount(2);
	geometry->addAttribute(indexAttribute); // We add the indices linking the points in the geometry

	// mesh
	auto *line = new Qt3DRender::QGeometryRenderer(_rootEntity);
	line->setGeometry(geometry);
	line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
	auto *material = new Qt3DExtras::QPhongMaterial(_rootEntity);
	material->setAmbient(color);
	
	auto deleter = [](Qt3DCore::QEntity* entity) {
		auto line1 = (Qt3DRender::QGeometryRenderer*)entity->components().at(0);
		delete line1->geometry();
		auto material1 = (Qt3DExtras::QPhongMaterial*)entity->components().at(1);
		delete line1;
		delete material1;
		entity->components().clear();
	};
	// entity
	shared_ptr<Qt3DCore::QEntity> lineEntity(new Qt3DCore::QEntity(_rootEntity), deleter);
	lineEntity->addComponent(line);
	lineEntity->addComponent(material);
	
	return lineEntity;
}