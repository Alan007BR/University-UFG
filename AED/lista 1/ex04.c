/* (++) 

Elabore um programa usando a linguagem C para calcular o rendimento obtido em uma
aplicação financeira pré-fixada após um certo número de anos. O programa deve receber o valor
inicialmente aplicado (P), a taxa percentual de juros anual (t), o número de anos em que a quantia
vai ser aplicada (n) e a taxa de comissão (c) sobre os rendimentos anuais que será devida como
taxa de administração do investimento. O algoritmo deve exibir o valor líquido acumulado ao final
de cada ano de aplicação.
*/

#include <stdio.h>

int main(){

    float p, t, c;
    int n, i = 0;
    float tot;

    //valor inicialmente aplicado (P), a taxa percentual de juros
    scanf("%f", &p);
    if(p <= 0){ printf("erro\n"); return 0;}
    
    //numero de anos que a quantia
    scanf("%d", &n);
    if(n <= 0){ printf("erro\n"); return 0;}
    
    //taxa de juros anual
    scanf("%f", &t);
    if(t <= 0 && t > 100){  
        printf("erro\n"); return 0;}

    //taxa de comissão
    scanf("%f", &c);
    if(c <= 0 && c > 100){ printf("erro\n"); return 0;}

    //tot = (p * (c/100));

    while (i < n){

    t = t - c;
    tot = p + ( p * (t/100)); 
    printf("%.2f\n", tot);

        i++;
        p = tot;
    }


    return 0;
}