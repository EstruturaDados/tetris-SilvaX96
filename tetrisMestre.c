#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura que representa uma peça
typedef struct {
    char nome;
    int id;
} Peca;

// Vetores simples para fila e pilha
Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];

int qtdFila = 0;
int topoPilha = -1;
int idGlobal = 0;

// Função que gera uma nova peça aleatória
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = idGlobal++;
    return p;
}

// Mostra o estado atual das estruturas
void mostrarEstado() {
    int i;
    printf("\n--- ESTADO ATUAL ---\n");
    printf("Fila: ");
    for (i = 0; i < qtdFila; i++)
        printf("[%c %d] ", fila[i].nome, fila[i].id);

    printf("\nPilha (topo -> base): ");
    for (i = topoPilha; i >= 0; i--)
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);

    printf("\n---------------------\n");
}

int main() {
    srand(time(NULL));

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        fila[i] = gerarPeca();
        qtdFila++;
    }

    int opcao;
    do {
        mostrarEstado();
        printf("\n1 - Jogar peça da fila");
        printf("\n2 - Reservar peça na pilha");
        printf("\n3 - Usar peça da pilha");
        printf("\n4 - Trocar frente da fila com topo da pilha");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (qtdFila > 0) {
                printf("Jogou [%c %d]!\n", fila[0].nome, fila[0].id);
                // remove da frente da fila
                for (int i = 0; i < qtdFila - 1; i++)
                    fila[i] = fila[i + 1];
                qtdFila--;
                // adiciona nova peça no final
                fila[qtdFila++] = gerarPeca();
            } else printf("Fila vazia!\n");
        }

        else if (opcao == 2) {
            if (qtdFila > 0 && topoPilha < TAM_PILHA - 1) {
                pilha[++topoPilha] = fila[0];
                printf("Reservou [%c %d]!\n", fila[0].nome, fila[0].id);
                // remove da fila
                for (int i = 0; i < qtdFila - 1; i++)
                    fila[i] = fila[i + 1];
                qtdFila--;
                fila[qtdFila++] = gerarPeca();
            } else printf("Não foi possível reservar!\n");
        }

        else if (opcao == 3) {
            if (topoPilha >= 0) {
                printf("Usou [%c %d]!\n", pilha[topoPilha].nome, pilha[topoPilha].id);
                topoPilha--;
            } else printf("Pilha vazia!\n");
        }

        else if (opcao == 4) {
            if (qtdFila > 0 && topoPilha >= 0) {
                Peca temp = fila[0];
                fila[0] = pilha[topoPilha];
                pilha[topoPilha] = temp;
                printf("Troca realizada!\n");
            } else printf("Não foi possível trocar!\n");
        }

        else if (opcao == 0) {
            printf("Encerrando...\n");
        }

        else {
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
