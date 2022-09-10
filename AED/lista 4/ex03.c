#include <stdio.h>
#include <stdlib.h>

void error(const char *function_name) {
    printf("Erro na função %s\n", function_name);
    exit(0);
}

int defineFrequency(int num1, int num2, int frequencyColor, int numColors, int *colors, int *anoes) {
        int j = 0;

        for(j = num1-1; j < num2; j++) {
            colors[anoes[j]-1]++;
        }

        frequencyColor = 0;
        for(j = 1; j < numColors; j++) {
            if(colors[j] > colors[frequencyColor]) frequencyColor = j;
        }

        return frequencyColor;
}
int main() {
    int *anoes = NULL;
    int *colors = NULL;

    int numAnoes, numColors, photos, NumA;
    int num1, num2, frequencyColor;
    int i = 0;

    scanf("%d %d", &numAnoes, &numColors);

    anoes = (int *) malloc(numAnoes * sizeof(int));
    colors = (int *) malloc(numColors * sizeof(int));

    for(i = 0; i < numAnoes; i++) {
        scanf("%d", &anoes[i]);
    }

    scanf("%d", &photos);

    for(i = 0; i < photos; i++) {
        scanf("%d %d", &num1, &num2);

        memset(colors, 0, numColors * sizeof(int));

        frequencyColor = defineFrequency(num1, num2, frequencyColor, numColors, colors, anoes);


        if(colors[frequencyColor] > (num2 - num1 + 1) / 2){
            printf("bonita %d\n", frequencyColor+1);
        } else {
            printf("feia\n");
        }
    }

    free(anoes); free(colors);
    
    return 0;
}