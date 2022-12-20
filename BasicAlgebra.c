#include "BasicAlgebra.h"

void addScalar(Mat *m, double scalar)
{
    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            m->Data[row * m->Cols + col] += scalar;
}

void multScalar(Mat *m, double scalar)
{
    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            m->Data[row * m->Cols + col] *= scalar;
}

double sumElements(Mat *m)
{
    double sum = 0.0;

    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            sum += m->Data[row * m->Cols + col];
    
    return sum;
}


Mat sumCols(Mat *m)
{
    Mat sum = zeroes(1,m->Rows);

    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            sum.Data[row] += m->Data[row * m->Cols + col];
    
    return sum;
}

Mat sumRows(Mat *m)
{
    Mat sum = zeroes(1,m->Cols);

    for (size_t row = 0; row < m->Rows; row++)
        for (size_t col = 0; col < m->Cols; col++)
            sum.Data[col] += m->Data[row * m->Cols + col];
    
    return sum;
}



void sumMat(Mat *inOut, Mat *b)
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
            inOut->Data[row * inOut->Cols + col] += b->Data[row * inOut->Cols + col];
}

Mat sumMats(Mat *a, Mat *b)
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
            ac.Data[row * ac.Cols + col] += b->Data[row * ac.Cols + col];
    
    return ac;
}

Mat mult(Mat *a, Mat *b)
{
    // check sizes for compatibility
    if (a->Cols != b->Rows)
    {
        printf("ERROR. Matrices sizes for multiplication do not match\n");
        exit(EXIT_FAILURE);
    }
    
    // allocate output memory space
    Mat res = zeroes(a->Rows, b->Cols);

    // do multiplication sequential
    for (size_t row = 0; row < res.Rows; row++)
        for (size_t col = 0; col < res.Cols; col++)
            for (size_t i = 0; i < a->Cols; i++)
                res.Data[row * res.Cols + col] += a->Data[row * a->Cols + i] * b->Data[i * b->Cols + col];

    return res;
}