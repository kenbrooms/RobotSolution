#pragma once
#include "stdafx.h"
#include "kinematic.h"

namespace robotender {
	class ROBOTENDERLIBRARY_API RT1Kinematic : public Kinematic {
		public:	
			RT1Kinematic();
			~RT1Kinematic();
			rl::math::Transform caculateCloseFormFK(Eigen::VectorXd joint_vector);
			std::vector<Eigen::VectorXd> caculateCloseFormIK(Eigen::VectorXd attitude_vector);
		
		private:	
			std::vector<double> j3_solver(const double x, const double y, const double a2, double a3);
			std::vector<double> j2_solver(const double x, const double a2, double a3, const double theta3);
			std::vector<double> j4_solver(const rl::math::Rotation R3t);
			std::vector<double> j5_solver(const rl::math::Rotation R3t);
			bool position_verification(const rl::math::Transform T05, rl::math::Transform T03, DHParam param4);
			rl::math::Transform generate_t03(const double theta2, const double theta3, const double a2, const double d1, const double d3);
	};
}
