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
		this->getResultMat(); // XXX : This is what we should print ?
#pragma region Printing Routine
			// debug
			rowvec rv = randu<rowvec>(_equations[i]->nSteps());
			// plot things (the SchEquation class will be able to write its solutions to file)
				stringstream sstream;
				sstream << i;
				mat result = this->getAMat(); // Then we get rv and the result
				_equations[i]->SetSolutions(rv,result); 
				_equations[i]->SaveSolutions("test" + sstream.str()+ ".txt"); // XXX : remettre en places
				_equations[i]->SetSolutions(rv,getResultMat());
				_equations[i]->SaveSolutions("result" + sstream.str()+ ".txt");
#pragma endregion
	}
}
