#include <iostream>
#include <cmath>


// Пусть есть магазин, время от времени заходят покупатели. При определенном допущении время между
// появлением двух последовательных покупателей будет случайной величиной с экспоненциальным распределением.
// Среднее время ожидания нового покупателя равно 1/lambda. Сам параметр lambda тогда может быть интерпретирован как
// среднее число новых покупателей за единицу времени. Пусть lambda = 1, единица времени = час. Хотим узнать,
// за какой промежуток времени придет новый покупатель с вероятностью p. Для этой задачи точность 1./60, т.е.
// минута кажется вполне разумной.
// Пришлось объявить глобальную переменную, т.к. функциональным указателям нельзя передать аргумент по умолчанию,
// не обернув в другую функцию, имеющую аргумент по умолчанию...
const double p = 0.9;
double function1(double x) {return 1 - exp(-1 * x) - p;}

inline bool differentSin(double x, double y) {return (x < 0) != (y < 0);}

using PF = double(*)(double);
bool bisectionMethod(PF func, double left, double right, double &res, double epsX = 1./60) {
    double length = right - left, center, valueLeft = func(left), valueRight = func(right), valueCenter;
    if(valueLeft == 0) {res = left; return true;}
    if(valueRight == 0) {res = right; return true;}
    if(!differentSin(valueLeft, valueRight)) {return false;}

    while(length > epsX) {
        length /= 2;
        center = left + length;
        valueCenter = func(center);
        if(valueCenter == 0) {break;}
        if (!differentSin(valueLeft, valueCenter)) {
            left = center;
            valueLeft = valueCenter;
        }
    }

    res = center;
    return true;
}

int main() {
    PF pf = function1;
    double res{}, left = 0, right = 24;

    if(bisectionMethod(pf, left, right, res))
        std::cout << "Root of the function on the interval [" << left << ", " << right << "]: " << res;
    else
        std::cout << "Function doesn't have roots on the interval [" << left << ", " << right << "].";

    return 0;
}