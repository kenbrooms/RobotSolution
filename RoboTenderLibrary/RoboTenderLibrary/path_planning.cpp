#include "stdafx.h"
#include "path_planning.h"

using namespace robotender;

PathPlanning::PathPlanning()
{
	this->pConsoleAppender = new ConsoleAppender();
	this->pLogger = Logger::getInstance(_T("LoggerName"));
	this->pLogger.addAppender(pConsoleAppender);
	this->pLogger.setLogLevel(WARN_LOG_LEVEL);
}

PathPlanning::~PathPlanning()
{

}

void PathPlanning::InsertPoint(PathPoint point, long idx)
{
	list<PathPoint>::iterator it = this->pointList.begin();
	advance(it, idx);
	this->pointList.insert(it, point);
}

void PathPlanning::RemovePoint(long idx)
{
	list<PathPoint>::iterator it = this->pointList.begin();
	advance(it, idx);
	this->pointList.erase(it);
} 

// According the via points, the planner will extend extra points name acceleration points.
// The robot arm will accelerate/deccelerate between via point and acceleration point.

void PathPlanning::Plan(list<PathPoint> *viaPointList)
{
	list<PathPoint>	*accPointList = new list<PathPoint>;
	list<PathPoint>	*quantizePointList = new list<PathPoint>;
	this->EstimateAccPoints(viaPointList, accPointList);
	this->QuantizePoints(accPointList, quantizePointList, 50);
}

void PathPlanning::QuantizePoints(list<PathPoint> *accPointList, list<PathPoint> *quantizePointList, long quantizeStep /*milli second*/)
{
	list<PathPoint>::iterator it = std::prev(accPointList->end(), 1);
	long timeLine = it->GetStartTime() + it->GetDurationTime();
	long deltaTime;
	PathPoint point;
	
	quantizePointList->clear();
	it = accPointList->begin();
	
	for (long t = 0; t < timeLine; t += quantizeStep)
	{
		if (t >= (it->GetStartTime() + it->GetDurationTime()))
		{
			it = std::next(it, 1);
		}
		
		deltaTime = t - it->GetStartTime();
		// p = p0 + vt + 1/2 at^2;
		point.position = it->position + (it->pVelocity*deltaTime) + ((it->pAcceleration * pow(deltaTime, 2.0))/2.0);
		point.rotation = it->rotation + (it->rVelocity*deltaTime) + ((it->rAcceleration * pow(deltaTime, 2.0))/2.0);
		point.pVelocity = it->pVelocity;
		point.rVelocity = it->rVelocity;
		point.pAcceleration = it->pAcceleration;
		point.rAcceleration = it->rAcceleration;
		point.SetStartTime(t);
		point.SetDurationTime(quantizeStep);
		quantizePointList->push_back(point);
	}
}

void PathPlanning::EstimateAccPoints(list<PathPoint> *viaPointList, list<PathPoint> *accPointList)
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
			pVelocity1  = (curIt->position - preIt->position)/((rl::math::Real)(preIt->GetDurationTime()));
			rVelocity1  = (curIt->rotation - preIt->rotation)/((rl::math::Real)(preIt->GetDurationTime()));
			
			point.pAcceleration = (pVelocity2 - pVelocity1) / (curIt->GetAccelerationTime());
			point.rAcceleration = (rVelocity2 - rVelocity1) / (curIt->GetAccelerationTime());
			
			point.position = curIt->position - (pVelocity1 * (curIt->GetAccelerationTime() / 2)); // p(t) = p0 + vt;
			point.rotation = curIt->rotation - (rVelocity1 * (curIt->GetAccelerationTime() / 2)); // p(t) = p0 + vt;
		
			point.pVelocity = pVelocity1;
			point.rVelocity = rVelocity1;
			point.SetStartTime(t0 - (curIt->GetAccelerationTime() / 2));
			point.SetDurationTime(curIt->GetAccelerationTime());
			accPointList->push_back(point); 
			
			point.position = curIt->position;
			point.rotation = curIt->rotation;
			point.pVelocity << 0, 0, 0;
			point.rVelocity << 0, 0, 0;
			point.pAcceleration << 0, 0, 0;
			point.rAcceleration << 0, 0, 0;
			point.SetStartTime(t0 + (curIt->GetAccelerationTime() / 2));
			point.SetDurationTime(0);
			accPointList->push_back(point); 
		} else {
			nxtIt = std::next(curIt, 1);
			point = (*curIt);
			
			if (curIt == viaPointList->begin())
			{
				t0 = (curIt->GetAccelerationTime() / 2);
				pVelocity2  = (nxtIt->position - curIt->position)/((rl::math::Real)(curIt->GetDurationTime()-(curIt->GetAccelerationTime()/2)));
				rVelocity2  = (nxtIt->rotation - curIt->rotation)/((rl::math::Real)(curIt->GetDurationTime()-(curIt->GetAccelerationTime()/2)));
				pVelocity1 << 0, 0, 0;
				rVelocity1 << 0, 0, 0;
			}
			else {
				preIt = std::prev(curIt, 1);
				pVelocity2  = (nxtIt->position - curIt->position)/((rl::math::Real)(curIt->GetDurationTime()));
				rVelocity2  = (nxtIt->rotation - curIt->rotation)/((rl::math::Real)(curIt->GetDurationTime()));
				pVelocity1  = (curIt->position - preIt->position)/((rl::math::Real)(preIt->GetDurationTime()));
				rVelocity1  = (curIt->rotation - preIt->rotation)/((rl::math::Real)(preIt->GetDurationTime()));
			}


			// parabolic function
			pAcceleration = (pVelocity2 - pVelocity1) / (curIt->GetAccelerationTime());
			rAcceleration = (rVelocity2 - rVelocity1) / (curIt->GetAccelerationTime());
			if (curIt == viaPointList->begin())
			{
				point.position = curIt->position;
				point.rotation = curIt->rotation;
			}
			else {
				point.position = curIt->position - (pVelocity1 * (curIt->GetAccelerationTime() / 2)); // p(t) = p0 + vt;
				point.rotation = curIt->rotation - (rVelocity1 * (curIt->GetAccelerationTime() / 2)); // p(t) = p0 + vt;
			}
			point.pVelocity = pVelocity1;
			point.rVelocity = rVelocity1;
			point.pAcceleration = (pVelocity2 - pVelocity1) / (curIt->GetAccelerationTime());
			point.rAcceleration = (rVelocity2 - rVelocity1) / (curIt->GetAccelerationTime());
			point.SetStartTime(t0 - (curIt->GetAccelerationTime() / 2));
			point.SetDurationTime(curIt->GetAccelerationTime());
			accPointList->push_back(point); 
			
			// linear function
			point.pVelocity  = pVelocity2;
			point.rVelocity  = rVelocity2;
			
			point.position = curIt->position + (pVelocity2 * (curIt->GetAccelerationTime() / 2)); // p(t) = p0 + vt;
			point.rotation = curIt->rotation + (rVelocity2 * (curIt->GetAccelerationTime() / 2)); // p(t) = p0 + vt;
			
			point.pAcceleration << 0.0, 0.0, 0.0;
			point.rAcceleration << 0.0, 0.0, 0.0;
			point.SetStartTime(t0 + (curIt->GetAccelerationTime()/2));
			point.SetDurationTime(curIt->GetDurationTime() - (curIt->GetAccelerationTime() / 2) - (nxtIt->GetAccelerationTime() / 2));
			accPointList->push_back(point); 
			
			// After all
			t0 = t0 + curIt->GetDurationTime();
		}
	}
	return;
}
