#include <stdio.h>
#include <stdlib.h>
#include "../algorithms/cache_fifo.h"
#include "../algorithms/cache_lru.h"
#include "../algorithms/cache_lfu.h"
#include "../simulation/simulacao.h"

#define MAX_TEXTOS 100

static void abrirTexto(int id) {
    char nome[64];
    sprintf(nome, "texts/%d.txt", id);
    FILE *f = fopen(nome, "r");
    if (!f) {
        printf("Erro ao abrir o texto %d\n", id);
        return;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), f)) printf("%s", linha);
    fclose(f);
}

void iniciarSistema(void) {
    int opcao, algoritmo;
    while (1) {
        printf("\n==== MENU PRINCIPAL ====\n");
        printf("1 - FIFO\n");
        printf("2 - LRU\n");
        printf("3 - LFU\n");
        printf("4 - Simular todos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &algoritmo) != 1) return;

        if (algoritmo == 0) break;
        if (algoritmo == 4) { executarSimulacao(); continue; }

        if (algoritmo == 1) inicializarCacheFIFO();
        else if (algoritmo == 2) inicializarCacheLRU();
        else if (algoritmo == 3) inicializarCacheLFU();
        else { printf("Opcao invalida\n"); continue; }

        while (1) {
            printf("\nDigite o numero do texto (0 para voltar, -1 para simulacao): ");
            if (scanf("%d", &opcao) != 1) return;

            if (opcao == 0) break;
            else if (opcao == -1) { executarSimulacaoAlgoritmo(algoritmo); }
            else if (opcao > 0 && opcao <= MAX_TEXTOS) {
                int hit = 0;
                if (algoritmo == 1) hit = buscarCacheFIFO(opcao);
                else if (algoritmo == 2) hit = buscarCacheLRU(opcao);
                else if (algoritmo == 3) hit = buscarCacheLFU(opcao);

                if (!hit) {
                    for (volatile int d = 0; d < 50000000; d++);
                    abrirTexto(opcao);
                    if (algoritmo == 1) inserirCacheFIFO(opcao);
                    else if (algoritmo == 2) inserirCacheLRU(opcao);
                    else if (algoritmo == 3) inserirCacheLFU(opcao);
                } else {
                    printf("Texto %d recuperado do cache\n", opcao);
                    abrirTexto(opcao);
                }
            } else {
                printf("Opcao invalida\n");
            }
        }
    }
}
