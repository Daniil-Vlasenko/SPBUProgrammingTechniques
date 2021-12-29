#include <iostream>
#include <cstdio>
#include <cstring>


// Ввод строк происходит до ввода пустой строки
char **readStrings(int &sizeOfArray, int sizeOfBuffer){
    int numberOfNewString = 0;
    char **arrayOfStrings = new char *[sizeOfArray];
    char *buffer = new char [sizeOfBuffer];

    std::cout << "Вводите строки (конец ввода - пустая строка):" << std::endl;
    while (*fgets(buffer, sizeOfBuffer, stdin) != '\n'){
        if (numberOfNewString + 1 > sizeOfArray){
            char **newArrayOfStrings = new char *[(sizeOfArray *= 2)];
            for (size_t i = 0; i < sizeOfArray / 2; ++i)
                newArrayOfStrings[i] = arrayOfStrings[i];
            delete [] arrayOfStrings;
            arrayOfStrings = newArrayOfStrings;
        }
        size_t length = strlen(buffer);     // считает '/n',если есть, и не считает '/0'
        arrayOfStrings[numberOfNewString] = new char [length];
        strncpy(arrayOfStrings[numberOfNewString], buffer, length - 1);
        arrayOfStrings[numberOfNewString][length - 1] = '\0';
        ++numberOfNewString;
    }
    sizeOfArray = numberOfNewString;
    return arrayOfStrings;
}


int main() {
    int sizeOfArray = 10, sizeOfBuffer = 512;
    char ** arrayOfStrings = readStrings(sizeOfArray, sizeOfBuffer);
    for (auto i =  0; i < sizeOfArray; ++i)
        std::cout << arrayOfStrings[i] << std::endl;
    return 0;
}
