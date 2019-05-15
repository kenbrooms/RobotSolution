/*
#ifndef KINEMATIC_H
#define KINEMATIC_H
#include <iostream>
#include <cmath>
#include <math.h>
#include <string>
#include <list> 
#include <iterator> 
#include <rl/math/Transform.h>
#include <rl/math/Unit.h>
#include <rl/xml/DomParser.h>

#include "math_common.h"
#include "joint.h"

template<class T>
class Kinematic 
{
	public:
		Kinematic(const char* xmlFile);
		~Kinematic();
		
		Joint* GetJoint(const int jointIndex);
		rl::math::Transform GenerateTransform(const double rx, const double ry, const double rz, const double px, const double py, const double pz);
	
	private:
		bool loadModel(const char* xmlFile);
	private:
		const char* xmlFile;
		std::list<Joint*> jointList;
		vector<shared_ptr<Joint>> _joints_ptr;

};

template<class T>
Kinematic<T>::Kinematic(const char* xmlFile)
{
	this->xmlFile = xmlFile;
	this->loadModel(this->xmlFile);
}

template<class T>
Kinematic<T>::~Kinematic()
{
	typename list<Joint*>::iterator it;
	Joint* jointPtr;

	it = this->jointList.begin();
	for (int i = 0; i < this->jointList.size(); i++)
	{
		std::advance(it, i);
		jointPtr = (*it);
		delete jointPtr;
	}
	this->jointList.clear();
}


template<class T>
bool Kinematic<T>::loadModel(const char* xmlFile)
{
	// The mechanism should be load from XML description file.
	// This part will be implemented later. It is a hard code right now for the schedule reason.
	Joint* jointPtr;
	DHTable dhTable;
	double d, theta, a, alpha;
	double theta_rad, alpha_rad;

	// Setup Joint1 parameter
	jointPtr = new Joint("Joint1", prismatic);
	jointPtr->setLimit(450.0, 0.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->setDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	// Setup Joint2 parameter
	jointPtr = new Joint("Joint2", revolute);
	jointPtr->setLimit(180.0, -180.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->setDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	// Setup Joint3 parameter
	jointPtr = new Joint("Joint3", revolute);
	jointPtr->setLimit(150.0, -150.0);

	d = 30.0; theta = 0.0; a = 280.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->setDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	// Setup Joint4 parameter
	jointPtr = new Joint("Joint4", revolute);
	jointPtr->setLimit(150.0, -150.0);

	d = -30.0; theta = 0.0; a = 210.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->setDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	// Setup Joint5 parameter
	jointPtr = new Joint("Joint5", revolute);
	jointPtr->setLimit(180.0, -180.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 90.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->setDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	return true;
}

template<class T>
Joint* Kinematic<T>::GetJoint(const int jointIndex)
{
	typename list<Joint*>::iterator it;

	it = this->jointList.begin();
	std::advance(it, jointIndex);
	return (*it);
}


template<class T>
rl::math::Transform Kinematic<T>::GenerateTransform(const double rx, const double ry, const double rz, const double px, const double py, const double pz)
{
	double rx_rad = rx * rl::math::DEG2RAD;
	double ry_rad = ry * rl::math::DEG2RAD;
	double rz_rad = rz * rl::math::DEG2RAD;

	rl::math::Transform rotation(rl::math::AngleAxis(rz_rad, rl::math::Vector3::UnitZ()) *
		rl::math::AngleAxis(ry_rad, rl::math::Vector3::UnitY()) *
		rl::math::AngleAxis(rx_rad, rl::math::Vector3::UnitX())
	);

	rl::math::Transform translation(rl::math::Translation(px, py, pz));
	rl::math::Transform transformation;
	transformation.matrix().block(0, 0, 3, 3) = rotation.matrix().block(0, 0, 3, 3);
	transformation.matrix().block(0, 3, 3, 1) = translation.matrix().block(0, 3, 3, 1);

	return transformation;
}

#endif*/

#pragma once
#include "stdafx.h"


namespace robotender {
	class ROBOTENDERLIBRARY_API Kinematic {
		public:
			Kinematic();
			~Kinematic();
		public:
			vector<shared_ptr<Joint>> loadModel(std::string xml_file);
			rl::math::Transform generateTransform(const double rx, const double ry, const double rz, const double px, const double py, const double pz);
			rl::math::Transform generateTransform(rl::math::Vector6 vector);
			shared_ptr<Joint> getJoint(const int jointIndex);
			void setToolFrame(rl::math::Transform transform);
			rl::math::Transform getToolFrame();
			rl::math::Transform caculateRecursiveFK(Eigen::VectorXd vector, int startIdx, int num);
		private:
	;		vector<shared_ptr<Joint>> _joints;
			rl::math::Transform _tool_frame;
	};
}
