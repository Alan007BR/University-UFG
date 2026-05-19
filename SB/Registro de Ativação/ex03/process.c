int calc(int i, int j, int k, int l, int m, int n);

int process(int a, int b, int c, int d, int e, int f) {
   int r = calc(f, e, d, c, b, a);

   return r + a + b + c + d + e + f;
}