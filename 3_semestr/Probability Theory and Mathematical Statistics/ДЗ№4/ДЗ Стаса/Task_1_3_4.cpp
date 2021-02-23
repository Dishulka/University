#include <iostream>

using namespace std;
int main()
{

    cout.setf(ios::fixed);

    double m[50];
    for (int i = 0; i < 50; i++)
    {
        cin >> m[i];
    }
    for (int i = 0; i <= 9; i++)
    {
        int n = 0;
        for (int j = 0; j < 50; j++)
        {
            if (m[j] >= (10 * (double)i) && m[j] <= (10 * (double)i + 9))
                n++;
            
        }
        cout << "[" << 10 * i << ";" << 10 * i + 9 << "]=" << n << endl;
    }
    double xi=0;
    for (int i = 0; i < 10; i++)
    {
        double a;
        cin >> a;
        xi += (a - 50 * 0.1) * (a - 50 * 0.1);
    }
    cout << endl << endl << xi / (5);
    return 0;
}
