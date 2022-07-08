#include <stdio.h>

    int main() {

        int account, option;
        double consum = 0.0;
        double value = 0.00;

        scanf("%d", &account);
        if(account <= 0 || account > 100000000) { printf("erro\n"); return 0;}
        scanf("%d", &option);
        if(option < 1 || option > 3) { printf("erro\n"); return 0;}
        scanf("%lf", &consum);
        if(consum < 0) { printf("erro\n"); return 0;}




        switch (option) {
        case 1:
            value = 5.0 + (0.05 * consum);
            break;
        case 2:
            if(consum > 80) {
                value = 500 +  (0.03 * (consum - 80));
            }else if(consum <= 80) { value = 500; return 0; }

            break;
        case 3:

            if(consum > 100) {
                value = 800 +  (0.04 * (consum - 100));
            }else if(consum <= 100) { value = 800; return 0; }
                        
            break;
        
        default:

            printf("error\n"); return 0;
            break;
        }

        printf("%.2lf\n", value);

        return 0;
    }