#include <stdio.h>

int main() {

    int n, c1, c2, h;

    scanf("%d", &n);

    for(h = 1; h <= n; h++) {

    for (c1 = 1; c1 <= h; c1++) {
        c2 = c1;

        while(c1*c1 + c2*c2 < h*h) {
            c2++;

            if (c2*c2 + c1*c1 == h*h) {
                printf("hipotenusa = %d, catetos %d e %d\n", h, c1, c2);

            }
        }
    }
    }

    return 0;
}