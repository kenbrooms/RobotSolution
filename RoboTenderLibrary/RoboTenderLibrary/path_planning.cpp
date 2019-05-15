#include "stdafx.h"
#include "path_planning.h"

using namespace robotender;

PathPlanning::PathPlanning()
{
	this->_console_appender = new ConsoleAppender();
	this->_logger = Logger::getInstance(_T("LoggerName"));
	this->_logger.addAppender(this->_console_appender);
	this->_logger.setLogLevel(WARN_LOG_LEVEL);
}

PathPlanning::~PathPlanning()
{

}

void PathPlanning::insertPoint(PathPoint point, long idx)
{
	list<PathPoint>::iterator it = this->_point_list.begin();
	advance(it, idx);
	this->_point_list.insert(it, point);
}

void PathPlanning::removePoint(long idx)
{
	list<PathPoint>::iterator it = this->_point_list.begin();
	advance(it, idx);
	this->_point_list.erase(it);
} 

// According the via points, the planner will extend extra points name acceleration points.
// The robot arm will accelerate/deccelerate between via point and acceleration point.

void PathPlanning::plan(list<PathPoint> *viaPointList, list<PathPoint> *quantizePointList) 
{
	list<PathPoint>	*accPointList = new list<PathPoint>;
	this->estimateAccPoints(viaPointList, accPointList);
	this->quantizePoints(accPointList, quantizePointList, 50);
	delete accPointList;
}

void PathPlanning::quantizePoints(list<PathPoint> *accPointList, list<PathPoint> *quantizePointList, long quantizeStep /*milli second*/)
{
	list<PathPoint>::iterator it = std::prev(accPointList->end(), 1);
	long timeLine = it->getStartTime() + it->getDurationTime();
	long deltaTime;
	PathPoint point;
	
	quantizePointList->clear();
	it = accPointList->begin();
	
	for (long t = 0; t < timeLine; t += quantizeStep)
	{
		if (t >= (it->getStartTime() + it->getDurationTime()))
		{
			it = std::next(it, 1);
		}
		
		deltaTime = t - it->getStartTime();
		// p = p0 + vt + 1/2 at^2;
		point.position = it->position + (it->pVelocity*deltaTime) + ((it->pAcceleration * pow(deltaTime, 2.0))/2.0);
		point.rotation = it->rotation + (it->rVelocity*deltaTime) + ((it->rAcceleration * pow(deltaTime, 2.0))/2.0);
		point.pVelocity = it->pVelocity;
		point.rVelocity = it->rVelocity;
		point.pAcceleration = it->pAcceleration;
		point.rAcceleration = it->rAcceleration;
		point.setStartTime(t);
		point.setDurationTime(quantizeStep);
		quantizePointList->push_back(point);
	}
}

