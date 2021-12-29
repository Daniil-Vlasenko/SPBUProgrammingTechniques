#include <iostream>
#include <cmath>
#include <climits>
#include <cfloat>
using namespace std;


double task1_1(double x, int n)
{
    double res;
    if (x - n > 0)
    {
        res = sqrt(n) + (x - n) / 2 - 8;
    } else
    {
        res = sqrt(n) + (n - x) / 2 - 8;
    }

    return res;
}

double task1_2(double x, int n)
{

    // double res = (x - n > 0) ? sqrt(n) + (x - n) / 2 - 8 : sqrt(n) + (n - x) / 2 - 8;
    // Переписал оператор ?:
    double res = sqrt(n) - 8 + ((x - n > 0) ? (x - n) : (n - x)) / 2;
    return res;
}

int main()
{
    cout << task1_1(0.0, 1) << endl;
    cout << task1_1(4 - 1e-3, 4 ) << endl;
    cout << task1_1(-DBL_MAX, 1) << endl;
    cout << task1_1(0, INT_MAX) << endl;
    cout << task1_1(DBL_MAX, INT_MAX) << endl;

    cout << endl;

    cout << task1_2(0.0, 1) << endl;
    cout << task1_2(4 - 1e-3, 4 ) << endl;
    cout << task1_2(-DBL_MAX, 1) << endl;
    cout << task1_2(0, INT_MAX) << endl;
    cout << task1_2(DBL_MAX, INT_MAX) << endl;

    return 0;
}
