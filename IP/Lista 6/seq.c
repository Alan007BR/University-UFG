#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int i = 0;
    int n, n2;

    FILE *arq = NULL;

    arq = fopen("seq", "w");
    
    if(argc != 3) {
        printf("Usage: \n"
        "./seq A B<ENTER>\n"
        );
        return 0;
    }

    n = strtol(argv[1], NULL, 10);
    n2 = strtol(argv[1], NULL, 10);

    if(n < n2) {
        for(i = n; i <= n2; i++) {
            fputs(i, arq);
            fputs(' ', arq);
        }
        fputs("\n", arq);
        return 0;
    }
    
    
    if(n > n2) {
        for(i = n; i >= n2; i--) {
            fputs(i, arq);
            fputs(' ', arq);
        }
        fputs("\n", arq);
        return 0;
    }

    fclose(arq);

    return 0;
}