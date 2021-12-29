#include <iostream>
#include <cstring>
#include "functions.h"
using namespace std;


int main() {
    unsigned int countOfDigits1, countOfLetters1, countOfDigits2, countOfLetters2;
    int const count = 5;
    char str[count][10] = {"rwert", "RTYIO", "12345", "!@#$%", "q 2%E",};
    for(int i = count; i < 5; ++i) {
        char strf1[10], strf2[10];
        strcpy(strf1, str[i]), strcpy(strf2, str[i]);
        functionWithoutLibrary(strf1, countOfDigits1, countOfLetters1);
        functionWithLibrary(strf2, countOfDigits2, countOfLetters2);
        cout << "Строка:" << str[i] << endl;
        cout << "Результат программы без библиотечных функций:" << strf1 << '\n'
             << "Число чисел:" << countOfDigits1 << endl
             << "Число букв:" << countOfLetters1 << endl;
        cout << "Результат программы c библиотечными функциями:" << strf2 << '\n'
             << "Число чисел:" << countOfDigits2 << endl
             << "Число букв:" << countOfLetters2 << endl << endl;
    }










    return 0;
}
// Что быстрее c >= '0' или c >= 48?