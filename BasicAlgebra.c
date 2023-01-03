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

    for (size_t col = 0; col < m->Cols; col += 4)
    {
        // sum 4 rows at a time
        for (size_t row = 0; row < m->Rows-4; row++)
        {
            matValues = _mm256_loadu_pd(&m->Data[row * m->Cols + col]);
            sums = _mm256_add_pd(sums, matValues);
        }

        // store in new mat
        _mm256_store_pd(&result.Data[col], sums);
    }

    return result;
}

void sumMat(Mat *inOut, Mat *b)
{
    if (!equalSize(inOut, b))
    {
        printf("ERROR sumMat: Matrices do not have the same size\n");
        exit(EXIT_FAILURE);
    }

    register __m256d matValA, matValB;

    for (size_t i = 0; i < b->Cols * b->Rows; i += 4)
    {
        // load data
        matValA = _mm256_loadu_pd(&inOut->Data[i]);
        matValB = _mm256_loadu_pd(&b->Data[i]);

        // sum
        matValA = _mm256_add_pd(matValA, matValB);

        // store the results
        _mm256_storeu_pd(&inOut->Data[i], matValA);
    }
}
Mat sumMats(Mat *a, Mat *b)
{
    if (!equalSize(a, b))
    {
        printf("ERROR sumMat: Matrices do not have the same size\n");
        exit(EXIT_FAILURE);
    }

    Mat m = zeroes(a->Rows, a->Cols);
    register __m256d matValA, matValB;

    for (size_t i = 0; i < b->Cols * b->Rows; i += 4)
    {
        // load data
        matValA = _mm256_loadu_pd(&a->Data[i]);
        matValB = _mm256_loadu_pd(&b->Data[i]);

        // sum
        matValA = _mm256_add_pd(matValA, matValB);

        // store the results
        _mm256_storeu_pd(&m.Data[i], matValA);
    }

    return m;
}

Mat product(Mat *a, Mat *b)
{
    if (a->Cols != b->Rows)
    {
        printf("ERROR product: Matrices sizes are incompatible\n");
        exit(EXIT_FAILURE);
    }
    
    Mat result = zeroes(a->Rows, b->Cols);
    __m256d aVals, bVals, sums;
    size_t dim = a->Cols, p, dimSeq = dim - dim % 4;
    double *sumsMem = aligned_alloc(32, 4 * sizeof(double));

    for (size_t row = 0; row < result.Rows; row++)
    {
        for (size_t col = 0; col < result.Cols; col++)
        {
            // rest sums for the next value in [row,col] posiition
            sums = _mm256_setzero_pd();

            for (size_t i = 0; i < dim - dim%4; i += 4)
            {
                aVals = _mm256_loadu_pd(&a->Data[row * a->Cols + i]);
                p = b->Cols * i + col;
                bVals = _mm256_setr_pd(b->Data[p], b->Data[p + b->Cols], b->Data[p + b->Cols * 2], b->Data[p + b->Cols * 3]);

                aVals = _mm256_mul_pd(aVals, bVals);
                sums = _mm256_add_pd(sums, aVals);
            }

            // cross sum to spare time
            sums = _mm256_hadd_pd(sums, sums);
            
            _mm256_store_pd(sumsMem, sums);

            // sequential sum the rest
            result.Data[row * result.Cols + col] = sumsMem[0] + sumsMem[2];

            // if the dimensions aren't optimal for the avx instructions load and to prevent entering forbidden memory spaces
            for (size_t i = 0; i < dim % 4; i++)
                result.Data[row * result.Cols + col] += a->Data[(dimSeq + i) + row * dim] * b->Data[(dimSeq + i) * dim + col];
        }
    }

    free(sumsMem);

    return result;
}