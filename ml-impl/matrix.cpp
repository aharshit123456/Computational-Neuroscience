#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100

Matrix *matrix_loadfromCSV(char *filestring)
{
    FILE *file = fopen(filestring, "r");
    char entry[MAXCHAR];
    fgets(entry, MAXCHAR, file);
    Matrix *matrix;
    int i = 0;
    int col = 0;
    while (true)
    {
        if (entry[i] == ',')
            col += 1;
        else if (entry[i] == '\0')
            break;
        i++;
    }
    printf("%d \n", col);
    int row = 0;
    fclose(file);
    file = fopen(filestring, "r");
    while (fgets(entry, MAXCHAR, file))
    {
        row++;
    }
    fclose(file);
    printf("%d \n", (row - 1));
    col++;
    matrix = matrix_create(row, col);

    // loop through the file while adding the numbers in a string
    // when the comma reaches, pause and
    // add the float to the matrix element
    // move to the next one and start from after the comma
    // repeat until end of line
    file = fopen(filestring, "r");

    for (int i = 0; i < row; i++)
    {

        int f_ind = 0;
        char numstr[3];
        float e;
        fgets(entry, MAXCHAR, file);
        int comma_count = 0;
        for (int j = 0; j < col; j++)
        {
            int k = 0;
            while (entry[f_ind] != ',' && comma_count < col)
            {
                numstr[k] = entry[f_ind];
                f_ind++;
                k++;
                if (comma_count == col)
                    break;
            }
            comma_count++;
            f_ind++;
            e = atof(numstr);
            printf("%1.2f ", e);
            matrix->entries[i][j] = e;
        }
    }

    fclose(file);
    matrix_print(matrix);
    return matrix;
}

Matrix *matrix_create(int row, int col)
{
    Matrix *matrix = new Matrix;
    matrix->rows = row;
    matrix->cols = col;
    matrix->entries = new double *[matrix->rows];
    for (int i = 0; i < matrix->rows; i++)
    {
        matrix->entries[i] = new double[matrix->cols];
    }

    return matrix;
}

void matrix_fill(Matrix *m, int n)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            m->entries[i][j] = n;
        }
    }
}

void matrix_free(Matrix *m)
{
    for (int i = 0; i < m->rows; i++)
    {
        free(m->entries[i]);
    }
    free(m->entries);
    free(m);
    m = NULL;
}

void matrix_print(Matrix *m)
{
    printf("Rows: %d Columns: %d\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            printf("%1.1f ", m->entries[i][j]);
        }
        printf("\n");
    }
}

Matrix *matrix_copy(Matrix *m)
{
    Matrix *mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->entries[i][j] = m->entries[i][j];
        }
    }
    return mat;
}

void matrix_save(Matrix *m, char *file_string)
{
    FILE *file = fopen(file_string, "w");
    fprintf(file, "%d\n", m->rows);
    fprintf(file, "%d\n", m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            fprintf(file, "%.6f\n", m->entries[i][j]);
        }
    }
    printf("Successfully saved matrix to %s \n", file_string);
    fclose(file);
}

Matrix *matrix_load(char *file_string)
{
    FILE *file = fopen(file_string, "r");
    char entry[MAXCHAR];
    fgets(entry, MAXCHAR, file);
    int rows = atoi(entry);
    fgets(entry, MAXCHAR, file);
    int cols = atoi(entry);
    Matrix *m = matrix_create(rows, cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fgets(entry, MAXCHAR, file);
            m->entries[i][j] = strtod(entry, NULL);
        }
    }
    printf("Succesfully loaded matrix from %s\n", file_string);
    fclose(file);
    return m;
}

double uniform_distribution(double low, double high)
{
    double difference = high - low;
    int scale = 10000;
    int scaled_diff = (int)(difference * scale);
    return low + (1.0 * (rand() % scaled_diff) / scale);
}

void matrix_randomize(Matrix *m, int n)
{
    double min = -1.0 / sqrt(n);
    double max = -1.0 / sqrt(n);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            m->entries[i][j] = uniform_distribution(min, max);
        }
    }
}

int matrix_argmax(Matrix *m)
{
    double max_score = 0;
    int max_idx = 0;
    for (int i = 0; i < m->rows; i++)
    {
        if (m->entries[i][0] > max_score)
        {
            max_score = m->entries[i][0];
            max_idx = i;
        }
    }
    return max_idx;
}

Matrix *matrix_flatten(Matrix *m, int axis)
{
    Matrix *mat;
    if (axis == 0)
    {
        mat = matrix_create(m->rows * m->cols, 1);
    }
    else if (axis == 1)
    {
        mat = matrix_create(1, m->rows * m->cols);
    }
    else
    {
        printf("Argument to matrix_flatten must be 0 or 1");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            if (axis == 0)
                mat->entries[i * m->cols + j][0] = m->entries[i][j];
            else if (axis == 1)
                mat->entries[0][i * m->cols + j] = m->entries[i][j];
        }
    }
    return mat;
}

Matrix *multiply(Matrix *m1, Matrix *m2)
{
    Matrix *mat;
    return mat;
}
Matrix *add(Matrix *m1, Matrix *m2)
{

    Matrix *mat = matrix_create(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows; i++)
    {
        for (int j = 0; j < m1->cols; j++)
        {
            mat->entries[i][j] = m1->entries[i][j] + m2->entries[i][j];
        }
    }
    return mat;
}

Matrix *subtract(Matrix *m1, Matrix *m2)
{
    Matrix *mat = matrix_create(m1->rows, m1->cols);
    for (int i = 0; i < m1->rows; i++)
    {
        for (int j = 0; j < m1->cols; j++)
        {
            mat->entries[i][j] = m1->entries[i][j] - m2->entries[i][j];
        }
    }
    return mat;
}
Matrix *dot(Matrix *m1, Matrix *m2)
{
    Matrix *mat;
    return mat;
}
Matrix *scale(double n, Matrix *m)
{
    Matrix *mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->entries[i][j] = n * m->entries[i][j];
        }
    }
    return mat;
}
Matrix *addScalar(double n, Matrix *m)
{
    Matrix *mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->entries[i][j] = n + m->entries[i][j];
        }
    }
    return mat;
}
Matrix *transpose(Matrix *m)
{
    Matrix *mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            mat->entries[i][j] = m->entries[j][i];
        }
    }
    return mat;
}