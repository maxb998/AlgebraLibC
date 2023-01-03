#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <immintrin.h>

#ifndef MAT_BASE
#define MAT_BASE

typedef struct
{
    double * Data;
    size_t Rows;
    size_t Cols;
} Mat;

Mat zeroes(size_t rows, size_t cols);

Mat ones(size_t rows, size_t cols);

Mat idMat(size_t size);

Mat loadMat(const char * csvPath);

Mat cloneMat(Mat *m);

Mat transpose(Mat *m);

double get(Mat *m, size_t row, size_t col);

void set(Mat *m, size_t row, size_t col, double d);

void freeMat(Mat *m);

void printMat(Mat *m);

bool equalSize(Mat *a, Mat *b);

#endif //MAT_BASE


#ifndef BASIC_ALGEBRA
#define BASIC_ALGEBRA

void addScalar(Mat *m, double scalar);
void multScalar(Mat *m, double scalar);

double sumElements(Mat *m);

Mat sumCols(Mat *m);
Mat sumRows(Mat *m);

void sumMat(Mat *inOut, Mat *b);
Mat sumMats(Mat *a, Mat *b);

Mat product(Mat *a, Mat *b);

#endif //BASIC_ALGEBRA_
