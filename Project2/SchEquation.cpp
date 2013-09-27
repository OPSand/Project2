#include "stdafx.h"
#include "SchEquation.h"

// constants
const double SchEquation::HM2 = 1.0; // h^(-2), where h is the Planck constant (dimensionless)

// constructor
SchEquation::SchEquation(double omega, double rhoMax, int nSteps, bool coulomb)
{
	// identify yourself!
	_type = "SchEquation";

	// simple parameters
	_nSteps = nSteps;
	_omega = omega;
	_coulomb = coulomb;

	// initialize rho
	_stepSize = rhoMax / (_nSteps - 1);
	_rho = vec(_nSteps);
	for(int i = 0; i < _nSteps; i++)
	{
		_rho(i) = i * _stepSize; // last element is rhoMax
	}

	// initialize matrix (note: coulomb, omega etc. MUST be set before this!)
	mat A = mat(_nSteps, _nSteps);
	A.fill(0);
	A.diag(0) = diag();
	A.diag(1) = nonDiag();
	A.diag(-1) = nonDiag();

	// initialize solutions
	_eigVal = rowvec(_nSteps);
	_eigVec = mat(_nSteps, _nSteps);
}

SchEquation::~SchEquation()
{
	// empty
}

// Save the eigenvectors in a file (for plotting etc)
void SchEquation::SaveSolutions(string path)
{
	mat plot = mat(_nSteps, 2);
	plot.col(0) = _rho; // x
	plot.col(1) = _eigVec; // y
	plot.save(path, raw_ascii);
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
inline double SchEquation::diagElem(int i)
{
	return 2 * HM2 + V(i);
}

// return nondiagonal matrix element
inline double SchEquation::nonDiagElem()
{
	return -HM2;
}

// return diagonal as column vector
vec SchEquation::diag()
{
	vec d = vec(_nSteps);
	
	for( int i = 0; i < _nSteps; i++ )
	{
		d(i) = diagElem(i);
	}

	return d;
}

// return non-diagonal as column vector
vec SchEquation::nonDiag()
{
	vec nd = vec(_nSteps - 1); // hopefully obvious

	nd.fill(nonDiagElem());

	return nd;
}

// provides the Solver with a matrix to work with
mat SchEquation::A()
{
	return _A;
}

// return number of steps
inline int SchEquation::nSteps()
{
	return _nSteps;
}

// set the solutions (for use by the Solver classes)
void SchEquation::SetSolutions(rowvec eigVal, mat eigVec)
{
	_eigVal = eigVal;
	_eigVec = eigVec;
}