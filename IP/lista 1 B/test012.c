#include <stdio.h>

#define VERDADEIRO 1
#define FALSO 0

int main() {
  int n, cateto1, cateto2, hipotenusa;
  int achou;

  printf("Digite o comprimento maximo da hipotenusa: ");
  scanf("%d" , &n);

  for (hipotenusa = 1; hipotenusa <= n; hipotenusa++) {
    achou = FALSO;
    /* testa todos os candidatos a cateto */
    for (cateto1 = 1; cateto1 < hipotenusa && !achou; cateto1++) {
      cateto2 = cateto1; /* cateto1 e' o menor cateto */
      while (cateto1*cateto1 + cateto2*cateto2 < hipotenusa*hipotenusa)
	cateto2++;
      if (cateto1*cateto1 + cateto2*cateto2 == hipotenusa*hipotenusa){
	printf("hipotenusa = %d, catetos %d e %d\n", hipotenusa, cateto1, cateto2);
	achou = VERDADEIRO;
      }
    }
  }

  return 0;
}