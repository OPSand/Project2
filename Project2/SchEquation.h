#pragma once
#include "equation.h"

// class for the Schrödinger equation with Coulomb potential
class SchEquation :
	public Equation
{

public:
	SchEquation(vec);
	~SchEquation(void);
};

