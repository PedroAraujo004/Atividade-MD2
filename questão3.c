/*
 * Exercício 3 de MD2
 * Aluno: Pedro Araujo Lucena
 * Matrícula: 222007077
 */

#include <stdio.h>

/* potencia_inteira: calcula base^exp por multiplicação iterativa */
long long potencia_inteira(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

/* fatoracao_prima: trial division até sqrt(n), preenche fatores[] e expoentes[] */
int fatoracao_prima(int valor, int fatores[], int expoentes[]) {
    int k = 0;
    int n = valor;

    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) {
                n /= p;
                e++;
            }
            fatores[k] = p;
            expoentes[k] = e;
            k++;
        }
    }
    if (n > 1) { /* fator primo restante */
        fatores[k] = n;
        expoentes[k] = 1;
        k++;
    }
    return k;
}

/* calcula_tau: tau(N) = prod_i (e_i + 1) 
   nota: recebe apenas expoentes[], pois fatores[] não é usado aqui */
int calcula_tau(int expoentes[], int qtd, int N) {
    int tau = 1;
    printf("\nCálculo intermediário de tau(%d):\n", N);
    printf("tau(%d) = ", N);
    for (int i = 0; i < qtd; i++) {
        printf("(%d+1)", expoentes[i]);
        tau *= (expoentes[i] + 1);
        if (i < qtd - 1) printf(" × ");
    }
    printf(" = %d\n", tau);
    return tau;
}

/* calcula_sigma: sigma(N) = prod_i ( (p^(e+1)-1) / (p-1) ) */
long long calcula_sigma(int fatores[], int expoentes[], int qtd, int N) {
    long long sigma = 1;
    printf("\nCálculo intermediário de sigma(%d):\n", N);
    printf("sigma(%d) = ", N);
    for (int i = 0; i < qtd; i++) {
        int p = fatores[i];
        int e = expoentes[i];
        long long numerador = potencia_inteira(p, e + 1) - 1;
        long long denominador = p - 1;
        long long termo = numerador / denominador;
        printf("((%d^(%d+1) - 1) / (%d - 1))", p, e, p);
        sigma *= termo;
        if (i < qtd - 1) printf(" × ");
    }
    printf(" = %lld\n", sigma);
    return sigma;
}

int main(void) {
    int N;
    int fatores[20], expoentes[20];
    int qtd_fatores;
    int tauN;
    long long sigmaN;
    double razao;

    printf("Informe um número inteiro N (1 ≤ N ≤ 105): ");
    if (scanf("%d", &N) != 1) {
        printf("Entrada inválida.\n");
        return 0;
    }

    if (N < 1 || N > 105) {
        printf("Erro: N deve estar entre 1 e 105.\n");
        return 0;
    }

    if (N == 1) {
        printf("\nO número 1 não possui decomposição em fatores primos.\n");
        printf("Razão de Eficiência = sigma(1)/tau(1) = 1/1 = 1.00\n");
        return 0;
    }

    qtd_fatores = fatoracao_prima(N, fatores, expoentes);

    printf("\nFatores primos de %d: ", N);
    for (int i = 0; i < qtd_fatores; i++) {
        printf("%d^%d", fatores[i], expoentes[i]);
        if (i < qtd_fatores - 1) printf(" * ");
    }
    printf("\n");

    /* chamada atualizada: passa apenas expoentes[] e qtd */
    tauN = calcula_tau(expoentes, qtd_fatores, N);
    sigmaN = calcula_sigma(fatores, expoentes, qtd_fatores, N);
    razao = (double)sigmaN / (double)tauN;

    printf("\nRazão de Eficiência = sigma(N)/tau(N) = %lld/%d = %.2f\n", sigmaN, tauN, razao);
    return 0;
}
