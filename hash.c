#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

void hash_inicializar(Hash *h) {
    int i;
    for (i = 0; i < HASH_TAM; i++)
        h->tabela[i] = NULL;
    h->total = 0;
}

// Função de hash djb2 aplicada à categoria
static unsigned int hash_func(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c;
    return (unsigned int)(hash % HASH_TAM);
}

int hash_inserir(Hash *h, Atendimento a) {
    unsigned int idx = hash_func(a.categoria);
    NoHash *novo = (NoHash *)malloc(sizeof(NoHash));
    if (!novo) return 0;
    novo->atendimento = a;
    novo->proximo = h->tabela[idx];
    h->tabela[idx] = novo;
    h->total++;
    return 1;
}

int hash_buscar_por_categoria(const Hash *h, const char *categoria) {
    unsigned int idx = hash_func(categoria);
    NoHash *atual = h->tabela[idx];
    int encontrados = 0;
    while (atual) {
        if (strcasecmp(atual->atendimento.categoria, categoria) == 0) {
            imprimir_atendimento(&atual->atendimento);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

void hash_categoria_mais_atendida(const Hash *h) {
    // Conta por categoria varrendo toda a tabela
    typedef struct { char cat[30]; int count; } CatCount;
    CatCount cats[100];
    int n = 0;

    int i;
    for (i = 0; i < HASH_TAM; i++) {
        NoHash *atual = h->tabela[i];
        while (atual) {
            // Procura categoria já registrada
            int found = 0, j;
            for (j = 0; j < n; j++) {
                if (strcasecmp(cats[j].cat, atual->atendimento.categoria) == 0) {
                    cats[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && n < 100) {
                strncpy(cats[n].cat, atual->atendimento.categoria, 29);
                cats[n].cat[29] = '\0';
                cats[n].count = 1;
                n++;
            }
            atual = atual->proximo;
        }
    }

    if (n == 0) { printf("  Nenhuma categoria registrada.\n"); return; }

    int max = 0;
    for (i = 0; i < n; i++)
        if (cats[i].count > max) max = cats[i].count;

    printf("  Categoria(s) com mais atendimentos (%d):\n", max);
    for (i = 0; i < n; i++)
        if (cats[i].count == max)
            printf("    - %s\n", cats[i].cat);
}

void hash_liberar(Hash *h) {
    int i;
    for (i = 0; i < HASH_TAM; i++) {
        NoHash *atual = h->tabela[i];
        while (atual) {
            NoHash *prox = atual->proximo;
            free(atual);
            atual = prox;
        }
        h->tabela[i] = NULL;
    }
    h->total = 0;
}
