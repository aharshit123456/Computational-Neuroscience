#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define MAXCHAR 100

int main()
{
    // Matrix *matrix = matrix_create(5, 5);
    // matrix_print(matrix);

    // matrix_fill(matrix, 6);
    // matrix_print(matrix);

    // Matrix *file_mat = matrix_load("iris/bezdekIris.data");
    // matrix_print(file_mat);

    Matrix *matrix = matrix_loadfromCSV("iris/iris.data");
}