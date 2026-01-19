#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa um cliente
typedef struct Cliente {
    char nome[100];
    long cpf;
    long celular;
    struct Cliente *proximo;
} Cliente;

// Ponteiro inicial da lista
Cliente *inicio = NULL;

// Função para criar um novo cliente
Cliente* criarCliente(char nome[], long cpf, long celular) {
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->cpf = cpf;
    novo->celular = celular;
    novo->proximo = NULL;
    return novo;
}

// Função para cadastrar um cliente na lista
void cadastrarCliente() {
    char nome[100];
    long cpf, celular;

    printf("\n--- Cadastro de Cliente ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("CPF (somente numeros): ");
    scanf("%ld", &cpf);
    printf("Celular (somente numeros): ");
    scanf("%ld", &celular);

    // Verifica se já existe um cliente com o mesmo CPF
    Cliente *temp = inicio;
    while (temp != NULL) {
        if (temp->cpf == cpf) {
            printf("CPF ja cadastrado!\n");
            return;
        }
        temp = temp->proximo;
    }

    Cliente *novo = criarCliente(nome, cpf, celular);

    // Insere no início da lista
    novo->proximo = inicio;
    inicio = novo;

    printf("Cliente cadastrado com sucesso!\n");
}

// Função para excluir cliente pelo CPF
void excluirCliente() {
    if (inicio == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    long cpf;
    printf("\nDigite o CPF do cliente a ser excluido: ");
    scanf("%ld", &cpf);

    Cliente *atual = inicio;
    Cliente *anterior = NULL;

    while (atual != NULL && atual->cpf != cpf) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Cliente excluido com sucesso!\n");
}

// Função para exibir todos os clientes
void exibirClientes() {
    if (inicio == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    Cliente *temp = inicio;
    printf("\n--- Lista de Clientes ---\n");
    while (temp != NULL) {
        printf("Nome: %s\n", temp->nome);
        printf("CPF: %ld\n", temp->cpf);
        printf("Celular: %ld\n", temp->celular);
        printf("-----------------------------\n");
        temp = temp->proximo;
    }
}

// Função para consultar cliente pelo CPF
void consultarCliente() {
    if (inicio == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    long cpf;
    printf("\nDigite o CPF do cliente que deseja consultar: ");
    scanf("%ld", &cpf);

    Cliente *temp = inicio;
    while (temp != NULL) {
        if (temp->cpf == cpf) {
            printf("\n--- Cliente Encontrado ---\n");
            printf("Nome: %s\n", temp->nome);
            printf("CPF: %ld\n", temp->cpf);
            printf("Celular: %ld\n", temp->celular);
            return;
        }
        temp = temp->proximo;
    }

    printf("Cliente nao encontrado.\n");
}

// Função principal com o menu
int main() {
    int opcao;

    do {
        printf("\n===== MENU CLIENTES =====\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Excluir Cliente\n");
        printf("3. Exibir Clientes\n");
        printf("4. Consultar Cliente por CPF\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                excluirCliente();
                break;
            case 3:
                exibirClientes();
                break;
            case 4:
                consultarCliente();
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    // Libera memória antes de sair
    Cliente *temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }

    return 0;
}