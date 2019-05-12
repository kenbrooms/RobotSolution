#ifndef DH_TABLE_H 
#define DH_TABLE_H
#include "stdafx.h"

using namespace rl::math;
using namespace robotender;

struct DHParam {
	double d;
	double theta;
	double a;
	double alpha;
};

class DHTable : public rl::math::Transform, public MathCommon {
public:	
	DHTable();
	virtual ~DHTable();

public:
	void fromDenavitHartenbergCraig(const double d, const double theta, const double a, const double alpha);
	void toDenavitHartenbergCraig(double &d, double &theta, double &a, double &alpha);

public:
	rl::math::Real a;
	rl::math::Real alpha;
	rl::math::Real theta;
	rl::math::Real d;
};

#endif