/*
 * Exercicio 1 de MD2
 * Aluno: Pedro Araujo Lucena
 * Matrícula: 222007077
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* protótipos */
int mapa_pre(char c);
char mapa_de(int codigo);
long long meu_mdc(long long a, long long b);
long long g_pollard(long long x, long long n);
long long fator_pollard(long long n);
long long ler_N(const char *nome);
long long inverso_extenso(long long a, long long m);
long long escolherE(long long phi);
long long powmod(long long M, long long E, long long n, long long phi);
void etapa3_processa(long long E, long long D, long long n, long long phi);
int eh_primo(long long n);

/* pré-codificação: A=11,...,Z=36, espaço=0 */
int mapa_pre(char c) {
    if (c >= 'A' && c <= 'Z') return 11 + (c - 'A');
    if (c >= 'a' && c <= 'z') return 11 + (c - 'a');
    if (c == ' ') return 0;
    return -1;
}
char mapa_de(int codigo) {
    if (codigo == 0) return ' ';
    return 'A' + (codigo - 11);
}

/* Algoritmo de Euclides (MDC) com detalhes */
long long meu_mdc(long long a, long long b) {
    long long A = a, B = b;
    printf("  -> Executando Euclides para mdc(%lld,%lld)\n", A, B);
    int passo = 0;
    while (b != 0) {
        long long resto = a % b;
        passo++;
        printf("     passo %d: %lld = (%lld * %lld) + %lld\n", passo, a, a / b, b, resto);
        a = b;
        b = resto;
    }
    printf("  -> Resultado final: mdc(%lld,%lld) = %lld\n", A, B, a);
    return a;
}

/* função g(x) = x^2 + 1 (mod n) com log */
long long g_pollard(long long x, long long n) {
    long long x2 = x * x;
    long long out = (x2 + 1) % n;
    printf("     g(%lld) = (%lld^2 + 1) %% %lld = %lld\n", x, x, n, out);
    return out;
}

/* Pollard rho com impressão dos passos */
long long fator_pollard(long long n) {
    if (n % 2 == 0) {
        printf("  Observação: %lld é par — fator trivial = 2\n", n);
        return 2;
    }
    long long x = 2, y = 2, d = 1;
    int iter = 0;
    printf("\n  >>> Iniciando Pollard ρ para N = %lld\n", n);
    printf("      semente x0 = 2\n");
    while (d == 1) {
        iter++;
        printf("\n    Iteração #%d\n", iter);
        x = g_pollard(x, n);
        long long t = g_pollard(y, n);
        y = g_pollard(t, n);
        long long diff = llabs(x - y);
        printf("    |x - y| = |%lld - %lld| = %lld\n", x, y, diff);
        d = meu_mdc(diff, n);
        if (d == 1) {
            printf("    sem divisor não-trivial nesta rodada.\n");
        } else if (d == n) {
            printf("    gcd == n -> falha na tentativa (tente outro N).\n");
            return -1;
        } else {
            printf("    divisor encontrado: %lld\n", d);
            break;
        }
    }
    return d;
}

/* leitura validada de N (100..9999) */
long long ler_N(const char *nome) {
    long long N;
    int ok = 0;
    do {
        printf("Digite %s (produto de primos distintos entre 100 e 9999): ", nome);
        if (scanf("%lld", &N) != 1) {
            printf("  Entrada inválida — insira apenas números.\n");
            while (getchar() != '\n');
            continue;
        }
        if (N < 100 || N > 9999) {
            printf("  Valor fora do intervalo. Tente novamente.\n");
        } else {
            ok = 1;
        }
    } while (!ok);
    return N;
}

