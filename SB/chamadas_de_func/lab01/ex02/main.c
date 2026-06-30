#define LEN 4
#define LIM 10

long filtro(unsigned char x, short lim, long b);

int i = 0;
long bias = 256;
unsigned char vet[LEN] = {12,3,20,8};

int main(){

  for (i = 0; i < LEN; i++) {
    bias = filtro(vet[i], LIM, bias);
  }

  return 0;
}