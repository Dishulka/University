#include "Channel.h"


Channel::Channel(unsigned long long int min, unsigned long long int max) : State(), _queue()
{
	_occupied = NULL;
	_isOccupied = false;
	_MIN = min;
	_MAX = max;
}

int Channel::getQueueSize()
{
	return _queue.getSize();
}

bool Channel::isOccupied()
{
	return _isOccupied;
}

void Channel::useTransact(Transact& transact, std::ofstream& file)
{
	if (!_isOccupied)
	{
		file << "At " << transact.getTimeNextEvent() << " transact with ID " << transact.getID() << " has start  processing at " << _ID <<" operator."<< std::endl;
		transact.setTimeNextEvent(transact.getTimeNextEvent() + (double)(_MIN + ((unsigned long long int)rand() % ((unsigned long long int)_MAX - 1)) + (double)rand() / RAND_MAX));
		_occupied = &transact;
		_isOccupied = true;
	}
	else if (&transact == _occupied) 
	{
		file << "At " << transact.getTimeNextEvent() << " transact with ID " << transact.getID() << " has ended processing at " << _ID <<" operator."<< std::endl;
		transact.setState(_nextState);
		if (_queue.getSize() > 0) 
		{
			Transact* next = _queue.ejectTransact();
			file << "At " << next->getTimeNextEvent() << " transact with ID " << next->getID() << " has start processing at " << _ID << " operator from queue." << std::endl;
			next->setTimeNextEvent(next->getTimeNextEvent() + (double)(_MIN + ((unsigned long long int)rand() % ((unsigned long long int)_MAX - 1)) + (double)rand() / RAND_MAX));
			_occupied = next;
		}
		else 
		{
			_isOccupied = false;
		}
	}
	else
	{
		if (!_queue.hasTransact(transact))
		{
			_queue.addTransact(&transact);
			file << "At " << transact.getTimeNextEvent() << " transact with ID " << transact.getID() << " has gone to queue " << _ID <<"."<< std::endl;
		}
		transact.setTimeNextEvent(_occupied->getTimeNextEvent());
	}
}
