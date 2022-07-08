#include <stdio.h>

contadordecons( char *text) {

    int cons = 0;
    int i = 0;

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] > 97 && text[i] <= 122 || text[i] > 65 && text[i] <= 90) {
            if (text[i] != 'e' && text[i] != 'i' && text[i] != 'o' && text[i] != 'u' && text[i] != 'E' && text[i] != 'I' && text[i] != 'O' && text[i] != 'U')
            cons++;       
        } 
    }
    return cons;
}

contadordevog(char *text) {

    int vog = 0;
    int i = 0;

    for (i = 0; text[i] !='\0'; i++) {
        if (text[i] == 'a' || text[i] == 'A') vog++;
        else if (text[i] == 'e' || text[i] == 'E') vog++;
        else if (text[i] == 'i' || text[i] == 'I') vog++;
        else if (text[i] == 'o' || text[i] == 'O') vog++;
        else if (text[i] == 'u' || text[i] == 'U') vog++;
    }
    return vog;
}

contadordeletras( char *text) {

    int letras = 0;
    int i = 0;

    for (i = 0; text[i] !='\0'; i++) {
        if(text[i] != ' ') {
            if (text[i] >= 65 && text[i] <= 90 || text[i] >= 97 && text[i] <= 122) {
            letras++;
            }
        }
    }
    return letras;
}
int main() {

    int n; //casos testes;
    char text[10000]; //textos
    int let, vog, con;
    int i = 0;

    scanf("%d\n", &n);

        for( i = 0; i < n; i++) {

        scanf("%[^\n]%*c", text);

        contadordeletras(text);
        let = contadordeletras(text);

        contadordevog(text);
        vog = contadordevog(text);

        contadordecons(text);
        con = contadordecons(text);

        printf("Letras = %d\n", let);
        printf("Vogais = %d\n", vog);
        printf("Consoantes = %d\n", con);


        }
    return 0;
}