#include "stdafx.h"
#include "path_point.h"

using namespace robotender;

PathPoint::PathPoint(double px, double py, double pz, double rx, double ry, double rz, long dt, long at, char attr)
{
	this->setPosition(px, py, pz);
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


void PathPoint::setPosition(double px, double py, double pz)
{
	this->position << px, py, pz;
}

void PathPoint::getPosition(double* px, double* py, double* pz)
{
	(*px) = this->position.coeff(0, 0);
	(*py) = this->position.coeff(1, 0);
	(*pz) = this->position.coeff(2, 0);
}

void PathPoint::setRotation(double rx, double ry, double rz)
{	
	this->rotation << rx, ry, rz;
}

void PathPoint::getRotation(double* rx, double* ry, double* rz)
{
	(*rx) = this->rotation.coeff(0, 0);
	(*ry) = this->rotation.coeff(1, 0);
	(*rz) = this->rotation.coeff(2, 0);
}


void PathPoint::setDurationTime(long dt)
{
	this->durationTime = dt;
}

long PathPoint::getDurationTime()
{
	return this->durationTime;
}

void PathPoint::setAccelearationTime(long at)
{
	this->accelerationTime = at;
}

long PathPoint::getAccelerationTime()
{
	return this->accelerationTime;
}


void PathPoint::setStartTime(long st)
{
	this->startTime = st;
}


long PathPoint::getStartTime()
{
	return this->startTime;
}


void PathPoint::setAttr(char attr)
{
	this->_attr = attr;
}

char PathPoint::getAttr()
{
	return this->_attr;
}
