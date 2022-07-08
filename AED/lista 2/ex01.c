/* ex01 (+)
    Sem dúvida a chamada “Sequência de Fibonacci” (ou “Sucessão de Fibonacci”) é uma das mais famosas
sequências numéricas da Matemática. Os dois primeiros termos desta sequência são: f0 = 0 f1 = 1.
A partir do terceiro termo, cada termo é obtido somando-se os dois termos imediatamente anteriores a ele,ou
seja: fn = fn−1 + fn−2, com n ∈ N e n ≥ 2
Considere que seja dado um número n, n N∗. Usando o conceito de recursividade, elabore um pro-
grama em C para imprimir até o n-ésimo termo da “Série de Fibonacci”.
*/

#include <stdio.h>

int fibo(int n) {

    if(n == 1 || n == 2)  return 1;
    if(n == 0) return 0;
    
    return(fibo(n - 1) + fibo(n - 2));
}

int main(){

    int n, i = 0;

    scanf("%d",&n);
    
    for(i = 0; i <= n; i++) {
    printf("%d ", fibo(i));
    }
    printf("\n");

    return 0;
}