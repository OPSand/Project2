#pragma once

#include "Equation.h"

class Solver
{
private:
	Equation* _equations;
	int _equationCount;
	bool _useTimers;
	clock_t _start;
	clock_t _finish;

public:
	Solver(int, bool);
	~Solver(void);
	void SolveAll();
	void Solve(Equation);
};

