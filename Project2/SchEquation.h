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
	rowvec _rho;
	double _omega;
	bool _coulomb; // whether Coulomb forces enter into the potential or not

public:
	// constructors and destructors
	SchEquation(rowvec, double, bool);
	~SchEquation(void);

	// ...
	void SaveSolution(string);

	// methods that expose parameters to the Solver classes go here
	double V(int);
	inline double diag(int);
	inline double nonDiag();
};

