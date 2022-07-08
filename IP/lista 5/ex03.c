#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *paises[24] = { "brasil", "alemanha", "austria", "coreia", "espanha", "grecia", "estados-unidos", "inglaterra", "australia", "portugal", "suecia", "turquia", "argentina", "chile", "mexico", "antardida", "canada", "irlanda", "belgica", "italia", "libia", "siria", "marrocos", "japao" };

char *palavras[24] = { "Feliz Natal!", "Frohliche Weihnachten!", "Frohe Weihnacht!", "Chuk Sung Tan!", "Feliz Navidad!", "Kala Christougena!", "Merry Christmas!", "Merry Christmas!", "Merry Christmas!", "Feliz Natal!", "God Jul!", "Mutlu Noeller", "Feliz Navidad!", "Feliz Navidad!", "Feliz Navidad!", "Merry Christmas!", "Merry Christmas!", "Nollaig Shona Dhuit!", "Zalig Kerstfeest!", "Buon Natale!", "Buon Natale!", "Milad Mubarak!", "Milad Mubarak!", "Merii Kurisumasu!" };


typedef struct {

    char pais[50];
    char palavra[100];

} tradutor;

tradutor trad[24];
int pos = 0;


void alimentarotradutor() {
    int i = 0;

    for(i = 0; i < 24; i++) {
        strcpy(trad[i].pais, paises[i]);
        strcpy(trad[i].palavra, palavras[i]);

    }

}

bool acharpais(char *pais) {

    int i = 0;

    for(i = 0; i < 24; i++) {
        if(strcmp(trad[i].pais, pais) == 0) {
            pos = i;
            return true;
        } 
    }
    return false;
}

int main() {

    alimentarotradutor();
    char pais[100];

    while(scanf(" %s", pais) != EOF) {

        if(acharpais(pais)) {
            printf("%s\n", trad[pos].palavra);
        } else {
            printf("-- NOT FOUND --\n");
        }
    }

    return 0;
}