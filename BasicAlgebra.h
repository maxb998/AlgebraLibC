#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#ifndef MAT_BASE
#define MAT_BASE

typedef struct
{
    double * Data;
    size_t Rows;
    size_t Cols;
    size_t memCols;    // number of cols including avx alignment placeholders
} Mat;

Mat zeroes(size_t rows, size_t cols);

Mat ones(size_t rows, size_t cols);

Mat idMat(size_t size);

Mat loadMat(const char * csvPath);

Mat cloneMat(Mat *m);

double get(Mat *m, size_t row, size_t col);

void set(Mat *m, size_t row, size_t col, double d);

void freeMat(Mat *m);

void printMat(Mat *m);
void printMatAVX(Mat *m);

bool equalSize(Mat *a, Mat *b);

#endif //MAT_BASE



#ifndef BASIC_ALGEBRA
#define BASIC_ALGEBRA

void addScalarSeq(Mat *m, double scalar);
void multScalarSeq(Mat *m, double scalar);

double sumElementsSeq(Mat *m);

Mat sumColsSeq(Mat *m);
Mat sumRowsSeq(Mat *m);

void sumMatSeq(Mat *inOut, Mat *b);
Mat sumMatsSeq(Mat *a, Mat *b);

Mat productSeq(Mat *a, Mat *b);

#endif //BASIC_ALGEBRA
