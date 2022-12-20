#include "BasicAlgebra.h"

Mat blankInit(size_t rows, size_t cols);

Mat blankInit(size_t rows, size_t cols)
{
    // initialize values
    Mat m;
    m.Rows = rows;
    m.Cols = cols;

    // allocate the memory(aligned so avx are happy)
    m.Data = (double*)malloc(m.Rows * m.Cols * sizeof(double));

    return m;
}

Mat zeroes(size_t rows, size_t cols)
{
    Mat m = blankInit(rows, cols);
    
    // fill the array with zeros
    memset(m.Data, (char)0U, m.Rows * m.Cols * sizeof(double));
    
    return m;
}

Mat ones(size_t rows, size_t cols)
{   
    Mat m = blankInit(rows, cols);

    // fill first row with ones
    for (size_t i = 0; i < m.Cols; i++)
        m.Data[i] = 1.0;

    // copy memory of first row to all other rows
    for (size_t row = 1; row < m.Rows; row++)
        memcpy(&m.Data[row * m.Cols], &m.Data[0], m.Cols*sizeof(double));
    
    return m;
}

Mat idMat(size_t size)
{
    Mat m = zeroes(size, size);
    for (size_t i = 0; i < size; i++)
        m.Data[i * m.Cols + i] = 1.0;
    
    return m;
}

Mat loadMat(const char * csvPath)
{
    FILE *f;

    f = fopen(csvPath, "r");

    // check if was able to open file
    if (!f)
    {
        fprintf (stderr, "failed to open file for reading\n");
        exit(-1);
    }

    // count number of rows and columns
    char c;
    size_t nRows = 1, nCols = 1;
    for (c = getc(f); (c != EOF); c = getc(f))
    {
        // count number of columns until the end of the first row
        if ((nRows < 2) && (c == ','))  
            nCols++;

        // count number of rows
        else if (c == '\n')
            nRows++;
    }

    // reset pointer to beginning of file
    rewind(f);

    // generate (empty)data structure and attributes
    Mat m = zeroes(nRows, nCols);

    // start parsing the file and filling the array with the data
    char * letterNumber = (char*)malloc(40U);    // don't think double point number in a text document takes more than 40 character
    size_t row = 0, col = 0, numSize = 0;
    for (c = getc(f); (c != EOF); c = getc(f))
    {
        switch (c)
        {
        case ',':
            letterNumber[numSize] = 0;  // terminate string
            m.Data[row * m.Cols + col] = (double)atof(letterNumber);  // convert number and place it in the matrix

            col++; numSize=0;
            break;
        
        case '\n':
            letterNumber[numSize] = 0;  // terminate string
            m.Data[row * m.Cols + col] = (double)atof(letterNumber);  // convert number and place it in the matrix

            row++; col=0; numSize=0;
            break;

        default:
            letterNumber[numSize] = c;
            numSize++;
            break;
        }
    }

    // add last element
    letterNumber[numSize] = 0;  // terminate string
    m.Data[row * m.Cols + col] = (double)atof(letterNumber);  // convert number and place it in the matrix

    free(letterNumber);

    return m;
}

Mat cloneMat(Mat *m)
{
    Mat cloned = zeroes(m->Rows, m->Cols);

    memcpy(cloned.Data, m->Data, (m->Rows * m->Cols * sizeof(double)));

    return cloned;
}

double get(Mat *m, size_t row, size_t col)
{
    double d;

    if ((m->Rows > row) && (m->Cols > col))
        d = m->Data[m->Cols * row + col];
    else
    {
        printf("Out of bounds");
        exit(1);
    }

    return d;
}

void set(Mat *m, size_t row, size_t col, double d)
{
    if ((m->Rows > row) && (m->Cols > col))
        m->Data[m->Cols * row + col] = d;
    else
    {
        printf("Out of bounds");
        exit(1);
    }
}

void freeMat(Mat *m)
{
    free(m->Data);   
}

void printMat(Mat *m)
{
    printf("\n");
    for (size_t row = 0; row < m->Rows; row++)
    {
        for (size_t col = 0; col < m->Cols-1; col++)
            printf("%.2f, ", m->Data[row * m->Cols + col]);
        printf("%.2f", m->Data[row * m->Cols + m->Cols-1]);
        printf("\n");
    }
    printf("\n");
}

bool equalSize(Mat *a, Mat *b)
{
    if ((a->Cols == b->Cols) && (a->Rows == b->Rows))
        return true;
    else
        return false;
}