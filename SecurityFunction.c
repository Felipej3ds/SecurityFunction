#include <stdio.h>
#include <locale.h>

int MDC(int G, int n) {
    printf("\nVamos verificar se G = %d e inversivel em n = %d com o Algoritmo de Euclides\n", G, n);
    while (n != 0) {
        printf("\nG = n * q + r\n");
        printf("G: %d, n: %d, q: %d, r : %d\n", G, n, G/n, G % n);
        int temp = n;
        n = G % n;
        G = temp;
    }
    if (G == 1) {
        printf("\nRelativamente primos (MDC = 1)\n");
    } else {
        printf("\nNao sao relativamente primos (MDC = %d)\n", G);
    }

    printf("\n ----------------------------------- \n");
    return G == 1;
}

int inverso(int G, int Zn) {
    if (!MDC(G, Zn)) {
        printf("\nNao e possivel calcular o inverso modular: G = %d em Zn = %d; G e n nao sao coprimos.\n", G, Zn);
        return -1;
    }

    printf("\nVamos calcular o inverso de G = %d em Zn = %d\n", G, Zn);
    printf("Usando o Algoritmo de Euclides Estendido:\n\n");

    int t = 0, novo_t = 1;
    int r = Zn, novo_r = G;

    while (novo_r != 0) {
        int quociente = r / novo_r;

        printf("r = %d, novo_r = %d, quociente = %d\n", r, novo_r, quociente);

        int temp_t = t;
        t = novo_t;
        novo_t = temp_t - quociente * novo_t;
        printf("Atualizando coeficientes: t = %d, novo_t = %d\n", t, novo_t);

        int temp_r = r;
        r = novo_r;
        novo_r = temp_r - quociente * novo_r;
        printf("Atualizando restos: r = %d, novo_r = %d\n\n", r, novo_r);
    }

    if (t < 0) {
        printf("O resultado t = %d e negativo. Ajustando para o intervalo [0, %d)\n", t, Zn);
        t += Zn;
    }

    printf("O inverso modular de G = %d em Zn = %d e: %d\n", G, Zn, t);
    printf("\n ----------------------------------- \n");
    return t;
}

int divisao(int H, int G, int n) {
    int G_inverso = inverso(G, n);

    if (G_inverso == -1) {
        printf("\nNao e possivel realizar a operacao (%d/%d mod %d) pois %d nao possui inverso em Z_%d.\n", H, G, n, G, n);
        return -1;
    }

    printf("\nRealizando a operacao H / G mod n:\n");
    int a = (H * G_inverso) % n;

    printf("%d * %d mod %d = %d\n", H, G_inverso, n, a);

    printf("\nobtemos a base a = %d", a);
    printf("\n----------------------------------- \n");
    return a;
}

int main() {


    int H = 20, G = 4, n = 3, x = 9, n1 = 5;

    int a = divisao(H, G, n);

    return 0;


}
