#include "stdafx.h"
#include "rt1_kinematic.h"

RT1Kinematic::RT1Kinematic()
{

}

RT1Kinematic::~RT1Kinematic()
{

}


rl::math::Transform RT1Kinematic::caculateCloseFormFK(Eigen::VectorXd joint_vector)
{
	rl::math::Transform fkTransform;
	rl::math::Real theta234, theta23;
	rl::math::Real a0, a1, a2, a3, a4;
	rl::math::Real r11, r12, r13;
	rl::math::Real r21, r22, r23;
	rl::math::Real r31, r32, r33;
	rl::math::Real px, py, pz;
	DHParam param1, param2, param3, param4, param5;
	double d1, theta2, theta3, theta4, theta5;
	d1 = joint_vector.coeff(0);
	theta2 = joint_vector.coeff(1);
	theta3 = joint_vector.coeff(2);
	theta4 = joint_vector.coeff(3);
	theta5 = joint_vector.coeff(4);
	
	param1 = this->getJoint(0)->getDHParameter();
	param2 = this->getJoint(1)->getDHParameter();
	param3 = this->getJoint(2)->getDHParameter();
	param4 = this->getJoint(3)->getDHParameter();
	param5 = this->getJoint(4)->getDHParameter();
		
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
	fkTransform = fkTransform * this->getToolFrame();
	return fkTransform;
}
		

std::vector<Eigen::VectorXd> RT1Kinematic::caculateCloseFormIK(Eigen::VectorXd attitude_vector /*vector(rx, ry, rz, px, py, pz)*/)
{
	if (attitude_vector.count() != 6)
	{
		std::cout << "Invalid dimension" << std::endl;
		throw;
	}
	
	std::vector<Eigen::VectorXd> ik_results;
	rl::math::Transform fkTransform;
	rl::math::Transform worldTransform;
	rl::math::Transform T05;
	rl::math::Transform T03;
	rl::math::Transform T5t;
	rl::math::Rotation R03, R05, R35, R5t, R3t;
	std::vector<double> j2_results, j3_results, j4_results, j5_results;
	DHParam param1, param2, param3, param4, param5;
	double ex, ey, ez;
	double d1, d3, d4;
	double a2, a3;
	double theta2, theta3, theta4, theta5;
	worldTransform = this->generateTransform(attitude_vector);
		
	T05 = worldTransform * this->getToolFrame().inverse();
	ex = T05.matrix()(0,3);
	ey = T05.matrix()(1,3);
	ez = T05.matrix()(2,3);
	
	param1 = this->getJoint(0)->getDHParameter();
	param2 = this->getJoint(1)->getDHParameter();
	param3 = this->getJoint(2)->getDHParameter();
	param4 = this->getJoint(3)->getDHParameter();
	param5 = this->getJoint(4)->getDHParameter();

	
	d3 = param3.d;
	d4 = param4.d;
	a2 = param3.a;
	a3 = param4.a;
	
	// Solve Joint 1 
	// d1 = z-d3-d4;
	d1 = ez - d3 - d4;
	//cout << "d1: " << d1 << endl;

	// Solve Joint 3
	j3_results = this->j3_solver(ex, ey, a2, a3);
	
	for (int j3 = 0; j3 < j3_results.size(); j3++)
	{
		//cout << "Theta3_" << j3 << ": " << j3_ans[j3]*rl::math::RAD2DEG << endl;
		theta3 = j3_results.at(j3);
		
		// Solve Joint 2 
		j2_results = this->j2_solver(ex, a2, a3, theta3);
		for (int j2 = 0; j2 < j2_results.size(); j2++)
		{
			theta2 = j2_results.at(j2);
			//cout << "Theta2_" << j2 << ": " << theta2 * rl::math::RAD2DEG << endl;
				
			T03 = this->generate_t03(theta2, theta3, a2, d1, d3);
			R03 = T03.rotation();
			R05 = T05.rotation();
			R35 = R03.inverse() * R05;
			R5t = this->getToolFrame().rotation();
			R3t = R35 * R5t;
			//cout << "R3t: " << R3t.matrix() << endl;
			//cout << "T03: " << T03.matrix() << endl;
			if (this->position_verification(T05, T03, param4))
			{
				// Solve Joint 4 & 5
				j4_results = this->j4_solver(R3t);
				j5_results = this->j5_solver(R3t);
				for (int j4 = 0; j4 < j4_results.size(); j4++)
				{
					theta4 = j4_results.at(j4);
					for (int j5 = 0; j5 < j5_results.size(); j5++)
					{
						theta5 = j5_results.at(j5);
						Eigen::VectorXd joint_vector;
						joint_vector << d1, theta2, theta3, theta4, theta5;

						fkTransform = this->caculateCloseFormFK(joint_vector);
						if (MathCommon::equalWithTol(fkTransform, worldTransform))
						{
							ik_results.push_back(joint_vector);
						}
					}
				}
			}
		}
	}
	return ik_results;

}


