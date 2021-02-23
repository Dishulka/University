#include "Queue.h"



Queue::Queue()
{
}

int Queue::getSize()
{
	return _transacts.size();
}

void Queue::addTransact(Transact* input)
{
	_transacts.push_back(input);
}

Transact* Queue::ejectTransact()
{
	Transact* ejected = _transacts.front();
	_transacts.pop_front();
	return ejected;
}

bool Queue::hasTransact(Transact& transact)
{
	std::list <Transact*> ::iterator iter = _transacts.begin();
	for (; iter != _transacts.end(); iter++)
	{
		if ((**iter).getID() == transact.getID())
			return true;
	}
	return false;
}