#include "stdafx.h"
#include "Solver.h"

// constructor
Solver::Solver(Equation** equations, int equationCount, bool useTimers)
{
	_equations = equations;
	_equationCount = equationCount;
	_useTimers = useTimers;
}

// destructor
Solver::~Solver(void)
{
	
	// I had to transform the "NUMBER_OF_EQUATIONS" variables into a global one, defined in 
	// the stdafx header ~
	for (int i= 0; i< _equationCount; i++)
		delete _equations[i];
	delete [] _equations;
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
inline double Solver::elapsedTime(void)
{
	return ((double)(_finish - _start))/((double)CLOCKS_PER_SEC);
}

// start timer
inline void Solver::startClock(void)
{
	_start = clock();
}

// stop timer
inline void Solver::stopClock(void)
{
	_finish = clock();
}