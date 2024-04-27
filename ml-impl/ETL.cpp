#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include "ETL.h"

/*
Functions needed

function :: input -> output


*stats*
mean :: 2d array (mxn) -> 1d array (n)
std-dev :: 2d array (mxn) -> 1d array (n)
maybe (scaled :: 2d array (mxn) -> 2s array(mxn))
norm :: 2d array (mxn) -> 2s array(mxn)
*/

Matrix *mean(Matrix *m)
{
    Matrix *meanmat = matrix_create(m->cols, 1);

    for (int j = 0; j < m->cols; j++)
    {
        float sum = 0.0;
        for (int i = 0; i < m->rows; i++)
        {
            sum += m->entries[i][j];
        }
        meanmat->entries[j][0] = sum / (m->rows);
    }
    return meanmat;
}

Matrix *stddiv(Matrix *m)
{
    Matrix *stddivmat = matrix_create(m->cols, 1);
    Matrix *meanmat = mean(m);
    for (int j = 0; j < m->cols; j++)
    {
        float sum = 0.0;
        for (int i = 0; i < m->rows; i++)
        {
            sum += pow(m->entries[i][j] - meanmat->entries[j][0], 2);
        }
        stddivmat->entries[j][0] = sqrt(sum / (m->rows - 1));
    }
    return stddivmat;
}

Matrix *norm(Matrix *m)
{
    Matrix *normmat = matrix_create(m->rows, m->cols);
    Matrix *meanmat = mean(m);
    Matrix *stddivmat = stddiv(m);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            printf("%1.3f ", (m->entries[i][j] - meanmat->entries[j][0]) / stddivmat->entries[j][0]);
            normmat->entries[i][j] = (m->entries[i][j] - meanmat->entries[j][0]) / stddivmat->entries[j][0];
        }
    }
    matrix_print(normmat);
    return normmat;
}

float MeanSquareError(Matrix *matrix, Matrix *weights)
{

    float sum = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        float y = weights->entries[0][0]; // y = c
        for (int j = 0; j < matrix->cols - 1; j++)
        {
            // y += sum(mx) => y = c + sum(mx)
            y += (matrix->entries[i][j]) * (weights->entries[j + 1][0]);
            float y_act = matrix->entries[i][matrix->cols - 1];
            sum += pow(y - y_act, 2);
        }

        // printf("Pred: %f, Actual: %f \n", y, matrix->entries[i][matrix->cols - 1]);
    }
    float mse = sum / matrix->rows;
    return mse;
}

std::tuple<Matrix *, Matrix *, Matrix *, Matrix *> TrainTestSplit(Matrix *data, float train_size)
{
    int rows = data->rows;
    int train_rows = round(train_size * rows);
    int test_rows = rows - train_rows + 1;

    Matrix *X_train = matrix_create(train_rows, data->cols - 1);
    Matrix *X_test = matrix_create(test_rows, data->cols - 1);
    Matrix *y_train = matrix_create(train_rows, 1);
    Matrix *y_test = matrix_create(test_rows, 1);

    printf("Train %d and Test %d", train_rows, test_rows);

    for (int i = 0; i < data->rows; i++)
    {
        // printf("Data Number: %d\n", i);
        if (i < train_rows)
        {
            for (int j = 0; j < data->cols - 1; j++)
            {
                X_train->entries[i][j] = data->entries[i][j];
                // printf("%f -%d-%d \n", data->entries[i][j], i, j);
            }
            y_train->entries[i][0] = data->entries[i][data->cols - 1];
        }
        else
        {
            int index = i - train_rows + 1;
            // printf("%d : ", index);
            for (int j = 0; j < data->cols - 1; j++)
            {
                X_test->entries[index][j] = data->entries[i][j];
                // printf("%f -%d-%d Test\n", data->entries[i][j], i, j);
            }
            y_test->entries[index][0] = data->entries[i][data->cols - 1];
        }
    }

    return std::make_tuple(X_train, y_train, X_test, y_test);
}

Matrix *computeGradient(Matrix *M, Matrix *theta, double epsilon)
{
    int n = theta->rows;
    Matrix *gradient = matrix_create(n, 1);
    float cost = MeanSquareError(M, theta); // Use your cost function here
    for (int i = 0; i < n; ++i)
    {
        Matrix *thetaPlus = matrix_copy(theta);
        thetaPlus->entries[i][0] += epsilon;
        float costPlus = MeanSquareError(M, thetaPlus); // Use your cost function here
        matrix_free(thetaPlus);

        Matrix *thetaMinus = matrix_copy(theta);
        thetaMinus->entries[i][0] -= epsilon;
        float costMinus = MeanSquareError(M, thetaMinus); // Use your cost function here
        matrix_free(thetaMinus);

        gradient->entries[i][0] = (costPlus - costMinus) / (2 * epsilon);
    }
    return gradient;
}

// Gradient Descent Algorithm
Matrix *GradientDescent(Matrix *M, Matrix *theta, double alpha, int iter)
{
    int m = M->rows;
    int n = M->cols;
    Matrix *newTheta = matrix_copy(theta);
    for (int i = 0; i < iter; ++i)
    {
        Matrix *gradient = computeGradient(M, newTheta, 1e-6);
        Matrix *temp = scale(alpha, gradient);
        matrix_print(temp);
        matrix_print(gradient);
        matrix_free(gradient);
        newTheta = subtract(theta, temp);
        matrix_free(temp);
    }
    return newTheta;
}

/*
lbltonum :: 1d label array -> 1d int array

traintestsplit :: (2d array,1d int array,int split-ratio(train)) -> (2d train 2d test 1d train 1d test)
generalised ordinary least squares
gradient descent : (X,y,theta, learning rate, iter) -> (theta, cost)
rsquared:: (1d pred, 1d actual) -> int r2value


*data-vis*
scatter-plot (x/y)
confusion matrix
*/