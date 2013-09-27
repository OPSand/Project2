#pragma once

#include "Equation.h"

class Solver abstract
{
private:
	int _equationCount;
	bool _useTimers;
	clock_t _start;
	clock_t _finish;
	Equation** _equations; // not a matrix, but an array of pointers (since the class is abstract)

public:
	Solver(Equation**, int, bool);
	~Solver(void);
	void SolveAll();
	inline double elapsedTime(void);
	inline void startClock(void);
	inline void stopClock(void);
	
	// abstract methods
	virtual void Solve(Equation*) abstract;
};