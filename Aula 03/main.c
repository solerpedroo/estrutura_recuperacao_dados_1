#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int id;
    int idade;
    char nome[50];
    struct No *prox;
} No;

No *inicio = NULL;
No *fim = NULL;
int contadorID = 1;

void inserir() {
    No *novo = (No *)malloc(sizeof(No));

    novo->id = contadorID++;

    printf("Nome do paciente: ");
    scanf(" %[^\n]", novo->nome);

    printf("Idade do paciente: ");
    scanf("%d", &novo->idade);

    novo->prox = NULL;

    if (fim == NULL) {
        inicio = fim = novo;
    } else {
        fim->prox = novo;
        fim = novo;
    }

    printf("Paciente adicionado com sucesso!\n");
}

void remover() {
    if (inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    No *temp = inicio;
    printf("Atendendo paciente - ID: %d | Nome: %s\n", temp->id, temp->nome);

    inicio = inicio->prox;
    if (inicio == NULL) {
        fim = NULL;
    }

    free(temp);
}

void exibirFila() {
    if (inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    No *aux = inicio;
    while (aux != NULL) {
        printf("ID: %d | Nome: %s | Idade: %d\n",
               aux->id, aux->nome, aux->idade);
        aux = aux->prox;
    }
}

void maisIdosos() {
    if (inicio == NULL) {
        printf("Fila vazia!\n");
        return;
    }

    No *aux = inicio;
    int maiorIdade = aux->idade;

    while (aux != NULL) {
        if (aux->idade > maiorIdade) {
            maiorIdade = aux->idade;
        }
        aux = aux->prox;
    }

    aux = inicio;
    printf("Paciente(s) mais idoso(s) (Idade: %d):\n", maiorIdade);
    while (aux != NULL) {
        if (aux->idade == maiorIdade) {
            printf("ID: %d | Nome: %s\n", aux->id, aux->nome);
        }
        aux = aux->prox;
    }
}

int main() {
    int opcao;

    do {
        printf("\n1 - Adicionar paciente\n");
        printf("2 - Atender paciente\n");
        printf("3 - Exibir fila\n");
        printf("4 - Procurar paciente(s) mais idoso(s)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserir(); break;
            case 2: remover(); break;
            case 3: exibirFila(); break;
            case 4: maisIdosos(); break;
            case 0: break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
