#include <iostream>
#define N 5
using namespace std;


void printPermutation(int permutation[])
{
	for (int i = 0; i < N; i++)
	{
		if (i == 0)
			cout << "A";
		else if (i == 1)
			cout << "B";
		else if (i == 2)
			cout << "C";
		else if (i == 3)
			cout << "D";
		else if (i == 4)
			cout << "E";

		cout << permutation[i] << " ";
	}
}


void rotationPermutation(int permutation[], int n)
{
	int firstNumPermutation = permutation[0];
	for (int i = 0; i < n; i++)
	{
		permutation[i] = permutation[i + 1];
	}

	permutation[n] = firstNumPermutation;
}


int checkBlackCells(int permutation[])
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		if ((((i + 1) % 2 == 0) && (permutation[i] % 2 == 0)) || (((i + 1) % 2 != 0) && (permutation[i] % 2 != 0)))
			++count;
	}
	if (count == N)
		return true;
	else
		return false;
}


void algorithmRotatingPermutations(int permutation[])
{
	for (int i = 0; i < N - 3; i++)
	{
		for (int j = 0; j < N - 2; j++)
		{
			for (int k = 0; k < N - 1; k++)
			{
				for (int m = 0; m < N; m++)
				{
					printPermutation(permutation);
					if (checkBlackCells(permutation))
						cout << " - all black cells" << endl;
					else
						cout << endl;
					rotationPermutation(permutation, N - 1);
				}
				rotationPermutation(permutation, N - 2);
			}
			rotationPermutation(permutation, N - 3);
		}
		rotationPermutation(permutation, N - 4);
	}
}


int main()
{
	int permutation[N];

	for (int i = 0; i < N; i++)
	{
		permutation[i] = i + 1;
	}

	algorithmRotatingPermutations(permutation);

	return 0;
}
