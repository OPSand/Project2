#include "stdafx.h"
#include "JacobiSolver.h"


JacobiSolver::JacobiSolver(Equation** equations, int equationCount, bool useTimers):Solver(equations, equationCount, useTimers)
{
}


JacobiSolver::~JacobiSolver(void)
{
}

void JacobiSolver::Solve(Equation* eq)
{
	if( eq->type() == "SchEquation" )
	{
		// The code to implement Jacobi's method goes here

		cout << "I can solve this! :D"; // debug
	}
	else 
	{
		cout << "I cannot solve this... :("; // debug
	}
}