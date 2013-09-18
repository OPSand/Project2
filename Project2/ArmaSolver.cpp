#include "stdafx.h"
#include "ArmaSolver.h"


ArmaSolver::ArmaSolver(Equation** equations, int equationCount, bool useTimers):Solver(equations, equationCount, useTimers)
{
}


ArmaSolver::~ArmaSolver(void)
{
}

// TODO: Implement Solve()