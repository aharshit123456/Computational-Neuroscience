#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <array>

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

double MeanSquareError(Matrix *m)
{
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