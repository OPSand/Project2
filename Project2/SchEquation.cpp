#include "stdafx.h"
#include "SchEquation.h"

// constants
const double SchEquation::HM2 = 1.0; // h^(-2), where h is the Planck constant (dimensionless)

// constructor
SchEquation::SchEquation(rowvec rho, double omega, bool coulomb)
{
	// identify yourself!
	_type = "SchEquation";

	// parameters
	_rho = rho;
	_omega = omega;
	_coulomb = coulomb;
}

SchEquation::~SchEquation()
{
}

// Save the solutions in a file (for plotting etc)
void SchEquation::SaveSolution(string path)
{
	//
}

// calculate potential element V[i]
double SchEquation::V(int i)
{
	if( ! _coulomb )
	{
		return pow(_rho(i), 2.0); // rho^2
	}
	else // coulomb interaction
	{
		return pow(_omega*_rho(i), 2.0) + (1.0/_rho(i)); // omega^2 * rho^2 + 1 / rho
	}
}

// return diagonal matrix element (@ row i)
inline double SchEquation::diag(int i)
{
	return 2 * HM2 + V(i);
}

// return nondiagonal matrix element
inline double SchEquation::nonDiag()
{
	return -HM2;
}