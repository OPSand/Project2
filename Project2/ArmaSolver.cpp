#include "stdafx.h"
#include "ArmaSolver.h"


ArmaSolver::ArmaSolver(SchEquation** equations, int equationCount, bool useTimers):Solver(equations, equationCount, useTimers)
{
	// remember: Solver constructor is called first
}


ArmaSolver::~ArmaSolver(void)
{
}

void ArmaSolver::Solve(SchEquation eq)
{
	int n = eq.A().n_cols; // nasty, fix later :P Should use eq.nSteps()
	vec ev = vec(n);
	mat em = mat(n, n);
	eig_sym(ev, em, eq.A());
	rowvec rev = ev; // seems to work well enough
	eq.SetSolutions(rev, em);
}