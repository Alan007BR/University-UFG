#include <stdio.h>



int main (void) {

  int x = 0xffffffff; // negativo, bit do sinal é 1
  int y = 2;

  printf("x = %d, y = %d\n", x, y);
  printf("x é menor do que y? %s\n", (x < y) ? "sim" : "não");

  return 0;

}