

//#pragma once
//#pragma message("kinematic.h --> Linking with libxml2.lib")
//#pragma comment(lib,"libxml2.lib")

#include "pch.h"

/*
#include <iostream>
#include <cmath>
#include <list> 
#include <iterator> 

#include <rl/math/Transform.h>
#include <rl/math/Unit.h>
#include <rl/xml/DomParser.h>


//#include "kinematic.h"
#include "xml_doc.h"

using namespace std;

template<class T>
Kinematic<T>::Kinematic(const char* xmlFile)
{
	this->xmlFile = xmlFile;
	this->loadModel(this->xmlFile);
}

template<class T>
Kinematic<T>::~Kinematic()
{
	list <Joint*> ::iterator it;
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
	jointPtr->SetLimit(450.0, 0.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->SetDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	// Setup Joint2 parameter
	jointPtr = new Joint("Joint2", revolute);
	jointPtr->SetLimit(180.0, -180.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->SetDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	// Setup Joint3 parameter
	jointPtr = new Joint("Joint3", revolute);
	jointPtr->SetLimit(150.0, -150.0);

	d = 30.0; theta = 0.0; a = 280.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->SetDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);


	// Setup Joint4 parameter
	jointPtr = new Joint("Joint4", revolute);
	jointPtr->SetLimit(150.0, -150.0);

	d = -30.0; theta = 0.0; a = 210.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->SetDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);
	
	
	// Setup Joint5 parameter
	jointPtr = new Joint("Joint5", revolute);
	jointPtr->SetLimit(180.0, -180.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 90.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	jointPtr->SetDHParameter(d, theta_rad, a, alpha_rad);
	this->jointList.push_back(jointPtr);

		
	return true;
}

template<class T>
Joint* Kinematic<T>::GetJoint(const int jointIndex)
{
	list <Joint*> ::iterator it;

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
}*/