#include "stdafx.h"
#include "RT1.h"
#include "math_common.h"

typedef struct
{
	int nPosition; //Position
	int nVelocity; //Velocity
	DWORD dwTime;  //Time
}PVT_T;


RT1::RT1(const char* xmlFile) : kinematic(xmlFile)
{
	//this->pPD6 = new PusicoDriver(6, 0);
	//this->pPD7 = new PusicoDriver(7, 1);
	//this->pPD8 = new PusicoDriver(8, 1);
	this->toolTransform.matrix() << 0, 1, 0, 0,
									0, 0, 1, 0,
									1, 0, 0, 100,
									0, 0, 0, 1;
}

RT1::~RT1()
{

}

void RT1::GoHome()
{
	//this->pPD8->GoHome(1, 4000, 300, 320);
	//this->pPD7->GoHome(1, 4000, 300, 320);
	//this->pPD6->GoHome(1, 25600, 6000, 3000);
	//this->pPD8->GoHome(1, 4000, 300, 320, 4793);
	//this->pPD8->StartAbsStep(0);
	//this->pPD7->GoHome(1, 4000, 300, 320, 989);
	//this->pPD7->StartAbsStep(0);
}

void RT1::TestFunction()
{
	double d1, theta2, theta3, theta4, theta5;
	IKResult result[10];
	int result_num;
	
	//this->pPD8->GoHome(1, 4000, 300, 320, 4793);
	//this->pPD8->StartAbsStep(0);
		
	//this->pPD7->GoHome(1, 4000, 300, 320, 989);
	//this->pPD7->StartAbsStep(0);
	//this->pPD7->SetExtStopEnable(0);
	
	
	this->GetIKTransformC(-30.0, 0.0, 40.0, 300.0, 100.0, 100.0, result, result_num);
	for (int i = 0; i < result_num; i++)
	{
			d1 = result[i].d1;
			theta2 = result[i].theta2;
			theta3 = result[i].theta3;
			theta4 = result[i].theta4;
			theta5 = result[i].theta5;

			cout << endl << "D1: " << d1 << " Theta2: " << theta2*rl::math::RAD2DEG << " Theta3: " << theta3*rl::math::RAD2DEG << " Theta4: " << theta4*rl::math::RAD2DEG << " Theta5: " << theta5*rl::math::RAD2DEG << endl;
			cout << endl << endl;
				
			//this->pPD7->GoPosition(theta2*rl::math::RAD2DEG, 5.5, 1);
			cout << "Finished Axis 2" << endl;
			//this->pPD8->GoPosition(theta3*rl::math::RAD2DEG, 3.0, 0);
			cout << "Finished Axis 3" << endl;
			Sleep(3000);
	}

	this->GetIKTransformC(-30.0, 0.0, 40.0, 400.0, 100.0, 100.0, result, result_num);
	for (int i = 0; i < result_num; i++)
	{
			d1 = result[i].d1;
			theta2 = result[i].theta2;
			theta3 = result[i].theta3;
			theta4 = result[i].theta4;
			theta5 = result[i].theta5;

			cout << endl << "D1: " << d1 << " Theta2: " << theta2*rl::math::RAD2DEG << " Theta3: " << theta3*rl::math::RAD2DEG << " Theta4: " << theta4*rl::math::RAD2DEG << " Theta5: " << theta5*rl::math::RAD2DEG << endl;
			cout << endl << endl;
				
			//this->pPD7->GoPosition(theta2*rl::math::RAD2DEG, 5.5, 1);
			//cout << "Finished Axis 2" << endl;
			//this->pPD8->GoPosition(theta3*rl::math::RAD2DEG, 3.0, 0);
			//cout << "Finished Axis 3" << endl;
			Sleep(3000);
	}

	//this->pPD8->GoPosition(90, 3.0, 0);
	//this->pPD7->GoPosition(90, 5.5, 1);
}

