#include <stdio.h>
#include <assert.h>

int mdc(int num1, int num2) {

    int resto;

    do {
        resto = num1 % num2;

        num1 = num2;
        num2 = resto;

    } while (resto != 0);

    return num1;
}

int main() {

    int num1, num2;
    scanf("%d", &num1);
    scanf("%d", &num2);

    printf("%d\n", mdc(num1, num2));

    return 0;
}