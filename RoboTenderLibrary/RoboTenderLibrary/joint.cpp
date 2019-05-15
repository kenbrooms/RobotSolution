#include "stdafx.h"
#include "joint.h"
using namespace robotender;

Joint::Joint(const std::string joint_name, const int joint_type)
{
	this->_name = joint_name;
	this->_joint_type = joint_type;
	this->_dhTable.matrix() = rl::math::Matrix44::Identity(4, 4);
}


std::string Joint::name()
{
	return this->_name;
}

void Joint::setDHParameter(double param_d, double param_theta, double param_a, double param_alpha)
{
	double val;
	if (this->_joint_type == prismatic)
	{
		val = param_d;
	}
	else {
		val = param_theta * rl::math::RAD2DEG;
	}
	
	if (val >= this->_min && val <= this->_max)
	{
		this->_dhTable.fromDenavitHartenbergCraig(param_d, param_theta, param_a, param_alpha);
	}
	else {
		throw ("Invalid value about parameter!");
	}
}

void Joint::getDHParameter(double &param_d, double &param_theta, double &param_a, double &param_alpha)
{
	this->_dhTable.toDenavitHartenbergCraig(param_d, param_theta, param_a, param_alpha);
}

DHParam Joint::getDHParameter()
{
	DHParam param;
	this->_dhTable.toDenavitHartenbergCraig(param.d, param.theta, param.a, param.alpha);
	return param;
}
	
void Joint::setLimit(double max, double min)
{
	if (max > min)
	{
		this->_max = max;
		this->_min = min;
	}
}


void Joint::setJointVal(double val)
{
	double param_d, param_theta, param_a, param_alpha;
	this->getDHParameter(param_d, param_theta, param_a, param_alpha);
	if (this->_joint_type == prismatic)
	{
		param_d = val;
	}
	else {
		param_theta = val;
	}
	this->setDHParameter(param_d, param_theta, param_a, param_alpha);
}

double Joint::getJointVal()
{
	double param_d, param_theta, param_a, param_alpha;
	this->getDHParameter(param_d, param_theta, param_a, param_alpha);
	if (this->_joint_type == prismatic)
	{
		return param_d;
	}
	else {
		return param_theta;
	}
}

DHTable Joint::getDHTable()
{
	return this->_dhTable;
}
