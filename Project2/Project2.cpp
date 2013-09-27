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
	const bool INCLUDE_ARMADILLO = true; // ex. b)
	const bool INCLUDE_TIMERS = true; // ex. b)
	const bool MAKE_PLOTS = false; // ex. d)
	// const bool INCLUDE_LANCZOS = false; // ex. e), voluntary

	//armaTest(); // debug

	// initiate Equation objects - with or without interaction
	// parameters (numbers) will need to be added to the class and constructor
	const int NUMBER_OF_EQUATIONS = 2;
	Equation** eqs = new Equation*[NUMBER_OF_EQUATIONS];
	for( int i = 0; i < NUMBER_OF_EQUATIONS; i++ )
	{
		rowvec rho(5);
		rho.fill(1);
		double omega = 1;

		eqs[i] = new SchEquation(rho, omega, false); // no parameters yet, but soon...
		//N: (I think that your weird degug assertion is now solved -unless I didn't get what you wanted to do -but answer just when you hav time:
		//why did you use 
		//"eqs[i] = &SchEquation();" ? 
		//What does the "&" stand here for? Seems to work fine with:
		//"eqs[i] = new SchEquation();")
	}
	
	if( INCLUDE_JACOBI )
	{
		// create JacobiSolver and add equations to it
		JacobiSolver js = JacobiSolver(eqs, NUMBER_OF_EQUATIONS, INCLUDE_TIMERS);

		// solve the equations
		js.SolveAll(); // NOTE: Causes assertion fault while debugging. Not fatal, but should be looked into.
	}

	if( INCLUDE_ARMADILLO )
	{
		// create ArmaSolver and add equations to it

		// solve the equations
	}

	if (MAKE_PLOTS)
	{
		// plot things (the Solver class will be able to write its solutions to file)
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