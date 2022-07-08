#include <stdio.h>
 
int canc(int *v, int min_pre, int a) {
 
    int i = 0;
    int pre = 0, falt = 0;
 
    for (i = 0; i < a; i++) {//incrementar alunos que faltou com alunos presentes
        if (v[i] <= 0) pre++;
        if (v[i] > 0 ) falt++;
    }
 
    if ( pre >= min_pre){
     printf("NAO\n");//printar
 
    for (i = a-1; i >= 0; i--) {
        if (v[i] <= 0) printf("%d\n", i+1);
    }
 
    }    
    else printf("SIM\n");
 
 
 
    return 0;
}
 
int main() {
 
    int a, min_pre;
    int i = 0;
 
    scanf("%d %d", &a, &min_pre);
 
    int v[a];
    for (i = 0; i < a; i++) {
        scanf("%d", &v[i]);
    }
 
    canc(v, min_pre, a);
 
    return 0;
}