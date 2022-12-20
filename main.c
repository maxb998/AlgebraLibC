#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "BasicAlgebra.h"

int main(int argc, char const *argv[])
{
    Mat a = zeroes(4,8);

    printf("\n a = ");
    printMat(&a);

    double d = 1.36;
    addScalarSeq(&a, d);
    printf("\n a + %.2f = ", d);
    printMat(&a);

    double sum = sumElementsSeq(&a);
    double calculatedSum = d*4.*8.;
    printf("\nComputed sum = %.2f \n", sum);
    printf("True sum = %.2f \n", calculatedSum);

    d = 10.0;
    multScalarSeq(&a, d);
    printf("\n a * %.2f = ", d);
    printMat(&a);

    sum = sumElementsSeq(&a);
    calculatedSum *= 10.;
    printf("\nComputed sum = %.2f \n", sum);
    printf("True sum = %.2f \n", calculatedSum);

    freeMat(&a);

    return 0;
}
