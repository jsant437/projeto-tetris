#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Estrutura da pilha (LIFO)
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;


// Gera uma peça aleatória
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}


// Inicializa a fila completamente preenchida
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

// Inicializa a pilha vazia
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Enfileira uma nova peça (a fila nunca fica vazia)
void enqueue(Fila *f, int *contadorID) {
    if (f->quantidade == TAM_FILA) return;

    f->itens[f->fim] = gerarPeca(*contadorID);
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
    (*contadorID)++;
}

// Remove peça da frente da fila
Peca dequeue(Fila *f) {
    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

// Empilha
int push(Pilha *p, Peca x) {
    if (p->topo == TAM_PILHA - 1)
        return 0;

    p->topo++;
    p->itens[p->topo] = x;
    return 1;
}

// Desempilha
int pop(Pilha *p, Peca *saida) {
    if (p->topo == -1)
        return 0;

    *saida = p->itens[p->topo];
    p->topo--;
    return 1;
}


// Exibe fila e pilha
void exibirEstado(Fila *f, Pilha *p) {
    printf("\n=== Estado Atual ===\n");

    printf("Fila de peças: ");
    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha de reserva (Topo -> Base): ");
    if (p->topo == -1) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}


int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    int contadorID = 0;
    int opcao;

    inicializarFila(&fila, &contadorID);
    inicializarPilha(&pilha);

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue(&fila);
            printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
            enqueue(&fila, &contadorID);
        }

        else if (opcao == 2) {
            if (pilha.topo == TAM_PILHA - 1) {
                printf("Pilha cheia! Não é possível reservar.\n");
            } else {
                Peca reservada = dequeue(&fila);
                push(&pilha, reservada);
                printf("Peça reservada: [%c %d]\n", reservada.nome, reservada.id);
                enqueue(&fila, &contadorID);
            }
        }

        else if (opcao == 3) {
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
            } else {
                printf("Pilha vazia! Não há peça reservada para usar.\n");
            }
        }

        else if (opcao == 0) {
            printf("Encerrando...\n");
        }

        else {
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
