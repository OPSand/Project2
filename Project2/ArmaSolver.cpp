#include "stdafx.h"
#include "ArmaSolver.h"


ArmaSolver::ArmaSolver(SchEquation* equations, int equationCount, bool useTimers):Solver(equations, equationCount, useTimers)
{
	// remember: Solver constructor is called first


}


ArmaSolver::~ArmaSolver(void)
{
}

void ArmaSolver::Solve(SchEquation eq)
{
	//
}