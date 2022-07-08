#include <stdio.h>

 

int main(){

    

    int n, sequencia = 0, segmentos = 0;//Declaração de variáveis.

    unsigned int n1, n2; //Declaração de variáveis.

    

    scanf("%d", &n); //Entrada da quantidade de teste.

 

    if(n>0){

        while(sequencia < n){ //Loop com entrada e processamento dos números.

        

            scanf("%d", &n1);

                if(n1 - n2 == 1){ //Teste lógico.

                    segmentos++; //soma mais um no segmento.

                }

                else if (n2 - n1 == -1){//Teste lógico.

                    segmentos++;//soma mais um no segmento.

                }

                

            n2 - n1 == 1;

            sequencia++;

        }

    } 

    else{

        return 0;

    }

    

    printf("O comprimento do segmento crescente maximo e: %d\n", segmentos);

 

    return 0;

}

 