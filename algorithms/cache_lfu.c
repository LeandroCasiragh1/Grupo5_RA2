#include <stdio.h>

#define TAM_CACHE 10

int cacheLFU[TAM_CACHE];
int freqLFU[TAM_CACHE];
int tamanhoLFU = 0;

void inicializarCacheLFU() {
    for (int i=0;i<TAM_CACHE;i++) {
        cacheLFU[i] = -1;
        freqLFU[i] = 0;
    }
    tamanhoLFU = 0;
}

int buscarCacheLFU(int id) {
    for (int i=0;i<TAM_CACHE;i++) {
        if (cacheLFU[i] == id) {
            freqLFU[i]++;
            return 1;
        }
    }
    return 0;
}

void inserirCacheLFU(int id) {
    if (tamanhoLFU < TAM_CACHE) {
        cacheLFU[tamanhoLFU] = id;
        freqLFU[tamanhoLFU] = 1;
        tamanhoLFU++;
    } else {
        int pos = 0;
        for (int i=1;i<TAM_CACHE;i++) {
            if (freqLFU[i] < freqLFU[pos]) pos = i;
        }
        cacheLFU[pos] = id;
        freqLFU[pos] = 1;
    }
}
