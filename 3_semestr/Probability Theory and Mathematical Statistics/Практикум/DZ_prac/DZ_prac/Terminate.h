#pragma once
#ifndef TERMANATEH
#define TERMANATEH


#include "State.h"
class TERMINATE : public State
{
public:
	TERMINATE(); //����������� ������
	void useTransact(Transact& transact, std::ofstream& file); //����� ���������
};

#endif