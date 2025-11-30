#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura que representa uma peça
typedef struct {
    char nome;   // Tipo da peça: I, O, T, L
    int id;      // Identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Gera automaticamente uma nova peça com tipo aleatório
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Inicializa a fila com peças iniciais
void inicializarFila(Fila *f, int *contadorID) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        f->itens[f->fim] = gerarPeca(*contadorID);
        f->fim = (f->fim + 1) % TAM_FILA;
        f->quantidade++;
        (*contadorID)++;
    }
}

// Insere uma nova peça no final (enqueue)
void enqueue(Fila *f, int *contadorID) {
    if (f->quantidade == TAM_FILA) {
        printf("Fila cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->itens[f->fim] = gerarPeca(*contadorID);
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
    (*contadorID)++;
}

// Remove peça da frente (dequeue)
void dequeue(Fila *f) {
    if (f->quantidade == 0) {
        printf("Fila vazia! Não há peça para jogar.\n");
        return;
    }

    Peca removida = f->itens[f->inicio];
    printf("Peça jogada: [%c %d]\n", removida.nome, removida.id);

    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");

    if (f->quantidade == 0) {
        printf("[vazia]\n");
        return;
    }

    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    Fila fila;
    int contadorID = 0;
    int opcao;

    inicializarFila(&fila, &contadorID);

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, &contadorID);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
