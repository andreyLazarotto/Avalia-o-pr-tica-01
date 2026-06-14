#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "atendimento.h"

// Ordena array por prioridade (decrescente) usando Insertion Sort
void ordenar_por_prioridade(Atendimento *arr, int n);

// Ordena array por tempo estimado (crescente) usando Selection Sort
void ordenar_por_tempo(Atendimento *arr, int n);

// Ordena por múltiplos critérios: prioridade desc, depois tempo asc
void ordenar_multiplo(Atendimento *arr, int n);

// Imprime o array de atendimentos
void imprimir_array(const Atendimento *arr, int n);

#endif
