#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ITENS 10


// Estrutura básica de item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// VARIÁVEIS GLOBAIS
Item mochilaVetor[MAX_ITENS];
int numItensVetor = 0;
No* inicioLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// FUNÇÕES AUXILIARES
void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

// OPERAÇÕES COM VETOR (LISTA SEQUENCIAL)
void inserirItemVetor() {
    if (numItensVetor >= MAX_ITENS) {
        printf("\nMochila (vetor) cheia!\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o tipo: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[numItensVetor++] = novo;
    printf("\nItem adicionado ao vetor com sucesso!\n");
}

void removerItemVetor() {
    if (numItensVetor == 0) {
        printf("\nMochila (vetor) vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < numItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < numItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            numItensVetor--;
            printf("\nItem '%s' removido do vetor!\n", nome);
            return;
        }
    }

    printf("\nItem não encontrado no vetor.\n");
}

void listarItensVetor() {
    if (numItensVetor == 0) {
        printf("\nNenhum item na mochila (vetor).\n");
        return;
    }

    printf("\nItens na mochila (vetor):\n");
    printf("---------------------------------------------\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------\n");

    for (int i = 0; i < numItensVetor; i++) {
        printf("%-20s %-15s %-10d\n",
               mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

void ordenarVetor() {
    if (numItensVetor < 2) {
        printf("\nPoucos itens para ordenar.\n");
        return;
    }

    // Bubble Sort por nome
    for (int i = 0; i < numItensVetor - 1; i++) {
        for (int j = 0; j < numItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }

    printf("\nMochila (vetor) ordenada por nome!\n");
}

void buscarSequencialVetor() {
    if (numItensVetor == 0) {
        printf("\nMochila (vetor) vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item para busca sequencial: ");
    scanf(" %[^\n]", nome);

    comparacoesSequencial = 0;
    for (int i = 0; i < numItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\nItem encontrado no vetor:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("\nItem não encontrado. Comparações: %d\n", comparacoesSequencial);
}

void buscarBinariaVetor() {
    if (numItensVetor == 0) {
        printf("\nMochila (vetor) vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item para busca binária: ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = numItensVetor - 1, meio;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0) {
            printf("\n🔍 Item encontrado (busca binária):\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações realizadas: %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }

    printf("\nItem não encontrado. Comparações: %d\n", comparacoesBinaria);
}

// OPERAÇÕES COM LISTA ENCADEADA
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("\nErro de alocação.\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Digite o tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicioLista;
    inicioLista = novo;

    printf("\nItem adicionado na lista encadeada!\n");
}

void removerItemLista() {
    if (inicioLista == NULL) {
        printf("\nLista encadeada vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\nItem não encontrado na lista.\n");
        return;
    }

    if (anterior == NULL)
        inicioLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("\nItem '%s' removido da lista!\n", nome);
}

void listarItensLista() {
    if (inicioLista == NULL) {
        printf("\nNenhum item na lista encadeada.\n");
        return;
    }

    printf("\nItens na mochila (lista encadeada):\n");
    printf("---------------------------------------------\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------\n");

    No* atual = inicioLista;
    while (atual != NULL) {
        printf("%-20s %-15s %-10d\n",
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void buscarSequencialLista() {
    if (inicioLista == NULL) {
        printf("\nLista encadeada vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item para busca sequencial: ");
    scanf(" %[^\n]", nome);

    comparacoesSequencial = 0;
    No* atual = inicioLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\n🔍 Item encontrado na lista encadeada:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            printf("Comparações realizadas: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("\nItem não encontrado. Comparações: %d\n", comparacoesSequencial);
}


// MENUS
void menuVetor() {
    int opc;
    do {
        printf("\n========== MOCHILA (VETOR) ==========\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar por nome\n");
        printf("5. Buscar (sequencial)\n");
        printf("6. Buscar (binária)\n");
        printf("0. Voltar\n");
        printf("=====================================\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        limparTela();

        switch (opc) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5: buscarSequencialVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opc != 0);
}

void menuLista() {
    int opc;
    do {
        printf("\n===== MOCHILA (LISTA ENCADEADA) =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar (sequencial)\n");
        printf("0. Voltar\n");
        printf("=====================================\n");
        printf("Escolha: ");
        scanf("%d", &opc);
        limparTela();

        switch (opc) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
            case 0: printf("\nRetornando ao menu principal...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opc != 0);
}


// FUNÇÃO PRINCIPAL
int main() {
    int opcao;
    do {
        printf("\n========================================\n");
        printf("CÓDIGO DA ILHA – COMPARADOR DE ESTRUTURAS\n");
        printf("========================================\n");
        printf("1. Usar mochila (vetor)\n");
        printf("2. Usar mochila (lista encadeada)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparTela();

        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("\Fim da simulação. Parabéns, Mestre dos Dados!\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
