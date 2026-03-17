#include <stdio.h>



// return 0 se o número de bits '1' em x for par, ou 1 se for ímpar
int odd_ones(unsigned int x) { // desloca o bit em vez de uma mascara
  int count = 0;

  for (int i = 0; i < 32; i++) {
    if (x & 0x01) {
        count++;
    }
    x = x >> 1;
  }
  return (count & 1); 
}

int odd_ones2(unsigned int x) { // desloca a mascara em vez do bit
  int count = 0;
  unsigned int mask = 1;

  for (int i = 0; i < 32; i++) {
    if (x & mask) {
        count++;
    }
    mask = mask << 1;
  }
  return (count & 1);
}


int main() {

  unsigned int v;



  v = 0x01010101;

  printf("%X tem número %s de bits\n", v, odd_ones(v) ? "impar" : "par");



  v = 0x01030101;

  printf("%X tem número %s de bits\n", v, odd_ones(v) ? "impar" : "par");



  return 0;

}