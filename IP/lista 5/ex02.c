#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    char nome[51];
    double preco;
} Fruta;


int main() {
Fruta frutas[1000];

    int n, f, d, i, j, s, quant;
    char list[51];
    double t;

    scanf("%d", &n);


    while (n--) {


        scanf("%d", &f);

        for (i=0; i<f; i++)
            scanf("%s %lf", frutas[i].nome, &frutas[i].preco);

            scanf("%d", &d);


            for (i=0, t = 0; i<d; i++) {
                scanf("%s %d", list, &quant);

                for(j=0,s=0; j<f && s==0; j++) {

                    if(strcmp(list, frutas[j].nome)==0){
                        t+=frutas[j].preco * quant;
                        s = 1;
                    }

                }
            }
                printf("R$ %.2lf\n", t);
    }

    return 0;
}