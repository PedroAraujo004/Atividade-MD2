/*
 * Exercício 4 de MD2
 * Aluno: Pedro Araujo Lucena
 * Matrícula: 222007077
 */

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Calcula o máximo divisor comum mostrando os passos
int gcdComPassos(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

// Inverso modular usando algoritmo extendido de Euclides
int inverso_modular(int valor, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = valor, B = m;

    if (gcdComPassos(valor, m) != 1) {
        // inverso não existe quando gcd != 1
        printf("\nNao existe inverso de %d em %d (mdc != 1).\n", A, B);
        return 0;
    }

    while (m != 0) {
        q = valor / m;
        t = m;
        m = valor % m;
        valor = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0; // ajustar para positivo

    printf("\nSubstituindo: o inverso de %d em %d eh %d.\n", A, B, x1);
    return x1;
}

// Exponenciacao modular (fast exponentiation: quadrado e multiplica)
int potencia_modular(int base, int expoente, int mod) {
    long long res = 1;
    long long b = base % mod;

    while (expoente > 0) {
        if (expoente % 2 == 1) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        expoente >>= 1; // dividir por 2
    }
    return (int)res;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    int H_val, G_val, Zn_val, X_val, n1_val;

    printf("Digite H: ");
    scanf("%d", &H_val);
    printf("Digite G: ");
    scanf("%d", &G_val);
    printf("Digite Zn: ");
    scanf("%d", &Zn_val);
    printf("Digite X: ");
    scanf("%d", &X_val);
    printf("Digite n1: ");
    scanf("%d", &n1_val);

    int inv = inverso_modular(G_val, Zn_val);
    if (inv == 0) {
        printf("Operacao modular interrompida: inverso inexistente.\n");
        return 1;
    }

    int a = (H_val * inv) % Zn_val;
    printf("Realizando multiplicacao modular: %d * %d mod %d = %d\n", H_val, inv, Zn_val, a);
    printf("Observacao: %d eh o inverso de %d em %d.\n", inv, G_val, Zn_val);

    int resultado = potencia_modular(a, X_val, n1_val);
    printf("Resultado final da congruencia: %d\n", resultado);

    return 0;
}
