char c = 67;

short s = 23;

int i = 0;

int j = 0;

long l = 1023;

unsigned int ui = 2047;

unsigned long ul = 4095;



void atribuicoes()

{

  c = 93;

  s = 75;

  j = 52;

  l = 7265;

  i = j;

}



void cast(){

    ui = i;

    j = s;

    ul = ui;

    s = c + j;

}



void expressoes()

{

  i = j * s;

  j = 1 + (s * 3);

  ui = 2 * (i + s * 2);

  ul = (l + j * 3) - (s + 1024);

}



void bitAbit(){

    c = c & 0x0F;

    s = s | 0x80;

    i = i ^ 0x55;

    j = (j | s) ^ c;

    l = l >> 2;

    ui = ui << 1;

    ul = ul >> 4;

}



void ponteiros(){

    short *ptr;

    ptr = &s;

    *ptr = 128;

}