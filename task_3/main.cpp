#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

// Размер файла
size_t sizeOfFile(char const *fileName) {
    FILE *file = fopen(fileName, "rb");
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);
    return size;
}

// Чтение файла
char *readFile(char const *inputName) {
    FILE *input = fopen(inputName, "rb");
    size_t size = sizeOfFile(inputName);
    char *str = new char[size];
    fread(str, 1, size, input);
    fclose(input);
    return str;
}

// Создание индексного файла
FILE *createIndexFile(char const *inputName, char const *indexFileName) {
    FILE *indexFile = fopen(indexFileName, "wb");
    char *str = readFile(inputName), *tmpptr2 = str, *tmpptr1 = str, name[3]{};
    unsigned int site, length;

    // Вывод в файл
    while(*tmpptr1) {
        strncpy(name, tmpptr1, 2);
        site = tmpptr1 - str + 2;
        tmpptr1= strchr(tmpptr1, '#') + 1;
        length = tmpptr1 - tmpptr2 - 3;
        tmpptr2 = tmpptr1;

        fwrite(name, 1, 2, indexFile);
        fwrite(&site, sizeof(site), 1, indexFile);
        fwrite(&length, sizeof(length), 1, indexFile);
    }
    // Вывод в файл

    fclose(indexFile);
    return indexFile;
}

// Поиск строки по имени
bool findString(char const *name, unsigned int &site, unsigned int &length, char const *indexFileName) {
    FILE *indexFile = fopen(indexFileName, "rb");
    char nameStr[3]{};
    size_t size = sizeOfFile(indexFileName);
    while(size > ftell(indexFile)) {
        fread(nameStr, 1, 2, indexFile);
        if(!strcmp(name, nameStr)) {
            // Взятие положения и длины из индексного файла
            fread(&site, 1, 4, indexFile);
            fread(&length, 1, 4, indexFile);
            // Взятие положения и длины из индексного файла

            fclose(indexFile);
            return true;
        }
        fseek(indexFile, 8, SEEK_CUR);
    }
    fclose(indexFile);
    return false;
}

// Поиск строки по имени
char *getStr(unsigned int &site, unsigned int &length, char const *inputName) {
    FILE *input = fopen(inputName, "rb");

    // Чтение строки из файла
    fseek(input, site, SEEK_SET);
    char *str = new char[length + 1]{};
    fread(str, 1, length, input);
    // Чтение строки из файла

    return str;
}

// Перезапись строки
FILE *overwritingStr(char const *name, char const *str, char const *indexFileName, char const *inputName) {
    FILE *input = fopen(inputName, "rb");
    char *inputStr = readFile(inputName), *newInputStr = new char[sizeOfFile(inputName)]{};
    unsigned int site = 0, length = 0;
    findString(name, site, length, indexFileName);

    strncpy(newInputStr, inputStr, site);
    strncat(newInputStr, str, length);
    unsigned int lengthNewStr = strlen(str);
    while(lengthNewStr < length) {
        ++lengthNewStr;
        strcat(newInputStr, " ");
    }
    strncat(newInputStr, inputStr + site + length, sizeOfFile(inputName) - site - length);

    fclose(input);
    input = fopen(inputName, "wb");
    fwrite(newInputStr, 1, strlen(newInputStr), input);
    fclose(input);
    return input;
}

int main() {
    chdir("../");   // Адрес, где лежит файл input.txt
    FILE *input;
    char inputName[10] = "input.txt", indexFileName[14] = "indexFile.b";
    if(!(input = fopen(inputName, "rb"))) {
        cout << "Error: there is no file to read." << endl;
        return -1;
    }

    createIndexFile(inputName, indexFileName);
    unsigned int length, site;
    findString("ew", site, length, indexFileName);
    char *str = getStr(site, length, inputName);
    std::cout << str << std:: endl;
    overwritingStr("ew", "1s", indexFileName, inputName);
    str = getStr(site, length, inputName);
    std::cout << str << std:: endl;

    return 0;
}