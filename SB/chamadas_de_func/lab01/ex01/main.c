#include <stdio.h>

int sum(const char *prefix, int v1, short v2, int *s);
void show(long err, int val, int r);

int val = 432;
short age = 4;
int r = 0;
long err = 2048;

int main(){

   val = sum("Hello", val, age, &r);
   show(err, val, r);

   return 0;

}