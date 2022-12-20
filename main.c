#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "BasicAlgebra.h"

int main(int argc, char const *argv[])
{
    // arguments check
    if (argc != 3)
    {
        printf("Wrong arguments: ./main <PATH_TO_MATRIX_A> <PATH_TO_MATRIX_B>\n");
        exit(EXIT_FAILURE);
    }
    // check if matrices files exist
    if (access(argv[1], F_OK) != 0)
    {
        printf("ERROR: Matrix A does not exist\n");
        exit(EXIT_FAILURE);
    }
    if (access(argv[2], F_OK) != 0)
    {
        printf("ERROR: Matrix B does not exist\n");
        exit(EXIT_FAILURE);
    }
    

    Mat a = loadMat(argv[1]);
    printMat(&a);

    Mat b = loadMat(argv[2]);
    printMat(&b);

    Mat c = mult(&a, &b);
    printMat(&c);

    freeMat(&a);
    freeMat(&b);
    freeMat(&c);

    return EXIT_SUCCESS;
}
