#include <stdio.h>

int main(int argc, char **argv) {

    FILE *arq = NULL;
    int ch;

    if(argc != 2) {
        printf("Usage: \n"
        "./fview <filename>\n"
        );
        return 0;
    }

    arq = fopen(argv[1], "r");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo <%s>.\n", argv[1]);
        return 0;
    }

    while(1) {
        ch = fgetc(arq);
        if(ch == EOF) break;
        printf("%c", (char)ch);
    }
    printf("\n: FIM DO ARQUIVO\n");
    fclose(arq);
    return 0;
}