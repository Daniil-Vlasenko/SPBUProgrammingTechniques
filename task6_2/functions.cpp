#include "functions.h"
#include <cstring>
#include <iostream>

// Временная сложность алгоритма (при строке букв высокого регистра DFSFWESFES) - n * 22 * O(1) ~ O(22n).
char *functionWithoutLibrary(char *str, unsigned int &countOfDigits, unsigned int &countOfLetters) {
    countOfDigits = 0, countOfLetters = 0;
    for(char *c = str; *c != '\0'; ++c) {
        if ((*c >= 48) && (*c <= 57)){
            ++countOfDigits;
            *c = ' ';
        }
        else if((*c >= 65) && (*c <= 90) || (*c >= 97) && (*c <= 122))
            ++countOfLetters;
    }
    return str;
}

// В худшем случае временная сложность алгоритма (при строке MMMM...) - n(62*7*O(1) + 11*O(1)) ~ O(445n)
char *functionWithLibrary(char *str, unsigned int &countOfDigits, unsigned int &countOfLetters) {
    countOfDigits = 0, countOfLetters = 0;
    char digitsAndLetter[63] = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    char *c = str;
    while((c = strpbrk(c , digitsAndLetter))) {
        if (isdigit(*c)) {
            *c = ' ';
            ++countOfDigits;
        }
        else if (islower(*c) || isupper(*c))
            ++countOfLetters;
        ++c;
    }

    return str;
}