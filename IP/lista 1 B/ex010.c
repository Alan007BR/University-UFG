#include <stdio.h>

int main() {

    int linha, colum;
    int nlinhas, ncolum;

    scanf("%d", &nlinhas);
    scanf("%d", &ncolum);

    for(linha = 1; linha  <= nlinhas; linha++) {
        

        for(colum = 1; colum <= ncolum; colum++) {
            
            if ( linha == colum) {
                break;

            }

            if ( colum == 1) {
                printf("(%d,%d)", linha, colum);

            } else {
                printf("-(%d,%d)", linha, colum);
            }


        }
    printf("\n");
    }

    return 0;
}