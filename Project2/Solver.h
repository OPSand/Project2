#pragma once

#include "Equation.h"
#include "SchEquation.h"

class Solver abstract
{
private:
	int _equationCount;
	bool _useTimers;
	clock_t _start;
	clock_t _finish;
	SchEquation** _equations; // not a matrix, but an array of pointers (since the class is abstract)
protected:
	mat _B;
public:
	Solver(SchEquation**, int, bool);
	~Solver(void);
	void SolveAll();
	inline double elapsedTime(void);
	inline void startClock(void);
	inline void stopClock(void);
	inline mat getResultMat()
	{
		return _B;
	};
	// abstract methods
	virtual void Solve(SchEquation) abstract;
};