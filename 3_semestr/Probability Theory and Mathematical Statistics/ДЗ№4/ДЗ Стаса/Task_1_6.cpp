#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    cout.setf(ios::fixed);

    int n;
    double m[50];
    double x_ = 0, sigma = 0, S = 0;
    for (int i = 0; i < 50; i++)
    {
        cin >> m[i];
    }

#pragma region n=5
    n = 5;
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
    cout << "x_ = " << setprecision(10) << x_ << "\t diff: " << x_ - 49.5 << endl;
    cout << "sigma = " << setprecision(10) << sigma << "\t diff: " << sigma - 816.75 << endl;
    cout << "S = " << setprecision(10) << S << "\t diff: " << S - 816.75 << endl;
#pragma endregion

#pragma region n=10
    n = 10;
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
    cout << "x_ = " << setprecision(10) << x_ << "\t diff: " << x_ - 49.5 << endl;
    cout << "sigma = " << setprecision(10) << sigma << "\t diff: " << sigma - 816.75 << endl;
    cout << "S = " << setprecision(10) << S << "\t diff: " << S - 816.75 << endl;
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
    cout << "x_ = " << setprecision(10) << x_ << "\t diff: " << x_ - 49.5 << endl;
    cout << "sigma = " << setprecision(10) << sigma << "\t diff: " << sigma - 816.75 << endl;
    cout << "S = " << setprecision(10) << S << "\t diff: " << S - 816.75 << endl;
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
    cout << "x_ = " << setprecision(10) << x_ << "\t diff: " << x_ - 49.5 << endl;
    cout << "sigma = " << setprecision(10) << sigma <<"\t diff: "<<sigma-816.75<< endl;
    cout << "S = " << setprecision(10) << S << "\t diff: " << S - 816.75 << endl;
#pragma endregion

    return 0;
}
