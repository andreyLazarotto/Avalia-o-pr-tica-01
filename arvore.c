#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

void arvore_inicializar(Arvore *a) {
    a->raiz = NULL;
}

static NoArvore *novo_no(Atendimento at) {
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (!no) return NULL;
    no->atendimento = at;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

static NoArvore *inserir_rec(NoArvore *raiz, Atendimento at, int *ok) {
    if (!raiz) {
        *ok = 1;
        return novo_no(at);
    }
    if (at.id < raiz->atendimento.id)
        raiz->esquerda = inserir_rec(raiz->esquerda, at, ok);
    else if (at.id > raiz->atendimento.id)
        raiz->direita = inserir_rec(raiz->direita, at, ok);
    else
        *ok = 0; // ID duplicado
    return raiz;
}

int arvore_inserir(Arvore *a, Atendimento at) {
    int ok = 0;
    a->raiz = inserir_rec(a->raiz, at, &ok);
    return ok;
}

static NoArvore *buscar_rec(NoArvore *raiz, int id) {
    if (!raiz) return NULL;
    if (id == raiz->atendimento.id) return raiz;
    if (id < raiz->atendimento.id)
        return buscar_rec(raiz->esquerda, id);
    return buscar_rec(raiz->direita, id);
}

Atendimento *arvore_buscar(const Arvore *a, int id) {
    NoArvore *no = buscar_rec(a->raiz, id);
    if (!no) return NULL;
    return &no->atendimento;
}

// Encontra o menor nó (para remoção)
static NoArvore *minimo(NoArvore *no) {
    while (no->esquerda) no = no->esquerda;
    return no;
}

static NoArvore *remover_rec(NoArvore *raiz, int id, int *removido) {
    if (!raiz) { *removido = 0; return NULL; }
    if (id < raiz->atendimento.id) {
        raiz->esquerda = remover_rec(raiz->esquerda, id, removido);
    } else if (id > raiz->atendimento.id) {
        raiz->direita = remover_rec(raiz->direita, id, removido);
    } else {
        *removido = 1;
        if (!raiz->esquerda) {
            NoArvore *tmp = raiz->direita;
            free(raiz);
            return tmp;
        } else if (!raiz->direita) {
            NoArvore *tmp = raiz->esquerda;
            free(raiz);
            return tmp;
        } else {
            NoArvore *suc = minimo(raiz->direita);
            raiz->atendimento = suc->atendimento;
            int dummy = 0;
            raiz->direita = remover_rec(raiz->direita, suc->atendimento.id, &dummy);
        }
    }
    return raiz;
}

int arvore_remover(Arvore *a, int id) {
    int removido = 0;
    a->raiz = remover_rec(a->raiz, id, &removido);
    return removido;
}

static void liberar_rec(NoArvore *raiz) {
    if (!raiz) return;
    liberar_rec(raiz->esquerda);
    liberar_rec(raiz->direita);
    free(raiz);
}

void arvore_liberar(Arvore *a) {
    liberar_rec(a->raiz);
    a->raiz = NULL;
}
