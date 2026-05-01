int i = 0;
int j;
int total = 0;

while (i < 3) {
    j = 0; // Inicialização do loop interno
    while (j < 2) {
        total = total + i;
        j++;
    }
    i++;
}