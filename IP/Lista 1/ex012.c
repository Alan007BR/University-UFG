#include <stdio.h>

int main() {

    float v, renda_bruta;
    int familiares, tipo_escola, etnia;

    scanf("%f", &v);
    scanf("%i %i %i", &familiares, &tipo_escola, &etnia);


    renda_bruta = v / familiares;

    if ( tipo_escola == 2 ) {


        if ( renda_bruta <= 1500 ) {

            if ( etnia <= 3){
                printf("ALUNO COTISTA (L2)");
            } else {
                printf("ALUNO COTISTA (L1)");
                
            }
            

        } else {

            if ( etnia <= 3 ) {
                printf("ALUNO COTISTA (L4)");
            } else {
                printf("ALUNO COTISTA (L3)");
            }

        }
    } else {
        printf("ALUNO NAO COTISTA");
    }


    return 0;
}