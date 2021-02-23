#include <iostream>
using namespace std;

int main()
{
	int startcolor = 0;
	int done = 1;
	while (done != 3)
	{
		//cout << "done: " << done << endl;
		int color = startcolor;
		for (int x = 10; x > 0; x--)
		{
			//cout << "      x: " << x << endl;
			color %= 8;
			//cout << "          color: " << x << endl;
			int k = color;
			for (int y = 1; y <= 15; y++)
			{
				//cout << "                 y: " << y << endl;
				k %= 8;
				int sgm = 47 - k;
				//cout << "                 SGM: " << (47 - k) << endl;
				//cout << "                 k: " << (47 - k) << endl;
				k++;
			}
			++color;
		}
		++startcolor;
		startcolor %= 8;
		//cout << "startcolor: " << done << endl;
		++done;
	}
	
}