#include <iostream>
#include <cmath>
using namespace std;


int gcdf(int a, int b) {
    int gcd;
    a = abs(a); b = abs(b);

    if (a == 0 and b == 0) { return 0; }
    else if (a == 0) { return b; }
    else if (b == 0) { return a; }
    else
    {
        while (a != b) {
            if (a > b) {
                int tmp = a;
                a = b;
                b = tmp;
            }
            b-=a;
        }
        gcd = a;
    }

    return gcd;
}

int main() {

    cout << gcdf(0, 0) << endl;
    cout << gcdf(0, 6) << endl;
    cout << gcdf(6, 0) << endl;
    cout << gcdf(2147483646, 2147483646 / 2) << endl;
    cout << gcdf(28, -4) << endl;
    cout << gcdf(-36, 27) << endl;
    cout << gcdf(-36, -27) << endl;
    cout << gcdf(7, 11) << endl;
    return 0;
}


