#include <stdio.h>



int match(unsigned long x, unsigned short y){
    for(int i = 0; i < 32; i+=4) { // a ideia central é fazer um loop que percorre os bits de x, verificando a cada iteração se os 16 bits menos significativos de x correspondem a y. Se houver uma correspondência, a função retorna 1. Caso contrário, x é deslocado para a direita em 4 bits (equivalente a dividir por 16) para verificar o próximo conjunto de bits. O loop continua até que todos os bits de x tenham sido verificados.
        unsigned short byte = x & 0xFFFF; // 0xFFFF é uma máscara que mantém apenas os 16 bits menos significativos de x, que correspondem a um "byte" de 16 bits. O operador & é usado para aplicar essa máscara a x, resultando em um valor que representa os 16 bits menos significativos de x.
        if(byte == y){
            return 1;
        }
        x = x >> 4;
    }

    return 0;
}



int main(){
  unsigned long x;
  unsigned short y;

  x = 28736452;
  y = 21;

  printf("X: 0x%.16lX\n", x);
  printf("Y: 0x%.4X\n", y);

  if (match(x, y))
    printf("Y está contido em X\n");
  else
    printf("Y não está contido em X\n");

  x = 28736452;
  y = 438;

  printf("X: 0x%.16lX\n", x);
  printf("Y: 0x%.4X\n", y);



  if (match(x, y))
    printf("Y está contido em X\n");
  else
    printf("Y não está contido em X\n");
  return 0;

}