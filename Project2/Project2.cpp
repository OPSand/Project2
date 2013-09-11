// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"armadillo"
#include<list>

using namespace arma;
using namespace std; 

int _tmain(int argc, _TCHAR* argv[])
{
	mat A = randu<mat>(5,5);
	cout << det(A);

	return 0;
}

