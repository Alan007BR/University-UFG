#include <stdio.h>
 
 
void elem(int *V, int num) {
 
    int i = 0;
    int final = num;
    int uni = 0;
    int t = 0;
 
    while(final > 1) {//bobble sort para ordenar a sequência
    for (i = 0; i < final - 1; i++) {//indice maior
        if(V[i] < V[i+1]) {
            t = V[i]; //swap
            V[i] = V[i+1];
            V[i+1] = t;
             }
        }
        final--;
    }
 
    for (i = 0; i < num; i++) {
        if(V[i] == V[i+1]) {
        //printf("%d - %d\n", V[i], V[i+1]);
        uni= uni + 2;
        }
    }
        printf("%d\n", num-uni);
}
 
int main() {
 
    int num;
    int i = 0;
 
    scanf("%d", &num);
 
    int n[num];
    for ( i = 0; i < num; i++){
        scanf("%d", &n[i]);
    }
        elem(n, num);
    
 
    return 0;
}