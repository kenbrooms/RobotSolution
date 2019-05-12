#pragma once
#include "stdafx.h"

namespace robotender {
	class ROBOTENDERLIBRARY_API AlgebraData {
		public:
			AlgebraData();
			~AlgebraData();
		public:
			rl::math::Vector3 positionVector;
			
			double position;
			double acceleration; // dt = duration time, at = acceleration time
			double p0;
			double v0;
			double t0;
	};
}