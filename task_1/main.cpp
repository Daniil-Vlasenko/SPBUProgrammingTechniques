#include <iostream>
using namespace std;


// Выдеоение памяти
void getMemory(int **& matrix, size_t rows, size_t cols){
    matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i)
        matrix[i] = new int[cols];
}

// Освобождение памяти
void freeMemory(int **& matrix, size_t rows, size_t cols){
    for (size_t i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete matrix;
    matrix = nullptr;
}

// Инициализация элементов массива
void initializationMatrix(int ** matrix, size_t rows, size_t cols, int number){
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            matrix[i][j] = number;
}

// Вывод массива
void printMatrix(int ** matrix, size_t rows, size_t cols){
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}


int main() {
    size_t const rows = 5, cols =6;
    int const number = 666;
    int **matrix = nullptr;

    getMemory(matrix, rows, cols);
    initializationMatrix(matrix, rows, cols, number);
    printMatrix(matrix, rows, cols);
    freeMemory(matrix, rows, cols);

    return 0;
}
