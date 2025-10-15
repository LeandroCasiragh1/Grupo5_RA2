#include <stdio.h>

#define TAM_CACHE 10

int cacheFIFO[TAM_CACHE];
int inicioFIFO = 0, fimFIFO = 0, tamanhoFIFO = 0;

void inicializarCacheFIFO() {
    for (int i=0;i<TAM_CACHE;i++) cacheFIFO[i]=-1;
}

int buscarCacheFIFO(int id) {
    for (int i=0;i<TAM_CACHE;i++) if (cacheFIFO[i]==id) return 1;
    return 0;
}

void inserirCacheFIFO(int id) {
    if (tamanhoFIFO < TAM_CACHE) {
        cacheFIFO[fimFIFO] = id;
        fimFIFO = (fimFIFO+1)%TAM_CACHE;
        tamanhoFIFO++;
    } else {
        cacheFIFO[inicioFIFO]=id;
        inicioFIFO=(inicioFIFO+1)%TAM_CACHE;
        fimFIFO=(fimFIFO+1)%TAM_CACHE;
    }
}
