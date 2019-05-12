#ifndef _MATH_COMMON_H
#define _MATH_COMMON_H

#define TOLERANCE 0.00000001
namespace robotender {
	class MathCommon {

	public:
		MathCommon();
		virtual ~MathCommon();
	public:
		//bool equalWithTol(::rl::math::Transform a, ::rl::math::Transform b, const double tol=0.0000001);
		static bool equalWithTol(::rl::math::Transform a, ::rl::math::Transform b, const double tol = TOLERANCE);
		static bool equalWithTol(rl::math::Matrix a, rl::math::Matrix b, ::rl::math::Real tol = TOLERANCE);
		static bool equalWithTol(const double a, const double b, const double tol = TOLERANCE);
	};
};
#endif
