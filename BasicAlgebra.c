#include "BasicAlgebra.h"

void addScalarSeq(Mat *m, double scalar)
{
    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            m->Data[row * m->memCols + col] += scalar;
}

void multScalarSeq(Mat *m, double scalar)
{
    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            m->Data[row * m->memCols + col] *= scalar;
}

double sumElementsSeq(Mat *m)
{
    double sum = 0.0;

    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            sum += m->Data[row * m->memCols + col];
    
    return sum;
}


Mat sumColsSeq(Mat *m)
{
    Mat sum = zeroes(1,m->Rows);

    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            sum.Data[row] += m->Data[row * m->memCols + col];
    
    return sum;
}

Mat sumRowsSeq(Mat *m)
{
    Mat sum = zeroes(1,m->Cols);

    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            sum.Data[col] += m->Data[row * m->memCols + col];
    
    return sum;
}



void sumMatSeq(Mat *inOut, Mat *b)
{
    // check sizes
    if (!equalSize(inOut, b))
    {
        printf("Matrices are not of the same size and cannot be summed by sumMat");
        exit(1);
    }
    
    // sum element-wise
    for (size_t row = 0; row < inOut->Rows; row++)
        for (size_t col = 0; col < inOut->Cols; col++)
            inOut->Data[row * inOut->memCols + col] += b->Data[row * inOut->memCols + col];
}

Mat sumMatsSeq(Mat *a, Mat *b)
{
    // check sizes
    if (!equalSize(a, b))
    {
        printf("Matrices are not of the same size and cannot be summed by sumMat");
        exit(1);
    }
    
    Mat ac = cloneMat(a);

    // sum element-wise
    for (size_t row = 0; row < a->Rows; row++)
        for (size_t col = 0; col < a->Cols; col++)
            ac.Data[row * ac.memCols + col] += b->Data[row * ac.memCols + col];
    
    return ac;
}

Mat productSeq(Mat *a, Mat *b)
{
    return zeroes(1,1);
}