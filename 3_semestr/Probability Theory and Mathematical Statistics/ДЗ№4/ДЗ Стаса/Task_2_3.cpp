#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    cout.setf(ios::fixed);

    int n;
    double x[100];
    double y[100];
    double x_ = 0, Sx = 0; 
    double y_ = 0, Sy = 0;
    double cov = 0, ro=0;
    for (int i = 0; i < 100; i++)
    {
        cin >> x[i];
    }
    for (int i = 0; i < 100; i++)
    {
        cin >> y[i];
    }

#pragma region n=10
    n = 10;
    x_ = 0;
    y_ = 0;
    for (int i = 0; i < n; i++)
    {
        x_ += x[i];
        y_ += y[i];
    }
    x_ = x_ / (double)n;

    Sx = 0;
    Sy = 0;
    for (int i = 0; i < n; i++)
    {
        Sx += (x[i] - x_) * (x[i] - x_);
        Sy += (y[i] - y_) * (y[i] - y_);
    }
    Sx = Sx / ((double)n - 1);
    Sx = sqrt(Sx);
    Sy = Sy / ((double)n - 1);
    Sy = sqrt(Sy);

    cov = 0; 
    for (int i = 0; i < n; i++)
    {
        cov += (x[i]-x_) * (y[i]-y_);
    }
    cov = cov / ((double)n - 1);

    ro = cov / (Sx * Sy);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "cov = " << cov << endl;
    cout << "ro = " << ro << endl;
#pragma endregion

#pragma region n=25
    n = 25;
    x_ = 0;
    y_ = 0;
    for (int i = 0; i < n; i++)
    {
        x_ += x[i];
        y_ += y[i];
    }
    x_ = x_ / (double)n;

    Sx = 0;
    Sy = 0;
    for (int i = 0; i < n; i++)
    {
        Sx += (x[i] - x_) * (x[i] - x_);
        Sy += (y[i] - y_) * (y[i] - y_);
    }
    Sx = Sx / ((double)n - 1);
    Sx = sqrt(Sx);
    Sy = Sy / ((double)n - 1);
    Sy = sqrt(Sy);

    cov = 0;
    for (int i = 0; i < n; i++)
    {
        cov += (x[i] - x_) * (y[i] - y_);
    }
    cov = cov / ((double)n - 1);

    ro = cov / (Sx * Sy);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "cov = " << cov << endl;
    cout << "ro = " << ro << endl;
#pragma endregion

#pragma region n=50
    n = 50;
    x_ = 0;
    y_ = 0;
    for (int i = 0; i < n; i++)
    {
        x_ += x[i];
        y_ += y[i];
    }
    x_ = x_ / (double)n;

    Sx = 0;
    Sy = 0;
    for (int i = 0; i < n; i++)
    {
        Sx += (x[i] - x_) * (x[i] - x_);
        Sy += (y[i] - y_) * (y[i] - y_);
    }
    Sx = Sx / ((double)n - 1);
    Sx = sqrt(Sx);
    Sy = Sy / ((double)n - 1);
    Sy = sqrt(Sy);

    cov = 0;
    for (int i = 0; i < n; i++)
    {
        cov += (x[i] - x_) * (y[i] - y_);
    }
    cov = cov / ((double)n - 1);

    ro = cov / (Sx * Sy);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "cov = " << cov << endl;
    cout << "ro = " << ro << endl;
#pragma endregion

#pragma region n=100
    n = 100;
    x_ = 0;
    y_ = 0;
    for (int i = 0; i < n; i++)
    {
        x_ += x[i];
        y_ += y[i];
    }
    x_ = x_ / (double)n;

    Sx = 0;
    Sy = 0;
    for (int i = 0; i < n; i++)
    {
        Sx += (x[i] - x_) * (x[i] - x_);
        Sy += (y[i] - y_) * (y[i] - y_);
    }
    Sx = Sx / ((double)n - 1);
    Sx = sqrt(Sx);
    Sy = Sy / ((double)n - 1);
    Sy = sqrt(Sy);

    cov = 0;
    for (int i = 0; i < n; i++)
    {
        cov += (x[i] - x_) * (y[i] - y_);
    }
    cov = cov / ((double)n - 1);

    ro = cov / (Sx * Sy);
    cout << endl;
    cout << "n = " << n << endl;
    cout << "cov = " << cov << endl;
    cout << "ro = " << ro << endl;
#pragma endregion

    return 0;
}
