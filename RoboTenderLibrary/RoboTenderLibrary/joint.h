#pragma once
#ifndef _JOINT_H
#define _JOINT_H
#include "stdafx.h"

enum joint_type {prismatic, revolute};

namespace robotender {
	class Joint {
	public:
		Joint(const std::string name, const int joint_type);
		void SetDHParameter(double param_d = 0.0, double param_theta = 0.0, double param_a = 0.0, double param_alpha = 0.0);
		void GetDHParameter(double &param_d, double &param_theta, double &param_a, double &param_alpha);
		void SetLimit(double max, double min);
		void SetJointVal(double val);
		void GetJointVal(double &val);
		void GetDHTable(DHTable& table);
		DHParam GetDHParameter();
		std::string GetName();
	private:
		DHTable dhTable;
		std::string name;
		int joint_type;
		double max, min;
	};
};
#endif