#pragma once
using namespace std;

class Equation abstract
{

protected:
	string _type;

public:
	Equation(void);
	~Equation(void);
	string type(void);
};