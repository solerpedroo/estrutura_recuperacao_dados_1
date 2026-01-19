#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char text[100];
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Pilha;

void init(Pilha* p) {
    p->top = NULL;
}

int isEmpty(Pilha* p) {
    return p->top == NULL;
}

void push(Pilha* p, char* palavra) {
    Node* novo = (Node*) malloc(sizeof(Node));
    strcpy(novo->text, palavra);
    novo->next = p->top;
    p->top = novo;
}

char* pop(Pilha* p) {
    if (isEmpty(p)) return NULL;

    Node* temp = p->top;
    p->top = p->top->next;

    char* palavra = (char*) malloc(100);
    strcpy(palavra, temp->text);

    free(temp);
    return palavra;
}

void limparPilha(Pilha* p) {
    while (!isEmpty(p)) {
        free(pop(p));
    }
}

void imprimirRec(Node* no) {
    if (no == NULL) return;

    imprimirRec(no->next);
    printf("%s ", no->text);
}

void imprimirTexto(Pilha* p) {
    if (isEmpty(p)) {
        printf("(frase vazia)\n");
        return;
    }
    imprimirRec(p->top);
    printf("\n");
}

int main() {
    Pilha pilhaUNDO, pilhaREDO;
    init(&pilhaUNDO);
    init(&pilhaREDO);

    int opcao;
    char palavra[100];

    do {
        printf("\n=============================\n");
        printf("Digite a opção desejada:\n");
        printf("0. Digitar nova palavra da frase\n");
        printf("1. Desfazer (Undo)\n");
        printf("2. Refazer (Redo)\n");
        printf("3. Imprimir a frase\n");
        printf("4. Sair\n");
        printf("Qual opção? ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Digite a nova palavra: ");
                scanf("%s", palavra);

                push(&pilhaUNDO, palavra);

                limparPilha(&pilhaREDO);

                break;

            case 1: {
                char* desf = pop(&pilhaUNDO);
                if (desf == NULL) {
                    printf("Nada a desfazer!\n");
                } else {
                    push(&pilhaREDO, desf);
                    printf("Desfeito: %s\n", desf);
                }
                break;
            }

            case 2: {
                char* ref = pop(&pilhaREDO);
                if (ref == NULL) {
                    printf("Nada a refazer!\n");
                } else {
                    push(&pilhaUNDO, ref);
                    printf("Refeito: %s\n", ref);
                }
                break;
            }

            case 3:
                printf("\nFrase atual: ");
                imprimirTexto(&pilhaUNDO);
                break;

            case 4:
                printf("Finalizando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 4);

    return 0;
}