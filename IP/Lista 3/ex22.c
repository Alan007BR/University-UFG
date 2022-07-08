#include <stdio.h>
 
void printar(int *v2, int erro, int erro2) {
    int i = 0;
        for (i = 0; i < 9; i++) {
            if(i!=erro && i!= erro2) {
                printf("%d \n", v2[i]);
            }
        }
}
 
void swap(int *v1, int *v2, int a) {
    int i = 0;
    int j = 0;
 
        for (i = 0; i < 9; i++) {//swap
            v2[i] = v1[i];
            for (j = i; j < 9; j++) {
                if(i<j && v2[i] > v1[j]) {
                    a = v1[j];
                    v1[j] = v2[i];
                    v2[i] = a;
                }
            }
        }
}
int main() {
    int i = 0, j = 0, soma = 0;
    int n, a, V, erro, erro2;
 
    int v1[100000], v2[100000];
 
    scanf("%d\n", &n);
    for (V = 0; V < n; V++) {
        for (i = 0; i < 9; i++) {
            scanf("%d", &v1[i]);
            soma += v1[i];
        }
 
        swap(v1, v2, a);
 
        for (i = 0; i < 9; i++) {//comparacao
            for(j = 1; j< 9; j++) {
            if(i<j && (soma-v2[i]-v2[j])==100) {
                erro=i;
                erro2=j;
            }
            }
         }
        printar(v2, erro, erro2);
 
        soma = 0;
    }
    return 0;
}