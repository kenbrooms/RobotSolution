#pragma once
#include "stdafx.h"

enum joint_type {prismatic, revolute};

namespace robotender {
	class ROBOTENDERLIBRARY_API Joint {
	public:
		Joint(const std::string joint_name, const int joint_type);
		std::string name();
		void setDHParameter(double param_d = 0.0, double param_theta = 0.0, double param_a = 0.0, double param_alpha = 0.0);
		void getDHParameter(double &param_d, double &param_theta, double &param_a, double &param_alpha);
		void setLimit(double max, double min);
		void setJointVal(double val);
		double getJointVal();
		DHTable getDHTable();
		DHParam getDHParameter();
	private:
		DHTable _dhTable;
		std::string _name;
		int _joint_type;
		double _max, _min;
		
	};
};