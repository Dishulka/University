#include <iostream>
#include <vector>
using namespace std;

#define HEIGHT 3
#define WEIGHT 2
#define DEPHT 2
//Right, Down
int main()
{
	vector<vector<vector<bool>>> maze;
	maze.resize(HEIGHT);
	for (int i = 0; i < HEIGHT; ++i)
	{
		maze[i].resize(WEIGHT);
		for (int j = 0; j < WEIGHT; ++j)
			maze[i][j].resize(DEPHT);
	}

	maze[0][0] = { 1,0 };
	maze[1][0] = { 0,0 };
	maze[2][0] = { 0,1 };
	maze[0][1] = { 1,0 };
	maze[1][1] = { 1,1 };
	maze[2][1] = { 1,1 };


	for (int i = 0; i < HEIGHT; ++i)
	{
		if (i == 0)
		{
			for (int j = 0; j < (HEIGHT + 2); j++)
				cout << '#';
			cout << endl;
		}

		cout << '#';
		for (int j = 0; j < WEIGHT; ++j)
		{
			cout << '.';
			if (maze[i][j][0] == 1)
				cout << '#';
			else
				cout << '-';
		}
		cout << endl;

		cout << '#';
		for (int j = 0; j < WEIGHT; ++j)
		{
			if (maze[i][j][1] == 0)
				cout << '|';
			else
				cout << '#';
			cout << '#';
		}
		cout << endl;

	}


	return 0;
}
