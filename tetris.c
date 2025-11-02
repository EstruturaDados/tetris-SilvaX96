#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ------------------------------
// Estrutura de uma peça do Tetris
// ------------------------------
typedef struct {
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// ------------------------------
// Fila circular de peças futuras
// ------------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio, fim, tamanho;
} Fila;

// ------------------------------
// Pilha de peças reservadas
// ------------------------------
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// ------------------------------
// Protótipos das funções
// ------------------------------
void inicializarFila(Fila *fila);
void inicializarPilha(Pilha *pilha);
Peca gerarPeca();
void enfileirar(Fila *fila, Peca p);
Peca desenfileirar(Fila *fila);
void empilhar(Pilha *pilha, Peca p);
Peca desempilhar(Pilha *pilha);
void exibirEstado(Fila fila, Pilha pilha);

// ------------------------------
// Variável global para controlar IDs únicos
// ------------------------------
int contadorID = 0;

// ------------------------------
// Função principal
// ------------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca());
    }

    int opcao;
    do {
        exibirEstado(fila, pilha);

        printf("\n===== MENU DE AÇÕES =====\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("=========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Jogar peça
                if (fila.tamanho > 0) {
                    Peca jogada = desenfileirar(&fila);
                    printf("\nVocê jogou a peça [%c %d]\n", jogada.nome, jogada.id);
                    enfileirar(&fila, gerarPeca()); // Gera nova peça
                } else {
                    printf("\nA fila está vazia!\n");
                }
                break;

            case 2: // Reservar peça
                if (fila.tamanho > 0 && pilha.topo < TAM_PILHA - 1) {
                    Peca reservada = desenfileirar(&fila);
                    empilhar(&pilha, reservada);
                    printf("\nPeça [%c %d] foi reservada!\n", reservada.nome, reservada.id);
                    enfileirar(&fila, gerarPeca());
                } else if (pilha.topo >= TAM_PILHA - 1) {
                    printf("\nA pilha de reserva está cheia!\n");
                } else {
                    printf("\nA fila está vazia!\n");
                }
                break;

            case 3: // Usar peça reservada
                if (pilha.topo >= 0) {
                    Peca usada = desempilhar(&pilha);
                    printf("\nVocê usou a peça reservada [%c %d]\n", usada.nome, usada.id);
                } else {
                    printf("\nA pilha está vazia!\n");
                }
                break;

            case 0:
                printf("\nEncerrando o jogo... Até a próxima!\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ------------------------------
// Inicializa a fila
// ------------------------------
void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->tamanho = 0;
}

// ------------------------------
// Inicializa a pilha
// ------------------------------
void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

// ------------------------------
// Gera uma nova peça com tipo aleatório
// ------------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// ------------------------------
// Enfileira (adiciona) uma peça
// ------------------------------
void enfileirar(Fila *fila, Peca p) {
    if (fila->tamanho == TAM_FILA) {
        printf("\nErro: Fila cheia!\n");
        return;
    }
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->itens[fila->fim] = p;
    fila->tamanho++;
}

// ------------------------------
// Desenfileira (remove) uma peça
// ------------------------------
Peca desenfileirar(Fila *fila) {
    Peca removida = {'-', -1};
    if (fila->tamanho == 0) {
        printf("\nErro: Fila vazia!\n");
        return removida;
    }
    removida = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->tamanho--;
    return removida;
}

// ------------------------------
// Empilha (coloca no topo da pilha)
// ------------------------------
void empilhar(Pilha *pilha, Peca p) {
    if (pilha->topo == TAM_PILHA - 1) {
        printf("\nErro: Pilha cheia!\n");
        return;
    }
    pilha->itens[++pilha->topo] = p;
}

// ------------------------------
// Desempilha (remove do topo)
// ------------------------------
Peca desempilhar(Pilha *pilha) {
    Peca removida = {'-', -1};
    if (pilha->topo == -1) {
        printf("\nErro: Pilha vazia!\n");
        return removida;
    }
    removida = pilha->itens[pilha->topo--];
    return removida;
}

// ------------------------------
// Exibe o estado atual da fila e da pilha
// ------------------------------
void exibirEstado(Fila fila, Pilha pilha) {
    printf("\n===== ESTADO ATUAL =====\n");
    printf("Fila de peças: ");
    int i, index;
    for (i = 0; i < fila.tamanho; i++) {
        index = (fila.inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila.itens[index].nome, fila.itens[index].id);
    }
    if (fila.tamanho == 0)
        printf("(vazia)");
    
    printf("\nPilha de reserva (Topo -> Base): ");
    if (pilha.topo == -1)
        printf("(vazia)");
    else {
        for (i = pilha.topo; i >= 0; i--) {
            printf("[%c %d] ", pilha.itens[i].nome, pilha.itens[i].id);
        }
    }
    printf("\n=========================\n");
}