void PathPlanning::estimateAccPoints(list<PathPoint> *viaPointList, list<PathPoint> *accPointList)
{
	PathPoint point;
	list<PathPoint>::iterator curIt, nxtIt, preIt;
	long t0;
	
	rl::math::Vector3 pVelocity1, pVelocity2;
	rl::math::Vector3 rVelocity1, rVelocity2;
	rl::math::Vector3 pAcceleration, rAcceleration;
	
	accPointList->clear();
	
	for (curIt = viaPointList->begin(); curIt != viaPointList->end(); curIt++)
	{
		if (curIt == std::prev(viaPointList->end(), 1))
		{
			// The last point
			preIt = std::prev(curIt, 1);
			
			pVelocity2 << 0, 0, 0;
			rVelocity2 << 0, 0, 0;
			pVelocity1  = (curIt->position - preIt->position)/((rl::math::Real)(preIt->getDurationTime()));
			rVelocity1  = (curIt->rotation - preIt->rotation)/((rl::math::Real)(preIt->getDurationTime()));
			
			point.pAcceleration = (pVelocity2 - pVelocity1) / (curIt->getAccelerationTime());
			point.rAcceleration = (rVelocity2 - rVelocity1) / (curIt->getAccelerationTime());
			
			point.position = curIt->position - (pVelocity1 * (curIt->getAccelerationTime() / 2)); // p(t) = p0 + vt;
			point.rotation = curIt->rotation - (rVelocity1 * (curIt->getAccelerationTime() / 2)); // p(t) = p0 + vt;
		
			point.pVelocity = pVelocity1;
			point.rVelocity = rVelocity1;
			point.setStartTime(t0 - (curIt->getAccelerationTime() / 2));
			point.setDurationTime(curIt->getAccelerationTime());
			accPointList->push_back(point); 
			
			point.position = curIt->position;
			point.rotation = curIt->rotation;
			point.pVelocity << 0, 0, 0;
			point.rVelocity << 0, 0, 0;
			point.pAcceleration << 0, 0, 0;
			point.rAcceleration << 0, 0, 0;
			point.setStartTime(t0 + (curIt->getAccelerationTime() / 2));
			point.setDurationTime(0);
			accPointList->push_back(point); 
		} else {
			nxtIt = std::next(curIt, 1);
			point = (*curIt);
			
			if (curIt == viaPointList->begin())
			{
				t0 = (curIt->getAccelerationTime() / 2);
				pVelocity2  = (nxtIt->position - curIt->position)/((rl::math::Real)(curIt->getDurationTime()-(curIt->getAccelerationTime()/2)));
				rVelocity2  = (nxtIt->rotation - curIt->rotation)/((rl::math::Real)(curIt->getDurationTime()-(curIt->getAccelerationTime()/2)));
				pVelocity1 << 0, 0, 0;
				rVelocity1 << 0, 0, 0;
			}
			else {
				preIt = std::prev(curIt, 1);
				pVelocity2  = (nxtIt->position - curIt->position)/((rl::math::Real)(curIt->getDurationTime()));
				rVelocity2  = (nxtIt->rotation - curIt->rotation)/((rl::math::Real)(curIt->getDurationTime()));
				pVelocity1  = (curIt->position - preIt->position)/((rl::math::Real)(preIt->getDurationTime()));
				rVelocity1  = (curIt->rotation - preIt->rotation)/((rl::math::Real)(preIt->getDurationTime()));
			}


			// parabolic function
			pAcceleration = (pVelocity2 - pVelocity1) / (curIt->getAccelerationTime());
			rAcceleration = (rVelocity2 - rVelocity1) / (curIt->getAccelerationTime());
			if (curIt == viaPointList->begin())
			{
				point.position = curIt->position;
				point.rotation = curIt->rotation;
			}
			else {
				point.position = curIt->position - (pVelocity1 * (curIt->getAccelerationTime() / 2)); // p(t) = p0 + vt;
				point.rotation = curIt->rotation - (rVelocity1 * (curIt->getAccelerationTime() / 2)); // p(t) = p0 + vt;
			}
			point.pVelocity = pVelocity1;
			point.rVelocity = rVelocity1;
			point.pAcceleration = (pVelocity2 - pVelocity1) / (curIt->getAccelerationTime());
			point.rAcceleration = (rVelocity2 - rVelocity1) / (curIt->getAccelerationTime());
			point.setStartTime(t0 - (curIt->getAccelerationTime() / 2));
			point.setDurationTime(curIt->getAccelerationTime());
			accPointList->push_back(point); 
			
			// linear function
			point.pVelocity  = pVelocity2;
			point.rVelocity  = rVelocity2;
			
			point.position = curIt->position + (pVelocity2 * (curIt->getAccelerationTime() / 2)); // p(t) = p0 + vt;
			point.rotation = curIt->rotation + (rVelocity2 * (curIt->getAccelerationTime() / 2)); // p(t) = p0 + vt;
			
			point.pAcceleration << 0.0, 0.0, 0.0;
			point.rAcceleration << 0.0, 0.0, 0.0;
			point.setStartTime(t0 + (curIt->getAccelerationTime()/2));
			if (curIt == viaPointList->begin())
			{
				point.setDurationTime(curIt->getDurationTime() - curIt->getAccelerationTime() - (nxtIt->getAccelerationTime() / 2));
				t0 = t0 + (curIt->getDurationTime()) - (curIt->getAccelerationTime()/2);
			}
			else {
				point.setDurationTime(curIt->getDurationTime() - (curIt->getAccelerationTime()/2) - (nxtIt->getAccelerationTime() / 2));
				t0 = t0 + curIt->getDurationTime();
			}
			accPointList->push_back(point); 
			
			// After all
		}
	}
	return;
}
