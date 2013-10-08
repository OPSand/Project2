// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Solver.h"

using namespace arma;
using namespace std; 

void armaTest();

int _tmain(int argc, _TCHAR* argv[])
{
	// Program flow control flags (set at compile time)
	const bool INCLUDE_JACOBI = true; // ex. b)
	const bool INCLUDE_ARMADILLO = false; // ex. b)
	const bool INCLUDE_TIMERS = true; // ex. b)
	const bool MAKE_PLOTS = true; // ex. d)
	const bool INCLUDE_LIB = false; // ex b)

	//armaTest(); // debug

	const int NUMBER_OF_EQUATIONS = 1;
	SchEquation** eqs = new SchEquation*[NUMBER_OF_EQUATIONS];
	// We create a set of equations
	for( int i = 0; i < NUMBER_OF_EQUATIONS; i++ )
	{
		double omega = 5.00;
		double rhoMax = 1000;
		int nSteps = 30;

		// We declare new instances for our whole set of equations
		eqs[i] = new SchEquation(omega, rhoMax, nSteps, true);
	}
	
	if( INCLUDE_JACOBI )
	{
		// create JacobiSolver and add equations to it
		JacobiSolver js = JacobiSolver(eqs, NUMBER_OF_EQUATIONS, INCLUDE_TIMERS);

		// solve the equations
		js.SolveAll();
		// XXX : The structure here is kind of weird. Shouldn't we do that directly 
		/*if (MAKE_PLOTS)
		{
			// debug
			rowvec rv = randu<rowvec>(nSteps);
			mat m = randu<mat>(nSteps, nSteps);

			// plot things (the SchEquation class will be able to write its solutions to file)
			for (int i= 0; i < NUMBER_OF_EQUATIONS; i++)
			{
				stringstream sstream;
				sstream << i;
				eqs[i]->SetSolutions(rv, m);
				//eqs[i]->SaveSolutions("test" + sstream.str()+ ".txt"); // XXX : remettre en place
			}
		}*/
	}
	if (INCLUDE_LIB)
	{
		// Param for tqli : vec d is the diagonal, vec e is the sub-diagonal. n is the size, z the output
		for (int i = 0 ; i < NUMBER_OF_EQUATIONS; i++)
		{
			double* d = new double [eqs[i]->nSteps()];
			double* e = new double [eqs[i]->nSteps()];
			double** z = new double*[eqs[i]->nSteps()];
			for (int j= 0; j<eqs[i]->nSteps(); j++)
				z[j] = new double [eqs[i]->nSteps()];
			d = eqs[i]->double_Diag();
			e = eqs[i]->double_nonDiag();
			printf("This is A before ! \n");
			for (int k = 0; k < eqs[i]->nSteps(); k++)
				printf("%f \t",d[k]); 
			tqli(d,e,eqs[i]->nSteps(),z);
			printf("This is A after ! \n");
			for (int k = 0; k < eqs[i]->nSteps(); k++)
				printf("%f \t",d[k]); 
		}
	}
	if( INCLUDE_ARMADILLO )
	{
		// create ArmaSolver and add equations to it
		ArmaSolver as = ArmaSolver(eqs, NUMBER_OF_EQUATIONS, INCLUDE_TIMERS);

		// solve the equations
		for (int i= 0 ; i < NUMBER_OF_EQUATIONS ; i++)
			as.Solve(*eqs[i]);

			// plot things (the SchEquation class will be able to write its solutions to file)
		for (int i= 0; i < NUMBER_OF_EQUATIONS; i++)
		{
			stringstream sstream;
			sstream << i;
			//eqs[i]->SetSolutions(rv, m);
			eqs[i]->SaveSolutions("test" + sstream.str()+ ".txt");
		}
	}

	cout << endl << endl << "Press ENTER to exit..." << endl;
	fflush(stdin);
	getchar(); // pause program before it closes (useful when debugging)

	return 0;
}

// Use this to check that Armadillo runs smoothly with BLAS and LAPACK
void armaTest()
{
	mat A = randu<mat>(5,5);
	cout << det(A) << endl << endl;

	mat L, U, P;
	if( lu(L, U, P, A) )
	{
		cout << "LU success!" << endl;
		cout << L << endl << endl;
		cout << U << endl << endl;
	}

	vec v = randu<vec>(5);
	vec x = solve(L, v);
	cout << x << endl << endl;
}