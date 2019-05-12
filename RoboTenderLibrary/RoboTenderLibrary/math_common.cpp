#include "stdafx.h"
using namespace robotender;

MathCommon::MathCommon() 
{

}

MathCommon::~MathCommon() 
{

}


bool MathCommon::equalWithTol(::rl::math::Transform a, ::rl::math::Transform b, ::rl::math::Real tol)
{
	rl::math::Transform tol_t;
	bool r;
	
	if (a.matrix().size() != b.matrix().size())
	{
		throw "Those dimension of matrics is not equal!";
	}
	tol_t = a;
	tol_t = tol_t.matrix().Constant(tol);

	r = ((a.matrix()-b.matrix()).cwiseAbs().matrix().array() <= tol_t.matrix().array()).all();
	return r;
}

bool MathCommon::equalWithTol(rl::math::Matrix a, rl::math::Matrix b, ::rl::math::Real tol)
{
	rl::math::Matrix tol_t(a);
	bool r = true;
	
	if (a.size() != b.size())
	{
		throw "Those dimension of matrics is not equal!";
	}
	//tol_t.matrix<>().Constant(tol);
	//tol_t.matrix().Constant(tol);
	tol_t.matrix() = rl::math::Matrix::Constant(a.rows(), a.cols(), tol) ;
		
	//std::cout << "tol_t: " << tol_t.matrix() << " Size: " << tol_t.size() << std::endl;
	r = ((a-b).cwiseAbs().matrix().array() <= tol_t.array()).all();
		
	return r;
}


bool MathCommon::equalWithTol(const double a, const double b, const ::rl::math::Real tol)
{
	if (fabs(a-b) < tol)
	{
		return true;
	}
	
	return false;
}	
