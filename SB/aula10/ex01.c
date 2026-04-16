#include <stdio.h>

#include <math.h>

#include <limits.h>



#define getsig(x)        ((x)>>31 & 1)

#define getexp(x)        ((x)>>23 & 0xff)

#define getfrac(x)       ((x) & 0x7fffff)

#define makefloat(s,e,f) ((s & 1)<<31 | (((e) & 0xff) << 23) | ((f) & 0x7fffff))



typedef union {
  float f;
  unsigned int i;

} U; 

int float2int(float value){
    // quebrar em componentes em 3
    // resolver o exponente
    // resolver o sinal
    // resolver a mantissa

    // quebrar em componentes em 3
    U u;
    unsigned int s = 0;
    unsigned int e = 0;
    unsigned int f = 0;

    u.f = value;
    s = getsig(u.i);
    e = getexp(u.i);
    f = getfrac(u.i);

    if(e == 0 && f == 0) { // Denormalizado
        return 0.0;
    }

    // Expoente
    int E = e - 127;

    f = f | 0x0080000;    // Mantissa
    f = f >> (23 - E); // Ajustar a mantissa de acordo com o expoente

    if(E <= 23) {
        f = f >> (23 - E);
    }
    if(E > 23) {
        f = f << (E - 23);
    }

    // Sinal
    if(s == 1) { //1 é negativo
        f = -f;
    }

    value = value + 1.0; // Adicionar 1 à mantissa

    return value;
}

int main() {
   float f;

   printf("\n******** float2int ****************\n");

   f = 432423442342.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -0.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 0.5;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -0.5;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 0.125;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -0.125;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 1.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -1.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 1.5;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -1.5;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 2.5;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -2.5;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 5.4;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -5.4;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 12345.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -12345.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 14690064.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -14690064.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = 167788544.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = -167788544.0;
   printf(" %+10.4f -> %d %d\n", f, (int)f, float2int(f));

   f = (float) pow(2,31);
   printf(" %+10.4f (2^31) = overflow -> %d %d\n", f, (int)f, float2int(f));

   f = -f;
   printf(" %+10.4f (-2^31) -> %d %d\n", f, (int)f, float2int(f));

   f = -((float) pow(2,32));
   printf(" %+10.4f (-2^32 = overflow) -> %d %d\n", f, (int)f, float2int(f));

   return 0;

}