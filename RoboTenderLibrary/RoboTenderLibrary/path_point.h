#pragma once
#include "stdafx.h"

namespace robotender {
	class ROBOTENDERLIBRARY_API PathPoint {
	public:
		PathPoint(double px, double py, double pz, double rx, double ry, double rz, long dt, long at, char attr);
		PathPoint();
		~PathPoint();
		//void SetPosition(double px, double py, double pz);
		//void SetRotation(double rx, double ry, double rz);
		//void SetDurationTime(long dt);
		//void SetAccelearationTime(long at);
		//void SetStartTime(long st);
		//void SetAttr(char attr);

		//void GetPosition(double* px, double* py, double* pz);
		//void GetRotation(double* rx, double* ry, double* rz);
		//void GetDurationTime(long* dt);
		//long GetDurationTime();
		//void GetAccelerationTime(long* at);
		//long GetAccelerationTime();
		//void GetStartTime(long* st);
		//long GetStartTime();
		//void GetAttr(char* attr);
	public:
		void setPosition(double px, double py, double pz);
		void getPosition(double* px, double* py, double* pz);
		void setRotation(double rx, double ry, double rz);
		void getRotation(double* rx, double* ry, double* rz);
		void setDurationTime(long dt);
		long getDurationTime();
		void setAccelearationTime(long at);
		long getAccelerationTime();
		void setStartTime(long st);
		long getStartTime();
		void setAttr(char attr);
		char getAttr();
	public:
		rl::math::Vector3 position;
		rl::math::Vector3 rotation;
		rl::math::Vector3 pVelocity;
		rl::math::Vector3 rVelocity;
		rl::math::Vector3 pAcceleration;
		rl::math::Vector3 rAcceleration;
	private:
		long startTime;
		long durationTime, accelerationTime; // dt = duration time, at = accleration time
		char _attr;
	};
}