void RT1::Cablibration()
{
/*	this->pPD8->SetMotorPos(0);
	//this->pPD7->SetMotorPos(0);
	
	this->pPD8->SetMaxSpeed(300);
	//this->pPD7->SetMaxSpeed(300);
	
	this->pPD8->SetDir(1);
	//this->pPD7->SetDir(1);
	
	// Go Home
	this->pPD8->SetVelocityMode();
	//this->pPD7->SetVelocityMode();
	
	this->pPD8->StartRelStep(2000, FALSE);
	//this->pPD7->StartRelStep(2000, FALSE);


	this->pPD8->GetMotorPos(&this->pd8_c);
	cout << "POS(8): " << this->pd8_c << endl;
	//this->pPD7->GetMotorPos(&this->pd7_c);
	//cout << "POS(7): " << this->pd7_c << endl;

	this->pPD8->SetMotorPos(0);
	//this->pPD7->SetMotorPos(0);
	
	this->pPD8->SetPosMode();
	//this->pPD7->SetPosMode();

	this->pPD8->SetDir(0);
	//this->pPD7->SetDir(0);

	this->pPD8->ClearExtStopFlag();
	//this->pPD7->ClearExtStopFlag();


	this->pPD8->StartAbsStep(-(this->pd8_c), FALSE);
	//this->pPD7->StartAbsStep(-(this->pd7_c), FALSE);
	this->pPD8->StartAbsStep(-(this->pd8_c), FALSE);
	//this->pPD7->StartAbsStep(-(this->pd7_c), FALSE);
	
	//int p8, p7;
	int p8;
	this->pPD8->GetMotorPos(&p8);
	cout << "Correct POS(8): " << p8 << endl;
	//this->pPD7->GetMotorPos(&p7);
	//cout << "Correct POS(7): " << p7 << endl;
*/	
}

void RT1::PVT()
{
/*	this->pPD8->SetGroupID(66);
	this->pPD7->SetGroupID(66);
	this->pPD8->SetPVTMode(PVT_MODE1);
	this->pPD7->SetPVTMode(PVT_MODE1);
	this->pPD8->SetMaxPVTNum(10);
	this->pPD7->SetMaxPVTNum(10);
*/
}

rl::math::Transform RT1::GetFKTransformC(const double d1, const double theta2, const double theta3, const double theta4, const double theta5)
{
	
	rl::math::Transform fkTransform;
	rl::math::Real theta234, theta23;
	rl::math::Real a0, a1, a2, a3, a4;
	rl::math::Real r11, r12, r13;
	rl::math::Real r21, r22, r23;
	rl::math::Real r31, r32, r33;
	rl::math::Real px, py, pz;
	DHParam param1, param2, param3, param4, param5;
	param1 = this->kinematic.GetJoint(0)->getDHParameter();
	param2 = this->kinematic.GetJoint(1)->getDHParameter();
	param3 = this->kinematic.GetJoint(2)->getDHParameter();
	param4 = this->kinematic.GetJoint(3)->getDHParameter();
	param5 = this->kinematic.GetJoint(4)->getDHParameter();
		
	a0 = param1.a;
	a1 = param2.a;
	a2 = param3.a;
	a3 = param4.a;
	a4 = param5.a;
	
	theta234 = theta2 + theta3 + theta4;
	theta23 = theta2 + theta3;
	
	r11 = cos(theta234) * cos(theta5);
	r12 = -cos(theta234) * sin(theta5);
	r13 = sin(theta234);
	r21 = sin(theta234) * cos(theta5);
	r22 = -sin(theta234) * sin(theta5);
	r23 = -cos(theta234);
	r31 = sin(theta5);
	r32 = cos(theta5);
	r33 = 0;
	px = (a3*cos(theta23)) + (a2*cos(theta2));
	py = (a3*sin(theta23)) + (a2*sin(theta2));
	pz = d1 + param3.d + param4.d;
	
	fkTransform.matrix() << r11, r12, r13, px,
							r21, r22, r23, py,
							r31, r32, r33, pz,
			0.0, 0.0, 0.0, 1.0;
	fkTransform = fkTransform * this->toolTransform;
	return fkTransform;
}


