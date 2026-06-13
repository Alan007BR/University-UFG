#include <stdlib.h>
#include <stdio.h>

#define JAN 1
#define FEV 2

#define SIZE 2

struct Produto {
  char  mes;    //+0: mes
  long  preco;  //+8: preco
  int   ano;    //+16: ano
};

struct Produto prods[SIZE];

long media(struct Produto *ptr, long size);
// {
//   int i = 0;           // usar obrigatoriamente o registrador %r12d para 'i'
//   long soma = 0;       // usar obrigatoriamente o registrador %r13  para 'soma'

//   for (i = 0; i < size; i++)
//      soma += ptr[i].preco;

//   return soma / size;
// }

int main()
{
  int i = 0;            // usar obrigatoriamente o registrador %r8d para 'i'

  prods[0].mes   = JAN;
  prods[0].preco = 100;
  prods[0].ano   = 2020;

  prods[1].mes   = FEV;
  prods[1].preco = 120;
  prods[1].ano   = 2020;

  long m = media(prods, SIZE);   // usar obrigatoriamente o registrador %r9 para 'm'

  while (i < SIZE) {
    printf("Diferença em %d/%d: %ld\n", 
       (int)prods[i].mes, prods[i].ano, prods[i].preco - m);
    i++;
  }

  return 0;
}
