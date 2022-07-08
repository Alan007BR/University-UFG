#include <stdio.h>
#include <stdlib.h>

void libera_matriz(unsigned char **A, int H) {
    int l;

    for(l = 0; l < H; l++) {
        free(A[l]);
    }

    free(A);
}

void print_pgm(unsigned char **I, int W, int H) {
    int l, c;

    printf("P2\n");
    printf("%d %d\n %d\n", W, H, 255);

    for(l = 0; l < H; l++) {
        for(c = 0; c < W; c++) {
            printf("%d ", I[l][c]);
            printf("\n");
        }
    }

}

void draw_rect(unsigned char **I, int W, int H, int w, int h, int x, int y, int cr) {//desenhar
    int l = 0, c = 0;

    for(l = y; l < (y+h); l++) {//linha
        if(l >= H) break;
        for(c = x; c < (x+w); c++) {//coluna
            if(c>= W) break;
            I[l][c] = cr;
        }
    }
}

void image_fill(unsigned char **A, int W, int H, unsigned char cor) {
    int l, c;

    for(l = 0; l < H; l++) {
        for(c=0; c < W; c++) {
            A[l][c] = cor;
        }
    }
}

unsigned char ** nova_matriz(int W, int H) {
    unsigned char **A;
    int i = 0;
    A = (unsigned char **)malloc(H*sizeof(unsigned char **));

    for(i = 0; i < H; i++) {

        A[i] = (unsigned char *)malloc(W*sizeof(char));
    }

    return A;
}

int main() {

    int H, W, h, w, x, y, cr;
    int i = 0, n;
    unsigned char **I;
    //largura, largura
    scanf("%d %d", &W, &H);
    scanf("%d", &n);

    //alocar dinamicamente a matriz
    I = nova_matriz(W, H);

    //preencher img com cor branca
    image_fill(I, W, H, 255);
    
    for(i = 0; i < n; i++) {
    //scanf("%d %d %d %d %d", &w, &h, &x, &y, &cr);

    w = 10 + rand() % 31;
    h = 2 + rand() % 199;
    x = rand() % H;
    y = rand() % W;
    cr = rand() % 255;

    draw_rect(I, W, H, w, h, x, y, cr);
    }

    // scanf("%d %d %d %d %d", &w, &h, &x, &y, &cr);
    // draw_rect(I, W, H, w, h, x, y, cr);


    print_pgm(I, W, H);
    libera_matriz(I, H);

    // 300 40 10 10 128;
    return 0;
}