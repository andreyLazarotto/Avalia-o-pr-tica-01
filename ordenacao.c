#include <stdio.h>
#include "ordenacao.h"
#include "atendimento.h"

// Insertion Sort por prioridade decrescente
void ordenar_por_prioridade(Atendimento *arr, int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        Atendimento chave = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].prioridade < chave.prioridade) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

// Selection Sort por tempo estimado crescente
void ordenar_por_tempo(Atendimento *arr, int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].tempo_estimado < arr[min_idx].tempo_estimado)
                min_idx = j;
        }
        if (min_idx != i) {
            Atendimento tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

// Ordenação múltipla: prioridade desc, depois tempo asc (Bubble Sort para clareza)
void ordenar_multiplo(Atendimento *arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int troca = 0;
            if (arr[j].prioridade < arr[j+1].prioridade) {
                troca = 1;
            } else if (arr[j].prioridade == arr[j+1].prioridade &&
                       arr[j].tempo_estimado > arr[j+1].tempo_estimado) {
                troca = 1;
            }
            if (troca) {
                Atendimento tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

void imprimir_array(const Atendimento *arr, int n) {
    if (n == 0) { printf("  Nenhum atendimento.\n"); return; }
    int i;
    for (i = 0; i < n; i++)
        imprimir_atendimento(&arr[i]);
}
