#pragma once
using namespace std;
using namespace arma;

class Equation abstract
{

protected:
	string _type;

public:
	Equation(void);
	~Equation(void);
	string type(void);

	// abstract methods
	virtual void SaveSolution(string) abstract;
};