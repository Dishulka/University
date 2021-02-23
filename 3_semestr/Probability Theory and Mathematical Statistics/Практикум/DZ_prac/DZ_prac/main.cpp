#include <iostream>
#include <fstream>
#include <list>
#include <iterator>

#include "Channel.h"
#include "Generate.h"
#include "Queue.h"
#include "State.h"
#include "Terminate.h"
#include "Transact.h"

using namespace std;

int main()
{
	int r1 = 8;
	int g1 = 7;
	int b1 = 5;
	int rnd = 20;
	int endTime = 60;

	std::ofstream file;
	file.open("result.txt");
	if (!file.is_open())
	{
		std::cout << "Cannot use file" << std::endl;
		return 1;
	}
	srand(rnd);

	GENERATE generate(0, r1 + g1 + b1);
	generate.setState(1);

	OPERATOR* operators[2];
	operators[0] = new OPERATOR(r1, r1 + g1 + b1);
	operators[0]->setState(4);
	operators[1] = new OPERATOR(g1, r1 + g1 + b1);
	operators[1]->setState(4);

	TERMINATE Terminator;

	list <Transact*> transacts;
	Transact* finish = new Transact();
	finish->setState(0);
	finish->setTime(endTime);
	transacts.push_front(finish);
	Transact* start = new Transact();
	start->setState(0);
	start->setTime(generate.getTime());
	transacts.push_front(start);
	list <Transact*> ::iterator iter;

	bool isFinish = false;
	while (!isFinish)
	{
		double tMin = (*transacts.begin())->getTime();
		for (iter = transacts.begin(); iter != transacts.end(); ++iter)
		{
			if (tMin > (*iter)->getTime())
				tMin = (*iter)->getTime();
		}
		for (iter = transacts.begin(); iter != transacts.end(); ++iter)
		{
			if ((*iter)->getTime() == tMin)
			{
				bool flag;
				switch ((*iter)->getState())
				{
				case 0:
					if ((**iter).getID() == (*finish).getID())
					{
						isFinish = true;
					}
					else
					{
						generate.useTransact(**iter, file);
						Transact* newTrans = new Transact();
						newTrans->setTime(generate.getTime());
						transacts.push_back(newTrans);
					}
					break;
				case 1:
					flag = false;
					for (int i = 0; i < sizeof(operators) / sizeof(*operators); ++i) {
						if (!(operators[i]->isBusy())) {
							(*iter)->setState(i + 2);
							operators[i]->useTransact(**iter, file);
							flag = true;
							break;
						}
					}
					if (!flag) 
					{
						int min = operators[0]->getSize();
						int minIndex = 0;
						for (int i = 0; i < sizeof(operators) / sizeof(*operators); ++i)
						{
							if (operators[i]->getSize() < min) {
								minIndex = i;
								min = operators[i]->getSize();
							}
						}
						(*iter)->setState(minIndex + 2);
						operators[minIndex]->useTransact(**iter, file);
					}
					break;
				case 2:
					operators[0]->useTransact(**iter, file);
					break;
				case 3:
					operators[1]->useTransact(**iter, file);
					break;
				case 4:
					Terminator.useTransact(**iter, file);
					iter = transacts.erase(iter);
					break;
				}
			}
		}
	}
	file.close();
	return 0;
}
