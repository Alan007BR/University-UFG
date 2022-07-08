#include <stdio.h>


int contab( int * v, int n, int K) {
    /* Função que encontra a posição de K, e encontra a quantidade de numeros maiores ou iguais a K;
    *Usando uma pesquisa linear;
    * 
    */ 
    int j = 0, achou = 0, num = 0;

    if (K == 0) { // se o numero para procurar for 0, logo terá que retornar a quantidade total de numeros
        num = n;
        return num;
    }
    for ( j = 0; j < n; j++ ) {//passar por todos os numeros até n
        if(v[j] >= K) {//checar se o numero é maior ou igual ao valor de K
            num++;// incrementar quantos numeros são maiores ou igual a K
        }
    }
        return num;//retornar o resultado
}

int main() {

    int K;
    int i = 0;
    int elem, n, resul;
//entrada
    while(1) {
        scanf("%d", &n);
        if (n >= 1 && n <= 1000) {
            break;
        }
    }
    int v[n];
    for(i=0; i<n; i++){
        scanf("%d", &v[i]);
    }
    scanf("%d", &K);
//saida
    resul = contab(v, n, K);
    printf("%d\n", resul);

    return 0;
}