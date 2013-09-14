// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "armadillo"
#include <time.h>

using namespace std;
using namespace arma;

typedef double num; // for quick switching between double/float as needed
typedef Mat<num> matr; // typed matrix
typedef Col<num> vect; // typed (column) vector