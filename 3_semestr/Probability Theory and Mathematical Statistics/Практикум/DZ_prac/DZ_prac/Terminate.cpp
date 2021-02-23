#include "Terminate.h"
using namespace std;

TERMINATE::TERMINATE():State()
{
}

void TERMINATE::useTransact(Transact& transact, std::ofstream& file)
{
	file << "� ������ ������� " << transact.getTime() << " ������� � ���������������� " << transact.getID() << " ����� �� ������." << endl;
	delete &transact;
}
