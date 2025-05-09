#include <stdio.h>

long long potencia(int a, int b) {
    if (b == 0)
        return 1;  
    else
        return a * potencia(a, b - 1);
}


int MDC(int G, int n) {
    printf("\nVamos verificar se %d e  %d sao coprimos e consequentemente inversiveis com o Algoritmo de Euclides\n", G, n);
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
        printf("\n nao foi possivel calcular a operacao (H/G mod n)\n");
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

int primo(int n) {
    if (n <= 1) {
        printf("Como %d e menor ou igual a 1, nao e primo.\n", n);
        return 0;
    }

    if (n == 2) {
        printf("%d e primo.\n", n);
        return 1;
    }

    if (n % 2 == 0) {
        printf("%d e divisivel por 2, portanto nao e primo.\n", n);
        return 0;
    }

    printf("verificar divisores impares ate a raiz quadrada de %d\n", n);
    for (int i = 3; i * i <= n; i += 2) {
        printf("Testando divisor %d...\n", i);
        if (n % i == 0) {
            printf("%d e divisivel por %d, portanto nao e primo.\n", n, i);
            return 0;
        }
    }

    printf("Nenhum divisor encontrado. %d e primo.\n", n);

    printf("\n----------------------------------- \n");
    return 1;
}

void decompor(int x, int x1, int *q, int *r){

    printf("\nvamos decompor o %d na forma %d = %d + q * r\n", x, x, x1);

    *q = x / x1;
    printf("\n o quociente da divisao de %d por %d = %d\n\n", x, x1, *q);

    *r = x % x1;
    printf("\n o resto da divisao de %d por %d = %d\n\n", x, x1, *r);

    printf("assim %d pode ser decomposto na forma %d = %d * %d + %d\n", x, x, x1, *q, *r);

}

void valorX2(int *x2, int a, int n1, int x1){
    *x2 = potencia(a, x1) % n1;

}

int combinar();


int main() {


    int H = 20, G = 4, n = 3, x = 9, n1 = 5;
    int x1 = 0;
    int q;
    int r;
    int x2;

    int a = divisao(H, G, n);
    if (a == -1) return 1;

    if (MDC(a, n1));

    if(primo(n1)){
        x1 = n-1;
    }

    decompor(x, x1, &q, &r);

    valorX2(&x2, a, n1, x1);
    
    return 0;


}
