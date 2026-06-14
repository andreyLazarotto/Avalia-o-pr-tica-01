#include <stdio.h>
#include <string.h>
#include "estatisticas.h"
#include "atendimento.h"

void exibir_estatisticas(const Lista *historico, const Hash *hash) {
    int total = 0, atendidos = 0, cancelados = 0, abertos = 0;
    int p_baixa = 0, p_media = 0, p_alta = 0;
    int tempo_total = 0;

    NoLista *atual = historico->cabeca;
    while (atual) {
        total++;
        tempo_total += atual->atendimento.tempo_estimado;

        if (strcmp(atual->atendimento.status, "atendido") == 0)   atendidos++;
        else if (strcmp(atual->atendimento.status, "cancelado") == 0) cancelados++;
        else abertos++;

        switch (atual->atendimento.prioridade) {
            case 1: p_baixa++; break;
            case 2: p_media++; break;
            case 3: p_alta++;  break;
        }
        atual = atual->proximo;
    }

    printf("  ======= ESTATISTICAS DO SISTEMA =======\n");
    printf("  Total de atendimentos cadastrados: %d\n", total);
    printf("  - Abertos:    %d\n", abertos);
    printf("  - Atendidos:  %d\n", atendidos);
    printf("  - Cancelados: %d\n", cancelados);
    printf("\n  Por prioridade:\n");
    printf("  - Alta  (3): %d\n", p_alta);
    printf("  - Media (2): %d\n", p_media);
    printf("  - Baixa (1): %d\n", p_baixa);
    if (total > 0)
        printf("\n  Tempo medio estimado: %.1f min\n", (float)tempo_total / total);
    printf("\n  Categoria com mais atendimentos:\n");
    hash_categoria_mais_atendida(hash);
    printf("  ========================================\n");
}
