#include "BasicAlgebra.h"

void addScalarAVX(Mat *m, double scalar)
{
    register __m256d matValues, results, scal = _mm256_set1_pd(scalar);

    for (size_t row = 0; row < m->Rows; row++)
    {
        for (size_t col = 0; col < m->Cols; col += 4)
        {
            // load data into AVX register
            matValues = _mm256_load_pd(&m->Data[row * m->memCols + col]);

            // compute sum of 4 elements
            results = _mm256_add_pd(matValues, scal);

            // store results back into memory
            _mm256_store_pd(&m->Data[row * m->memCols + col], results);
        }
    }
}
void multScalarAVX(Mat *m, double scalar)
{
    register __m256d matValues, results, scal = _mm256_set1_pd(scalar);

    for (size_t row = 0; row < m->Rows; row++)
    {
        for (size_t col = 0; col < m->Cols; col += 4)
        {
            // load data into AVX register
            matValues = _mm256_load_pd(&m->Data[row * m->memCols + col]);

            // compute multiplication of 4 elements
            results = _mm256_mul_pd(matValues, scal);

            // store results back into memory
            _mm256_store_pd(&m->Data[row * m->memCols + col], results);
        }
    }
}

double sumElementsAVX(Mat *m)
{
    register __m256d matValues, sums = _mm256_setzero_pd();

    for (size_t row = 0; row < m->Rows; row++)
    {
        // set garbage elements to 0
        size_t numGarbageElems = m->memCols - m->Cols;
        for (size_t col = m->memCols-1; col >= m->memCols-numGarbageElems; col++)
            m->Data[row * m->memCols + col] = 0.0;
        

        // do all but last set of 4 element per row
        for (size_t col = 0; col < m->Cols; col += 4)
        {
            // load data into AVX register
            matValues = _mm256_load_pd(&m->Data[row * m->memCols + col]);

            // sum elements
            sums = _mm256_add_pd(sums, matValues);
        }
    }

    double convertedReg[4];
    _mm256_store_pd(convertedReg, sums);

    double result = 0.0;
    for (size_t i = 0; i < 4; i++)
        result += convertedReg[i];
    
    return result;
}

Mat sumColsAVX(Mat *m)
{

}
Mat sumRowsAVX(Mat *m)
{

}

void sumMatAVX(Mat *inOut, Mat *b)
{

}
Mat sumMatsAVX(Mat *a, Mat *b)
{

}

Mat productAVX(Mat *a, Mat *b)
{

}