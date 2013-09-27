#pragma once
#include "solver.h"
class ArmaSolver :
	public Solver
{
public:
	// constructors and destructors
	ArmaSolver(Equation**, int, bool);
	~ArmaSolver(void);
	void Solve(Equation*);
};

