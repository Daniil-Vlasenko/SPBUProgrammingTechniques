#include <iostream>
#include "functions.h"
#include <cstring>


int main(int argc, char *argv[]) {
    FILE *input, *output;
    if(argc == 1) {
        std::cout << "";
        return 1;
    }
    if(!(input = fopen(argv[1], "rb"))) {
        std::cout << "Error: there is no file to read." << std::endl;
        return -1;
    }

    char nameOfOutput[50] = "output.txt";
    if (argc == 3)
        strcpy(nameOfOutput, argv[2]);

    while((output = fopen(nameOfOutput, "rb"))){
        fclose(output);
        std::cout << "File " << nameOfOutput << " exists. " << "Do you want to overwrite the file? (y/n): ";
        char c; std::cin >> c;
        if(c == 'y')
            break;
        std::cout << "Enter name of the new file:";
        std::cin >> nameOfOutput;
    }
    output = fopen(nameOfOutput, "wb");

    unsigned int countOfDigits, countOfLetters;
    fseek(input, 0, SEEK_END);
    size_t size = ftell(input);
    fseek(input, 0, SEEK_SET);
    char *str = new char[size];
    fread(str, 1, size, input);
    functionWithoutLibrary(str, countOfDigits, countOfLetters);
    fwrite(str, 1, size, output);
    fprintf(output, "\ndigits: %d\nletters: %d\n", countOfDigits, countOfLetters);

    delete[] str;
    fclose(input);
    fclose(output);

    return 0;
}
