#include <stdio.h>


double raiz( double n, double error, double err ) {

    double r0 = 1;

    r0 = (r0 + (n/r0)) / 2;
    error = (n - (r0*r0));
    if (error < 0) {
        error = error * (-1);
    }


    printf("r: %.9lf, err: %.9lf\n", r0, error);

    while (error > err) {

    r0 = (r0 + (n/r0)) / 2;
    error = (n - (r0*r0));
    if (error < 0) {
        error = error * (-1);
    }
    printf("r: %.9lf, err: %.9lf\n", r0, error);

    }

    return 0;
}


int main() {

    double n;
    double error;


    scanf("%lf", &n);
    scanf("%lf", &error);
    double err = error;

    raiz( n, error, err );



    return 0;
}