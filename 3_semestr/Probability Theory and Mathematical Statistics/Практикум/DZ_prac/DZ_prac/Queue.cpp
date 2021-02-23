#include "Queue.h"



QUEUE::QUEUE()
{
}

int QUEUE::getSize()
{
	return _transacts.size();
}

void QUEUE::addTransact(Transact* transact)
{
	_transacts.push_back(transact);
}

Transact* QUEUE::popTransact()
{
	Transact* element = _transacts.front();
	_transacts.pop_front();
	return element;
}

bool QUEUE::hasTransact(Transact& transact)
{
	std::list <Transact*> ::iterator iter = _transacts.begin();
	for (; iter != _transacts.end(); iter++)
	{
		if ((**iter).getID() == transact.getID())
			return true;
	}
	return false;
}