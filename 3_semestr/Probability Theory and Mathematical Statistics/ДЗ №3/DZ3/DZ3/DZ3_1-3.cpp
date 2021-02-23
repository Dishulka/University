#include <iostream>
#include <iomanip>
using namespace std;

int factorial(int n)
{
	int res = 1;
	for (int i = 1; i <= n; ++i)
	{
		res *= i;
	}
	return res;
}


int main()
{
	int tService = 11, tApplication = 20;
	int operators = 1;
	double mathExpect, P0, rejectionP, opLoadFactor;
	double r = (double)tService / (double)tApplication;

	bool flag = true;
	do
	{
		P0 = 0;
		mathExpect = 0;
		for (int i = 0; i <= operators; i++)
		{
			P0 += pow(r, i) / factorial(i);
		}
		P0 = 1 / P0;

		rejectionP = P0 * pow(r, operators) / factorial(operators);

		for (int i = 0; i <= operators; i++)
		{
			mathExpect += i * P0 * pow(r, i) / factorial(i);
		}

		opLoadFactor = mathExpect / (double)operators;

		cout << setprecision(5) << operators << ": " << opLoadFactor << endl;

		if (rejectionP <= 0.01)
			flag = false;
		operators++;
	} while (flag);

	return 0;
}