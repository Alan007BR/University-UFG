    #include <stdio.h>
    #define MAX 201
    typedef struct Countries {
        int id;
        int O;
        int P;
        int B;
    }   Countries;
     
    void swap(Countries *c, int i, int j){
        Countries tmp;
     
        tmp = c[j];
        c[j] = c[j+1];
        c[j+1] = tmp;
    }
    void initialize(Countries *c, int i){
        c[i].id = i+1;
        c[i].O  = 0;
        c[i].P  = 0;
        c[i].B  = 0;
    }
     
    int main(){
     
        Countries c[MAX];
        int modalities;
        int countries_size;
        int O, P, B;
        int i = 0, j = 0;
        int tmp;
     
        scanf("%d %d", &countries_size, &modalities);
     
        for (i = 0; i < countries_size;i++){
            initialize(c, i);
        }
            
        for(i = 0; i < modalities; i++){
            scanf("%d %d %d", &O, &P, &B);
            c[O-1].O++;
            c[P-1].P++;
            c[B-1].B++;
        }
     
        //bubbleSort
        for(i = 0; i < countries_size; i++){
            for(j = 0; j < countries_size-1; j++){
     
                if(c[j].O > c[j+1].O){
                    swap(&c, i, j);
                }
     
                if (c[j].O > c[j+1].O) swap(&c, i, j);
                else if (c[j].O == c[j+1].O){
                    if (c[j].P > c[j+1].P) swap(&c, i, j);
                    else if (c[j].P == c[j+1].P){
                        if (c[j].B > c[j+1].B) swap(&c, i, j);
                        else if (c[j].B == c[j+1].B){
                            if (c[j].id > c[j+1].id) swap(&c, i, j);
                        }
                    }
                }
     
            }
        }
     
        //exit
        for(i = countries_size-1; i >= 0; i--){
            printf("%d ", c[i].id);
        }
        printf("\n");
     
    }