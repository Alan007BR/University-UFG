#include <stdio.h>

int main() {
    float a = 0.0, b = 0.0, c = 0.0, d = 0.0, e = 0.0, f = 0.0;

    float det = 0.0, detX = 0.0, detY = 0.0;

    float x = 0.0, y = 0.0;

    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);
    scanf("%f", &d);
    scanf("%f", &e);
    scanf("%f", &f);


    det = (a * e) - (d * b);
    detX = (c * e) - (f * b);
    detY = (a * f) - (d * c);

    x = detX/det;
    y = detY/det;


    printf("O VALOR DE X E = %.2f\n", x);
    printf("O VALOR DE Y E = %.2f\n", y);   

    return 0;
}