#include "BasicAlgebra.h"

void addScalar(Mat *m, double scalar)
{
    register __m256d matValues, results, scal = _mm256_set1_pd(scalar);

    for (size_t row = 0; row < m->Rows; row++)
    {
        for (size_t col = 0; col < m->Cols; col += 4)
        {
            // load data into AVX register
            matValues = _mm256_loadu_pd(&m->Data[row * m->Cols + col]);

            // compute sum of 4 elements
            results = _mm256_add_pd(matValues, scal);

            // store results back into memory
            _mm256_store_pd(&m->Data[row * m->Cols + col], results);
        }
    }
}
void multScalar(Mat *m, double scalar)
{
    register __m256d matValues, results, scal = _mm256_set1_pd(scalar);

    for (size_t row = 0; row < m->Rows; row++)
    {
        for (size_t col = 0; col < m->Cols; col += 4)
        {
            // load data into AVX register
            matValues = _mm256_loadu_pd(&m->Data[row * m->Cols + col]);

            // compute multiplication of 4 elements
            results = _mm256_mul_pd(matValues, scal);

            // store results back into memory
            _mm256_store_pd(&m->Data[row * m->Cols + col], results);
        }
    }
}

double sumElements(Mat *m)
{
    register __m256d matValues, sums = _mm256_setzero_pd();

    for (size_t row = 0; row < m->Rows; row++)
    {
        // do all but last set of 4 element per row
        for (size_t col = 0; col < m->Cols; col += 4)
        {
            // load data into AVX register
            matValues = _mm256_loadu_pd(&m->Data[row * m->Cols + col]);

            // sum elements
            sums = _mm256_add_pd(sums, matValues);
        }
    }

    double *convertedReg = (double*)aligned_alloc(32, 4 * sizeof(double));
    _mm256_store_pd(convertedReg, sums);

    double result = 0.0;
    for (size_t i = 0; i < 4; i++)
        result += convertedReg[i];
    
    free(convertedReg);

    return result;
}

Mat sumCols(Mat *m)
{
    Mat result = zeroes(m->Rows, 1);
    register __m256d matValues, sums;
    double *convertedReg = (double*)aligned_alloc(32, 4 * sizeof(double));

    for (size_t row = 0; row < m->Rows; row++)
    {
        // set line sum to 0
        sums = _mm256_setzero_pd();

        for (size_t col = 0; col < m->Cols; col += 4)
        {
            // load data into AVX register
            matValues = _mm256_loadu_pd(&m->Data[row * m->Cols + col]);

            // sum elements
            sums = _mm256_add_pd(sums, matValues);
        }

        // sum the elements inside the avx register "sums"
        _mm256_store_pd(convertedReg, sums);

        for (size_t i = 0; i < 4; i++)
            result.Data[row * result.Cols] += convertedReg[i];
    }

    free(convertedReg);

    return result;
}
Mat sumRows(Mat *m)
{
    Mat result = zeroes(1, m->Cols);
    register __m256d matValues, sums;
    double *convertedReg = (double*)aligned_alloc(32, 4 * sizeof(double));

    for (size_t col = 0; col < m->Cols; col += 4)
    {
        // sum 4 rows at a time
        for (size_t row = 0; row < m->Rows-4; row++)
        {
            matValues = _mm256_loadu_pd(&m->Data[row * m->Cols + col]);
            sums = _mm256_add_pd(sums, matValues);
        }

        if (col < m->Cols-4)
            _mm256_store_pd(&result.Data[col], sums);
        else
        {
            // THIS
        }
    }
    

    return result;
}

void sumMat(Mat *inOut, Mat *b)
{

}
Mat sumMats(Mat *a, Mat *b)
{

}

Mat product(Mat *a, Mat *b)
{

}