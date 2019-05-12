#include "stdafx.h"

DHTable::DHTable()
{

}

DHTable::~DHTable()
{
	
}
	
void DHTable::fromDenavitHartenbergCraig(const double d, const double theta, const double a, const double alpha)
{
	this->a = a;
	this->alpha = alpha;
	this->theta = theta;
	this->d = d;

	rl::math::Real c_theta = cos(this->theta);
	rl::math::Real s_theta = sin(this->theta);
	rl::math::Real c_alpha = cos(this->alpha);
	rl::math::Real s_alpha = sin(this->alpha);
	
	rl::math::Real r11 = c_theta;
	rl::math::Real r12 = -s_theta;
	rl::math::Real r13 = 0.0;
	rl::math::Real r14 = this->a;
	
	rl::math::Real r21 = s_theta*c_alpha;
	rl::math::Real r22 = c_theta*c_alpha;
	rl::math::Real r23 = -s_alpha;
	rl::math::Real r24 = -s_alpha*this->d;

	rl::math::Real r31 = s_theta*s_alpha;
	rl::math::Real r32 = c_theta*s_alpha;
	rl::math::Real r33 = c_alpha;
	rl::math::Real r34 = c_alpha*this->d;

	this->matrix() << r11, r12, r13, r14,
		r21, r22, r23, r24,
		r31, r32, r33, r34,
		0.0, 0.0, 0.0, 1.0;
}

void DHTable::toDenavitHartenbergCraig(double &d, double &theta, double &a, double &alpha)
{
	d = this->d;
	theta = this->theta;
	a = this->a;
	alpha = this->alpha;
}
