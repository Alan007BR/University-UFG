#include "complex.h"
#include <stdlib.h>

int main() {

    Complex *A, *B, *C;

    A = B = C = NULL;

    A = complex_new();
    complex_set(A, 2, 3);//2+3i

    B = complex_new();
    complex_set(B, 2, -3);

    C = complex_new();

    complex_mult2(A, B, C);
    complex_print(*C);

    complex_free(A);
    complex_free(B);
    complex_free(C);

    
}