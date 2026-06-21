struct Y {
    long limit;
    char flag;
    short values[8];
};

void process(struct Y *v, short w, char z);

struct Y * init(struct Y *v, int pos) {
    return &v[pos];
}

void foo(char a, long b, short c) {
    struct Y vet[2];

    short j = 0;                        // 'j' deve ser alocado na pilha
    int i = 0;                          // 'i' deve ser alocado em 'r15'
    struct Y *ptr = init(vet, i);       // 'ptr' deve ser alocado em 'rcx'

    while (ptr->flag > a) {
        ptr->flag = (char)(b * j);
        if (ptr->values[j] == c) {
            ptr = &vet[i];
            i++;
        }
        j++;
        process(ptr, c, a);
    }
}