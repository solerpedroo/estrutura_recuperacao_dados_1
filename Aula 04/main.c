#include <stdio.h>

#define MAX 10

typedef struct {
    int dados[MAX];
    int topo;
} Pilha;

void inicializar(Pilha *p) {
    p->topo = -1;
}

int estaVazia(Pilha *p) {
    return p->topo == -1;
}

int estaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

int push(Pilha *p, int valor) {
    if (estaCheia(p)) {
        return 0;
    }
    p->dados[++p->topo] = valor;
    return 1;
}

int pop(Pilha *p, int *valor) {
    if (estaVazia(p)) {
        return 0;
    }
    *valor = p->dados[p->topo--];
    return 1;
}

int main() {
    Pilha p;
    int x;

    inicializar(&p);

    push(&p, 10);
    push(&p, 20);
    push(&p, 30);

    while (!estaVazia(&p)) {
        pop(&p, &x);
        printf("%d\n", x);
    }

    return 0;
}
