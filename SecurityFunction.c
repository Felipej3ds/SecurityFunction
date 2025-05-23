#include <stdio.h>

long long potencia(int a, int b) {
    if (b == 0)
        return 1;  
    else
        return a * potencia(a, b - 1);
}


int MDC(int G, int n) {
    printf("Vamos verificar se %d e  %d sao coprimos e consequentemente inversiveis com o Algoritmo de Euclides\n", G, n);
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
    int original_G = G, original_Zn = Zn;

    if (!MDC(G, Zn)) {
        printf("\nNao e possivel calcular o inverso modular: G = %d em Zn = %d; G e n nao sao coprimos.\n", G, Zn);
        printf("\n nao foi possivel calcular a operacao (H/G mod n)\n");
        return -1;
    }

    printf("\n2. Vamos calcular o inverso de G = %d em Zn = %d\n", G, Zn);
    printf("Usando o Algoritmo de Euclides Estendido com divisoes sucessivas:\n\n");

    int r[100], q[100];  // vetores para restos e quocientes
    int i = 0;

    r[0] = Zn;
    r[1] = G;

    while (r[i + 1] != 0) {
        q[i] = r[i] / r[i + 1];
        r[i + 2] = r[i] % r[i + 1];
        printf("Divisao: %d = %d * %d + %d\n", r[i], q[i], r[i + 1], r[i + 2]);
        i++;
    }

    // Coeficientes de Bezout (s, t), voltando pelas divisoes
    int s[i + 2], t[i + 2];
    s[0] = 1; s[1] = 0;
    t[0] = 0; t[1] = 1;

    for (int j = 2; j <= i + 1; j++) {
        s[j] = s[j - 2] - q[j - 2] * s[j - 1];
        t[j] = t[j - 2] - q[j - 2] * t[j - 1];
        printf("Passo %d: s = %d, t = %d\n", j - 1, s[j], t[j]);
    }

    int inverso = t[i];
    if (inverso < 0) {
        printf("O resultado t = %d e negativo. Ajustando para o intervalo [0, %d)\n", inverso, original_Zn);
        inverso += original_Zn;
    }

    printf("O inverso modular de G = %d em Zn = %d e: %d\n", original_G, original_Zn, inverso);
    printf("\n ----------------------------------- \n");
    return inverso;
}

int divisao(int H, int G, int n) {
    int G_inverso = inverso(G, n);

    if (G_inverso == -1) {
        printf("\nNao e possivel realizar a operacao (%d/%d mod %d) pois %d nao possui inverso em Z_%d.\n", H, G, n, G, n);
        return -1;
    }

    printf("\n3. Realizando a operacao H / G mod n:\n");
    int a = (H * G_inverso) % n;

    printf("%d * %d mod %d = %d\n", H, G_inverso, n, a);

    printf("\nobtemos a base a = %d", a);
    printf("\n----------------------------------- \n");
    return a;
}

int primo(int n) {
    printf("\n5. vamos verificar se %d seria primo\n", n);
    if (n <= 1) {
        printf("Como %d e menor ou igual a 1, nao e primo.\n", n);
        printf("\n----------------------------------- \n");
        return 0;
    }

    if (n == 2) {
        printf("%d e primo.\n", n);
        printf("\n----------------------------------- \n");
        return 1;
    }

    if (n % 2 == 0) {
        printf("%d e divisivel por 2, portanto nao e primo.\n", n);
        printf("\n----------------------------------- \n");
        return 0;
    }

    printf("verificar divisores impares ate a raiz quadrada de %d\n", n);
    for (int i = 3; i * i <= n; i += 2) {
        printf("Testando divisor %d...\n", i);
        if (n % i == 0) {
            printf("%d e divisivel por %d, portanto nao e primo.\n", n, i);
            printf("\n----------------------------------- \n");
            return 0;
        }
    }

    printf("Nenhum divisor encontrado. %d e primo.\n", n);

    printf("\n----------------------------------- \n");
    return 1;
}

