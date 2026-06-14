#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

void lista_inicializar(Lista *l) {
    l->cabeca = NULL;
    l->tamanho = 0;
}

int lista_vazia(const Lista *l) {
    return l->cabeca == NULL;
}

int lista_inserir(Lista *l, Atendimento a) {
    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    if (!novo) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        return 0;
    }
    novo->atendimento = a;
    novo->proximo = l->cabeca;
    l->cabeca = novo;
    l->tamanho++;
    return 1;
}

void lista_listar(const Lista *l) {
    if (lista_vazia(l)) {
        printf("  Historico vazio.\n");
        return;
    }
    printf("  Total de atendimentos no historico: %d\n\n", l->tamanho);
    NoLista *atual = l->cabeca;
    while (atual) {
        imprimir_atendimento(&atual->atendimento);
        atual = atual->proximo;
    }
}

// Busca sequencial por nome exato (case insensitive parcialmente)
int lista_buscar_por_nome(const Lista *l, const char *nome) {
    int encontrados = 0;
    NoLista *atual = l->cabeca;
    while (atual) {
        if (strcasecmp(atual->atendimento.cliente, nome) == 0) {
            imprimir_atendimento(&atual->atendimento);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

// Busca sequencial por prioridade
int lista_buscar_por_prioridade(const Lista *l, int prioridade) {
    int encontrados = 0;
    NoLista *atual = l->cabeca;
    while (atual) {
        if (atual->atendimento.prioridade == prioridade) {
            imprimir_atendimento(&atual->atendimento);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

// Busca parcial por nome (contém o trecho)
int lista_buscar_por_nome_parcial(const Lista *l, const char *trecho) {
    int encontrados = 0;
    NoLista *atual = l->cabeca;

    // cópia lower do trecho
    char trecho_lower[50];
    int i;
    for (i = 0; trecho[i] && i < 49; i++)
        trecho_lower[i] = tolower((unsigned char)trecho[i]);
    trecho_lower[i] = '\0';

    while (atual) {
        char nome_lower[50];
        for (i = 0; atual->atendimento.cliente[i] && i < 49; i++)
            nome_lower[i] = tolower((unsigned char)atual->atendimento.cliente[i]);
        nome_lower[i] = '\0';

        if (strstr(nome_lower, trecho_lower)) {
            imprimir_atendimento(&atual->atendimento);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

int lista_cancelar(Lista *l, int id) {
    NoLista *atual = l->cabeca;
    while (atual) {
        if (atual->atendimento.id == id) {
            if (strcmp(atual->atendimento.status, "atendido") == 0) {
                printf("  Atendimento ja foi atendido, nao pode ser cancelado.\n");
                return 0;
            }
            strncpy(atual->atendimento.status, "cancelado", 19);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void lista_atualizar_status(Lista *l, int id, const char *status) {
    NoLista *atual = l->cabeca;
    while (atual) {
        if (atual->atendimento.id == id) {
            strncpy(atual->atendimento.status, status, 19);
            return;
        }
        atual = atual->proximo;
    }
}

Atendimento *lista_para_array(const Lista *l, int *tamanho) {
    *tamanho = l->tamanho;
    if (l->tamanho == 0) return NULL;
    Atendimento *arr = (Atendimento *)malloc(sizeof(Atendimento) * l->tamanho);
    if (!arr) return NULL;
    NoLista *atual = l->cabeca;
    int i = 0;
    while (atual) {
        arr[i++] = atual->atendimento;
        atual = atual->proximo;
    }
    return arr;
}

void lista_liberar(Lista *l) {
    NoLista *atual = l->cabeca;
    while (atual) {
        NoLista *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    l->cabeca = NULL;
    l->tamanho = 0;
}
