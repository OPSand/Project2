#include "stdafx.h"
#include "ArmaSolver.h"


ArmaSolver::ArmaSolver(Equation** equations, int equationCount, bool useTimers):Solver(equations, equationCount, useTimers)
{
}


ArmaSolver::~ArmaSolver(void)
{
}

void ArmaSolver::Solve(Equation* eq)
{
	if( eq->type() == "SchEquation" )
	{
		// yay
	}
	// else do nothing
}