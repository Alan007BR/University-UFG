#include <stdio.h>

void pparachar( char * s, int n) {

    s[n] = '\0';//o char vai receber um quebra linhas no exatos s[n] do char
    printf("%s", s);//vai printar até o s[n]
}

int main() {

    int n, num, i = 0;
    char s[500];

    scanf("%d", &num);//num de repetições

    for (i = 0; i < num; i++) {//contador
    scanf("%d %[^\n]", &n, &s);//ler o int e o char

    pparachar(s, n);//mmandar pra mágica

    printf("\n");//quebra de linha para o próximo laço de repetição
    }

    return 0;
}