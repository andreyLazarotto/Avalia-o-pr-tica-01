#include <stdio.h>
#include <string.h>
#include "atendimento.h"

Atendimento criar_atendimento(int id, const char *cliente, const char *categoria,
                               int prioridade, int tempo_estimado) {
    Atendimento a;
    a.id = id;
    strncpy(a.cliente, cliente, 49);
    a.cliente[49] = '\0';
    strncpy(a.categoria, categoria, 29);
    a.categoria[29] = '\0';
    a.prioridade = prioridade;
    a.tempo_estimado = tempo_estimado;
    strncpy(a.status, "aberto", 19);
    a.status[19] = '\0';
    return a;
}

const char *prioridade_str(int prioridade) {
    switch (prioridade) {
        case 1: return "Baixa";
        case 2: return "Media";
        case 3: return "Alta";
        default: return "Desconhecida";
    }
}

void imprimir_atendimento(const Atendimento *a) {
    printf("  ID: %d\n", a->id);
    printf("  Cliente: %s\n", a->cliente);
    printf("  Categoria: %s\n", a->categoria);
    printf("  Prioridade: %s\n", prioridade_str(a->prioridade));
    printf("  Tempo Estimado: %d min\n", a->tempo_estimado);
    printf("  Status: %s\n", a->status);
    printf("  -------------------------\n");
}
