struct Test {
    int    si;
    double sd;
    float  sf;
    long   sl;
};

void init(struct Test *vet);

float process(double limit, int factor, struct Test *old)
{
    double i = 0.0;
    struct Test new[5];

    init(new);

    for ( ; i < limit; i = i + 1.0) {
        int tmp = (int)i;
        double value = (old[tmp].sl / new[tmp].sd);
        printf("value = %f, factor = %d\n", value, factor);
        if (tmp & 0x40)
            limit = value - tmp;
    }

    return (float)limit + new[2].sf - factor;
}