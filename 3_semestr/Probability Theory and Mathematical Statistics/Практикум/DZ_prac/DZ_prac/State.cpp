#include "State.h"

int State::_currID = 0;

State::State()
{
	_ID = _currID;
	_currID++;
	_state = 0;
}

int State::getID()
{
	return _ID;
}

void State::setState(int state)
{
	_state = state;
}
