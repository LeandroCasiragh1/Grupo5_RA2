#include <stdio.h>

#define TAM_CACHE 10

int cacheLRU[TAM_CACHE];
int ordemLRU[TAM_CACHE];
int tamanhoLRU = 0;

void inicializarCacheLRU() {
    for (int i=0;i<TAM_CACHE;i++) {
        cacheLRU[i] = -1;
        ordemLRU[i] = 0;
    }
    tamanhoLRU = 0;
}

int buscarCacheLRU(int id) {
    for (int i=0;i<TAM_CACHE;i++) {
        if (cacheLRU[i] == id) {
            for (int j=0;j<TAM_CACHE;j++) ordemLRU[j]++;
            ordemLRU[i] = 0;
            return 1;
        }
    }
    return 0;
}

void inserirCacheLRU(int id) {
    if (tamanhoLRU < TAM_CACHE) {
        cacheLRU[tamanhoLRU] = id;
        for (int j=0;j<TAM_CACHE;j++) ordemLRU[j]++;
        ordemLRU[tamanhoLRU] = 0;
        tamanhoLRU++;
    } else {
        int pos = 0;
        for (int i=1;i<TAM_CACHE;i++) {
            if (ordemLRU[i] > ordemLRU[pos]) pos = i;
        }
        cacheLRU[pos] = id;
        for (int j=0;j<TAM_CACHE;j++) ordemLRU[j]++;
        ordemLRU[pos] = 0;
    }
}
