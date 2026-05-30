int max = 256;
short lim = -3;
char timer = 100;

long vet1[5] = {1, 0, 2, 3, 4};
int vet2[5] = {0, 0, 0, 0, 0};

char calc(long *a, int *b);
long complex(int i, short j, int *v);

void modify(int *v1, long *v2, char value) {
    long index;
    
    while (value > calc(v2, v1)) {
        index = complex(max, lim, v1);
    }
    
    v1[ v2[index] ] = (int)value;
}

void basic(int sum) {
    long *ptr = vet1;
    
    while (sum < timer) {
        if (sum == 13) {
            break;
        }
        
        for (int i = 0; i < 10; i++, sum++) {
            printf("i = %d, sum = %d\n", i, sum);
        }
        
        modify(vet2, ptr, timer);
        ptr++;
    }
}