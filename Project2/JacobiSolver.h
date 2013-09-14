#pragma once
#include "solver.h"
class JacobiSolver :
	public Solver
{
public:
	JacobiSolver(int, bool);
	~JacobiSolver(void);
};

