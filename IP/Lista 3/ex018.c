#include <stdio.h>

int main() {

    int i = 0;
    char letras[50], resul[50];
    int m = 0;


	while (scanf("%[^\n]%*c", letras) != EOF) {

        int i = 0, j = 0, pos = 0;

        while(letras[i] != '\0') {
            
            if(letras[i] == ' ') {
                resul[j++] = letras[i++];
            }

            else if(letras[i] >= 'a' && letras[i] <= 'z' && pos % 2 == 0) {
                resul[j++] = toupper(letras[i]);
                pos++;
                i++;
            }
            else if(letras[i] >= 'A' && letras[i] <= 'Z' && pos % 2 != 0) {
                resul[j++] = tolower(letras[i]);
                pos++;
                i++;
            }
            else {
                resul[j++] = letras[i++];
                pos++;
            }
        }

        resul[j] = '\0';
        printf("%s\n", resul);
    }


    return 0;
}