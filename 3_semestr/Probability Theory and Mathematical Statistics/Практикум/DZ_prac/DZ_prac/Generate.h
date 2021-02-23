#pragma once
#ifndef GENERATEH
#define GENERATEH

#include "State.h"
#include <cstdlib>

class GENERATE : public State
{
private:
	double _time;					//����� ��������� �������
	int _max;						//������������ ����� ��� ����������
	int _min;						//����������� ����� ��� ����������
public:
	GENERATE(int min, int max);			//���������� ������
	double getTime();					//���������� �����
	void useTransact(Transact& transact, std::ofstream& file); //����� ���������
};


#endif 



