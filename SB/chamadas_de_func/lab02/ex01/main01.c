#include <stdio.h>

int maximo(char x, char y);

char a = 97;
char b = 105;

int main()
{
   // Use um registrador para 'ret'

   int ret = maximo(a, b);



   if (ret == a)
     printf("'a' maior do que 'b'\n");

   else
     printf("Valor de 'b': %d\n", (int)b);



   return 0;

}