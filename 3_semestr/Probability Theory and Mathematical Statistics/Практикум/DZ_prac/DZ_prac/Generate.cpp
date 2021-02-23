#include "Generate.h"
using namespace std;

GENERATE::GENERATE(int min, int max):State()
{
	_time = 0;
	_min = min;
	_max = max;
}

double GENERATE::getTime()
{
	_time += (double)(_min + (rand() % (_max - 1)) + (double)rand() / RAND_MAX);
	return _time;
}

void GENERATE::useTransact(Transact& transact, std::ofstream& file)
{
	transact.setState(_state);
	file << "В момент времни " << transact.getTime() << " транзакт с индентификатором " << transact.getID() << " вошел в модель." << endl;
}
