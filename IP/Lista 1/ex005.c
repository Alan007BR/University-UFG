#include <stdio.h>

int main() {

    float v1, v2, v3;
    float temp;
    scanf("%f %f %f", &v1, &v2, &v3);

    if (v1 > v3) {
        temp = v3;
        v3 = v1;
        v1 = temp;
    } if (v1 > v2) {
        temp = v2;
        v2 = v1;
        v1 = temp;
    } if (v2 > v3) {
        temp = v3;
        v3 = v2;
        v2 = temp;
    }

    printf("%.2f, %.2f, %.2f", v1, v2, v3);

    return 0;
}