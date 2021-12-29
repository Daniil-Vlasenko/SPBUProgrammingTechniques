#include <iostream>


// Вывод массива
int printMatrix(int rows, int cols, int (matrix)[5][5]){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 1;
}

// Сортировка статического массива
int sortSMatrix(int rows, int cols, int matrix[5][5]) {
    int countOFGoodStrings = 0;

    for (int i = 0; i < rows; ++i) {
        int countOfZeros = 0;
        // Выявление строк, в которых более 3 нулей
        for (int j = 0; j < cols; ++j)
            if (matrix[i][j] == 0)
                ++countOfZeros;
        // Сортировка массива
        if (countOfZeros <= 3) {
            if (countOFGoodStrings < i){
                for (int k = 0; k < cols; ++k){
                    matrix[countOFGoodStrings][k] = matrix[i][k];
                }
            }
            ++countOFGoodStrings;
        }

    }
    return countOFGoodStrings;
}

int main()
{
    const int rows = 5, cols = 5;

    int SMatrix1[rows][cols] = {{1,1,1,1,1},{1,1,1,1,0},{1,1,1,0,0},{1,1,0,0,0},{1,1,1,1,1}};
    int SMatrix2[rows][cols] = {{0,0,0,0,0},{0,0,0,0,1},{0,0,0,1,0},{0,0,1,0,0},{0,1,0,0,0}};
    int SMatrix3[rows][cols] = {{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0}};
    int SMatrix4[rows][cols] = {{0,1,1,1,1},{0,0,0,0,0},{1,1,0,1,1},{0,0,0,0,0},{1,1,1,1,0}};

    std::cout << "Матрица 1:" << std::endl;
    printMatrix(rows, cols, SMatrix1);
    std::cout << "Новая матрица:" << std::endl;
    int goodSRows1 = sortSMatrix(rows, cols, SMatrix1);
    printMatrix(goodSRows1, cols, SMatrix1);
    std::cout << std::endl;

    std::cout << "Матрица 2:" << std::endl;
    printMatrix(rows, cols, SMatrix2);
    std::cout << "Новая матрица:" << std::endl;
    int goodSRows2 = sortSMatrix(rows, cols, SMatrix2);
    printMatrix(goodSRows2, cols, SMatrix2);
    std::cout << std::endl;

    std::cout << "Матрица 3:" << std::endl;
    printMatrix(rows, cols, SMatrix3);
    std::cout << "Новая матрица:" << std::endl;
    int goodSRows3 = sortSMatrix(rows, cols, SMatrix3);
    printMatrix(goodSRows3, cols, SMatrix3);
    std::cout <<  std::endl;

    std::cout << "Матрица 4:" << std::endl;
    printMatrix(rows, cols, SMatrix4);
    std::cout << "Новая матрица:" << std::endl;
    int goodSRows4 = sortSMatrix(rows, cols, SMatrix4);
    printMatrix(goodSRows4, cols, SMatrix4);

    return 0;
}