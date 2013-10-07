#pragma once
#include "equation.h"

// class for the Schrödinger equation with Coulomb potential
class SchEquation :
	public Equation
{

protected:
	// physical consants
	static const double HM2;
	
	// all input parameters go here
	double _omega;
	bool _coulomb; // whether Coulomb forces enter into the potential or not
	double _rhoMax;
	int _nSteps;

	// intermediate and helper data
	vec _rho;
	double _stepSize;
	mat _A;

	// solutions
	mat _eigVec; // eigenvectors (for plotting)
	rowvec _eigVal; // eigenvalues

	// protected methods
	double V(int);
	mat SchEquation::InitMat();
	vec diag(void);
	vec nonDiag(void);
	double SchEquation::diagElem(int i);
	double SchEquation::nonDiagElem();
public:
	// constructors and destructors
	SchEquation(double omega, double rhoMax, int nSteps, bool coulomb);
	~SchEquation(void);

	// other methods
	void SetSolutions(rowvec, mat);
	void SaveSolutions(string path);

	// methods that expose parameters to the Solver classes go here
	inline int nSteps(void)
	{return _nSteps;};
	double* SchEquation::double_nonDiag(); // Function used for tqli. We're not working with vector from arma anymore
	double* SchEquation::double_Diag(); // Function used for tqli
	mat A(void);
};

