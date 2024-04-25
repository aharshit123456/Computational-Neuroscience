#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "ETL.h"

#define MAXCHAR 100
#define LEARNING_RATE 0.001
#define MAX_ITERATIONS 10000
#define EPSILON 1e-6

int main()
{
    // Matrix *matrix = matrix_create(5, 5);
    // matrix_print(matrix);

    // matrix_fill(matrix, 6);
    // matrix_print(matrix);

    // Matrix *file_mat = matrix_load("iris/bezdekIris.data");
    // matrix_print(file_mat);

    Matrix *matrix = matrix_loadfromCSV2("iris/iris.data");

    // linear regression
    // y = sum(x_i * theta_i) (x_0=0)

    // MSE is calcuated as avg of all the y_pred - y_act

    float sum = 0;
    Matrix *theta = matrix_create(matrix->cols + 1, 1);
    matrix_fill(theta, 1);

    for (int i = 0; i < matrix->rows; i++)
    {
        float y = theta->entries[0][0];
        for (int j = 0; j < matrix->cols - 1; j++)
        {
            y += (matrix->entries[i][j]) * (theta->entries[j + 1][0]);
            sum += pow(y - matrix->entries[i][matrix->cols - 1], 2);
        }

        printf("Pred: %f, Actual: %f \n", y, matrix->entries[i][matrix->cols - 1]);
    }
    float mse = sum / matrix->rows;

    printf("%1.3f", mse);

    // now the mse is minimised while 0e-3 step sized derivatives are calculated to manipulate the theta values
}