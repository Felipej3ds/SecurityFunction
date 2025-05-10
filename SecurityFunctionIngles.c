#include <stdio.h>

long long potencia(int a, int b) {
    if (b == 0)
        return 1;  
    else
        return a * potencia(a, b - 1);
}

int MDC(int G, int n) {
    printf("Let's check if %d and %d are coprime and therefore invertible using the Euclidean Algorithm\n", G, n);
    while (n != 0) {
        printf("\nG = n * q + r\n");
        printf("G: %d, n: %d, q: %d, r : %d\n", G, n, G/n, G % n);
        int temp = n;
        n = G % n;
        G = temp;
    }
    if (G == 1) {
        printf("\nRelatively prime (GCD = 1)\n");
    } else {
        printf("\nNot relatively prime (GCD = %d)\n", G);
    }
    printf("\n ----------------------------------- \n");
    return G == 1;
}

int inverso(int G, int Zn) {
    int original_G = G, original_Zn = Zn;

    if (!MDC(G, Zn)) {
        printf("\nCannot compute modular inverse: G = %d in Zn = %d; G and n are not coprime.\n", G, Zn);
        printf("\nCould not compute the operation (H/G mod n)\n");
        return -1;
    }

    printf("\n2. Let's calculate the inverse of G = %d in Zn = %d\n", G, Zn);
    printf("Using the Extended Euclidean Algorithm with successive divisions:\n\n");

    int r[100], q[100];
    int i = 0;

    r[0] = Zn;
    r[1] = G;

    while (r[i + 1] != 0) {
        q[i] = r[i] / r[i + 1];
        r[i + 2] = r[i] % r[i + 1];
        printf("Division: %d = %d * %d + %d\n", r[i], q[i], r[i + 1], r[i + 2]);
        i++;
    }

    int s[i + 2], t[i + 2];
    s[0] = 1; s[1] = 0;
    t[0] = 0; t[1] = 1;

    for (int j = 2; j <= i + 1; j++) {
        s[j] = s[j - 2] - q[j - 2] * s[j - 1];
        t[j] = t[j - 2] - q[j - 2] * t[j - 1];
        printf("Step %d: s = %d, t = %d\n", j - 1, s[j], t[j]);
    }

    int inverso = t[i];
    if (inverso < 0) {
        printf("The result t = %d is negative. Adjusting to interval [0, %d)\n", inverso, original_Zn);
        inverso += original_Zn;
    }

    printf("The modular inverse of G = %d in Zn = %d is: %d\n", original_G, original_Zn, inverso);
    printf("\n ----------------------------------- \n");
    return inverso;
}

int divisao(int H, int G, int n) {
    int G_inverso = inverso(G, n);

    if (G_inverso == -1) {
        printf("\nCannot perform the operation (%d/%d mod %d) because %d has no inverse in Z_%d.\n", H, G, n, G, n);
        return -1;
    }

    printf("\n3. Performing the operation H / G mod n:\n");
    int a = (H * G_inverso) % n;

    printf("%d * %d mod %d = %d\n", H, G_inverso, n, a);
    printf("\nObtained base a = %d", a);
    printf("\n----------------------------------- \n");
    return a;
}

int primo(int n) {
    printf("\n5. Let's check whether %d is prime\n", n);
    if (n <= 1) {
        printf("Since %d is less than or equal to 1, it is not prime.\n", n);
        printf("\n----------------------------------- \n");
        return 0;
    }

    if (n == 2) {
        printf("%d is prime.\n", n);
        printf("\n----------------------------------- \n");
        return 1;
    }

    if (n % 2 == 0) {
        printf("%d is divisible by 2, so it is not prime.\n", n);
        printf("\n----------------------------------- \n");
        return 0;
    }

    printf("Check odd divisors up to the square root of %d\n", n);
    for (int i = 3; i * i <= n; i += 2) {
        printf("Testing divisor %d...\n", i);
        if (n % i == 0) {
            printf("%d is divisible by %d, so it is not prime.\n", n, i);
            printf("\n----------------------------------- \n");
            return 0;
        }
    }

    printf("No divisors found. %d is prime.\n", n);
    printf("\n----------------------------------- \n");
    return 1;
}