std::vector<double> RT1Kinematic::j3_solver(const double x, const double y, const double a2, double a3)
{
	std::vector<double> result_vector;
	double r;
	double theta3_rad;
	double rad;

	r = pow(x, 2.0) + pow(y, 2.0);
	if (abs(r - pow(a3, 2.0) - pow(a2, 2.0)) <= abs(2 * a2*a3))
	{
		rad = ((r - pow(a3, 2.0) - pow(a2, 2.0)) / (2 * a2*a3));
		theta3_rad = acos(rad);
		result_vector.push_back(theta3_rad);
		theta3_rad = -acos(rad);
		result_vector.push_back(theta3_rad);
		return result_vector;
	}
	else {
		cout << "No solution about Theta3" << endl;
		throw;
	}
}


std::vector<double> RT1Kinematic::j2_solver(const double x, const double a2, double a3, const double theta3)
{
	std::vector<double> result_vector;
	MathCommon mathCommon;
	double f1, f2;
	double det, r, theta2;
	f1 = a3 * cos(theta3) + a2;
	f2 = a3 * sin(theta3);

	if (MathCommon::equalWithTol(f1 + x, 0))
	{
		result_vector.push_back(180.0*rl::math::DEG2RAD);
		result_vector.push_back(0.0);
		return result_vector;
	}
	else {
		det = pow(f2, 2) + pow(f1, 2) - pow(x, 2);
		if (det >= 0.0)
		{
			r = (-f2 + sqrt(det)) / (f1 + x);
			theta2 = 2 * atan(r);
			result_vector.push_back(theta2);

			r = (-f2 - sqrt(det)) / (f1 + x);
			theta2 = 2 * atan(r);
			result_vector.push_back(theta2);
			return result_vector;
		}
	}
	cout << "There have no solution about theta2" << endl;
	throw;
}


std::vector<double> RT1Kinematic::j4_solver(const rl::math::Rotation R3t)
{
	std::vector<double> result_vector;
	double val;

	val = acos(R3t.matrix()(0, 0)) - (270.0*rl::math::DEG2RAD); // acos(r11) - 270(degree)
	result_vector.push_back(val);
	val = (-acos(R3t.matrix()(0, 0))) - (270.0*rl::math::DEG2RAD); // acos(r11) - 270(degree)
	result_vector.push_back(val);
	return result_vector;
}


std::vector<double> RT1Kinematic::j5_solver(const rl::math::Rotation R3t)
{
	std::vector<double> result_vector;
	double val;
		
	val = acos(R3t.matrix()(2, 2)); // acos(r33)
	result_vector.push_back(val);
	val = -acos(R3t.matrix()(2, 2)); // acos(r33)
	result_vector.push_back(val);
	return result_vector;
}


rl::math::Transform RT1Kinematic::generate_t03(const double theta2, const double theta3, const double a2, const double d1, const double d3)
{
	const double theta23 = theta2 + theta3;
	rl::math::Transform T03;
	T03.matrix() << cos(theta23), -sin(theta23), 0, a2*cos(theta2),
		sin(theta23), cos(theta23), 0, a2*sin(theta2),
		0, 0, 1, (d1 + d3),
		0, 0, 0, 1;
	return T03;
}


bool RT1Kinematic::position_verification(const rl::math::Transform T05, rl::math::Transform T03, DHParam param4)
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

