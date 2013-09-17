#include "stdafx.h"
#include "Solver.h"

// constructor
Solver::Solver(int equationCount, bool useTimers)
{
	_equations = new Equation*[equationCount];
	_equationCount = equationCount;
	_useTimers = useTimers;
}

// destructor
Solver::~Solver(void)
{
	delete &_equations;
}

// solve ALL the equations :O
void Solver::SolveAll()
{
	for( int i = 0; i < _equationCount; i++ )
	{
		Solve(_equations[i]); // abstract function to be defined in subclasses
	}
}

// return the time used to solve
inline num Solver::elapsedTime(void)
{
	return ((num)(_finish - _start))/((num)CLOCKS_PER_SEC);
}