#include "stdafx.h"
#include "Solver.h"

// constructor
Solver::Solver(SchEquation** equations, int equationCount, bool useTimers)
{
	_equations = equations;
	_equationCount = equationCount;
	_useTimers = useTimers;
}

// destructor
Solver::~Solver(void)
{
	// Now that we're back at the "set of equations" stage, we should be picky about
	// The way we delete them

	for (int i= 0; i< _equationCount; i++)
		delete _equations[i];
	delete [] _equations;

	
	// Still getting the weird debug assertion.
	//delete _equations;
}

// solve ALL the equations :O
void Solver::SolveAll()
{
	for( int i = 0; i < _equationCount; i++ )
	{
		// N: This is not working, since we're not wirking with table anymore !
		Solve(*_equations[i]); // abstract function to be defined in subclasses
		//this->getResultMat(); // XXX : This is what we should print ?
#pragma region Printing Routine
	 //if (MAKE_PLOTS)
	//	{
			// debug
		rowvec rv = randu<rowvec>(_equations[i]->nSteps());
			//mat m = randu<mat>(nSteps, nSteps);

			// plot things (the SchEquation class will be able to write its solutions to file)
				stringstream sstream;
				sstream << i;
				mat result = this->getResultMat();
				/*for (int j = 0; j <_equations[i]->nSteps(); j++)
				{
					for (int k = 0; k< _equations[i]->nSteps(); k++)
						printf ("(%d %d) \t  %f ||", j,k,result(j,k));
				}*/
				//_equations[i]->SetSolutions(rv,this->getResultMat());
				//_equations[i]->SaveSolutions("test" + sstream.str()+ ".txt"); // XXX : remettre en places
		//}
#pragma endregion
	}
	//Solve(_equations[0]);
}

// return the time used to solve
inline double Solver::elapsedTime(void)
{
	return ((double)(_finish - _start))/((double)CLOCKS_PER_SEC);
}

// start timer
inline void Solver::startClock(void)
{
	_start = clock();
}

// stop timer
inline void Solver::stopClock(void)
{
	_finish = clock();
}