#pragma once
#include "matrix.h"
#include <tuple>
#include <vector>

Matrix *mean(Matrix *m);
Matrix *stddiv(Matrix *m);
Matrix *norm(Matrix *m);
float MeanSquareError(Matrix *m, Matrix *t);

std::tuple<Matrix *, Matrix *, Matrix *, Matrix *> TrainTestSplit(Matrix *data, float train_size);
Matrix *GradientDescent(Matrix *M, Matrix *theta, double alpha, int iter);
Matrix *computeGradient(Matrix *M, Matrix *theta, double epsilon);