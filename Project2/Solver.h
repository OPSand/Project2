#pragma once

#include "Equation.h"

class Solver abstract
{
private:
	Equation** _equations; // not a matrix, but an array of pointers (since the class is abstract)
	int _equationCount;
	bool _useTimers;
	clock_t _start;
	clock_t _finish;

public:
	Solver(int, bool);
	~Solver(void);
	void SolveAll();
	virtual void Solve(Equation*) abstract;
	inline num elapsedTime(void);
};

