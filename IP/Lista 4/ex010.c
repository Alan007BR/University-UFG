#include <stdio.h>

int main() {

    int l, c;
    int i = 0, j = 0;
    int li = 0, ln, ci = 0, cn;
    // li = linha inicial, ln = linha final
    // ci = coluna inicial, cn = coluna final

    scanf("%d %d", &l, &c);

    if (l <= 0 || c <= 0 || l > 10 || c > 10) {
        printf("Dimensao invalida\n");
        return 0;
    }

    int M[l][c];

    ln = l;
    cn = c;

    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &M[i][j]);
        }
    }

    while(li < ln && ci < cn) {
        
        //imprimir a primeira linha dos elementos
        for(i = ci; i < cn; i++) {
            printf("%d ", M[li][i]);
        }
        li++;

        //imprime o ultimo elemento da linhas restantes
        for(i = li; i < ln; i++) {
            printf("%d ", M[i][cn-1]);
        }
        cn--;

        // imprime a ultima linha dos elementos restantes
        if (li < ln) {
            for(i = cn - 1; i >= ci; --i) {
                printf("%d ", M[ln - 1][i]);
            }
            ln--;
        }

        //imprime a primeira coluna das colunas restantes
        if(ci < cn) {
            for(i = ln - 1; i >= li; --i) {
                printf("%d ", M[i][ci]);
            }
            ci++;
        }
    }
    printf("\n");

    return 0;
}