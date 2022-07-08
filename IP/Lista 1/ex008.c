#include <stdio.h>
 
int main() {
 
    int valor, novo;
    int unidade, dezena, centena;
 
    scanf("%d", &valor);
 
    
 
 
    if (valor == 0 || valor%10==0) {
        return 0;
    } else{
        
 
            unidade = valor % 10;
            dezena = (valor % 100) / 10;
            centena = valor / 100;
 
            novo = unidade * 100 + dezena * 10 + centena;
 
    printf("%i", novo);
    }
    
 
 
    return 0;
}