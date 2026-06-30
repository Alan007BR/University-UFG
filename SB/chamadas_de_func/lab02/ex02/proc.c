#include <stdio.h>



void process(int x, short v, int *pos)

{

  printf("process: x = %d, v = %d, pos = 0x%p\n", x, v, pos);

  printf("---\n");

  *pos = x * v;

}



void show(int *vet, long size)
{

  int first = 1;
  printf("vet = [");

  for (int i = 0; i < size; i++) {
    if (first) first = 0;
    else       printf(", ");
    printf("%d", vet[i]);
  }

  printf("]\n");
}