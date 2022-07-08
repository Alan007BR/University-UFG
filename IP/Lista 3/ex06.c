#include <stdio.h>
     
int analizawords ( char *palavras) {
 
    int letras = 0;
    int i = 0;
    //for para contar quantidade de letras
    for (i = 0; palavras[i] !='\0'; i++) {
        letras++;
    }
 
    if (letras == 3 && palavras[0] == 'o' && palavras[1] == 'n' || palavras[0] == 'o' && palavras[2] == 'e' || palavras[1] == 'n' && palavras[2] == 'e') {//checar se a palavras é um, 3 letras, pares de letras on, oe, ne;
        return 1;
    }
 
    if (letras == 3 && palavras[0] == 't' && palavras[1] == 'w' || palavras[0] == 't' && palavras[2] == 'o' || palavras[1] == 'w' && palavras[2] == 'o') {//checar se a palavras é dois, 3 letras, pares de letras tw, to, wo
       return 2;
    }
 
    else if (letras == 5 && palavras[0] == 't' && palavras[1] == 'h' || palavras[0] =='t' && palavras[2] =='r' || palavras[1] =='h' && palavras[2] =='r') { //checar se a palavras é três. pares de letras th, tr, hr
    return 3;
    }
}

int main() {
     
    char palavras[1000];
    int i = 0;
    int n;
 
    scanf("%d", &n);//quantidades de testes
 
    for (i = 0; i < n; i++) {
    scanf("%s", palavras);//palavra
 
    printf("%d\n", analizawords(palavras));
 
    }
 
    return 0;
}