#include <stdio.h>
#include <math.h>
   
  double abs(double n) {
      if(n<0) return -n;
      return n;
  }
  
  int next_power(int n, int p) {
   
      double ur = 0, ant = 0;
      int i;
   
      if (p == 0) {
          return 1;
      }
   
      for(i = 1; n - ur >= 0; i++) {
          ant = ur;
          ur = pow (i, p);
      }
   
   
      if( abs(ur-n) < abs(ant-n) ) {
          return i-1;
      }
      return i-2;
  }
   
  int main() {
   
      int num, exp, base;
      scanf("%d %d", &num, &exp);
   
      if (exp == 0) {
          return 1;
      }
   
      base = next_power(num, exp);
   
      printf("%d -> %d^%d = %.0f\n", num, base, exp, pow(base, exp));
   
      return 0;
  }