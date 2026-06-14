#ifndef FILA_H
#define FILA_H

#include "atendimento.h"

typedef struct NoFila {
    Atendimento atendimento;
    struct NoFila *proximo;
} NoFila;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} Fila;

void fila_inicializar(Fila *f);
int  fila_vazia(const Fila *f);
int  fila_enfileirar(Fila *f, Atendimento a);
int  fila_desenfileirar(Fila *f, Atendimento *destino);
void fila_listar(const Fila *f);
void fila_liberar(Fila *f);

#endif
