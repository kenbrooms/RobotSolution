#pragma once

#include <rl/xml/Document.h>
#include <rl/xml/DomParser.h>
#include <rl/xml/Stylesheet.h>
#include "kinematic.h"

struct IKResult {
	double d1;
	double theta2;
	double theta3;
	double theta4;
	double theta5;
};

class RT1
{
public:
	RT1(const char* xmlFile);
	~RT1();
	void GoHome();
	void Cablibration();
	void PVT();
	void ControlJoint(const double j1, const double j2, const double j3, const double j4, const double j5);
	void TestFunction();
public: // inhired from kinematic class
	rl::math::Transform GetFKTransformC(const double d1, const double theta2, const double theta3, const double theta4, const double theta5);
	bool GetIKTransformC(const double rx, const double ry, const double rz, const double px, const double py, double pz, IKResult *result, int &result_num);
private:
	void j3Solver(const double x, const double y, const double a2, double a3, double *ans, int &ans_num);
	void j2Solver(const double x, const double a2, double a3, const double theta3, double *ans, int &ans_num);
	void j4Solver(const rl::math::Rotation R3t, double *ans, int &ans_num);
	void j5Solver(const rl::math::Rotation R3t, double *ans, int &ans_num);
	bool positionVerification(const rl::math::Transform T05, rl::math::Transform T03, DHParam param4);
	rl::math::Transform generateT03(const double theta2, const double theta3, const double a2, const double d1, const double d3);

private:
	rl::math::Transform toolTransform;
	Kinematic<int> kinematic;
private:
	//PusicoDriver *pPD6;
	//PusicoDriver *pPD7;
	//PusicoDriver *pPD8;
private:
	int pd6_c;
	int pd7_c;
	int pd8_c;
};
