#include "stdafx.h"
#include "JacobiSolver.h"


JacobiSolver::JacobiSolver(Equation** equations, int equationCount, bool useTimers):Solver(equations, equationCount, useTimers)
{
	// remember: Solver constructor is called first

	d_tolerance = 0.00000001;
}


JacobiSolver::~JacobiSolver(void)
{
}

void JacobiSolver::Solve(Equation* eq)
{
	if( eq->type() == "SchEquation" ) 
	{
		// The code to implement Jacobi's method goes here
		// First, we should "transform" our equation into a matrix, then look for 
		// The biggest non diag. element. Then check if bigger than the tolerance, and ! Hop!
		// How do we describe the eigenvectors ?
		int nbSteps = 0;
		int nbIterations = 0;
		printf("How many steps? \t");
		cin >> nbSteps;
		double h = (1.0/(((double)nbSteps) - 1.0)); // This is our step length
		double x = 0.0f;
		mat A = mat(nbSteps,nbSteps);
		// We have initialize our matrix  .
		A.zeros();
		for (int i= 0; i < nbSteps; i++)
		{
			x = i*h;
			A(i,i) = 2/pow(h,2) + pow(x,2);
			if (i >= 1)
				A(i,i-1)= -1/pow(h,2);
			if (i < (nbSteps-1))
				A(i,i+1) = -1/pow(h,2);
		}

		// And then, launch the Jacobi rotation
		int rowLargest = 0;
		int columnLargest = 0;
		mat B = mat(nbSteps,nbSteps);
		B.eye();
		while (isBiggerThanTolerance(offDiag(A,&rowLargest,&columnLargest))) // While the biggest element is bigger than the tolerance threshold
		{
			// Then similarity transfo.
			JacobiRotation(A,rowLargest,columnLargest,B);
			nbIterations ++;
		}
		// Then we have finish our Jacobi's process
		// And we need to print the result ...
		for (int i=0; i < B.n_rows; i++)
		{
			for (int j=0; j< B.n_rows; j++)
				printf(" %f \t", B(i,j));
			printf("\n");
		}


		cout << "I solved this! :D" << endl; // debug
		printf("And it took me : %d similarity transformations\n", nbIterations);
	}
	else 
	{
		cout << "I cannot solve this... :("; // debug
	}
}

/* This function finds the largest non diagonal element of a matrix */
double JacobiSolver::offDiag(mat &A, int* row, int* column)
{
	double dLargest = 0.0;
	bool bIsLargerThanTolerance = true;
	int sizeMatrix = A.n_rows;
	for (int i = 0; i < sizeMatrix ; i++)
	{
		for (int j = 0; j < sizeMatrix ; j++)
		{
			if ((abs(A(i,j)) >= dLargest) && (i != j)) // Guess we should take the absolute value 
			{
				dLargest = abs(A(i,j));
				*row = i;
				*column = j;
			}
		}
	}

	return dLargest;
}

/* This function test the largest off diag element against the tolerance */
inline bool JacobiSolver::isBiggerThanTolerance(double valueToTest)
{
	bool bIsLargerThanTolerance = true;
	if (valueToTest < d_tolerance) 
		bIsLargerThanTolerance = false;
	return bIsLargerThanTolerance;
}

/* This function will process the whole similarity transformation process */
void JacobiSolver::JacobiRotation(mat &A, int rowLargest,int columnLargest,mat &B)
{
	int sizeMatrix = A.n_rows;
	// First, we have to compute tau: (all - akk)/2akl
	double tau = 0.0;
	// We don't have to worry about a 0 case here, unless our tolerance is 0. But if our tolerance is 0, we should be worried by something else
	// (for example the fact that it will neeever end)
	tau = (A(columnLargest,columnLargest)- A(rowLargest,rowLargest))/(2*A(rowLargest,columnLargest));
	// Then, we find tan
	double t = 0.0;
	if (tau >= 0)
		t = tau + sqrt(1 + pow(tau,2));
	else
		t = -(-tau +sqrt(1 + pow(tau,2)));

	// Once we have tan, we can find cos and sin
	double c = 0.0;
	double s = 0.0;
	c = 1/sqrt(pow(t,2) +1 );
	s = c*t;

	// Then, we modify the A matrix:
	for (int i = 0; i< sizeMatrix; i++)
	{
		// But first, we have to store our rotation values, before erasing them
		double ik = A(i,rowLargest);
		double il = A(i,columnLargest);
		double kk = A(rowLargest,rowLargest);
		double ll = A(columnLargest,columnLargest);
		// We change the value of the different coef of A
		A(i,rowLargest) = ik*c - il*s;
		A(i,columnLargest) = il*c + ik*s;
		A(rowLargest,rowLargest) = kk*pow(c,2) - 2*A(rowLargest,columnLargest)*c*s + ll*pow(s,2);
		A(columnLargest,columnLargest) = ll*pow(c,2) + 2*A(rowLargest,columnLargest)*c*s + kk*pow(s,2);
		A(rowLargest,columnLargest) = (kk - ll)*c*s + A(rowLargest,columnLargest)*(pow(c,2) - pow(s,2));
	}

	// We have to compute our new eigenvectors too
	for (int i = 0; i< sizeMatrix ; i++)
	{
		// Same than for A: we have to store some values before computing
		double ik = B(i,rowLargest);
		B(i,rowLargest) = c* ik - s*B(i,columnLargest);
		B(i,columnLargest) = c*B(i,columnLargest) + s*B(i,rowLargest);
	}

	return;
}