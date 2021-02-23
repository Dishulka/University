#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

double comb(int n, int k)
{
	if ((k == 0) || (k == n))
		return 1;
	if ((k == 1) || (k == n - 1))
		return n;

	int numStart;
	if (k > (n / 2))
		numStart = k + 1;
	else
		numStart = (n - k) + 1;

	int denom;
	if (k > (n / 2))
		denom = n - k;
	else
		denom = k;

	int amount;
	if (denom > (n - numStart))
		amount = n - numStart + 1;
	else
		amount = denom;

	double res = 1;
	int divider = 1, multiplier = numStart;
	for (int i = 1; i <= amount; ++i)
	{
		res *= multiplier;
		res /= divider;

		multiplier++;
		divider++;
	}

	return res;
}

double functionBernulli(int n, int k, double p, double q)
{
	return comb(n, k) * pow(p, k) * pow(q, n - k);
}

double dispersionRelative(int n, double p, double q)
{
	double res1 = 0, res2 = 0;
	for (int k = 0; k <= n; ++k)
	{
		double Bernulli = functionBernulli(n, k, p, q);
		res1 += Bernulli * (double)(k * k) / (double)(n * n);
		res2 += Bernulli * (double)(k) / (double)n;
	}

	res2 = pow(res2, 2);
	return (res1 - res2);
}

int main()
{
	int n;
	cout << "n = ";
	cin >> n;
	cout << endl;

	int r = 8, g = 7, b = 5;
	double p = (double)r / ((double)r + (double)g + (double)b);
	double q = 1 - p;

	double x = p / sqrt(dispersionRelative(n, p, q));
	cout << "F(" << setprecision(4) << x << ") = ";
	double F;
	cin >> F;

	cout << "P = " << setprecision(4) << 2 * F << endl;

	return 0;
}