int calcular_mdc(int a, int b) {
    // Exemplo de implementação do MDC (Algoritmo de Euclides)
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int totiente_de_Euler(int n) {
    printf("\n7. como n1 nao seria primo vamos aplicar o Teorema de Euler, e definir x1 = phi(n)\n");
    if (n <= 0) {
        printf("Erro: n deve ser um inteiro positivo.\n");
        printf("\n----------------------------------- \n");
        return 0; 
    }

    if (n == 1) {
        printf("como n = 1, phi(1) = 1\n");
        printf("\n----------------------------------- \n");
        return 1; 
    }

    int contador = 0;
    for (int i = 1; i < n; i++) { 
        if (calcular_mdc(n, i) == 1) { 
            printf("mdc(%d, %d) = 1\n", n, i);
            contador++;
        }
    }
    printf("phi(%d) = %d\n", n, contador);
    printf("\n----------------------------------- \n");
    return contador;
}

void decompor(int x, int x1, int *q, int *r){

    printf("\n8 .vamos decompor o %d na forma %d = k * q + r\n", x, x, x1);

    *q = x / x1;
    printf("\n o quociente q da divisao de %d por %d = %d\n\n", x, x1, *q);

    *r = x % x1;
    printf("\n o resto r da divisao de %d por %d = %d\n\n", x, x1, *r);

    printf("assim %d pode ser decomposto na forma %d = %d * %d + %d\n\n", x, x, x1, *q, *r);

    printf("\n----------------------------------- \n");

}

int reescrever(int a, int x1, int r, int q, int n1){
    printf("\n 9. vamos reescrever a exprecao {a^x mod n como a^x congruente a (((a^x1)^q mod n1)(a^r mod n1))mod n1} diretamente\n");
    int resultado = (potencia(potencia(a, x1), q) % n1) * (potencia(a, r) % n1) % n1;
    printf(" o resultado da congruencia vai ser %d\n", resultado);
    printf("\n----------------------------------- \n");
}

// Função de exponenciação modular: (base^exp) % mod
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }

    return result;
}

// Função principal baseada na fórmula: a^x mod n1
long long fast_exp_mod(long long a, long long x1, long long q, long long r, long long n1) {
    printf("Etapa 1: Calcular x2 = a^x1 mod n1\n");
    printf("         x2 = %lld^%lld mod %lld\n", a, x1, n1);
    long long x2 = mod_exp(a, x1, n1);
    printf("         Resultado: x2 = %lld\n\n", x2);

    printf("Etapa 2: Calcular y = x2^q mod n1\n");
    printf("         y = %lld^%lld mod %lld\n", x2, q, n1);
    long long y = mod_exp(x2, q, n1);
    printf("         Resultado: y = %lld\n\n", y);

    printf("Etapa 3: Calcular z = a^r mod n1\n");
    printf("         z = %lld^%lld mod %lld\n", a, r, n1);
    long long z = mod_exp(a, r, n1);
    printf("         Resultado: z = %lld\n\n", z);

    printf("Etapa 4: Combinar os resultados\n");
    printf("         resultado = (y * z) mod n1 = (%lld * %lld) mod %lld\n", y, z, n1);
    long long result = (y * z) % n1;
    printf("         Resultado final: %lld\n", result);

    return result;
}



int main() {

    int H = 0;
    int G = 0; 
    int n = 0;
    int x = 0; 
    int n1 = 0;
    int x1 = 0;
    int q;
    int r;
    int x2;

    printf("vamos calcular o valor da base a com a operacao H / G em Zn\n");

    printf("primeiro introduza o valor de H: \n");
    scanf("%d", &H);
    printf("segundo introduza o valor de G: \n");
    scanf("%d", &G);
    printf("introduza o varlor do modulo m: \n");
    scanf("%d", &n);
    printf("\ndigite o valor do expoente x: \n");
    scanf("%d", &x);  
    printf("\ndigite o valor do modulo n1\n");
    scanf("%d", &n1);

    printf("\n1. ");
    int a = divisao(H, G, n);
    if (a == -1) return 1;

    printf("4. \n");
    MDC(a, n1);

    if(primo(n1)){
        printf("6. com n1 primo vamos aplicar o Pequeno Teorema de Fermat, e definir x1=n-1\n\n");
        x1 = n-1;
        printf("\n----------------------------------- \n");
    }
    else {
        x1 = totiente_de_Euler(n);
    }


    decompor(x, x1, &q, &r);

    reescrever(a, x1, r, q, n1);

    printf("10/11 vamos calcular os valores intermediarios e Combinar os resultados\n\n");

    fast_exp_mod(a, x1, q, r, n1);


    
    return 0;


}
