#include <stdio.h>

int main() {

 //   double temp1 = 0.0, temp2 = 0.0, temp3 = 0.0, temp4 = 0.0;
    double C1 = 0.0;
    int nvezes = 0, i = 0;


    scanf("%d", &nvezes);
    
    double temp[nvezes];

    // for (i = 0; i <= (nvezes - 1); i++) {
    // scanf("%lf", &temp[i]);

    // }

    while ( i <= (nvezes - 1) ) {

        i++;
        scanf("%lf", &temp[i]);
    }

i = 0;
while ( i <= (nvezes - 1) ){

    i++;
    
    C1 = 5*(temp[i] - 32)/9;
    printf("%.2lf FAHRENHEIT EQUIVALE A %.2lf CELSIUS\n", temp[i], C1);
}   

// for (i = 0; i <= (nvezes - 1); i++) {
    
//     C1 = 5*(temp[i] - 32)/9;
//     printf("%.2lf FAHRENHEIT EQUIVALE A %.2lf CELSIUS\n", temp[i], C1);
// }



    

    return 0;
}