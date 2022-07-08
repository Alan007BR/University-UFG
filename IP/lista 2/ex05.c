#include <stdio.h>
#include <math.h>


int raizes(double a, double b, double c, double *px1, double *px2) {

    double t;
    double delta;
    delta = b*b -4 * a * c;

    *px1 = 0;
    *px2 = 0;

    if(a == 0) {
        if(b!=0) {
            *px1 = *px2 = -c/b;

            return 1;
        }
    }

    if(delta < 0) {
        return 0;
    } else if (delta == 0) {
        *px1 = *px2 = -b/(2*a);
        return 1;
    } else {
        *px1 = (-b + sqrt(delta))/( 2 * a);
        *px2 = (-b - sqrt(delta))/( 2 * a);

        if (*px2 < *px1) {
            t = *px2;
            *px2 = *px1;
            *px1 = t;

        }

            return 2;
    }

}



int main() {
    double a, b, c, x1, x2;
    int raiz;

    scanf("%lf %lf %lf", &a, &b, &c);
    raiz = raizes(a, b, c, &x1, &x2);

    if (raiz == 2 ) {
    printf("RAIZES DISTINTAS\n");
    printf("X1 = %.2lf\nX2 = %.2lf\n", x1, x2);
    } else if (raiz == 1) {
    printf("RAIZ UNICA\n");
    printf("X1 = %.2lf\n", x1);
    } else {
    printf("RAIZES IMAGINARIAS\n");
    }


    return 0;
}