#include <stdio.h>

void desloc1(char *text, int tam) {

    int i = 0;

    for (i = tam/2; i < tam; i++) {//percorrer da metade do vetor até o final
        text[i] -= 1;//mudar na tabela ASCII um caracter para a esquerda
    }
}

 void inverter ( char *text, int tam){

    int temp = tam, aux, fim;
    int i = 0;

    fim = tam - 1;//tamanho -1
    for(i = 0; i < tam/2; i++){
        aux = text[i];//aux salvando o estado atual do text[i];
        text[i] = text[fim];//text[i] sobrepondo o valor de fim
        text[fim] = aux;//fim pegando o valor do estado inicial de aux
        fim--;//decrementando o fim;
    }

 }

int cript(char *text, int n) {

    int i = 0;
    int tam = 0;

//contador de letras -- para ver o tamanho do vetor
    for (i = 0; text[i] != '\0'; i++) {
        tam++;//ignorar os espaços
    }

    //acrecentar +3 para cada letra maiuscula e minúscula
     for (i = 0; i < tam; i++) {
         if (text[i] >= 65 && text[i] <= 90 || text[i] >= 97 && text[i] <= 122) text[i] += 3;
     }

    //inverter
    inverter(text, tam);

    //deslocar 1 posição para a esquerda
    desloc1(text, tam);

        printf("%s\n", text);
    
    return tam;
}
int main() {

    int n;
    char text[1000000];
    int i = 0;

    scanf("%d\n", &n);

    for (i = 0; i < n; i++) {
        scanf("%[^\n]%*c", text);
    
    cript(text, n);
    }

    return 0;
}