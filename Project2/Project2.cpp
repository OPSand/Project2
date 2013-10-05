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
	// const bool INCLUDE_LANCZOS = false; // ex. e), voluntary

	//armaTest(); // debug


#pragma region To Be Removed !!! ... Security for now
	// initiate Equation objects - with or without interaction
	// parameters (numbers) will need to be added to the class and constructor
	const int NUMBER_OF_EQUATIONS = 1;
	SchEquation** eqs = new SchEquation*[NUMBER_OF_EQUATIONS];// Do we want/need a table here ? Not really ?
	/*double omega = 1;
	double rhoMax = 5;
	int nSteps = 1000000;*/
	
	//SchEquation* eq = new SchEquation(omega,rhoMax,nSteps,false);

#pragma endregion
	// I want to create a bunch of equations with arguments known. Because right now, i only manage one equation ... é_è
	for( int i = 0; i < NUMBER_OF_EQUATIONS; i++ )
	{
		double omega = 1;
		double rhoMax = 10;
		int nSteps = 10;

		// We declare new instances for our whole set of equations
		eqs[i] = new SchEquation(omega, rhoMax, nSteps, false); // no parameters yet, but soon...
	}
	
	if( INCLUDE_JACOBI )
	{
		// create JacobiSolver and add equations to it
		JacobiSolver js = JacobiSolver(eqs, NUMBER_OF_EQUATIONS, INCLUDE_TIMERS);

		// solve the equations
		js.SolveAll(); // NOTE: Causes assertion fault while debugging. Not fatal, but should be looked into.
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