    #include <stdio.h>
    #include <stdlib.h>
     
    #define MAX_ 60
     
    typedef struct Polinomios
    {
        double cof[MAX_];
    } poli;
     
    void posoma(void);
    void posub(void);
     
    int main(void)
    {
        int n;
        char sinal;
     
        scanf("%d", &n);
     
        while(n--)
        {
            getchar();
            scanf("%c", &sinal);

            if(sinal=='+') posoma();
            if(sinal=='-') posub();
        }
     
        return 0;
    }
     
    void posoma(void)
    {
        int n1, n2;
        int i, j;
        int exp;
        double cof;
        poli v1[5];
     
        for(i=0 ; i<MAX_ ; i++){
            v1[0].cof[i] = 0;
            v1[1].cof[i] = 0;
        }
     
        scanf("%d", &n1);
     
        for(i=0 ; i<n1 ; i++)
        {
            scanf("%lf %d", &cof, &exp);
            v1[0].cof[exp] = cof;
        }
     
        scanf("%d", &n2);
     
        for(i=0 ; i<n2 ; i++)
        {
            scanf("%lf %d", &cof, &exp);
            v1[1].cof[exp] = cof;
        }
     
        for(i=0 ; i<MAX_ ; i++)
        {
            v1[2].cof[i] = v1[0].cof[i] + v1[1].cof[i];
        }
     
        for(i=MAX_-1 ; i>=0 ; i--)
        {
            if(v1[2].cof[i] != 0)
            {
                if(v1[2].cof[i] > 0)
                {
                    printf("+");
                    if(i==0)
                    {
                        printf("%.2lf\n", v1[2].cof[i]);
                    }
                    else printf("%.2lfX^%d", v1[2].cof[i], i);
                }
                else if(v1[2].cof[i] < 0)
                {
                    if(i==0)
                    {
                        printf("%.2lf\n", v1[2].cof[i]);
                    }
                    else printf("%.2lfX^%d", v1[2].cof[i], i);;
                }
            }
        }
     
    }
     
    void posub() {
        int n1, n2;
        int i, j;
        int exp;
        double cof;
        poli v1[5];
     
        for(i=0 ; i<MAX_ ; i++)
        {
            v1[0].cof[i] = 0;
            v1[1].cof[i] = 0;
        }
     
        scanf("%d", &n1);
     
        for(i=0 ; i<n1 ; i++)
        {
            scanf("%lf %d", &cof, &exp);
            v1[0].cof[exp] = cof;
        }
     
        scanf("%d", &n2);
     
        for(i=0 ; i<n2 ; i++)
        {
            scanf("%lf %d", &cof, &exp);
            v1[1].cof[exp] = cof;
        }
     
        for(i=0 ; i<MAX_ ; i++)
        {
            v1[2].cof[i] = v1[0].cof[i] - v1[1].cof[i];
        }
     
        for(i=MAX_-1 ; i>=0 ; i--)
        {
            if(v1[2].cof[i] != 0)
            {
                if(v1[2].cof[i] > 0)
                {
                    printf("+");
                    if(i==0)
                    {
                        printf("%.2lf\n", v1[2].cof[i]);
                    }
                    else printf("%.2lfX^%d", v1[2].cof[i], i);
                }
                else if(v1[2].cof[i] < 0)
                {
                    if(i==0)
                    {
                        printf("%.2lf\n", v1[2].cof[i]);
                    }
                    else printf("%.2lfX^%d", v1[2].cof[i], i);;
                }
            }
        }
     
    }