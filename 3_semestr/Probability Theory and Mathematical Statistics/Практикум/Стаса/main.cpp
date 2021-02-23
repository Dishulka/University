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
	//Start init
	unsigned long long int r1 = 11;
	unsigned long long int g1 = 10;
	unsigned long long int b1 = 11;
	std::cout << "Enter random seed: ";
	unsigned int rnd=20;
	//std::cin >> rnd;
	std::cout << "Enter time of simulation: ";
	int endTime=60;
	//std::cin >> endTime;
	std::ofstream file;
	file.open("result.txt");
	if (!file.is_open())
	{
		std::cout << "Cannot use file" << std::endl;
		return 1;
	}
	srand(rnd);

	//Create generator transacts
	Generate generate(0, r1 + g1 + b1);
	generate.setNextState(1);

	//Create channels
	Channel* channels[2];
	channels[0] = new Channel(r1, r1 + g1 + b1);
	channels[0]->setNextState(4);
	channels[1] = new Channel(g1, r1 + g1 + b1);
	channels[1]->setNextState(4);

	//Create TERMINATOR
	Terminate Terminator;

	// Create list of all transacts
	std::list <Transact*> transacts;
	Transact* end = new Transact();
	end->setState(0);
	end->setTimeNextEvent(endTime);
	transacts.push_front(end);
	Transact* start = new Transact();
	start->setState(0);
	start->setTimeNextEvent(generate.getTime());
	transacts.push_front(start);
	list <Transact*> ::iterator iter;

	//Start main cycle

	bool isEnd = false;
	while (!isEnd)
	{
		double minTime = (*transacts.begin())->getTimeNextEvent();
		for (iter = transacts.begin(); iter != transacts.end(); ++iter)
		{
			minTime = minTime > (*iter)->getTimeNextEvent() ? (*iter)->getTimeNextEvent() : minTime;
		}
		for (iter = transacts.begin(); iter != transacts.end(); ++iter)
		{
			if ((*iter)->getTimeNextEvent() == minTime)
			{
				bool flag;
				switch ((*iter)->getState())
				{
				case 0:
					if ((**iter).getID() == (*end).getID())
					{
						isEnd = true;
					}
					else
					{
						generate.useTransact(**iter, file);
						Transact* newTrans = new Transact();
						newTrans->setTimeNextEvent(generate.getTime());
						transacts.push_back(newTrans);
					}
					break;
				case 1:
					flag = false;
					for (int i = 0; i < sizeof(channels) / sizeof(*channels); ++i) {
						if (!(channels[i]->isOccupied())) {
							(*iter)->setState(i + 2);
							channels[i]->useTransact(**iter, file);
							flag = true;
							break;
						}
					}
					if (!flag) 
					{
						int min = channels[0]->getQueueSize();
						int minIndex = 0;
						for (int i = 0; i < sizeof(channels) / sizeof(*channels); ++i) 
						{
							if (channels[i]->getQueueSize() < min) {
								minIndex = i;
								min = channels[i]->getQueueSize();
							}
						}
						(*iter)->setState(minIndex + 2);
						channels[minIndex]->useTransact(**iter, file);
					}
					break;
				case 2:
					channels[0]->useTransact(**iter, file);
					break;
				case 3:
					channels[1]->useTransact(**iter, file);
					break;
				case 4:
					Terminator.useTransact(**iter, file);
					iter = transacts.erase(iter);
					break;
				}
			}
		}






	}

	//Close file
	file.close();
	return 0;
}
