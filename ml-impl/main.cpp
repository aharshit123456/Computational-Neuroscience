#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "ETL.h"
#include <tuple>

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

    matrix = norm(matrix);

    // for (int i = 0; i < matrix->rows; i++)
    // {
    //     float y = theta->entries[0][0]; // y = c
    //     for (int j = 0; j < matrix->cols - 1; j++)
    //     {
    //         // y += sum(mx) => y = c + sum(mx)
    //         y += (matrix->entries[i][j]) * (theta->entries[j + 1][0]);
    //         float y_act = matrix->entries[i][matrix->cols - 1];
    //         sum += pow(y - y_act, 2);
    //     }

    //     printf("Pred: %f, Actual: %f \n", y, matrix->entries[i][matrix->cols - 1]);
    // }
    // float mse = sum / matrix->rows;
    float mse = MeanSquareError(matrix, theta);
    printf("MSE is %1.3f", mse);

    // now the mse is minimised while 0e-3 step sized derivatives are calculated to manipulate the theta values
    std::tuple<Matrix *, Matrix *, Matrix *, Matrix *> TrainTest = TrainTestSplit(matrix, 0.8);

    Matrix *XTrain, *y_train, *X_test, *y_test;

    std::tie(XTrain, y_train, X_test, y_test) = TrainTest;
    Matrix *newTheta = GradientDescent(matrix, theta, LEARNING_RATE, MAX_ITERATIONS);

    matrix_print(newTheta);
    printf("Old %f, New %f", MeanSquareError(matrix, theta), MeanSquareError(matrix, newTheta));
}