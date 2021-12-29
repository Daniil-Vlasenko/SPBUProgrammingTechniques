#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


void output(int  N, int length){
    int NLocal = N,  countOfDigitsInN = 1, countOfDigitsInX = 1;
    long x = 1, factorial = 1;
    double sqrt1_2x, sqrt1_3x;

    for (int i = 1; i <= N; ++i)
            factorial *= i;
    while(factorial /= 10)
        ++countOfDigitsInX;
    while(NLocal /= 10)
        ++countOfDigitsInN;

    cout << "|" << setw(countOfDigitsInN) << "N" << "|" << setw(countOfDigitsInX + 2) << "x " << "|"
              << setw(length + 7) << "x^(1/2)" << "|" << setw(length + 7) << "x^(1/3)" << "|"
              << endl;

    long factorial1 = 1;
    std::cout << std::setprecision(length);
    for (int i = 1; i <= N; ++i){
        factorial1 *= i;

//        x = (i & 1 ? -1 : 1) * factorial1 ;
        x = i & 1 ? -factorial1 : factorial1;
        sqrt1_2x = sqrt(x > 0 ? x : -x);
        sqrt1_3x = pow((x > 0 ? x : -x), 1./3);

        if (i & 1)
            cout << "|" << setw(countOfDigitsInN) << i << "|" << setw(countOfDigitsInX + 1) << x << ".|"
                 << "i" << setw(length + 6) << scientific << sqrt1_2x << "|"
                 << "-" << setw(length + 6) << scientific << sqrt1_3x << "|"
                 << endl;
        else
            cout << "|" << setw(countOfDigitsInN) << i << "|" << setw(countOfDigitsInX + 1) << x << ".|"
                 << setw(length + 7) << scientific << sqrt1_2x << "|"
                 << setw(length + 7) << scientific << sqrt1_3x << "|"
                 << endl;
    }
}


int main() {
    int const N = 10, length = 20;
    output(N, length);

    return 0;
}
