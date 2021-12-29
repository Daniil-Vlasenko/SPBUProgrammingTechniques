#include <iostream>
#include "R64M.hpp"
#include <iomanip>
using namespace std;


double square(long countOfPoints){
    double realSquareOfFigure = 4 - 4./3, squareOfFigure = 0, x, y;
    double const squareOfArea = 4;
    long countOfPointsInFigure = 0;

    for(long i = 1, j = 100; i <= countOfPoints; ++i){
        x = rnunif() * 2 - 1;
        y = rnunif() * 2;
        if(y >= 2 * x * x)
            ++countOfPointsInFigure;
        if(i == j){
            squareOfFigure = (double) countOfPointsInFigure / i * squareOfArea;
            cout << "Для N = " << i << " результат программы = " << squareOfFigure << ", погрешность: "
                 << abs(realSquareOfFigure - squareOfFigure) << endl;
            j *= 100;
        }
    }
    return squareOfFigure;
}


int main() {
    unsigned long seed =  time(0);
    rninit(seed); //1636018125
    int const N = 1000000;

    cout << fixed << setprecision(20);

    square(N);

    rnunif();
    return 0;
}
