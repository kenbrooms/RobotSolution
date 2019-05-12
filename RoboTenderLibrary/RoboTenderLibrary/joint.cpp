#include "stdafx.h"
using namespace robotender;

Joint::Joint(const std::string name, const int joint_type)
{
	this->name = name;
	this->joint_type = joint_type;
	this->dhTable.matrix() = rl::math::Matrix44::Identity(4, 4);
}


void Joint::SetDHParameter(double param_d, double param_theta, double param_a, double param_alpha)
{
	double val;
	if (this->joint_type == prismatic)
	{
		val = param_d;
	}
	else {
		val = param_theta * rl::math::RAD2DEG;
	}
	
	if (val >= min && val <= max)
	{
		this->dhTable.fromDenavitHartenbergCraig(param_d, param_theta, param_a, param_alpha);
	}
	else {
		throw ("Invalid value about parameter!");
	}
}

void Joint::GetDHParameter(double &param_d, double &param_theta, double &param_a, double &param_alpha)
{
	this->dhTable.toDenavitHartenbergCraig(param_d, param_theta, param_a, param_alpha);
}

DHParam Joint::GetDHParameter()
{
	DHParam param;
	this->dhTable.toDenavitHartenbergCraig(param.d, param.theta, param.a, param.alpha);
	return param;
}
	
void Joint::SetLimit(double max, double min)
{
	if (max > min)
	{
		this->max = max;
		this->min = min;
	}
}


void Joint::SetJointVal(double val)
{
	double param_d, param_theta, param_a, param_alpha;
	this->GetDHParameter(param_d, param_theta, param_a, param_alpha);
	if (this->joint_type == prismatic)
	{
		param_d = val;
	}
	else {
		param_theta = val;
	}
	this->SetDHParameter(param_d, param_theta, param_a, param_alpha);
}

void Joint::GetJointVal(double &val)
{
	double param_d, param_theta, param_a, param_alpha;
	this->GetDHParameter(param_d, param_theta, param_a, param_alpha);
	if (this->joint_type == prismatic)
	{
		val = param_d;
	}
	else {
		val = param_theta;
	}
}

void Joint::GetDHTable(DHTable& table)
{
	table = this->dhTable;
}
		
std::string Joint::GetName()
{
	return this->name;
}
