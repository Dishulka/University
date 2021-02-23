#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    cout.setf(ios::fixed);

    int n;
    double x[100];
    double x_ = 0, Sx = 0;
    double alpha[2] = { 0.1,0.001 };
    double t[2];
    for (int i = 0; i < 100; i++)
    {
        cin >> x[i];
    }

#pragma region n=10
    n = 10;
    x_ = 0;
    for (int i = 0; i < n; i++)
    {
        x_ += x[i];
    }
    x_ = x_ / (double)n;

    Sx = 0;
    for (int i = 0; i < n; i++)
        Sx += (x[i] - x_) * (x[i] - x_);
    Sx = Sx / ((double)n - 1);
    Sx = sqrt(Sx);

    cout << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "n-1 = " << n-1 << endl;
        cout << "alpha = " << alpha[i] << endl;
        cout << "t = ";
        cin >> t[i];
    }
    for (int i = 0; i < 2; i++)
    {
        cout << endl<<endl;
        cout << "n = " << n << endl;
        cout << "alpha = " << alpha[i]<<endl;
        cout << x_ - t[i] * Sx / sqrt(n)<<"< M <"<< x_ + t[i] * Sx / sqrt(n);
        cout << endl << endl;
    }
#pragma endregion

#pragma region n=25
    n = 25;
    x_ = 0;
    for (int i = 0; i < n; i++)
    {
        x_ += x[i];
    }
    x_ = x_ / (double)n;

    Sx = 0;
    for (int i = 0; i < n; i++)
        Sx += (x[i] - x_) * (x[i] - x_);
    Sx = Sx / ((double)n - 1);
    Sx = sqrt(Sx);
    cout << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "n-1 = " << n - 1 << endl;
        cout << "alpha = " << alpha[i] << endl;
        cout << "t = ";
        cin >> t[i];
    }
    for (int i = 0; i < 2; i++)
    {
        cout << endl << endl;
        cout << "n = " << n << endl;
        cout << "alpha = " << alpha[i] << endl;
        cout << x_ - t[i] * Sx / sqrt(n) << "< M <" << x_ + t[i] * Sx / sqrt(n);
        cout << endl << endl;
    }
#pragma endregion

#pragma region n=60
    n = 60;
    x_ = 0;
    for (int i = 0; i < n; i++)
    {
        x_ += x[i];
    }
    x_ = x_ / (double)n;

    Sx = 0;
    for (int i = 0; i < n; i++)
        Sx += (x[i] - x_) * (x[i] - x_);
    Sx = Sx / ((double)n - 1);
    Sx = sqrt(Sx);
    cout << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "n-1 = " << n - 1 << endl;
        cout << "alpha = " << alpha[i] << endl;
        cout << "t = ";
        cin >> t[i];
    }
    for (int i = 0; i < 2; i++)
    {
        cout << endl << endl;
        cout << "n = " << n << endl;
        cout << "alpha = " << alpha[i] << endl;
        cout << x_ - t[i] * Sx / sqrt(n) << "< M <" << x_ + t[i] * Sx / sqrt(n);
        cout << endl << endl;
    }
#pragma endregion
    return 0;
}