void RT1::ControlJoint(const double j1, const double j2, const double j3, const double j4, const double j5)
{
	this->kinematic.GetJoint(0)->setJointVal(j1); // prismatic
	this->kinematic.GetJoint(1)->setJointVal(j2*rl::math::DEG2RAD);
	this->kinematic.GetJoint(2)->setJointVal(j3*rl::math::DEG2RAD);
	this->kinematic.GetJoint(3)->setJointVal(j4*rl::math::DEG2RAD);
	this->kinematic.GetJoint(4)->setJointVal(j5*rl::math::DEG2RAD);
}


bool RT1::GetIKTransformC(const double rx, const double ry, const double rz, const double px, const double py, double pz, IKResult *result, int &result_num)
{
	rl::math::Transform fkTransform;
	rl::math::Transform worldTransform;
	rl::math::Transform T05;
	rl::math::Transform T03;
	rl::math::Transform T5t;
	rl::math::Rotation R03, R05, R35, R5t, R3t;
	DHParam param1, param2, param3, param4, param5;
	double ex, ey, ez;
	double d1, d3, d4;
	double a2, a3;
	double j2_ans[2], j3_ans[2], j4_ans[2], j5_ans[2];
	int j2_ans_num, j3_ans_num, j4_ans_num, j5_ans_num;
	double theta2, theta3, theta4, theta5;
	result_num = 0;
	worldTransform = this->kinematic.GenerateTransform(rx, ry, rz, px, py, pz);
		
	T05 = worldTransform * this->toolTransform.inverse();
	ex = T05.matrix()(0,3);
	ey = T05.matrix()(1,3);
	ez = T05.matrix()(2,3);
	
	param1 = this->kinematic.GetJoint(0)->getDHParameter();
	param2 = this->kinematic.GetJoint(1)->getDHParameter();
	param3 = this->kinematic.GetJoint(2)->getDHParameter();
	param4 = this->kinematic.GetJoint(3)->getDHParameter();
	param5 = this->kinematic.GetJoint(4)->getDHParameter();

	
	d3 = param3.d;
	d4 = param4.d;
	a2 = param3.a;
	a3 = param4.a;
	
	// Solve d1
	// d1 = z-d3-d4;
	d1 = ez - d3 - d4;
	//cout << "d1: " << d1 << endl;
	
	this->j3Solver(ex, ey, a2, a3, j3_ans, j3_ans_num);
	if (j3_ans_num == 0)
	{
		cout << "The theta3 have no solution!!" << endl;
		return false;
	}
	
	for (int j3 = 0; j3 < j3_ans_num; j3++)
	{
		//cout << "Theta3_" << j3 << ": " << j3_ans[j3]*rl::math::RAD2DEG << endl;
		theta3 = j3_ans[j3];
		
		this->j2Solver(ex, a2, a3, theta3, j2_ans, j2_ans_num);
		for (int j2 = 0; j2 < j2_ans_num; j2++)
		{
			theta2 = j2_ans[j2];
			//cout << "Theta2_" << j2 << ": " << theta2 * rl::math::RAD2DEG << endl;
				
			T03 = this->generateT03(theta2, theta3, a2, d1, d3);
			R03 = T03.rotation();
			R05 = T05.rotation();
			R35 = R03.inverse() * R05;
			R5t = this->toolTransform.rotation();
			R3t = R35 * R5t;
			//cout << "R3t: " << R3t.matrix() << endl;
			//cout << "T03: " << T03.matrix() << endl;
			if (this->positionVerification(T05, T03, param4))
			{
				this->j4Solver(R3t, j4_ans, j4_ans_num);
				this->j5Solver(R3t, j5_ans, j5_ans_num);
				for (int j4 = 0; j4 < j4_ans_num; j4++)
				{
					theta4 = j4_ans[j4];
					for (int j5 = 0; j5 < j5_ans_num; j5++)
					{
						theta5 = j5_ans[j5];
						fkTransform = this->GetFKTransformC(d1, theta2, theta3, theta4, theta5);
						if (MathCommon::equalWithTol(fkTransform, worldTransform))
						{
							result[result_num].d1 = d1;
							result[result_num].theta2 = theta2;
							result[result_num].theta3 = theta3;
							result[result_num].theta4 = theta4;
							result[result_num].theta5 = theta5;
							result_num++;
						}
					}
				}
			}
		}
	}
	return true;
	// Return All solution
}


