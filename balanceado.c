#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pilha {
    char itens[100];
    int topo;
};

void inicializar(struct Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(struct Pilha *p) {
    if (p->topo == -1)
        return 1;
    else
        return 0;
}

int pilhaCheia(struct Pilha *p) {
    if (p->topo == 99)
        return 1;
    else
        return 0;
}

void empilhar(struct Pilha *p, char valor) {
    if (pilhaCheia(p) == 0) {
        p->topo++;
        p->itens[p->topo] = valor;
    }
}

char desempilhar(struct Pilha *p) {
    char valor = ' ';
    if (pilhaVazia(p) == 0) {
        valor = p->itens[p->topo];
        p->topo--;
    }
    return valor;
}

int corresponde(char abertura, char fechamento) {
    if (abertura == '(' && fechamento == ')')
        return 1;
    if (abertura == '[' && fechamento == ']')
        return 1;
    if (abertura == '{' && fechamento == '}')
        return 1;
    return 0;
}

int verificarExpressao(char exp[]) {
    struct Pilha p;
    inicializar(&p);

    int i;
    int tamanho = strlen(exp);

    for (i = 0; i < tamanho; i++) {
        char c = exp[i];

        if (c == '(' || c == '[' || c == '{') {
            empilhar(&p, c);
        } 
        else if (c == ')' || c == ']' || c == '}') {
            if (pilhaVazia(&p) == 1)
                return 0;

            char topo = desempilhar(&p);

            if (corresponde(topo, c) == 0)
                return 0;
        }
    }

    if (pilhaVazia(&p) == 1)
        return 1;
    else
        return 0;
}

int main() {
    char expressao[100];

    printf("Digite a expressao: ");
    fgets(expressao, 100, stdin);

    expressao[strcspn(expressao, "\n")] = '\0';

    if (verificarExpressao(expressao) == 1)
        printf("Expressao valida.\n");
    else
        printf("Expressao invalida.\n");

    return 0;
}