#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "atendimento.h"
#include "fila.h"
#include "lista.h"
#include "arvore.h"
#include "hash.h"
#include "ordenacao.h"
#include "estatisticas.h"

// ---- Utilitários de entrada ----
static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int ler_int(const char *prompt, int min, int max) {
    int val;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &val) == 1 && val >= min && val <= max) {
            limpar_buffer();
            return val;
        }
        limpar_buffer();
        printf("  Valor invalido. Informe um numero entre %d e %d.\n", min, max);
    }
}

static void ler_string(const char *prompt, char *dest, int tamanho) {
    printf("%s", prompt);
    if (fgets(dest, tamanho, stdin)) {
        dest[strcspn(dest, "\n")] = '\0';
    }
}

// ---- Geração automática para testes ----
static void gerar_automatico(Fila *fila, Lista *historico, Arvore *arvore,
                              Hash *hash, int *proximo_id) {
    const char *nomes[]    = {"Ana Lima", "Bruno Souza", "Carla Neves",
                               "Diego Alves", "Elisa Ramos", "Fabio Cruz"};
    const char *cats[]     = {"Hardware", "Software", "Rede",
                               "Impressora", "Email"};
    int n_nomes = 6, n_cats = 5;

    srand((unsigned int)time(NULL));
    int qtd = ler_int("  Quantos atendimentos gerar (1-20): ", 1, 20);
    int i;
    for (i = 0; i < qtd; i++) {
        Atendimento a = criar_atendimento(
            *proximo_id,
            nomes[rand() % n_nomes],
            cats[rand() % n_cats],
            (rand() % 3) + 1,
            (rand() % 60) + 5
        );
        (*proximo_id)++;
        lista_inserir(historico, a);
        fila_enfileirar(fila, a);
        arvore_inserir(arvore, a);
        hash_inserir(hash, a);
    }
    printf("  %d atendimento(s) gerado(s) com sucesso.\n", qtd);
}

// ---- Menu ----
static void exibir_menu(void) {
    printf("\n===== SISTEMA DE ATENDIMENTOS =====\n");
    printf(" 1  - Cadastrar atendimento\n");
    printf(" 2  - Atender proximo da fila\n");
    printf(" 3  - Cancelar atendimento\n");
    printf(" 4  - Listar fila de espera\n");
    printf(" 5  - Listar historico\n");
    printf(" 6  - Buscar por nome do cliente\n");
    printf(" 7  - Buscar por prioridade\n");
    printf(" 8  - Buscar por ID (arvore BST)\n");
    printf(" 9  - Buscar por categoria (hash)\n");
    printf(" 10 - Ordenar historico por prioridade\n");
    printf(" 11 - Ordenar historico por tempo estimado\n");
    printf(" 12 - Ordenar por multiplos criterios\n");
    printf(" 13 - Exibir estatisticas\n");
    printf(" 14 - Gerar atendimentos automaticos\n");
    printf(" 0  - Sair\n");
    printf("===================================\n");
}

