#include "Channel.h"
using namespace std;


OPERATOR::OPERATOR(int min, int max) : State(), _queue()
{
	_served = NULL;
	_isBusy = false;
	_min = min;
	_max = max;
}

int OPERATOR::getSize()
{
	return _queue.getSize();
}

bool OPERATOR::isBusy()
{
	return _isBusy;
}

void OPERATOR::useTransact(Transact& transact, std::ofstream& file)
{
	if (!_isBusy)
	{
		file << "В момент времени " << transact.getTime() << " транзакт с идентификатором " << transact.getID() << " занял устройство " << _ID << endl;
		transact.setTime(transact.getTime() + (double)(_min + (rand() % (_max - 1)) + (double)rand() / RAND_MAX));
		_served = &transact;
		_isBusy = true;
	}
	else if (&transact == _served)
	{
		file << "В момент времни " << transact.getTime() << " транзакт с индентификатором " << transact.getID() << " освободил устройство " << _ID << endl;
		transact.setState(_state);
		if (_queue.getSize() > 0) 
		{
			Transact* next = _queue.popTransact();
			file << "В момент времени " << next->getTime() << " транзакт с индентификатором " << next->getID() << " занял устройство " << _ID << endl;
			next->setTime(next->getTime() + (double)(_min + ((unsigned long long int)rand() % ((unsigned long long int)_max - 1)) + (double)rand() / RAND_MAX));
			_served = next;
		}
		else 
		{
			_isBusy = false;
		}
	}
	else
	{
		if (!_queue.hasTransact(transact))
		{
			_queue.addTransact(&transact);
			file << "В момент времени " << transact.getTime() << " транзакт с идентификатором " << transact.getID() << " встал в очередь " << _ID << endl;
		}
		transact.setTime(_served->getTime());
	}
}