/* Euclides estendido para inverso modular (com logs) */
long long inverso_extenso(long long a, long long m) {
    long long r1 = a, r2 = m;
    long long s1 = 1, s2 = 0;
    long long t1 = 0, t2 = 1;
    int it = 0;
    printf("\n  >>> Iniciando Euclides Estendido para inverso de %lld mod %lld\n", a, m);
    while (r2 != 0) {
        it++;
        long long q = r1 / r2;
        long long r = r1 - q * r2;
        long long s = s1 - q * s2;
        long long t = t1 - q * t2;
        printf("    iter %d: q=%lld, r=%lld, s=%lld, t=%lld\n", it, q, r, s, t);
        r1 = r2; r2 = r;
        s1 = s2; s2 = s;
        t1 = t2; t2 = t;
    }
    if (r1 != 1) {
        printf("  Não existe inverso (mdc != 1). mdc=%lld\n", r1);
        return -1;
    }
    long long inv = s1;
    if (inv < 0) inv += m;
    printf("  Inverso modular: %lld (verificação: (%lld * %lld) %% %lld = %lld)\n", inv, a, inv, m, (a*inv)%m);
    return inv;
}

/* escolhe o menor E>1 coprimo com phi */
long long escolherE(long long phi) {
    printf("\n  Buscando expoente público E coprimo com φ=%lld...\n", phi);
    for (long long e = 2; e < phi; e++) {
        if (meu_mdc(e, phi) == 1) {
            printf("  -> E escolhido = %lld\n", e);
            return e;
        }
    }
    return -1;
}

/* exponenciação modular com escolha de teorema e logs */
long long powmod(long long M, long long E, long long n, long long phi) {
    printf("\n  Calculando %lld^%lld (mod %lld)\n", M, E, n);
    if (M % n == 0) {
        printf("   M é múltiplo de n -> resultado 0.\n");
        return 0;
    }
    long long expo = E;
    if (meu_mdc(M, n) == 1) {
        if (phi != n-1) {
            printf("   Aplicando Teorema de Euler: reduzir expoente modulo φ(%lld)=%lld\n", n, phi);
            expo = E % phi;
            printf("   expo reduzido = %lld mod %lld = %lld\n", E, phi, expo);
        } else {
            printf("   Aplicando Pequeno Teorema de Fermat: n é primo\n");
            expo = E % (n-1);
            printf("   expo reduzido = %lld mod %lld = %lld\n", E, (n-1), expo);
        }
    } else {
        printf("   Aplicando redução pelo Algoritmo da Divisão Euclidiana\n");
        expo = E % (n-1);
        printf("   expo reduzido = %lld mod %lld = %lld\n", E, (n-1), expo);
    }

    long long res = 1;
    long long base = M % n;
    long long e = expo;
    while (e > 0) {
        if (e & 1) {
            long long antes = res;
            res = (res * base) % n;
            printf("    multiplica: (%lld * %lld) mod %lld = %lld\n", antes, base, n, res);
        }
        long long bantes = base;
        base = (base * base) % n;
        e >>= 1;
        printf("    base^2: (%lld^2) mod %lld = %lld, expo agora = %lld\n", bantes, n, base, e);
    }
    printf("   -> Resultado: %lld\n", res);
    return res;
}

