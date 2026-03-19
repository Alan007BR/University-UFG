#include <stdio.h>

typedef unsigned char byte; // tipo byte, por exemplo.

// o ponteiro pra void é um tipo genérico, que pode apontar para qualquer tipo de dado.
void dump(void *p, int n) { // dump é uma função que recebe um ponteiro para void (p) e um inteiro (n) que representa o número de bytes a serem exibidos.

  unsigned char *p1 = p; //transforma p em unsigned char, como não tem um tipo byte, o char é o tipo mais próximo de byte (1 byte), e o unsigned char é usado para garantir que os valores sejam tratados como bytes sem sinal.
  while (n--) { //n é o tamanho
    printf("%p - 0x%02X\n", p1, *p1);
    p1++;
  }

}



int main() {

  short s;
  int i;
  long l;

  s = 108;
  i = (int)s;

  printf("--- s:\n");
  dump(&s, sizeof(s));
  printf("--- i:\n");
  dump(&i, sizeof(i));

  printf("-----------------------------------------------------------------");


  i = -10;
  l = (long)i;

  printf("--- i:\n");
  dump(&i, sizeof(i));
  printf("--- c:\n");
  dump(&l, sizeof(l));


  printf("-----------------------------------------------------------------");


  l = 83728472363;
  i = (int)l;
  s = (short)l;

  printf("--- c:\n");
  dump(&l, sizeof(l));
  printf("--- i:\n");
  dump(&i, sizeof(i));
  printf("--- s:\n");
  dump(&s, sizeof(s));

  return 0;

}