int main(void) {
    Fila    fila;
    Lista   historico;
    Arvore  arvore;
    Hash    hash;

    fila_inicializar(&fila);
    lista_inicializar(&historico);
    arvore_inicializar(&arvore);
    hash_inicializar(&hash);

    int proximo_id = 1;
    int opcao;

    do {
        exibir_menu();
        opcao = ler_int("Opcao: ", 0, 14);

        switch (opcao) {

        // ---- 1: Cadastrar ----
        case 1: {
            char cliente[50], categoria[30];
            printf("\n--- Cadastrar Atendimento ---\n");
            ler_string("  Cliente: ", cliente, 50);
            ler_string("  Categoria: ", categoria, 30);
            int prio = ler_int("  Prioridade (1=Baixa, 2=Media, 3=Alta): ", 1, 3);
            int tempo = ler_int("  Tempo estimado (min): ", 1, 1440);

            Atendimento a = criar_atendimento(proximo_id++, cliente, categoria, prio, tempo);
            lista_inserir(&historico, a);
            fila_enfileirar(&fila, a);
            arvore_inserir(&arvore, a);
            hash_inserir(&hash, a);
            printf("  Atendimento #%d cadastrado com sucesso.\n", a.id);
            break;
        }

        // ---- 2: Atender próximo ----
        case 2: {
            printf("\n--- Atender Proximo da Fila ---\n");
            Atendimento a;
            if (fila_desenfileirar(&fila, &a)) {
                printf("  Atendendo:\n");
                imprimir_atendimento(&a);
                lista_atualizar_status(&historico, a.id, "atendido");
                printf("  Status atualizado para 'atendido'.\n");
            } else {
                printf("  Fila vazia. Nenhum atendimento pendente.\n");
            }
            break;
        }

        // ---- 3: Cancelar ----
        case 3: {
            printf("\n--- Cancelar Atendimento ---\n");
            int id = ler_int("  ID do atendimento: ", 1, 999999);
            if (lista_cancelar(&historico, id))
                printf("  Atendimento #%d cancelado.\n", id);
            else
                printf("  Atendimento #%d nao encontrado ou nao pode ser cancelado.\n", id);
            break;
        }

        // ---- 4: Listar fila ----
        case 4:
            printf("\n--- Fila de Espera ---\n");
            fila_listar(&fila);
            break;

        // ---- 5: Listar histórico ----
        case 5:
            printf("\n--- Historico de Atendimentos ---\n");
            lista_listar(&historico);
            break;

        // ---- 6: Busca por nome ----
        case 6: {
            printf("\n--- Busca por Nome ---\n");
            char nome[50];
            ler_string("  Informe parte do nome: ", nome, 50);
            int n = lista_buscar_por_nome_parcial(&historico, nome);
            if (n == 0) printf("  Nenhum atendimento encontrado para '%s'.\n", nome);
            else printf("  %d resultado(s) encontrado(s).\n", n);
            break;
        }

        // ---- 7: Busca por prioridade ----
        case 7: {
            printf("\n--- Busca por Prioridade ---\n");
            int prio = ler_int("  Prioridade (1=Baixa, 2=Media, 3=Alta): ", 1, 3);
            int n = lista_buscar_por_prioridade(&historico, prio);
            if (n == 0) printf("  Nenhum atendimento com prioridade %s.\n", prioridade_str(prio));
            else printf("  %d resultado(s) encontrado(s).\n", n);
            break;
        }

        // ---- 8: Busca por ID na árvore ----
        case 8: {
            printf("\n--- Busca por ID (Arvore BST) ---\n");
            int id = ler_int("  ID do atendimento: ", 1, 999999);
            Atendimento *encontrado = arvore_buscar(&arvore, id);
            if (encontrado) {
                printf("  Atendimento encontrado:\n");
                imprimir_atendimento(encontrado);
            } else {
                printf("  Atendimento #%d nao encontrado na arvore.\n", id);
            }
            break;
        }

        // ---- 9: Busca por categoria na hash ----
        case 9: {
            printf("\n--- Busca por Categoria (Hash) ---\n");
            char cat[30];
            ler_string("  Categoria: ", cat, 30);
            int n = hash_buscar_por_categoria(&hash, cat);
            if (n == 0) printf("  Nenhum atendimento na categoria '%s'.\n", cat);
            else printf("  %d resultado(s) encontrado(s).\n", n);
            break;
        }

        // ---- 10: Ordenar por prioridade ----
        case 10: {
            printf("\n--- Historico Ordenado por Prioridade (decrescente) ---\n");
            int tam;
            Atendimento *arr = lista_para_array(&historico, &tam);
            if (arr) {
                ordenar_por_prioridade(arr, tam);
                imprimir_array(arr, tam);
                free(arr);
            } else {
                printf("  Historico vazio.\n");
            }
            break;
        }

        // ---- 11: Ordenar por tempo ----
        case 11: {
            printf("\n--- Historico Ordenado por Tempo Estimado (crescente) ---\n");
            int tam;
            Atendimento *arr = lista_para_array(&historico, &tam);
            if (arr) {
                ordenar_por_tempo(arr, tam);
                imprimir_array(arr, tam);
                free(arr);
            } else {
                printf("  Historico vazio.\n");
            }
            break;
        }

        // ---- 12: Ordenar múltiplos critérios ----
        case 12: {
            printf("\n--- Historico Ordenado por Prioridade e Tempo ---\n");
            int tam;
            Atendimento *arr = lista_para_array(&historico, &tam);
            if (arr) {
                ordenar_multiplo(arr, tam);
                imprimir_array(arr, tam);
                free(arr);
            } else {
                printf("  Historico vazio.\n");
            }
            break;
        }

        // ---- 13: Estatísticas ----
        case 13:
            printf("\n");
            exibir_estatisticas(&historico, &hash);
            break;

        // ---- 14: Geração automática ----
        case 14:
            printf("\n--- Gerar Atendimentos Automaticos ---\n");
            gerar_automatico(&fila, &historico, &arvore, &hash, &proximo_id);
            break;

        case 0:
            printf("\nEncerrando o sistema. Liberando memoria...\n");
            break;

        default:
            printf("  Opcao invalida.\n");
        }

    } while (opcao != 0);

    // Liberar toda a memória
    fila_liberar(&fila);
    lista_liberar(&historico);
    arvore_liberar(&arvore);
    hash_liberar(&hash);

    printf("Memoria liberada. Ate logo!\n");
    return 0;
}
