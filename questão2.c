/*
 * Exercício 2 de MD2
 * Aluno: Pedro Araujo Lucena
 * Matricula: 222007077
 */

#include <stdio.h>
#include <stdlib.h>

/* Imprime lista de inteiros separados por espaço */
static void mostrar_lista(const int *vet, int n) {
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", vet[i]);
    }
    printf("\n");
}

/* Descarta o restante da linha do stdin */
static void descartar_resto_linha(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

/* Lê um inteiro com rótulo e validação [min..max] */
static int ler_inteiro(const char *rotulo, int min, int max) {
    int valor;
    for (;;) {
        printf("%s", rotulo);
        int ok = scanf("%d", &valor);
        if (ok != 1) {
            printf("  -> Entrada inválida. Informe um número inteiro no intervalo [%d,%d].\n", min, max);
            descartar_resto_linha();
            continue;
        }
        if (valor < min || valor > max) {
            printf("  -> Valor fora do intervalo. Digite um inteiro entre %d e %d.\n", min, max);
            descartar_resto_linha();
            continue;
        }
        descartar_resto_linha();
        return valor;
    }
}

/* MDC (algoritmo de Euclides) com impressão de passos */
static int mdc_euclides_detalhado(int a, int b, int *etapa) {
    (void)etapa;
    int a0 = a, b0 = b;
    printf("   [MDC] Iniciando Euclides para mdc(%d, %d)\n", a, b);
    int it = 0;
    while (b != 0) {
        int resto = a % b;
        int quoc = a / b;
        it++;
        printf("     -> %d = (%d * %d) + %d\n", a, quoc, b, resto);
        a = b;
        b = resto;
    }
    printf("   [MDC] Resultado: mdc(%d,%d) = %d\n", a0, b0, a);
    return a;
}

/* MMC via (a*b)/mdc com impressão informativa */
static int mmc_via_mdc_detalhado(int x, int y, int *etapa) {
    printf("Etapa %d: Calculando MMC(%d, %d) usando (a*b)/MDC\n", (*etapa)++, x, y);
    long long prod = (long long)x * (long long)y;
    printf("  -> Produto: %d * %d = %lld\n", x, y, prod);
    int g = mdc_euclides_detalhado(x, y, etapa);
    long long l = prod / g;
    printf("  -> MMC(%d,%d) = %lld\n", x, y, l);
    return (int)l;
}

int main(void) {
    int n_chaves;
    int ciclos[10];
    int etapa = 1;

    printf("Etapa %d: Informe a quantidade de chaves N (1..10)\n", etapa++);
    n_chaves = ler_inteiro("Digite N (1..10): ", 1, 10);

    printf("Etapa %d: Informe os %d ciclos (cada Ci entre 2 e 20)\n", etapa++, n_chaves);
    for (int i = 0; i < n_chaves; i++) {
        char rot[64];
        snprintf(rot, sizeof(rot), "Digite C%d (2..20): ", i + 1);
        ciclos[i] = ler_inteiro(rot, 2, 20);
    }

    printf("Etapa %d: Ciclos recebidos:\n", etapa++);
    printf("  -> ");
    mostrar_lista(ciclos, n_chaves);

    /* Calcula MMC iterativamente */
    printf("Etapa %d: Inicializando MMC parcial com C1 = %d\n", etapa++, ciclos[0]);
    int mmc_parcial = ciclos[0];

    for (int i = 1; i < n_chaves; i++) {
        printf("Etapa %d: Unindo MMC parcial (%d) com C%d = %d\n", etapa++, mmc_parcial, i + 1, ciclos[i]);
        mmc_parcial = mmc_via_mdc_detalhado(mmc_parcial, ciclos[i], &etapa);
        printf("  -> Novo MMC parcial: %d\n", mmc_parcial);
        if (mmc_parcial > 50) {
            printf("Etapa %d: MMC parcial ultrapassou 50. Não há sincronização em 1..50.\n", etapa++);
            printf("Resultado final: Não foi possível encontrar um ano sincronizado entre 1 e 50.\n");
            return 0;
        }
    }

    /* Verifica se mmc_parcial é múltiplo de todos e está no intervalo */
    printf("Etapa %d: Verificando se X = %d atende todos os ciclos\n", etapa++, mmc_parcial);
    int valido = 1;
    for (int i = 0; i < n_chaves; i++) {
        int r = mmc_parcial % ciclos[i];
        printf("  -> %d %% %d = %d %s\n", mmc_parcial, ciclos[i], r, (r == 0 ? "(ok)" : "(falha)"));
        if (r != 0) valido = 0;
    }

    if (mmc_parcial > 0 && mmc_parcial <= 50 && valido) {
        printf("Resultado final: Primeiro ano sincronizado = %d\n", mmc_parcial);
    } else {
        printf("Resultado final: Não foi possível encontrar um ano sincronizado entre 1 e 50.\n");
    }

    return 0;
}
