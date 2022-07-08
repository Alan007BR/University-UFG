#include <stdio.h>

int main() {

    double n = 0;
    double error = 0, err = 0;
    double r0 = 1;

    scanf("%lf", &n);
    scanf("%lf", &error);

        err = error;

        r0 = (r0 + (n/r0)) / 2;
        error = (n - (r0*r0));
            if (error < 0) {
                error = error * (-1);
                }

        printf("r: %.9lf, err: %.9lf\n", r0, error);

        while ( error > err) {
        
        r0 = (r0 + (n/r0)) / 2;
        error = (n - (r0*r0));

            if (error < 0) {
                error = error * (-1);
                }

        printf("r: %.9lf, err: %.9lf\n", r0, error);

     }
    


    return 0;
}