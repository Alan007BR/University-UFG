#include <stdio.h>

#include <math.h>



#define getsig(i)        ((i)>>31 & 1)

#define getexp(i)        ((i)>>23 & 0xff)

#define getfrac(i)       ((i) & 0x7fffff)

#define makefloat(s,e,f) ( (((s) & 1) << 31) | (((e) & 0xff) << 23) | ((f) & 0x7fffff) )



typedef union {

  float f;
  unsigned int i;

} U;



float int2float(int value)

{
    
  U u;

  unsigned int s = 0;
  unsigned int e = 0;
  unsigned int f = 0;
  
  s = getsig(u.i);
  e = getexp(u.i);
  f = getfrac(u.i);

  e = e + 1;
  u.i = makefloat(s, e, f);

  if (value == 0)
    return 0.0;

  // sinal e corrigir o numero
  if(value < 0) {
    s = 1;
    value = -value;
  }

  // encontrar representação binaria
  unsigned int E = 31;
  unsigned int mask = 0x80000000;
  for (int i = 0; i < 32; i++) {
    if((value & mask) != 0 )
        break;
    mask = mask >> 1;
    E--;
  }

//   for (int i = 0; i < 32; i++) {
//     if(value & (1 << i)) {
//       f = f | (1 << (22 - i)); // 1 mais a esquerda
//     }
//   }

  // a tal da mantissa
  e = E + 127; // expoente com bias
  // float = 127
  // double = 1023
  if(E == 23)
   f = value;
  else if (E > 23)
    f = value << (E - 23);
  else
    f = value >> (23 - E);

  u.i = makefloat(s, e, f);

  return u.f;
}



int main() {

   int i;



   printf("\n******** int2float ****************\n");



   i = 0;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = 1;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = -1;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = 12345;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = -12345;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = 13631488;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = 1879048192;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = 0x7fffffff;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   i = -i;

   printf(" %d -> %+10.4f, %+10.4f\n", i, (float)i, int2float(i));



   return 0;

}