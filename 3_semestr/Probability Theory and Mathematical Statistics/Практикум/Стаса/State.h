#pragma once
#ifndef STATEH
#define STATEH

#include "Transact.h"
#include <fstream>
class State
{
protected:
	static unsigned long long int _currID;
	unsigned long long int _ID;
	unsigned int _nextState;
public:
	State();
	unsigned long long int getID();
	void setNextState(unsigned int input);
	virtual void useTransact(Transact& transact, std::ofstream& file) = 0;
};

#endif // !STATEH