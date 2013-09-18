#pragma once
#include "equation.h"

// class for the Schrödinger equation with Coulomb potential
class SchEquation :
	public Equation
{

protected:
	// all input parameters go here

public:
	// constructors and destructors
	SchEquation(void); // TODO: change to take arguments when parameters are in
	~SchEquation(void);

	// methods that expose parameters to the Solver classes go here
};

