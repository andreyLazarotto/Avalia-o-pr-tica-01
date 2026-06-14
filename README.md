# Sistema de Atendimento Inteligente

Trabalho da disciplina de Estruturas de Dados em C.

## Como compilar

```bash
gcc main.c atendimento.c fila.c lista.c arvore.c hash.c ordenacao.c estatisticas.c -o sistema
```

## Como executar

Linux/macOS:
```bash
./sistema
```

Windows:
```bash
sistema.exe
```

## O que o sistema faz

- Cadastrar atendimentos técnicos
- Organizar em fila de espera (quem chegou primeiro é atendido primeiro)
- Guardar histórico de todos os atendimentos
- Buscar por nome, prioridade, ID ou categoria
- Ordenar o histórico por prioridade ou tempo estimado
- Ver estatísticas gerais do sistema
- Cancelar atendimentos
- Gerar atendimentos automáticos para teste

## Arquivos do projeto

- `main.c` — menu e fluxo principal
- `atendimento.h/c` — estrutura do atendimento
- `fila.h/c` — fila dinâmica (ordem de atendimento)
- `lista.h/c` — lista encadeada (histórico)
- `arvore.h/c` — árvore binária de busca (busca por ID)
- `hash.h/c` — tabela hash (busca por categoria)
- `ordenacao.h/c` — algoritmos de ordenação
- `estatisticas.h/c` — estatísticas do sistema

## Divisão de tarefas

| Integrante | O que fez |
|------------|-----------|
| Integrante A | Estrutura do atendimento, fila, menu principal |
| Integrante B | Lista, árvore, hash, ordenação, estatísticas |
