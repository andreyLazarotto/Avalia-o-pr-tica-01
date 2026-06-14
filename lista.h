#ifndef LISTA_H
#define LISTA_H

#include "atendimento.h"

typedef struct NoLista {
    Atendimento atendimento;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *cabeca;
    int tamanho;
} Lista;

void lista_inicializar(Lista *l);
int  lista_vazia(const Lista *l);
int  lista_inserir(Lista *l, Atendimento a);
void lista_listar(const Lista *l);
int  lista_buscar_por_nome(const Lista *l, const char *nome);
int  lista_buscar_por_prioridade(const Lista *l, int prioridade);
int  lista_buscar_por_nome_parcial(const Lista *l, const char *trecho);
int  lista_cancelar(Lista *l, int id);
void lista_liberar(Lista *l);

// Para ordenação: retorna array de ponteiros (chamador deve free)
Atendimento *lista_para_array(const Lista *l, int *tamanho);
void lista_atualizar_status(Lista *l, int id, const char *status);

#endif
