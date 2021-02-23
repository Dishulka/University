#pragma once
#ifndef CHANNELH
#define CHANNELH


#include "State.h"
#include "Queue.h"

class OPERATOR : public State
{
private:
	int _min;				//����������� ����� ��� ����������
	int _max;				//������������ ����� ��� ����������
	bool _isBusy;			//����, ���������� ����� ��� ��� ��������
	Transact* _served;		//��������� �� ��������, ������� �������������
	QUEUE _queue;			//������� � ���������
public:
	OPERATOR(int min, int max);	//����������
	int getSize();				//����������� ����� ������� � ���������
	bool isBusy();				//���������� �������� �����
	void useTransact(Transact& transact, std::ofstream& file); //����� ���������
};

#endif 

