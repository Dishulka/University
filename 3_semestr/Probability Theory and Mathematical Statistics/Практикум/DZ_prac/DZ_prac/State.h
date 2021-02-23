#pragma once
#ifndef STATEH
#define STATEH

#include "Transact.h"
#include <fstream>
class State
{
protected:
	static int _currID;			//������������� ������� ������
	int _ID;					//������������� ���������� ������
	int _state;					//����� ��������� ��������� ���������
public:
	State();								//���������� ������
	int getID();							//���������� ������������� 
	void setState(int state);				//���������� ����� ���������� ���������
	virtual void useTransact(Transact& transact, std::ofstream& file) = 0;	//����������� �����
};

#endif