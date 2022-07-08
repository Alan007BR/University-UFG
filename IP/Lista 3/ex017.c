#include <stdio.h>
#define D 3

double max(double * v, int t) {
    int i;
    double max = *v;
    for(i = 1; i < t; i++) {
        if(v[i] > max)
            max = v[i];
    }
    return max;
}

void read_vector(double * v, int t) {
    int i;
    for(i = 0; i < t; i++) {
        scanf("%lf", &v[i]);
    }
}

void differ(double * A, double * B, double * R, int t) {
    int i;
    for(i = 0; i < t; i++) {
        R[i] = A[i] - B[i];
    }
}

void copy(double * A, double * B, int t){
    int i;
    for(i = 0; i < t; i++) {
        A[i] = B[i];
    }
}

void abs(double * A, int t) {
    int i;
    for(i = 0; i < t; i++) {
        if(A[i] < 0) A[i]*= -1;
    }
}

int main() {
    double A[D], B[D], R[D], k;
    int i, n, t;

    scanf("%d", &n);
    read_vector(A, D);
    for(i = 1; i < n; i++) {
        read_vector(B, D);
        differ(A, B, R, D);

        abs(R, D);

        k = max(R, D);

        printf("%.2lf\n", k);
        copy(A, B, D);
    }
    return 0;
};