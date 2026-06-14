#ifndef ARVORE_H
#define ARVORE_H

#include "atendimento.h"

typedef struct NoArvore {
    Atendimento atendimento;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

typedef struct {
    NoArvore *raiz;
} Arvore;

void arvore_inicializar(Arvore *a);
int  arvore_inserir(Arvore *a, Atendimento at);
Atendimento *arvore_buscar(const Arvore *a, int id);
int  arvore_remover(Arvore *a, int id);
void arvore_liberar(Arvore *a);

#endif
