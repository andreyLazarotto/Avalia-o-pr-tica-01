#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void fila_inicializar(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}

int fila_vazia(const Fila *f) {
    return f->inicio == NULL;
}

int fila_enfileirar(Fila *f, Atendimento a) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (!novo) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        return 0;
    }
    novo->atendimento = a;
    novo->proximo = NULL;

    if (fila_vazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->proximo = novo;
        f->fim = novo;
    }
    f->tamanho++;
    return 1;
}

int fila_desenfileirar(Fila *f, Atendimento *destino) {
    if (fila_vazia(f)) return 0;

    NoFila *removido = f->inicio;
    *destino = removido->atendimento;
    f->inicio = removido->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(removido);
    f->tamanho--;
    return 1;
}

void fila_listar(const Fila *f) {
    if (fila_vazia(f)) {
        printf("  Fila de espera vazia.\n");
        return;
    }
    printf("  Posicao na fila: %d atendimento(s)\n\n", f->tamanho);
    NoFila *atual = f->inicio;
    int pos = 1;
    while (atual) {
        printf("  [%d]\n", pos++);
        imprimir_atendimento(&atual->atendimento);
        atual = atual->proximo;
    }
}

void fila_liberar(Fila *f) {
    NoFila *atual = f->inicio;
    while (atual) {
        NoFila *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}
