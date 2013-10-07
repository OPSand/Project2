#include "stdafx.h"
#include "JacobiSolver.h"

// Isn't this suppose to be a by copy constructor ?!! Nop
JacobiSolver::JacobiSolver(SchEquation** equations, int equationCount, bool useTimers):Solver(equations, equationCount, useTimers)
{
	// remember: Solver constructor is called first

	d_tolerance = 0.0000000001;
}


JacobiSolver::~JacobiSolver(void)
{
}

void JacobiSolver::Solve(SchEquation eq)
{
	if(eq.type() == "SchEquation" ) 
	{
		// We want to time our function
		startClock();

		int nbIterations = 0;
		// The code to implement Jacobi's method goes here
		// First, we should "transform" our equation into a matrix, then look for 
		// The biggest non diag. element. Then check if bigger than the tolerance, and ! Hop!
		// How do we describe the eigenvectors ?
		int nbSteps = eq.nSteps();
		printf("Beginning A ! \t");
		_A = eq.A();
		
		// XXX :  This is just printing the A matrix
		/*for (unsigned int i=0; i < _A.n_rows; i++) // Unsigned to prevent a warning to be fire.
		{
			for (unsigned int j=0; j< _A.n_rows; j++)
				printf(" %f \t", _A(i,j));
			printf("\n");
		}*/
		// And then, launch the Jacobi rotation
		int rowLargest = 0;
		int columnLargest = 0;
		_B = mat(nbSteps,nbSteps);
		_B.eye();
		while (isBiggerThanTolerance(offDiag(_A,&rowLargest,&columnLargest))) // While the biggest element is bigger than the tolerance threshold
		{
			// Then similarity transfo.
			JacobiRotation(_A,rowLargest,columnLargest,_B);
			nbIterations ++;
		}
		// Then we have finish our Jacobi's process
		// And we need to print the result ...
			
#pragma region Printing matrix
		
		printf ("And this is A ! \n");
		int machin = 0;
		for (unsigned int i=0; i < _A.n_rows; i++) // Unsigned to prevent a warning to be fire.
		{
			machin ++;
			if (machin < 6)
				printf(" %f \t", _A(i,i));
		}

#pragma endregion 

		cout << "I solved this! :D" << endl; // debug
		printf("And it took me : %d similarity transformations\n", nbIterations);
		// Finally, we stop our timer
		stopClock();
		printf("[Jacobi's rotation] Elapsed time: %f",elapsedTime());
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
	int sizeMatrix = A.n_rows;
	for (int i = 0; i < sizeMatrix ; i++)
	{
		for (int j = 0; j < sizeMatrix ; j++)
		{
			if ((abs(A(i,j)) > dLargest) && (i != j)) // Guess we should take the absolute value 
			{
				dLargest = abs(A(i,j));
				*row = i;
				*column = j;
			}
		}
	}
	return dLargest;
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
	if (tau > 0)
		t = -tau + sqrt(1 + pow(tau,2));
	else
		t = -tau - sqrt(1 + pow(tau,2));

	// Once we have tan, we can find cos and sin
	double c = 1/sqrt(t*t +1 );
	double s = c*t;

	double a_kk = A(rowLargest,rowLargest);
	double a_ll = A(columnLargest,columnLargest);
	double a_kl= A(rowLargest,columnLargest);
	A(rowLargest,rowLargest) = a_kk*pow(c,2) - 2*a_kl*c*s + a_ll*pow(s,2);
	A(columnLargest,columnLargest) = a_ll*pow(c,2) + 2*a_kl*c*s + a_kk*pow(s,2);
	A(rowLargest,columnLargest) = 0;//(a_kk - a_ll)*c*s + a_kl*(pow(c,2) - pow(s,2));
	A(columnLargest,rowLargest) = A(rowLargest,columnLargest);
	// Then, we modify the rest of the matrix:
	for (int i = 0; i< sizeMatrix; i++)
	{
		// But first, we have to store our rotation values, before erasing them
		if (i != rowLargest && i!= columnLargest)
		{
			double a_ik = A(i,rowLargest);
			double a_il = A(i,columnLargest);
			A(i,rowLargest) = a_ik*c - a_il*s;
			A(i,columnLargest) = a_il*c + a_ik*s;
			A(rowLargest,i) = A(i,rowLargest);
			A(columnLargest,i) = A(i,columnLargest);
		}
		// We store some values and compute the newB
		double ik = B(i,rowLargest);
		double il = B(i,columnLargest);
		B(i,rowLargest) = c* ik - s*il;
		B(i,columnLargest) = c*il + s*ik;
	}
	return;
}