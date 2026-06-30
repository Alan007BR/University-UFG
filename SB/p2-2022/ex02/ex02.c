#define SIZE 120

void escape(long *x);
void init(long *x, short *v, int s);

long a;

int aux(short *ptr, int step, char *fmt, char limit) {
    init(&a, ptr, SIZE);

    for ( ; *ptr ; ptr++) {
        if ( (char)ptr[a] > limit )
            printf(fmt, *ptr);
        else {
            int i = 5;
            while (i > step) {
                a = a + i;
                escape(&a);
            }
        }
    }

    return (int)a;
}