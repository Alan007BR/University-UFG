/* ++
Elabore um programa em C para receber dois vetores de números inteiros e mostrar os
vetores que representam o conjunto união dos elementos, o conjunto intersecção dos
elementos e o conjunto diferença dos elementos. O programa deve receber como entrada o
número de elementos de cada vetor e cada um dos elementos que compõe esses vetores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uniao(int * v1, int * v2, int n1, int n2) {
    int uni = n1 + n2;

    int v3[uni];
    int i = 0;

    for(i = 0; i < n1; i++){
        v3[i] = v1[i];
    }

    for(i = n1; i < n2; i++){
        v3[i] = v2[i];
    }
    
    for(i = 0; i < uni; i++){
        printf("%d", v3[i]);
    }
}


int main(){

    int n1;
    int n2;
    int *v1, *v2;

    int i = 0;


    scanf("%d", &n1);
    scanf("%d", &n2);

    v1 = (int *) malloc(n1 * sizeof(int));
    v2 = (int *) malloc(n2 * sizeof(int));

    for(i = 0; i < n1; i++){
        scanf("%d", &v1[i]);
    }

    for(i = 0; i < n1; i++){
        scanf("%d", &v2[i]);
    }

    uniao(v1, v2, n1, n2);

    free(v1);
    free(v2);

    return 0;
}