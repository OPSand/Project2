// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

	armaTest(); // debug

	// create SchEquation objects - with or without interaction

	if( INCLUDE_JACOBI )
	{
		// create and add JacobiSolver

		// solve the equations
	}

	if( INCLUDE_ARMADILLO )
	{
		// create and add ArmaSolver

		// solve the equations
	}

	if (MAKE_PLOTS)
	{
		// plot things (the Solver class will be able to write its solutions to file)
	}

	cout << endl << endl << "Press ENTER to exit..." << endl;
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