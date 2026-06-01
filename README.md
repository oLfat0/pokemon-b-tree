# Árvore B — Pokédex

Implementação de uma **Árvore B** em C (ANSI C) para armazenamento e busca de nomes de Pokémon, desenvolvida como Trabalho Prático da disciplina de **Estruturas de Dados** (UFMS, 2026-1, Prof. Dr. Anderson Bessa da Costa).

A estrutura é construída a partir de um arquivo de nomes e disponibiliza um menu interativo para busca e inserção de novas chaves.

## Sobre a Árvore B

Uma Árvore B de ordem *d* é uma árvore ordenada e balanceada em que:

- A raiz é uma folha ou possui no mínimo dois filhos.
- Cada nó interno (exceto a raiz) possui no mínimo *d + 1* filhos.
- Cada nó possui no máximo *2d + 1* filhos.
- Todas as folhas estão no mesmo nível.

Cada nó (também chamado de *página*) armazena um conjunto ordenado de chaves e ponteiros para seus filhos. Um nó com *k* filhos contém *k − 1* chaves, e cada nó interno possui entre *d* e *2d* chaves. Essa organização reduz a altura da árvore e o número de acessos necessários em cada operação, o que torna a estrutura adequada para cenários de manipulação de grandes volumes de dados.

## Funcionalidades

- Definição da ordem *d* da árvore pelo usuário (com *d ≥ 2*).
- Construção automática da árvore a partir do arquivo `pokemon_names.txt`.
- Busca de uma chave, informando se foi encontrada e a posição dentro do nó.
- Inserção de novas chaves, com divisão (*split*) automática de nós cheios.

A operação de remoção não faz parte do escopo deste trabalho.

## Estrutura do nó

Cada nó armazena a quantidade de chaves presentes, um vetor de chaves (strings) e um vetor de ponteiros para os filhos. O tamanho dos vetores é dimensionado por uma constante `D_MAX`, e a ordem real *d* escolhida pelo usuário é guardada em uma variável global usada por toda a lógica da árvore.

## Compilação e execução

O programa utiliza apenas bibliotecas padrão da linguagem C. O arquivo `pokemon_names.txt` deve estar no mesmo diretório do executável.

Compilação:

```
gcc arvore_b.c -o arvore_b
```

Execução (Linux/macOS):

```
./arvore_b
```

Execução (Windows / PowerShell):

```
.\arvore_b.exe
```

Ao iniciar, o programa solicita a ordem *d*, carrega os nomes do arquivo e em seguida apresenta o menu:

```
// ----- // ----- // ARVORE B // ----- // ----- //
[1] - Buscar
[2] - Inserir
[9] - Finalizar
-------------------------------
Entre com a sua opcao:
```

## Organização do repositório

```
.
├── arvore_b.c          # Código-fonte
├── pokemon_names.txt   # Arquivo de chaves para construção da árvore
└── README.md
```

## Autores

- (Nome do integrante 1)
- (Nome do integrante 2)
- (Nome do integrante 3)

Trabalho desenvolvido para a disciplina de Estruturas de Dados — UFMS, 2026-1.
