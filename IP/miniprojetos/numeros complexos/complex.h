struct complex {
    double i, r;
};

typedef struct complex Complex;

    void complex_print    (struct complex c);
    Complex complex_read  (void);
    void complex_read2    (Complex *C);
    Complex complex_sum   (Complex A, Complex B);
    Complex complex_sum2  (Complex const *A, Complex const *B, Complex *C);
    Complex complex_neg   (Complex A);
    void complex_neg2     (Complex *A);
    Complex complex_sub   (Complex A, Complex B);
    void complex_sub2     (Complex const *A, Complex const *B, Complex *C);
    Complex complex_mult  (Complex A, Complex B);
    void complex_mult2    (Complex const *A, Complex const *B, Complex *C);
    void complex_div2     (Complex const *A, Complex const *B, Complex *C);
    Complex * complex_new (void);
    void complex_free     (Complex const * C);
    void complex_set2     (Complex *A, double r, double i);
    void complex_conj2    (Complex *A);
    Complex complex_conj  (Complex const A);