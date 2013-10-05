#pragma once
#include "solver.h"
class ArmaSolver :
	public Solver
{
public:
	// constructors and destructors
	ArmaSolver(SchEquation**, int, bool);
	~ArmaSolver(void);
	void Solve(SchEquation);
};

