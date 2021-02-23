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
		file << "� ������ ������� " << transact.getTime() << " �������� � ��������������� " << transact.getID() << " ����� ���������� " << _ID << endl;
		transact.setTime(transact.getTime() + (double)(_min + (rand() % (_max - 1)) + (double)rand() / RAND_MAX));
		_served = &transact;
		_isBusy = true;
	}
	else if (&transact == _served)
	{
		file << "� ������ ������ " << transact.getTime() << " �������� � ���������������� " << transact.getID() << " ��������� ���������� " << _ID << endl;
		transact.setState(_state);
		if (_queue.getSize() > 0) 
		{
			Transact* next = _queue.popTransact();
			file << "� ������ ������� " << next->getTime() << " �������� � ���������������� " << next->getID() << " ����� ���������� " << _ID << endl;
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
			file << "� ������ ������� " << transact.getTime() << " �������� � ��������������� " << transact.getID() << " ����� � ������� " << _ID << endl;
		}
		transact.setTime(_served->getTime());
	}
}
