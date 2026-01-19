/*
Gerenciador de Contatos com Árvore Binária
Pedro Henrique Contardi Soler - 25005592
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de um Contato, que será o nó da árvore.
// Conforme o anexo, o nome é a 'key' (chave) de organização.
typedef struct Contato {
    char nome[50];      // Chave de busca e ordenação. (Até 50 caracteres)
    char celular[15];   // char que armazena o celular
    struct Contato* esquerda; // Ponteiro para o filho esquerdo.
    struct Contato* direita;  // Ponteiro para o filho direito.
} Contato;


Contato* criarNovoContato(const char* nome, const char* celular) {
    // Alocação de memória para o novo nó. É importante verificar se a alocação foi bem-sucedida.
    Contato* novo = (Contato*)malloc(sizeof(Contato));
    if (novo == NULL) {
        printf("ERRO: Falha ao alocar memória para novo contato.\n");
    }
    
    // Copia os dados para dentro do nó.
    // Usamos strncpy para garantir que não ultrapassamos o tamanho do array.
    strncpy(novo->nome, nome, 49);
    novo->nome[49] = '\0'; // Garantir que a string é terminada.
    
    strncpy(novo->celular, celular, 19);
    novo->celular[19] = '\0'; // Garantir que a string é terminada.

    // Um novo nó é sempre criado como folha, então seus filhos são NULL.
    novo->esquerda = NULL;
    novo->direita = NULL;
    
    return novo;
}

Contato* inserir(Contato* raiz, Contato* novo) {
    // CASO DE PARADA (Condição base da recursão): Se a subárvore estiver vazia,
    // o novo nó é inserido aqui e se torna a raiz desta subárvore.
    if (raiz == NULL) {
        return novo; // Retorna o novo nó para ser ligado ao pai.
    }

    // CASO RECURSIVO: Compara o nome do novo contato com o nome do nó atual (raiz).
    int comparacao = strcmp(novo->nome, raiz->nome);

    if (comparacao < 0) {
        // Se o nome do novo contato for lexicograficamente MENOR,
        // chama recursivamente para a subárvore esquerda.
        // O resultado da chamada recursiva é o novo ponteiro do filho esquerdo.
        raiz->esquerda = inserir(raiz->esquerda, novo);
    } else if (comparacao > 0) {
        // Se o nome for MAIOR,
        // chama recursivamente para a subárvore direita.
        // O resultado da chamada recursiva é o novo ponteiro do filho direito.
        raiz->direita = inserir(raiz->direita, novo);
    } else {
        // Se comparacao == 0, significa que o contato com este nome JÁ EXISTE.
        // Em uma árvore com chaves únicas (que é o caso aqui, nome é a key),
        // não permite duplicado.
        printf("ATENÇÃO: Contato com o nome '%s' já existe e não foi inserido.\n", novo->nome);
        // Libera a memória do nó que tenta inserir, pois ele não foi usado.
        free(novo); 
    }
    
    // Retorna a raiz atual, inalterada (se não for o ponto de inserção).
    return raiz;
}

Contato* buscar(Contato* raiz, const char* nome) {
    // CASO DE PARADA 1: Se a raiz é NULL, o contato não está nesta subárvore.
    if (raiz == NULL) {
        return NULL;
    }

    // CASO DE PARADA 2: Se o nome for igual, o contato foi encontrado.
    int comparacao = strcmp(nome, raiz->nome);
    if (comparacao == 0) {
        return raiz;
    }

    // CASO RECURSIVO:
    if (comparacao < 0) {
        // Se o nome for menor (vem antes no dicionário), busca na ESQUERDA.
        return buscar(raiz->esquerda, nome);
    } else { // comparacao > 0
        // Se o nome for maior (vem depois no dicionário), busca na DIREITA.
        return buscar(raiz->direita, nome);
    }
}

Contato* encontrarMinimo(Contato* no) {
    Contato* atual = no;
    // O nó com o menor valor em uma árvore está sempre mais à esquerda.
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

Contato* remover(Contato* raiz, const char* nome) {
    // CASO DE PARADA 1: Árvore vazia ou nome não encontrado.
    if (raiz == NULL) {
        printf("AVISO: O contato '%s' não foi encontrado para remoção.\n", nome);
        return raiz;
    }

    // Navegação recursiva até encontrar o nó a ser removido.
    int comparacao = strcmp(nome, raiz->nome);

    if (comparacao < 0) {
        // O nó está na subárvore esquerda.
        raiz->esquerda = remover(raiz->esquerda, nome);
    } else if (comparacao > 0) {
        // O nó está na subárvore direita.
        raiz->direita = remover(raiz->direita, nome);
    } else {
        // ENCONTRA O NÓ PARA REMOVER (comparacao == 0)!

        // --- CASO 1: Nó com 0 ou 1 filho ---
        if (raiz->esquerda == NULL) {
            // Pode ser 0 filho (direita=NULL) ou 1 filho (direita != NULL).
            Contato* temp = raiz->direita; // Pega o filho da direita (ou NULL).
            free(raiz); // Libera o nó atual.
            return temp; // O filho (ou NULL) sobe e se liga ao pai.
        } else if (raiz->direita == NULL) {
            // Nó tem apenas o filho esquerdo.
            Contato* temp = raiz->esquerda; // Pega o filho da esquerda.
            free(raiz); // Libera o nó atual.
            return temp; // O filho sobe e se liga ao pai.
        }

        // --- CASO 2: Nó com 2 filhos ---
        // Aqui, precisa encontrar o sucessor (o menor nó da subárvore direita).
        Contato* temp = encontrarMinimo(raiz->direita);

        // 1. Copia o conteúdo do sucessor para o nó que quer remover.
        // Copiam a 'key' (nome) e o 'celular'.
        strcpy(raiz->nome, temp->nome);
        strcpy(raiz->celular, temp->celular);

        // 2. Remove recursivamente o sucessor
        // O sucessor, por definição, não tem filho esquerdo, o que simplifica sua remoção.
        raiz->direita = remover(raiz->direita, temp->nome);
    }
    
    // Retorna o nó atual após as possíveis alterações nos ponteiros de seus filhos.
    return raiz;
}

void ImprimirArvoreDeContatos(Contato* raiz) {
    // CASO DE PARADA: Se o nó for NULL, apenas retorna.
    if (raiz != NULL) {
        // 1. Percorre a subárvore esquerda (Esquerda).
        ImprimirArvoreDeContatos(raiz->esquerda);
        
        // 2. Processa o nó atual (Raiz).
        printf("   - Nome: %s, Celular: %s\n", raiz->nome, raiz->celular);
        
        // 3. Percorre a subárvore direita (Direita).
        ImprimirArvoreDeContatos(raiz->direita);
    }
}

void liberarArvore(Contato* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda); // Libera a subárvore esquerda.
        liberarArvore(raiz->direita);  // Libera a subárvore direita.
        free(raiz);                    // Libera o nó atual.
    }
}

int main() {
    // A raiz da árvore de contatos. Começa como NULL (árvore vazia).
    Contato* raiz = NULL;
    int opcao;

    do {
        // Exibição do menu principal
        printf("\n============================================\n");
        printf("   GERENCIADOR DE CONTATOS\n");
        printf("============================================\n");
        printf("1. Inserir Novo Contato\n");
        printf("2. Buscar Contato por Nome\n");
        printf("3. Remover Contato por Nome\n");
        printf("4. Imprimir Todos os Contatos (Ordem Alfabética)\n");
        printf("5. Sair\n");
        printf("--------------------------------------------\n");
        printf("Escolha uma opção: ");

        // Ler a opção do usuário
        if (scanf("%d", &opcao) != 1) {
            // Se a leitura falhar (ex: usuário digitou uma letra),
            // limpa o buffer de entrada e setamos uma opção inválida.
            while (getchar() != '\n');
            opcao = 0; 
        } else {
            // Consumir o restante da linha após a leitura do número.
            while (getchar() != '\n'); 
        }

        switch (opcao) {
            case 1: {
                // Inserir contato
                char nome[50], celular[20];
                printf("\n--- Inserir Contato ---\n");
                printf("Nome: ");
                scanf("%[^\n]", nome);
                while (getchar() != '\n'); // Limpar o buffer
                
                printf("Celular: ");
                scanf("%[^\n]", celular);
                while (getchar() != '\n'); // Limpar o buffer

                // Cria o nó e chama a função recursiva de inserção.
                Contato* novo = criarNovoContato(nome, celular);
                raiz = inserir(raiz, novo);
                printf("\n[SUCESSO] Tentativa de insercao concluida.\n");
                break;
            }

            case 2: {
                // Buscar contato
                char nome[50];
                printf("\n--- Buscar Contato ---\n");
                printf("Nome para buscar: ");
                scanf("%[^\n]", nome);
                while (getchar() != '\n');
                
                Contato* encontrado = buscar(raiz, nome);

                if (encontrado) {
                    printf("\n[ENCONTRADO!] Contato: %s, Celular: %s\n", encontrado->nome, encontrado->celular);
                } else {
                    printf("\n[AVISO] Contato '%s' não foi encontrado na agenda.\n", nome);
                }
                break;
            }

            case 3: {
                // Remover contato
                char nome[50];
                printf("\n--- Remover Contato ---\n");
                printf("Nome para remover: ");
                scanf("%[^\n]", nome);
                while (getchar() != '\n');
                
                raiz = remover(raiz, nome);
                printf("\n[SUCESSO] Tentativa de remocao concluida. Verifique a lista (Opcao 4).\n");
                break;
            }

            case 4: {
                // Imprimir contatos (em ordem alfabética)
                printf("\n--- Contatos na Agenda (Ordem Alfabetica) ---\n");
                if (raiz == NULL) {
                    printf("A agenda esta vazia. Insira um contato primeiro.\n");
                } else {
                    ImprimirArvoreDeContatos(raiz);
                }
                break;
            }

            case 5: {
                // Sair
                printf("\nFinalizando o sistema de Gerenciamento de Contatos.\n");
                // Importante: liberar toda a memória alocada antes de sair.
                liberarArvore(raiz);
                printf("[SUCESSO] Memoria da arvore liberada.\n");
                break;
            }

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente (1 a 5).\n");
                break;
        }

    } while (opcao != 5);

    return 0;
}