int calcular_mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int totiente_de_Euler(int n) {
    printf("\n7. Since n1 is not prime, we apply Euler's theorem and define x1 = phi(n)\n");
    if (n <= 0) {
        printf("Error: n must be a positive integer.\n");
        printf("\n----------------------------------- \n");
        return 0; 
    }

    if (n == 1) {
        printf("Since n = 1, phi(1) = 1\n");
        printf("\n----------------------------------- \n");
        return 1; 
    }

    int contador = 0;
    for (int i = 1; i < n; i++) { 
        if (calcular_mdc(n, i) == 1) { 
            printf("gcd(%d, %d) = 1\n", n, i);
            contador++;
        }
    }
    printf("phi(%d) = %d\n", n, contador);
    printf("\n----------------------------------- \n");
    return contador;
}

void decompor(int x, int x1, int *q, int *r) {
    printf("\n8. Let's decompose %d as %d = k * q + r\n", x, x, x1);

    *q = x / x1;
    printf("\nThe quotient q of dividing %d by %d = %d\n\n", x, x1, *q);

    *r = x % x1;
    printf("\nThe remainder r of dividing %d by %d = %d\n\n", x, x1, *r);

    printf("So %d can be decomposed as %d = %d * %d + %d\n\n", x, x, x1, *q, *r);
    printf("\n----------------------------------- \n");
}

int reescrever(int a, int x1, int r, int q, int n1) {
    printf("\n9. Let's rewrite the expression {a^x mod n as a^x congruent to (((a^x1)^q mod n1)(a^r mod n1))mod n1} directly\n");
    int resultado = (potencia(potencia(a, x1), q) % n1) * (potencia(a, r) % n1) % n1;
    printf("The result of the congruence is %d\n", resultado);
    printf("\n----------------------------------- \n");
}

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

long long fast_exp_mod(long long a, long long x1, long long q, long long r, long long n1) {
    printf("Step 1: Calculate x2 = a^x1 mod n1\n");
    printf("         x2 = %lld^%lld mod %lld\n", a, x1, n1);
    long long x2 = mod_exp(a, x1, n1);
    printf("         Result: x2 = %lld\n\n", x2);

    printf("Step 2: Calculate y = x2^q mod n1\n");
    printf("         y = %lld^%lld mod %lld\n", x2, q, n1);
    long long y = mod_exp(x2, q, n1);
    printf("         Result: y = %lld\n\n", y);

    printf("Step 3: Calculate z = a^r mod n1\n");
    printf("         z = %lld^%lld mod %lld\n", a, r, n1);
    long long z = mod_exp(a, r, n1);
    printf("         Result: z = %lld\n\n", z);

    printf("Step 4: Combine the results\n");
    printf("         result = (y * z) mod n1 = (%lld * %lld) mod %lld\n", y, z, n1);
    long long result = (y * z) % n1;
    printf("         Final result: %lld\n", result);

    return result;
}

int main() {
    int H = 0, G = 0, n = 0, x = 0, n1 = 0, x1 = 0, q, r, x2;

    printf("Let's calculate the value of base a with the operation H / G in Zn\n");
    printf("First, enter the value of H: \n");
    scanf("%d", &H);
    printf("Second, enter the value of G: \n");
    scanf("%d", &G);
    printf("Enter the value of the modulus m: \n");
    scanf("%d", &n);
    printf("\nEnter the value of the exponent x: \n");
    scanf("%d", &x);
    printf("\nEnter the value of the modulus n1\n");
    scanf("%d", &n1);

    printf("\n1. ");
    int a = divisao(H, G, n);
    if (a == -1) return 1;

    printf("4. \n");
    MDC(a, n1);

    if (primo(n1)) {
        printf("6. Since n1 is prime, we apply Fermat's Little Theorem and define x1 = n - 1\n\n");
        x1 = n - 1;
        printf("\n----------------------------------- \n");
    } else {
        x1 = totiente_de_Euler(n);
    }

    decompor(x, x1, &q, &r);
    reescrever(a, x1, r, q, n1);

    printf("10/11. Let's calculate the intermediate values and combine the results\n\n");
    fast_exp_mod(a, x1, q, r, n1);

    return 0;
}
