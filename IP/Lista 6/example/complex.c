#include <stdio.h>
#include "complex.h"

void complex_print(Complex A) {
    if (A.r != 0) {
        printf("%.2lf", A.r);
    }
    if(A.i != 0) {
        if(A.r == 0)printf("%.2lfi\n", A.i);
        else printf("%+.2lfi\n", A.i);        
    }
    if(A.r == 0 && A.i == 0) printf("0");
}

Complex complex_read(void) {
    Complex A;
    scanf("%lf%lf", &(A.r), &(A.i));//2 + 3
    return A;
}

void complex_read2(Complex *A) {
    scanf("%lf %lf", &(A->r), &(A->i));
}

Complex complex_sum(Complex A, Complex B) {
    Complex C;
    C.r = A.r + B.r;
    C.i = A.i + B.i;

    return C;
}
Complex complex_sum2  (Complex const *A, Complex const *B, Complex *C) {

    C->r = A->r + B->r;
    C->i = A->i + B->i;
}

Complex complex_sub(Complex A, Complex B) {
    Complex C;
    C.r = A.r - B.r;
    C.i = A.i - B.i;

    return C;
}

void complex_sub2 (Complex const *A, Complex const *B, Complex *C) {
    C->r = A->r - B->r;
    C->i = A->i - B->i;
}

Complex complex_neg(Complex A){
    Complex C;

    C.r = -C.r;
    C.i = -C.i;

    return C;
}

// Complex complex_sub(Complex A, Complex B) {
//     return complex_sum(A, complex_neg(B));
// }

void complex_neg2(Complex * A) {
    A->r = -A->r;
    A->i = -A->i;
}


Complex complex_mult(Complex A, Complex B) {
    Complex C;
    C.r = A.r * B.r - A.i * B.i;
    C.i = A.r * B.i + A.i * B.r;

    return C;
}

void complex_mult2(Complex const *A, Complex const *B, Complex *C) {
    C->r = A->r * B->r - A->i * B->i;
    C->i = A->r * B->i + A->i * B->r;

}

void complex_div2(Complex const *A, Complex const *B, Complex *C) {

}
Complex complex_conj(Complex A) {

    A.i = -A.i;

    return A;
}

void complex_conj2 (Complex *A) {

    A->i = -A->i;
}

Complex complex_div ( Complex A, Complex B) {

    double K;
    Complex C;

    C = complex_mult(A, complex_conj(B));
    K = B.r*B.r + B.i*B.i;
    C.r /= K;
    C.i /= K;

    return C;
}
void complex_div2(Complex const *A, Complex const *B, Complex *C) {

    double K;
    Complex C;
    Complex temp;
    temp = complex_conj(*B);
    complex_mult2(A, &temp, C);

    K = temp.r * temp.r + temp.i + temp.i;
    C->r = C->r/K;//C-> r /= K;
    C->i = C->i/K;
}
Complex *complex_new(void) {

    return (Complex*)malloc(sizeof(Complex));
}

void complex_set(Complex *A, double r, double i) {

    A->r = r;
    A->i = i;
}
void complex_free(Complex const * A) {

    free((void *)A);
    
}