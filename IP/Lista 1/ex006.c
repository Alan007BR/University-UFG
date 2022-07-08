#include <stdio.h>
#include <math.h>

int main() {

     double a, b, c, delta;
     double x1, x2;
     double m;

    scanf("%lf %lf %lf", &a, &b, &c);
    
    delta = b*b - 4 * a*c;



   if(delta < 0) {
        printf("RAIZES IMAGINARIAS\n");
    } else if (delta == 0) {

        x1 =  -b / (2*a);
    
        printf("RAIZ UNICA\n");
        printf("X1 = %.2lf\n", x1);

        } 
        else {

            x1 =  (-b + sqrt(delta)) / (2*a);
            x2 =  (-b - sqrt(delta)) / (2*a);


            if  (x1 > x2) {
             m = x1;
            x1 = x2;
            x2 = m;

            }

            printf("RAIZES DISTINTAS\n");
            printf("X1 = %.2lf\n", x1);
            printf("X2 = %.2lf\n", x2);
        }


    return 0;
}