char constante() { return 0xFF; }

void init(short factor, long *pl, int *pi)
{
  *pl = factor*10;
  *pi = factor*20;
}
