#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    cout.setf(ios::fixed);

    int n;
    double m[100];
    double x_ = 0, sigma = 0, S = 0;
    for (int i = 0; i < 100; i++)
    {
        cin >> m[i];
    }

#pragma region n=10
    n = 10;
    x_ = 0;
    for (int i = 0; i < n; i++)
        x_ += m[i];
    x_ = x_ / (double)n;

    sigma = 0;
    for (int i = 0; i < n; i++)
        sigma += (m[i] - x_) * (m[i] - x_);
    S = sigma;
    sigma = sigma / (double)n;
    S = S / ((double)n - 1);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "x_ = " << setprecision(10) << x_ << endl;
    cout << "sigma = " << setprecision(10) << sigma << endl;
    cout << "S = " << setprecision(10) << S << endl;
#pragma endregion

#pragma region n=25
    n = 25;
    x_ = 0;
    for (int i = 0; i < n; i++)
        x_ += m[i];
    x_ = x_ / n;

    sigma = 0;
    for (int i = 0; i < n; i++)
        sigma += (m[i] - x_) * (m[i] - x_);
    S = sigma;
    sigma = sigma / (double)n;
    S = S / ((double)n - 1);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "x_ = " << setprecision(10) << x_ << endl;
    cout << "sigma = " << setprecision(10) << sigma << endl;
    cout << "S = " << setprecision(10) << S << endl;
#pragma endregion

#pragma region n=50
    n = 50;
    x_ = 0;
    for (int i = 0; i < n; i++)
        x_ += m[i];
    x_ = x_ / n;

    sigma = 0;
    for (int i = 0; i < n; i++)
        sigma += (m[i] - x_) * (m[i] - x_);
    S = sigma;
    sigma = sigma / (double)n;
    S = S / ((double)n - 1);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "x_ = " << setprecision(10) << x_ << endl;
    cout << "sigma = " << setprecision(10) << sigma << endl;
    cout << "S = " << setprecision(10) << S << endl;
#pragma endregion

#pragma region n=100
    n = 100;
    x_ = 0;
    for (int i = 0; i < n; i++)
        x_ += m[i];
    x_ = x_ / n;

    sigma = 0;
    for (int i = 0; i < n; i++)
        sigma += (m[i] - x_) * (m[i] - x_);
    S = sigma;
    sigma = sigma / (double)n;
    S = S / ((double)n - 1);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "x_ = " << setprecision(10) << x_ << endl;
    cout << "sigma = " << setprecision(10) << sigma << endl;
    cout << "S = " << setprecision(10) << S << endl;
#pragma endregion

    return 0;
}
