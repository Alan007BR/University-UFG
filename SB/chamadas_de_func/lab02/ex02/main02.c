#include <stdio.h>



void show(int *vet, long size);
void process(int x, short v, int *pos);



int   i = 0;

short v = 0;

short vetA[5] = {28,42,16,23,47};

int   vetB[5] = {0,0,0,0,0};



int main(){

  while (i < 5) {

    v = vetA[i] << 2;
    printf("Iteração %d, v = %d\n", i, (int)v);
    process(i, v, &vetB[i]);
    i++;

  }

  show(vetB, 5);

  return 0;

}