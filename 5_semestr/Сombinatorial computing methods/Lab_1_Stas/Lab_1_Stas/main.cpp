#include <iostream>
using namespace std;

#define N 8
unsigned char word[] = "INTEGRAL";


void printSequance(int seq[]) {
	for (int i = 0; i < N; i++) {
		if (seq[i] == 1) {
			cout << word[i];
		}
	}
	cout << endl;
}

void leftShiftTransposition(int array[]) {
	int flag = 1;
	while (flag)  
	{
		flag = 0;
		for (int i = 0; i < N - 1; i++) {
			if (array[i] == 0 && array[i + 1] == 1) 
			{
				flag = 1;

				array[i] = 1;       
				array[i + 1] = 0;

				printSequance(array);

				if (i > 1)
				{
					int k = 1;
					for (int j = i - 2; j >= 0; j--)
					{
						if (array[j] == 1 && array[j + 1] == 0)
						{
							array[i - k] = 1;
							array[j] = 0;
							k++;
						}
					}
				}
				break;
			}
		}
	}
}

int main() {
	int sequance[N] = { 0, 0, 0, 0, 1, 1, 1, 1 };
	printSequance(sequance);

	leftShiftTransposition(sequance);

	return 0;
}

