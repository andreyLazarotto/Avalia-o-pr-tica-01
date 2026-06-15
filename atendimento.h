#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

typedef struct {
    int id;
    char cliente[50];
    char categoria[30];
    int prioridade;       // 1 = baixa, 2 = média, 3 = alta
    int tempo_estimado;   // em minutos
    char status[20];      // aberto, atendido ou cancelado
} Atendimento;

Atendimento criar_atendimento(int id, const char *cliente, const char *categoria,
                               int prioridade, int tempo_estimado);
const char *prioridade_str(int prioridade);
void imprimir_atendimento(const Atendimento *a);

#endif