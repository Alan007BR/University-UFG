#include <stdio.h>



int odd_ones(unsigned int x) {

// 1 se for par
// 0 se for impar
int count = 0;

for (int i = 0; i < 32; i++) {
  int bit = x & 1; // 00000001
  if(bit == 1) {
    count++;
  }
  x = x >> 1;
}

return count & 1; //numeros impar em binario sempre termina em 1
}



int main() {

  unsigned int v;



  v = 0x01010101;

  printf("%X tem número %s de bits\n", v, odd_ones(v) ? "impar" : "par");



  v = 0x01030101;

  printf("%X tem número %s de bits\n", v, odd_ones(v) ? "impar" : "par");



  return 0;

}