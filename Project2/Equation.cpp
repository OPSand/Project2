#include "stdafx.h"
#include "Equation.h"

Equation::Equation(vec parameters)
{
	_parameters = parameters;
}

Equation::Equation(void)
{
	Equation(vec());
}

Equation::~Equation(void)
{
	delete &_parameters;
}