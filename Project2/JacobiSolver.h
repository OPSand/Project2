#pragma once
#include "stdafx.h"
#include "Solver.h"
#include "SchEquation.h"
using namespace std;
using namespace arma;
class JacobiSolver:
	public Solver
{
private :
	double d_tolerance;
public:
	JacobiSolver(SchEquation**, int, bool);
	~JacobiSolver(void);
	void Solve(SchEquation);
	double offDiag(mat &A, int* row, int* column);
	inline bool isBiggerThanTolerance(double valueToTest)
	{
		bool bIsLargerThanTolerance = true;
		if (valueToTest < d_tolerance) 
			bIsLargerThanTolerance = false;
		return bIsLargerThanTolerance;
	};
	void JacobiRotation(mat &A, int rowLargest,int columnLargest,mat &B);
	void NormalizedEigenvector(mat &B);
};

