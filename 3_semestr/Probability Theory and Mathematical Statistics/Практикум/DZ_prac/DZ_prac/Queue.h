#pragma once
#ifndef QUEUEH
#define QUEUEH

#include <list>
#include "Transact.h"
#include <iterator>
class QUEUE
{
private:
	std::list <Transact*> _transacts; //������ ���������� �� ������� Transact
public:
	QUEUE();							//�����������
	int getSize();						//���������� ����� �������
	void addTransact(Transact*);		//��������� � ������� ��������� �� ����� ������ 
	Transact* popTransact();			//���������� 1 �� ������� ���������
	bool hasTransact(Transact& transact); //��������� ������� ��������� � �������

};

#endif