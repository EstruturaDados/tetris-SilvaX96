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

Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];
int qtdFila = 0;
int topo = -1;
int contadorID = 0;

// Gera uma nova peça com tipo aleatório
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// Mostra fila e pilha
void mostrarEstado() {
    printf("\n--- ESTADO ATUAL ---\n");
    printf("Fila: ");
    for (int i = 0; i < qtdFila; i++)
        printf("[%c %d] ", fila[i].nome, fila[i].id);
    if (qtdFila == 0) printf("(vazia)");

    printf("\nPilha: ");
    for (int i = topo; i >= 0; i--)
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    if (topo == -1) printf("(vazia)");
    printf("\n---------------------\n");
}

int main() {
    srand(time(NULL));

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++)
        fila[qtdFila++] = gerarPeca();

    int opcao;
    do {
        mostrarEstado();
        printf("\n1 - Jogar peça");
        printf("\n2 - Reservar peça");
        printf("\n3 - Usar peça reservada");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) { // Jogar peça
            if (qtdFila > 0) {
                printf("Jogou [%c %d]\n", fila[0].nome, fila[0].id);
                for (int i = 0; i < qtdFila - 1; i++)
                    fila[i] = fila[i + 1];
                qtdFila--;
                fila[qtdFila++] = gerarPeca();
            } else printf("Fila vazia!\n");
        }

        else if (opcao == 2) { // Reservar peça
            if (qtdFila > 0 && topo < TAM_PILHA - 1) {
                pilha[++topo] = fila[0];
                printf("Reservou [%c %d]\n", fila[0].nome, fila[0].id);
                for (int i = 0; i < qtdFila - 1; i++)
                    fila[i] = fila[i + 1];
                qtdFila--;
                fila[qtdFila++] = gerarPeca();
            } else printf("Não foi possível reservar!\n");
        }

        else if (opcao == 3) { // Usar peça
            if (topo >= 0) {
                printf("Usou [%c %d]\n", pilha[topo].nome, pilha[topo].id);
                topo--;
            } else printf("Pilha vazia!\n");
        }

        else if (opcao == 0) {
            printf("Encerrando...\n");
        }

        else printf("Opção inválida!\n");

    } while (opcao != 0);

    return 0;
}
