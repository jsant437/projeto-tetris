#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Representa uma peça do jogo
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

// Gera peças aleatórias
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Inicializações
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

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Operações da fila
Peca dequeue(Fila *f) {
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return p;
}

void enqueue(Fila *f, int *contadorID) {
    if (f->quantidade == TAM_FILA) return;
    f->itens[f->fim] = gerarPeca(*contadorID);
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
    (*contadorID)++;
}

// Operações da pilha
int push(Pilha *p, Peca x) {
    if (p->topo == TAM_PILHA - 1)
        return 0;
    p->topo++;
    p->itens[p->topo] = x;
    return 1;
}

int pop(Pilha *p, Peca *saida) {
    if (p->topo == -1)
        return 0;
    *saida = p->itens[p->topo];
    p->topo--;
    return 1;
}

// Exibição do estado atual
void exibirEstado(Fila *f, Pilha *p) {
    printf("\n=======================\n");
    printf("Estado Atual:\n");

    printf("Fila: ");
    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++) {
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha (Topo -> Base): ");
    if (p->topo == -1) {
        printf("[vazia]");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n=======================\n");
}

// Troca simples entre fila e pilha
void trocaSimples(Fila *f, Pilha *p) {
    if (p->topo == -1) {
        printf("Pilha vazia — não é possível trocar.\n");
        return;
    }

    int idxFila = f->inicio;

    Peca temp = f->itens[idxFila];
    f->itens[idxFila] = p->itens[p->topo];
    p->itens[p->topo] = temp;

    printf("Troca simples realizada.\n");
}

// Troca múltipla entre três peças da fila e três da pilha
void trocaMultipla(Fila *f, Pilha *p) {
    if (p->topo < 2) {
        printf("A pilha não possui 3 peças.\n");
        return;
    }

    if (f->quantidade < 3) {
        printf("A fila não possui 3 peças.\n");
        return;
    }

    int idx = f->inicio;

    for (int i = 0; i < 3; i++) {
        Peca temp = f->itens[idx];
        f->itens[idx] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;

        idx = (idx + 1) % TAM_FILA;
    }

    printf("Troca múltipla realizada.\n");
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
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Reservar peça da fila para a pilha\n");
        printf("3 - Usar peça reservada da pilha\n");
        printf("4 - Troca simples entre fila e pilha\n");
        printf("5 - Troca múltipla (3x3)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue(&fila);
            printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
            enqueue(&fila, &contadorID);
        }

        else if (opcao == 2) {
            if (push(&pilha, fila.itens[fila.inicio])) {
                Peca r = dequeue(&fila);
                printf("Peça reservada: [%c %d]\n", r.nome, r.id);
                enqueue(&fila, &contadorID);
            } else {
                printf("Pilha cheia — não é possível reservar.\n");
            }
        }

        else if (opcao == 3) {
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("Peça usada: [%c %d]\n", usada.nome, usada.id);
            } else {
                printf("Pilha vazia — nada a usar.\n");
            }
        }

        else if (opcao == 4) {
            trocaSimples(&fila, &pilha);
        }

        else if (opcao == 5) {
            trocaMultipla(&fila, &pilha);
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
