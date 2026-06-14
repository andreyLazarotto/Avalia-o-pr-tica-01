#ifndef HASH_H
#define HASH_H

#include "atendimento.h"

#define HASH_TAM 31  // Tamanho primo para reduzir colisões

typedef struct NoHash {
    Atendimento atendimento;
    struct NoHash *proximo;  // Encadeamento para colisões
} NoHash;

typedef struct {
    NoHash *tabela[HASH_TAM];
    int total;
} Hash;

void hash_inicializar(Hash *h);
int  hash_inserir(Hash *h, Atendimento a);
int  hash_buscar_por_categoria(const Hash *h, const char *categoria);
void hash_categoria_mais_atendida(const Hash *h);
void hash_liberar(Hash *h);

#endif