void RT1::j3Solver(const double x, const double y, const double a2, double a3, double* ans, int& ans_num)
{
	double r;
	double theta3_rad;
	double rad;
	
	ans_num = 0;
	r = pow(x, 2.0) + pow(y, 2.0);
	if (abs(r - pow(a3, 2.0) - pow(a2, 2.0)) <= abs(2 * a2*a3))
	{
		rad = ((r - pow(a3, 2.0) - pow(a2, 2.0)) / (2 * a2*a3));
		theta3_rad = acos(rad);
		ans[ans_num] = theta3_rad;
		ans_num++;
		theta3_rad = -acos(rad);
		ans[ans_num] = theta3_rad;
		ans_num++;
		//cout << "Theta3_1: " << theta3_rad * rl::math::RAD2DEG;
	}
	else {
		cout << "No solution about Theta3" << endl;
	}
}


void RT1::j2Solver(const double x, const double a2, double a3, const double theta3, double *ans, int &ans_num)
{
	MathCommon mathCommon;
	double f1, f2;
	double det, r, theta2;
	f1 = a3 * cos(theta3) + a2;
	f2 = a3 * sin(theta3);
	
	ans_num = 0;
	
	if (MathCommon::equalWithTol(f1 + x, 0))
	{
		ans[ans_num] = 180.0*rl::math::DEG2RAD;
		ans_num++;
		ans[ans_num] = 0.0;
		ans_num++;
		return;
	}
	else {
		det = pow(f2, 2) + pow(f1, 2) - pow(x, 2);
		if (det >= 0.0)
		{
			r = (-f2 + sqrt(det)) / (f1 + x);
			theta2 = 2 * atan(r);
			ans[ans_num] = theta2;
			ans_num++;
	
			r = (-f2 - sqrt(det)) / (f1 + x);
			theta2 = 2 * atan(r);
			ans[ans_num] = theta2;
			ans_num++;
			return;
		}
	}
	cout << "There have no solution about theta2" << endl;
	return;
}


void RT1::j4Solver(const rl::math::Rotation R3t, double *ans, int &ans_num)
{
	ans_num = 0;
	ans[ans_num] = acos(R3t.matrix()(0, 0)) - (270.0*rl::math::DEG2RAD); // acos(r11) - 270(degree)
	ans_num++;
	ans[ans_num] = (-acos(R3t.matrix()(0, 0))) - (270.0*rl::math::DEG2RAD); // acos(r11) - 270(degree)
	ans_num++;
}

void RT1::j5Solver(const rl::math::Rotation R3t, double *ans, int &ans_num)
{
	ans_num = 0;
	ans[ans_num] = acos(R3t.matrix()(2, 2)); // acos(r33)
	ans_num++;
	ans[ans_num] = -acos(R3t.matrix()(2, 2)); // acos(r33)
	ans_num++;
}


rl::math::Transform RT1::generateT03(const double theta2, const double theta3, const double a2, const double d1, const double d3)
{
	const double theta23 = theta2 + theta3;
	rl::math::Transform T03;
	T03.matrix() << cos(theta23), -sin(theta23), 0, a2*cos(theta2),
					sin(theta23), cos(theta23), 0, a2*sin(theta2),
					0, 0, 1, (d1 + d3),
					0, 0, 0, 1;
	return T03;
}
	


bool RT1::positionVerification(const rl::math::Transform T05, rl::math::Transform T03, DHParam param4)
{
	rl::math::Matrix p(4, 1);
	rl::math::Matrix p4Org(4, 1);
	rl::math::Matrix pWorld(4, 1);

	double d4 = param4.d;
	double a3 = param4.a;
	p.matrix() << a3, 0, d4, 1;
	p4Org = T03.matrix() * p;
	pWorld = T05.matrix().block(0, 3, 4, 1);
	return MathCommon::equalWithTol(p4Org, pWorld);
} 