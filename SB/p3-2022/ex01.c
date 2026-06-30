struct X {
    char  x;
    long  y;
    short z;
};

struct X varx;

int process(short *a, short *b, int c);

int calc() {
    int i;          // 'i' deve ser o registrador 'rdx'
    int j;          // 'j' deve ser o registrador 'r12'
    int tmp = 3;
    short vector[5];

    for (i = 0; i < 3; i++) {
        j = i + 1;
        tmp += process(&varx.z, &vector[j], (int)varx.x);
    }

    return tmp;
}