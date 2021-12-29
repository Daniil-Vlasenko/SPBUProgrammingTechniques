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
//int sortSMatrix(int rows, int cols, int matrix[5][5]) {
//    int goodStrings[rows]; // Строки, которые нужно вывести в итоговой матрице
//    int countOFGoodStrings = rows;
//    for (int i = 0; i < rows; ++i)
//        goodStrings[i] = 1;
//
//    // Выявление строк, в которых более 3 нулей
//    for (int i = 0; i < rows; ++i) {
//        int countOfZeros = 0;
//        for (int j = 0; j < cols; ++j) {
//            if (matrix[i][j] == 0) {
//                ++countOfZeros;
//                if (countOfZeros > 3) {
//                    --countOFGoodStrings;
//                    goodStrings[i] = 0;
//                    break;
//                }
//            }
//        }
//    }
//    // Сортировка статического массива
//    int stringForGoodString = 0;
//    for (int i = 0; i < rows; ++i){
//        if (goodStrings[i] == 1){
//            for (int j = 0; j < cols; ++j){
//                matrix[stringForGoodString][j] = matrix[i][j];
//            }
//            ++stringForGoodString;
//        }
//    }
//
//    return countOFGoodStrings;
//}

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

// Выделение памяти для динамического массива
void getMemory(int **&matrix, size_t rows, size_t cols){
    matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i)
        matrix[i] = new int[cols];
}

// Вывод динамического массива
void printMatrix(int ** matrix, size_t rows, size_t cols){
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}

// Сортировка динамического массива
//int sortDMatrix(int **&matrix, int rows, int cols){
//    int goodStrings[rows]; // Строки, которые нужно вывести в итоговой матрице
//    int countOFGoodStrings = rows;
//    for (int i = 0; i < rows; ++i)
//        goodStrings[i] = 1;
//
//    // Выявление строк, в которых более 3 нулей
//    for (int i = 0; i < rows; ++i) {
//        int countOfZeros = 0;
//        for (int j = 0; j < cols; ++j) {
//            if (matrix[i][j] == 0) {
//                ++countOfZeros;
//                if (countOfZeros > 3) {
//                    --countOFGoodStrings;
//                    delete[] matrix[i];
//                    matrix[i] = nullptr;
//                    goodStrings[i] = 0;
//                    break;
//                }
//            }
//        }
//    }
//    // Сортировка динамического массива
//    int **newMatrix;
//    getMemory(newMatrix, countOFGoodStrings, cols);
//    int stringForGoodString = 0;
//    for (int i = 0; i < rows; ++i){
//        if (goodStrings[i] == 1){
//            newMatrix[stringForGoodString] = matrix[i];
//            ++stringForGoodString;
//        }
//    }
//    delete matrix;
//    matrix = newMatrix;
//
//    return countOFGoodStrings;
//}

// Сортировка динамического массива
int sortDMatrix(int **&matrix, int rows, int cols){
    int countOFGoodStrings = rows;

    // Выявление строк, в которых более 3 нулей, и освобождение памяти
    for (int i = 0; i < rows; ++i) {
        int countOfZeros = 0;
        for (int j = 0; j < cols; ++j)
            if (matrix[i][j] == 0)
                ++countOfZeros;
        if (countOfZeros > 3) {
            --countOFGoodStrings;
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
    }
    // Сортировка динамического массива
    int **newMatrix;
    getMemory(newMatrix, countOFGoodStrings, cols);
    int stringForGoodString = 0;
    for (int i = 0; i < rows; ++i){
        if(matrix[i] != nullptr){
            newMatrix[stringForGoodString] = matrix[i];
            ++stringForGoodString;
        }
    }
    delete matrix;
    matrix = newMatrix;

    return countOFGoodStrings;
}

int main()
{
    const int rows = 5, cols = 5;

    int SMatrix1[rows][cols] = {{1,1,1,1,1},{1,1,1,1,0},{1,1,1,0,0},{1,1,0,0,0},{1,1,1,1,1}};
    int SMatrix2[rows][cols] = {{0,0,0,0,0},{0,0,0,0,1},{0,0,0,1,0},{0,0,1,0,0},{0,1,0,0,0}};
    int SMatrix3[rows][cols] = {{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0}};
    int SMatrix4[rows][cols] = {{0,1,1,1,1},{0,0,0,0,0},{1,1,0,1,1},{0,0,0,0,0},{1,1,1,1,0}};

    int **DMatrix1;
    getMemory(DMatrix1, rows, cols);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            DMatrix1[i][j] = SMatrix1[i][j];
    int **DMatrix2;
    getMemory(DMatrix2, rows, cols);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            DMatrix2[i][j] = SMatrix2[i][j];
    int **DMatrix3;
    getMemory(DMatrix3, rows, cols);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            DMatrix3[i][j] = SMatrix3[i][j];
    int **DMatrix4;
    getMemory(DMatrix4, rows, cols);
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            DMatrix4[i][j] = SMatrix4[i][j];

// Блок работы со статическими массивами:
    std::cout << "Статические матрицы:" << std::endl << std::endl;

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

// Блок работы с динамическими массивами:
    std::cout << std::endl << std::endl << "Динамические матрицы:" << std::endl << std::endl;

    std::cout << "Матрица 1:" << std::endl;
    printMatrix(DMatrix1, rows, cols);
    std::cout << "Новая матрица:" << std::endl;
    int goodDRows1 = sortDMatrix(DMatrix1, rows, cols);
    printMatrix(DMatrix1, goodDRows1, cols);
    std::cout << std::endl;

    std::cout << "Матрица 2:" << std::endl;
    printMatrix(DMatrix2, rows, cols);
    std::cout << "Новая матрица:" << std::endl;
    int goodDRows2 = sortDMatrix(DMatrix2, rows, cols);
    printMatrix(DMatrix2, goodDRows2, cols);
    std::cout << std::endl;

    std::cout << "Матрица 3:" << std::endl;
    printMatrix(DMatrix3, rows, cols);
    std::cout << "Новая матрица:" << std::endl;
    int goodDRows3 = sortDMatrix(DMatrix3, rows, cols);
    printMatrix(DMatrix3, goodDRows3, cols);
    std::cout << std::endl;

    std::cout << "Матрица 4:" << std::endl;
    printMatrix(DMatrix4, rows, cols);
    std::cout << "Новая матрица:" << std::endl;
    int goodDRows4 = sortDMatrix(DMatrix4, rows, cols);
    printMatrix(DMatrix4, goodDRows4, cols);
    std::cout << std::endl;

    return 0;
}