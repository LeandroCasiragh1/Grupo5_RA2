#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../algorithms/cache_fifo.h"
#include "../algorithms/cache_lru.h"
#include "../algorithms/cache_lfu.h"
#include "simulacao.h"

static void relatorioGeral(const int hitsFIFO, const int hitsLRU, const int hitsLFU, int total) {
    FILE *f = fopen("docs/relatorio.md", "w");
    if (!f) { printf("Erro ao criar docs/relatorio.md\n"); return; }
    fprintf(f, "# Relatorio de Simulacao\n\n");
    fprintf(f, "FIFO: %d hits (%.2f%%)\n", hitsFIFO, hitsFIFO * 100.0 / total);
    fprintf(f, "LRU: %d hits (%.2f%%)\n", hitsLRU, hitsLRU * 100.0 / total);
    fprintf(f, "LFU: %d hits (%.2f%%)\n", hitsLFU, hitsLFU * 100.0 / total);
    int best = 0; int arr[3] = {hitsFIFO, hitsLRU, hitsLFU};
    for (int i = 1; i < 3; i++) if (arr[i] > arr[best]) best = i;
    const char *nomes[3] = {"FIFO","LRU","LFU"};
    fprintf(f, "\n**Algoritmo recomendado: %s**\n", nomes[best]);
    fclose(f);
    printf("Relatorio salvo em docs/relatorio.md\n");
}

void executarSimulacao(void) {
    const int N = 200;
    int acessos[N];
    for (int i = 0; i < N; i++) acessos[i] = (rand() % 100) + 1;

    int hits[3] = {0};
    const char *nomes[3] = {"FIFO","LRU","LFU"};

    inicializarCacheFIFO();
    for (int i = 0; i < N; i++) { if (buscarCacheFIFO(acessos[i])) hits[0]++; else inserirCacheFIFO(acessos[i]); }

    inicializarCacheLRU();
    for (int i = 0; i < N; i++) { if (buscarCacheLRU(acessos[i])) hits[1]++; else inserirCacheLRU(acessos[i]); }

    inicializarCacheLFU();
    for (int i = 0; i < N; i++) { if (buscarCacheLFU(acessos[i])) hits[2]++; else inserirCacheLFU(acessos[i]); }

    printf("\n===== RESULTADOS =====\n");
    for (int i = 0; i < 3; i++) printf("%s: %d hits (%.2f%%)\n", nomes[i], hits[i], hits[i]*100.0/N);

    int best = 0; for (int i = 1; i < 3; i++) if (hits[i] > hits[best]) best = i;
    printf("\n>>> Algoritmo recomendado: %s\n", nomes[best]);

    relatorioGeral(hits[0], hits[1], hits[2], N);
}

void executarSimulacaoAlgoritmo(int algoritmo) {
    const int N = 200;
    int acessos[N];
    for (int i = 0; i < N; i++) acessos[i] = (rand() % 100) + 1;

    int hits = 0;

    if (algoritmo == 1) {
        inicializarCacheFIFO();
        for (int i = 0; i < N; i++) { if (buscarCacheFIFO(acessos[i])) hits++; else inserirCacheFIFO(acessos[i]); }
        printf("FIFO: %d hits (%.2f%%)\n", hits, hits*100.0/N);
    } else if (algoritmo == 2) {
        inicializarCacheLRU();
        for (int i = 0; i < N; i++) { if (buscarCacheLRU(acessos[i])) hits++; else inserirCacheLRU(acessos[i]); }
        printf("LRU: %d hits (%.2f%%)\n", hits, hits*100.0/N);
    } else if (algoritmo == 3) {
        inicializarCacheLFU();
        for (int i = 0; i < N; i++) { if (buscarCacheLFU(acessos[i])) hits++; else inserirCacheLFU(acessos[i]); }
        printf("LFU: %d hits (%.2f%%)\n", hits, hits*100.0/N);
    }
}
