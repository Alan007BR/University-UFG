#include <stdio.h>

void maioremenor(int *vetor, int n, int *ortve, int *maior, int *menor) {

    int i = 0;
    *maior = *vetor;//evitar lixo de memória, pegar a primeira posição do vetor
    *menor = *ortve;//evitar lixo de memória, pegar a primeira posição do vetor
    
    for (i = 1; i < n; i++) {//achar o maior valor
        if (*(vetor + i) > *maior)// se o vetor no indice i for maior que maior,
            *maior = *(vetor+i);//a posição de maior é atualizada para o vetor de indice i atual.
    }
    for (i = 1; i < n; i++) {//achar o menor valor
        if (*(ortve + i) < *menor)// se o vetor no indice i for menor que menor,
        *menor = *(ortve + i);//a posição de menor é atualizada para o vetor de indice i atual.
    }
}

void inverter( int *vetor, int n, int *ortve) {//funcao para inverter o vetor

    int i = 0;//aux
    for (i = 0; i < n; i++) {//contador de 1 até n
        ortve[i] = vetor[n-i-1];//o vetor invertido vai receber o vetor original [n-i-1] faça as contas no papel que da certo, confia
    }
}

int main() {

    int n;
    int i = 0, maior, menor;
    scanf("%d", &n);

    int vetor[n];
    int ortve[n];

    for (i = 0; i < n; i++) {scanf("%d", &vetor[i]);}//contador de lei para capturar a entrada do vetor

    inverter(vetor, n, ortve);//jogar dentro da função que faz a mágica

    printf("%d", vetor[0]); for (i = 1; i < n; i++) {printf(" %d", vetor[i]);}//gambiarra para não tem espaço no final
    printf("\n");//imprimir o espaço
    printf("%d", ortve[0]); for (i = 1; i < n; i++) {printf(" %d", ortve[i]);}//gambiarra para não tem espaço no final
    printf("\n");
    
    maioremenor(vetor, n, ortve, &maior, &menor);//descobrir o maior e o menor

    //printar o maior e o menor;
    printf("%d\n", maior);
    printf("%d\n", menor);

    //flw
    return 0;
}