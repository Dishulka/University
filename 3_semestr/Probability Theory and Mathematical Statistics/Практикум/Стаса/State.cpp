#include "State.h"
unsigned long long int State::_currID = 0;
State::State()
{
	_ID = _currID;
	_currID++;
	_nextState = 0;
}

unsigned long long int State::getID()
{
	return _ID;
}

void State::setNextState(unsigned int input)
{
	_nextState = input;
}
