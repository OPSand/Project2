#include "stdafx.h"
#include "Solver.h"

// constructor
Solver::Solver(int equationCount, bool useTimers)
{
	_equations = new Equation[equationCount];
	_equationCount = equationCount;
	_useTimers = useTimers;
}

// destructor
Solver::~Solver(void)
{
	delete &_equations;
}

// solve individual equation (to be overloaded)
void Solver::Solve(Equation eq)
{
	// include timers here?
}

// solve ALL the equations
void Solver::SolveAll()
{
	for( int i = 0; i < _equationCount; i++ )
	{
		Solve(_equations[i]); // abstract function to be defined in subclasses
	}
}