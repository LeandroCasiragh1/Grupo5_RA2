# Projeto RA2 - Sistema de Cache em C

## Estrutura

- `/core/` → Interface do usuário e controle do sistema
- `/algorithms/` → Implementação dos algoritmos de cache (FIFO, LRU, LFU)
- `/simulation/` → Simulação de usuários
- `/texts/` → 100 textos
- `/docs/` → Documentação
- `ra2_main.c` → Arquivo principal

## Uso

```bash
gcc -O2 -std=c11 -o ra2_main ra2_main.c core/interface.c algorithms/cache_fifo.c algorithms/cache_lru.c algorithms/cache_lfu.c simulation/simulacao.c -lm
./ra2_main
```
