#pragma once
#include "Solver.h"
#include "SchEquation.h"
class JacobiSolver :
	public Solver
{
public:
	JacobiSolver(Equation**, int, bool);
	~JacobiSolver(void);
	void Solve(Equation*);
};