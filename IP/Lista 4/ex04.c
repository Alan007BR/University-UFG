#include <stdio.h>
     
int main() {
 
    int m, n;
    int i = 0, j = 0, k = 0;
 
    while(1) {
    scanf("%d ", &m);
    if(m > 0 && m <= 10) {
        break;
    }
    }

    while(1) {
    scanf("%d",&n);
    if(n > 0 && n <= 10) {
    break;
    }
    }
 
    int M[m][n];
 
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &M[i][j]);
        }
    }
 
    for( i = 0; i < m; i++) {
        printf("linha %d: ", i+1);

        printf("%d", M[i][0]);
        for(j = 1; j < n; j++) {
            printf(",%d", M[i][j]);
        }

        printf("\n");
        
        }
 
    return 0;
}