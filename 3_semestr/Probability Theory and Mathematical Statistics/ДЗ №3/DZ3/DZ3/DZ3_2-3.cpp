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
	int operators = 4;
	double P0, rejectionP, mathExpectOp, opLoadFactor;
	double r = (double)tService / (double)tApplication;

	for (int n = 1; n <= operators; n++)
	{
		bool flag = true;
		int m = 1;
		do
		{
			P0 = 0;
			rejectionP = 0;
			mathExpectOp = 0;
			opLoadFactor = 0;

			for (int i = 0; i <= n; i++)
			{
				P0 += pow(r, i) / factorial(i);
			}
			P0 += pow(r, (double)n + 1) * (1 - pow((r / n), m)) / (factorial(n) * (n - r));
			P0 = 1 / P0;

			rejectionP = P0 * pow(r, (double)m + (double)n) / (pow(n, m) * factorial(n));
			if ((rejectionP <= 0.01) && (m >= 4))
			{
				flag = false;
			}

			for (int i = 0; i <= n; i++)
			{
				mathExpectOp += i * P0 * pow(r, i) / factorial(i);
			}
			for (int i = 1; i <= m; i++)
			{
				mathExpectOp += n * P0 * pow(r, n + i) / (pow(n, i) * factorial(n));
			}

			opLoadFactor = mathExpectOp / n;

			cout << setprecision(5) << n << "-" << m << ": " << opLoadFactor << endl;

			m++;

		} while (flag);
		cout << endl;
	}

	return 0;
}