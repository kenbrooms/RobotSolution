#include "stdafx.h"
#include "path_point.h"

using namespace robotender;

PathPoint::PathPoint(double px, double py, double pz, double rx, double ry, double rz, long dt, long at, char attr)
{
	this->setPostion(px, py, pz);
	this->setRotation(rx, ry, rz);

	this->setDurationTime(dt);
	this->setAccelearationTime(at);

	this->setAttr(attr);
}


PathPoint::PathPoint()
{

}


PathPoint::~PathPoint()
{

}

void PathPoint::setPostion(double px, double py, double pz)
{
	//this->pxAxis.position = px;
	//this->pyAxis.position = py;
	//this->pzAxis.position = pz;
	this->position << px, py, pz;
}


void PathPoint::setRotation(double rx, double ry, double rz)
{	
	//this->rxAxis.position = rx;
	//this->ryAxis.position = ry;
	//this->rzAxis.position = rz;
	this->rotation << rx, ry, rz;
}

void PathPoint::setDurationTime(long dt)
{
	this->durationTime = dt;
}

void PathPoint::setAccelearationTime(long at)
{
	this->accelerationTime = at;
}

void PathPoint::setStartTime(long st)
{
	this->startTime = st;
}

void PathPoint::setAttr(char attr)
{
	this->attr = attr;
}

void PathPoint::SetPosition(double px, double py, double pz)
{
	this->setPostion(px, py, pz);
}

void PathPoint::SetRotation(double rx, double ry, double rz)
{
	this->setRotation(rx, ry, rz);
}

void PathPoint::SetDurationTime(long dt)
{
	this->setDurationTime(dt);
}

void PathPoint::SetAccelearationTime(long at)
{
	this->setAccelearationTime(at);
}

void PathPoint::SetStartTime(long st)
{
	this->setStartTime(st);
}

void PathPoint::SetAttr(char attr)
{
	this->setAttr(attr);
}

void PathPoint::GetPosition(double* px, double* py, double* pz)
{
	//(*px) = this->pxAxis.position;
	//(*py) = this->pyAxis.position;
	//(*pz) = this->pzAxis.position;
	(*px) = this->position.coeff(0, 0);
	(*py) = this->position.coeff(1, 0);
	(*pz) = this->position.coeff(2, 0);
}


void PathPoint::GetRotation(double* rx, double* ry, double* rz)
{
	//(*rx) = this->rxAxis.position;
	//(*ry) = this->ryAxis.position;
	//(*rz) = this->rzAxis.position;
	(*rx) = this->rotation.coeff(0, 0);
	(*ry) = this->rotation.coeff(1, 0);
	(*rz) = this->rotation.coeff(2, 0);
}

void PathPoint::GetDurationTime(long* dt)
{
	(*dt) = this->durationTime;
}

long PathPoint::GetDurationTime()
{
	return this->durationTime;
}

void PathPoint::GetAccelerationTime(long* at)
{
	(*at) = this->accelerationTime;
}

long PathPoint::GetAccelerationTime()
{
	return this->accelerationTime;
}

void PathPoint::GetStartTime(long* st)
{
	(*st) = this->startTime;
}

long PathPoint::GetStartTime()
{
	return this->startTime;
}

void PathPoint::GetAttr(char *attr)
{
	(*attr) = this->attr;
}
