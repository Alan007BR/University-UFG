int values[8] = {10,20,10,40,20,50,30,10};

long aux(short size, int *slice);

long process(int stamp, long limit, char base) {

int i;

for (i = 7; i >= 0; i--) {
    if (stamp > values[i])
        limit = (2*limit) + aux((short)i, (values + i));
    else
        printf("%d, %ld\n", stamp, limit);
}

return limit;
}