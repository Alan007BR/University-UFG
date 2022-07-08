#include <stdio.h>
 
int indice(int *notas, int maior, int n) {
 
    int indice;
    int i = 0;
 
    
    for (i = 0; i < n; i++) {//algoritmo para pesquisa linear

        if (notas[i] == maior) {//se a posição atual do vetor notas for igual a ultima posição de notas
            indice = i;
            break;
        }
    }
    return indice;
}
 
maior(int *notas, int n) {
 
    int maior = 0;
    int i = 0;
 
    for (i = 0; i < n; i++) {//achar maior nota, usando pesquisa linear
        if (notas[i] >= maior) {//se a nota no indice i for maior ou igual a maior,
            maior = notas[i];//realizar a atualização do novo maior valor.
        }
    }
    return maior;
}
 
frequ(int *notas, int n) {//calcular o valor da frquencia da ultima nota
 
    int i = 0;
    int freq = 0, ind = 0;
 
    for (i = 0; i < n; i++) {//algoritmo para pesquisa linear
        if (notas[i] == notas[n-1]) {//se a posição atual do vetor notas for igual a ultima posição de notas
            freq++;//incrementa o valor da frquencia da ultima nota em +1;
            ind = i;
        }
    }    
    return freq;
}
 
int main() {
 
    int n, freq, ma, id;
    int i = 0;
    scanf("%d", &n);
 
    int notas[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &notas[i]);
    }
 
    freq = frequ(notas, n);
    ma = maior(notas, n);
    id = indice(notas, ma, n);
 
    printf("Nota %d, %d vezes\n", notas[n-1], freq);
    printf("Nota %d, indice %d\n", ma, id);
 
    return 0;
}