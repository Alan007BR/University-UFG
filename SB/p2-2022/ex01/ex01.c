int vet[5] = {10,20,10,40,20};

void calc(int *resp, int mark) {
  int i = 0;
  while (i < 5) {
    if (vet[i] == mark)
      *resp = vet[i];
    else
      mark = *resp;
    i++;
  }
}