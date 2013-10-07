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
	mat _A;
public:
	Solver(SchEquation**, int, bool);
	~Solver(void);
	void SolveAll();
	inline double elapsedTime(void)
	{
		return ((double)(_finish - _start))/((double)CLOCKS_PER_SEC);
	};
	inline void startClock(void)
	{
		_start = clock();
	};
	inline void stopClock(void)
	{
		_finish = clock();
	};
	inline mat getResultMat()
	{
		return _B;
	};
	inline mat getAMat()
	{
		return _A;
	};
	// abstract methods
	virtual void Solve(SchEquation) abstract;
};