/* Etapa 3: cifrar e decifrar */
void etapa3_processa(long long E, long long D, long long n, long long phi) {
    printf("\n--- Etapa 3: Criptografia / Descriptografia ---\n");
    char msg[1024];
    printf("Escreva a mensagem (somente letras e espaços): ");
    while (getchar() != '\n');
    fgets(msg, sizeof(msg), stdin);

    int blocos[1024]; char orig[1024]; char minus[1024]; int t = 0;
    for (int i=0; msg[i] != '\0' && msg[i] != '\n'; i++) {
        int code = mapa_pre(msg[i]);
        if (code == -1) continue;
        blocos[t] = code; orig[t] = msg[i];
        minus[t] = (msg[i] >= 'a' && msg[i] <= 'z') ? 1 : 0;
        t++;
    }

    int width = 1;
    { long long tmp = n - 1; width = 0; do { width++; tmp/=10; } while (tmp>0); }

    long long cifrados[1024];
    printf("\n-- Criptografando cada bloco (2 dígitos) --\n");
    for (int i=0; i<t; i++) {
        printf("\n Bloco M = %02d  (caractere '%c')\n", blocos[i], orig[i]);
        cifrados[i] = powmod(blocos[i], E, n, phi);
        if (cifrados[i] == 0) printf("  Cifrado C = %02lld\n", cifrados[i]);
        else printf("  Cifrado C = %0*lld\n", width, cifrados[i]);
    }

    printf("\nMensagem cifrada (blocos):\n");
    for (int i=0; i<t; i++) {
        if (cifrados[i] == 0) printf("%02lld ", cifrados[i]);
        else printf("%0*lld ", width, cifrados[i]);
    }
    printf("\n");

    /* Decodificar */
    printf("\n-- Decifrando --\n");
    char dec[t+1];
    for (int i=0; i<t; i++) {
        if (cifrados[i] == 0) printf("\n Bloco C = %02lld\n", cifrados[i]);
        else printf("\n Bloco C = %0*lld\n", width, cifrados[i]);
        long long M = powmod(cifrados[i], D, n, phi);
        char letra = mapa_de((int)M);
        if (M != 0 && minus[i]) letra = (char)(letra + ('a' - 'A'));
        printf("  M recuperado = %02lld -> '%c'\n", M, letra);
        dec[i] = letra;
    }
    dec[t] = '\0';
    printf("\nMensagem decodificada: %s\n", dec);
}

/* primalidade simples (ok para 3-4 dígitos) */
int eh_primo(long long n) {
    if (n < 2) return 0;
    if (n % 2 == 0) return n == 2;
    for (long long i = 3; i*i <= n; i += 2) if (n % i == 0) return 0;
    return 1;
}

/* fluxo principal */
int main(void) {
    printf("=== Etapa 1: Fatoração interativa (ρ de Pollard) ===\n");
    printf("Nota: insira números resultantes do produto de primos distintos.\n\n");

    long long N1 = ler_N("N1");
    long long N2 = ler_N("N2");

    long long p = fator_pollard(N1);
    if (p == -1) { printf("\nErro na fatoração de N1. Encerrando.\n"); return 1; }
    long long cof1 = (p != 0) ? (N1 / p) : 0;
    if (p <= 1 || cof1 <= 1 || p == cof1 || !eh_primo(p) || !eh_primo(cof1)) {
        printf("\n[Validação] N1 não satisfaz a condição (primos distintos). Fatores detectados: %lld e %lld\n", p, cof1);
        return 1;
    }

    long long q = fator_pollard(N2);
    if (q == -1) { printf("\nErro na fatoração de N2. Encerrando.\n"); return 1; }
    long long cof2 = (q != 0) ? (N2 / q) : 0;
    if (q <= 1 || cof2 <= 1 || q == cof2 || !eh_primo(q) || !eh_primo(cof2)) {
        printf("\n[Validação] N2 não satisfaz a condição (primos distintos). Fatores detectados: %lld e %lld\n", q, cof2);
        return 1;
    }

    printf("\n=== Fatores finais obtidos ===\n");
    printf("p (de N1) = %lld\n", p);
    printf("q (de N2) = %lld\n", q);

    /* Etapa 2: gerar chaves */
    printf("\n=== Etapa 2: Geração das chaves RSA ===\n");
    long long n = p * q;
    printf("Módulo n = p * q = %lld * %lld = %lld\n", p, q, n);

    long long phi = (p - 1) * (q - 1);
    printf("Totiente φ(n) = (p-1)*(q-1) = %lld\n", phi);

    long long E = escolherE(phi);
    if (E == -1) { printf("Não foi possível escolher E. Abortando.\n"); return 1; }
    long long D = inverso_extenso(E, phi);
    if (D == -1) { printf("Não existe inverso modular para E. Abortando.\n"); return 1; }

    printf("\n--- Par de chaves ---\n");
    printf("Chave pública  (n, e) = (%lld, %lld)\n", n, E);
    printf("Chave privada (n, d) = (%lld, %lld)\n", n, D);

    etapa3_processa(E, D, n, phi);

    return 0;
}
