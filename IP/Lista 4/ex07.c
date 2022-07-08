#include <stdio.h>
void preencher(char M[1000][1000], int n) {
    int i, j;
    for(i=0; i<n; i++){
        for(j=0; j<(2*n)-1; j++){
            M[i][j]=' ';
        }
        M[i][j]='\0';
    }
}
int main() {
    char M[1000][1000];
    char a, b;
    int n, i, j=0, c;
 
    scanf("%d%s%*c%c", &n, &a, &b);
    if(n%2!=0 && n>0) {    
        preencher(M, n);
        for(i=0; i<=n/2; i++) {
            M[i][n-j-1]=a;
            M[n-i-1][n-j-1]=a;
 
            M[i][n+j-1]=a;
            M[n-i-1][n+j-1]=a;
 
            j+=2;
        }
        j=0;
        i=1;
        for(c=1; i<=(n/2); c++) {
            
            M[c][n-j-1]=b;
            M[n-c-1][n-j-1]=b;
 
            M[c][n+j-1]=b;
            M[n-c-1][n+j-1]=b;
 
            j+=2;
            if(c>=n/2) {
                i++;
                j=0;
                c=i-1;
            }
        }
 
        for(i=0; i<n; i++) {
            printf("%s\n", M[i]);
        }
    }
    else printf("Dimensao invalida!");
    return 0;
}