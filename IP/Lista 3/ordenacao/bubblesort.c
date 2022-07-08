#include <stdio.h>

int main() {

    int V[5] = {3,2,7,1,5};
    int final = 5;
    int i;
    int t;

    while(final > 1) {
    for (i = 0; i < final - 1; i++) {//indice maior
        if(V[i] > V[i+1]) {// se quiser fazer decresente trocar o sinal de > para <
            t = V[i]; //swap
            V[i] = V[i+1];
            V[i+1] = t;
             }
        }
        final--;
    }

    return 0;
}