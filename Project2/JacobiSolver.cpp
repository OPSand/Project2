#include "stdafx.h"
#include "JacobiSolver.h"


JacobiSolver::JacobiSolver(int equationCount, bool useTimers):Solver(equationCount, useTimers)
{
}


JacobiSolver::~JacobiSolver(void)
{
}

void JacobiSolver::Solve(Equation* eq)
{
	if( eq->type() == "SchEquation" )
	{
		cout << "I can solve this! :D";
	}
	else 
	{
		cout << "I cannot solve this... :(";
	}
}