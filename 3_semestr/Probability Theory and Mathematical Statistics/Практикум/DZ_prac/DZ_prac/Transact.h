#pragma once
#ifndef TRANSACTH

class Transact 
{
private:
	static int _currID;				//������������� ������� ������
	int _ID;						//������������� ���������� ������
	double _time;					//����� ��������� ���������
	int _state;						//����� ������� ���������
public:
	Transact();							//���������� ������
	int getID();						//���������� �������������		
	double getTime();					//���������� ����� 
	int getState();						//���������� ������ ��������
	void setTime(double time);			//������������� �����
	void setState(int state);			//������������� ����� ������� ���������
};

#define TRANSACTH
#endif


