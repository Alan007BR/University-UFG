#include <stdio.h>
#include <math.h>


int main() {


    char operador;

    const float num1;
    const float num2;


    scanf("%f", &num1);
    scanf("%c", &operador);
    scanf("%f", &num2);


    switch(operador) {

// Aritmeticos

        case '+':
            printf("%g", num1 + num2);
        break;

        case '-':
            printf("%g", num1 - num2);
        break;

        case '*':
            printf("%g", num1 * num2);
        break;

        case '/':
            printf("%g", num1 / num2);
        break;

        case '%':
            printf("%i", (int) num1 % (int) num2);
        break;

        case '~':
            printf("%g", pow(num1, num2));
        break;


// Relacionais

        case '=':
            printf("%s", (num1 == num2) ? "true":"false");
        break;

        case '!':
            printf("%s", (num1 != num2) ? "true":"false");
        break;

        case '<':
            printf("%s", (num1 < num2) ? "true":"false");
        break;

        case '>':
            printf("%s", (num1 > num2) ? "true":"false");
        break;

// Logicos

        case '^':
            printf("%s", (num1 && num2) ? "true":"false");
        break;

        case 'v':
            printf("%s", (num1 || num2) ? "true":"false");
        break;

        case 'x':
            printf("%s", ( (int) num1 ^ (int) num2) ? "true":"false");
        break;


    }


    return 0;
}