#include <stdio.h>

int main() {

    int num;
    int line, column, finalnumber;

    scanf("%d", &num);

    if (num < 2) {
        printf("Campeonato invalido!\n");
        return 0;
    }

    finalnumber = 1;
    for (line = 1; line < num; line++) {
        for (column = line+1; column <= num; column++) {
                printf("Final %d: Time%d X Time%d\n", finalnumber, line, column);
                finalnumber++;
        }
    }

    return 0;
}