#include <stdio.h>

char constante();
void init(short factor, long *pl, int *pi);

int main()
{
  short s;     // Deve ser registrador
  int i;
  long l;

  s = (short)constante();
  init(s, &l, &i);

  printf("Soma: %ld\n", l + i + s);

  return 0;
}
