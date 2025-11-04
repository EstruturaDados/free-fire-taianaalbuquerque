#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5 (1 = baixa, 5 = alta)
} Item;

// Enum que define critérios de ordenação
typedef enum {
    ORDENAR_POR_NOME = 1,
    ORDENAR_POR_TIPO,
    ORDENAR_POR_PRIORIDADE
} CriterioOrdenacao;

// Variáveis globais
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;
int comparacoes = 0;

// Funções auxiliares
void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

void exibirMenu() {
    printf("========================================\n");
    printf("CÓDIGO DA ILHA - EDIÇÃO FREE FIRE\n");
    printf("========================================\n");
    printf("Status da ordenação: %s\n", ordenadaPorNome ? "Ordenada por nome" : "❌ Não ordenada");
    printf("----------------------------------------\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens (nome, tipo, prioridade)\n");
    printf("5. Realizar busca binária por nome\n");
    printf("0. Sair\n");
    printf("----------------------------------------\n");
    printf("Escolha uma opção: ");
}

// Inserir novo item
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    Item novo;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    printf("Digite a prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens++] = novo;
    ordenadaPorNome = false;

    printf("\nItem '%s' adicionado à mochila!\n", novo.nome);
}

// Remover item
void removerItem() {
    if (numItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    bool encontrado = false;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            encontrado = true;
            printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado.\n");
}

// Listar todos os itens
void listarItens() {
    if (numItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\nItens atuais na mochila:\n");
    printf("-------------------------------------------------------------\n");
    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("-------------------------------------------------------------\n");
}

// Insertion Sort (genérico)
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            bool cond = false;
            if (criterio == ORDENAR_POR_NOME)
                cond = strcmp(chave.nome, mochila[j].nome) < 0;
            else if (criterio == ORDENAR_POR_TIPO)
                cond = strcmp(chave.tipo, mochila[j].tipo) < 0;
            else if (criterio == ORDENAR_POR_PRIORIDADE)
                cond = chave.prioridade > mochila[j].prioridade; // prioridade maior vem primeiro

            if (!cond) break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }

    if (criterio == ORDENAR_POR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;

    printf("\nMochila ordenada com sucesso! Comparações realizadas: %d\n", comparacoes);
}

// Menu de ordenação
void menuDeOrdenacao() {
    int opc;
    printf("\nEscolha o critério de ordenação:\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Tipo (A-Z)\n");
    printf("3. Prioridade (5 → 1)\n");
    printf("Opção: ");
    scanf("%d", &opc);

    switch (opc) {
        case 1:
            insertionSort(ORDENAR_POR_NOME);
            break;
        case 2:
            insertionSort(ORDENAR_POR_TIPO);
            break;
        case 3:
            insertionSort(ORDENAR_POR_PRIORIDADE);
            break;
        default:
            printf("\nOpção inválida.\n");
            return;
    }
}

// Busca binária por nome
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("\nA mochila precisa estar ordenada por nome para usar a busca binária.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int inicio = 0, fim = numItens - 1, meio;
    bool encontrado = false;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int cmp = strcmp(nomeBusca, mochila[meio].nome);
        if (cmp == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                   mochila[meio].nome, mochila[meio].tipo,
                   mochila[meio].quantidade, mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (!encontrado)
        printf("\nItem não encontrado na busca binária.\n");
}

// Função principal
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparTela();

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                listarItens();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\nEncerrando o programa. Missão concluída!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
