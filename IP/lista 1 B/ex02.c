#include <stdio.h>

int main() {

    int i = 1, num = 0;

    scanf("%d", &num);

    while (i <= num) {
        i++;

        if (i % 2 == 0) {
            printf("%d^2 = %d\n", i, i*i);
        }
    }

    return 0;
}