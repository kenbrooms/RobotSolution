#include "stdafx.h"
#include "kinematic.h"

Kinematic::Kinematic()
{

}

Kinematic::~Kinematic()
{

}

vector<shared_ptr<Joint>> Kinematic::loadModel(std::string xml_file)
{
	shared_ptr<Joint> joint;
	DHTable dhTable;
	double d, theta, a, alpha;
	double theta_rad, alpha_rad;

	// Setup Joint1 parameter
	joint =shared_ptr<Joint>(new Joint("Joint1", prismatic));
	joint->setLimit(450.0, 0.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	joint->setDHParameter(d, theta_rad, a, alpha_rad);
	this->_joints.push_back(joint);


	// Setup Joint2 parameter
	joint =shared_ptr<Joint>(new Joint("Joint2", revolute));
	joint->setLimit(180.0, -180.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	joint->setDHParameter(d, theta_rad, a, alpha_rad);
	this->_joints.push_back(joint);


	// Setup Joint3 parameter
	joint =shared_ptr<Joint>(new Joint("Joint3", revolute));
	joint->setLimit(150.0, -150.0);

	d = 30.0; theta = 0.0; a = 280.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	joint->setDHParameter(d, theta_rad, a, alpha_rad);
	this->_joints.push_back(joint);


	// Setup Joint4 parameter
	joint =shared_ptr<Joint>(new Joint("Joint4", revolute));
	joint->setLimit(150.0, -150.0);

	d = -30.0; theta = 0.0; a = 210.0; alpha = 0.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	joint->setDHParameter(d, theta_rad, a, alpha_rad);
	this->_joints.push_back(joint);


	// Setup Joint5 parameter
	joint =shared_ptr<Joint>(new Joint("Joint5", revolute));
	joint->setLimit(180.0, -180.0);

	d = 0.0; theta = 0.0; a = 0.0; alpha = 90.0;
	alpha_rad = alpha * rl::math::DEG2RAD;
	theta_rad = theta * rl::math::DEG2RAD;
	joint->setDHParameter(d, theta_rad, a, alpha_rad);
	this->_joints.push_back(joint);

	return this->_joints;
}


rl::math::Transform Kinematic::generateTransform(rl::math::Vector6 vector)
{
	// vector.coeff(0) = rx;
	// vector.coeff(1) = ry;
	// vector.coeff(2) = rz;
	// vector.coeff(3) = px;
	// vector.coeff(4) = py;
	// vector.coeff(5) = pz;
	double rx_rad = vector.coeff(0) * rl::math::DEG2RAD;
	double ry_rad = vector.coeff(1) * rl::math::DEG2RAD;
	double rz_rad = vector.coeff(2) * rl::math::DEG2RAD;
	rl::math::Transform rotation(rl::math::AngleAxis(rz_rad, rl::math::Vector3::UnitZ()) *
		rl::math::AngleAxis(ry_rad, rl::math::Vector3::UnitY()) *
		rl::math::AngleAxis(rx_rad, rl::math::Vector3::UnitX())
	);
	
	rl::math::Transform translation(rl::math::Translation(vector.coeff(3), vector.coeff(4), vector.coeff(5)));
	rl::math::Transform transformation;
	transformation.matrix().block(0, 0, 3, 3) = rotation.matrix().block(0, 0, 3, 3);
	transformation.matrix().block(0, 3, 3, 1) = translation.matrix().block(0, 3, 3, 1);
	return transformation;
}

rl::math::Transform Kinematic::generateTransform(const double rx, const double ry, const double rz, const double px, const double py, const double pz)
{
	rl::math::Vector6 v;
	v << rx, ry, rz, px, py, pz;
	return this->generateTransform(v);
}

shared_ptr<Joint> Kinematic::getJoint(const int jointIndex)
{
	vector<shared_ptr<Joint>>::iterator it;
	it = this->_joints.begin();
	std::advance(it, jointIndex);
	return *it;
}

void Kinematic::setToolFrame(rl::math::Transform transform)
{
	this->_tool_frame = transform;
}

rl::math::Transform Kinematic::getToolFrame()
{
	return this->_tool_frame;
}


rl::math::Transform Kinematic::caculateRecursiveFK(Eigen::VectorXd vector, int startIdx, int num)
{
	shared_ptr<Joint> joint;
	rl::math::Transform transform;
	transform =	rl::math::Matrix44::Identity();

	if (num <= 0 || num > vector.count() || startIdx < 0 || startIdx >= vector.count())
	{
		std::cout << "Invalid index or num" << std::endl;
		throw;
	}
	
	for (int i = 0; i < vector.count(); i++)
	{
		this->getJoint(i)->setJointVal(vector.coeff(i));
		transform = transform * this->getJoint(i)->getDHTable();
	}
	return transform;
}
