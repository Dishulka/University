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
	double P0, rejectionP, Pq;
	double r = (double)tService / (double)tApplication;

	for (int n = 1; n <= operators; n++)
	{
		bool flag = true;
		int m = 1;
		do
		{
			P0 = 0;
			rejectionP = 0;
			Pq = 0;

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

			Pq = P0 * pow(r, n) * (1 - pow((r / n), m)) / (factorial(n) * (1 - (r / n)));


			cout << setprecision(5) << n << "-" << m << ": " << Pq << endl;

			m++;

		} while (flag);
		cout << endl;
	}

	return 0;
}