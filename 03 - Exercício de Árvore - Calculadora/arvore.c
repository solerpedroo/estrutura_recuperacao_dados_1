#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct NodePilha {
    char data;
    struct NodePilha* next;
} NodePilha;

typedef struct {
    NodePilha* top;
} Pilha;

void inicializarPilha(Pilha* p) {
    p->top = NULL;
}

int pilhaVazia(Pilha* p) {
    return (p->top == NULL);
}

void empilhar(Pilha* p, char valor) {
    NodePilha* novo = (NodePilha*) malloc(sizeof(NodePilha));
    novo->data = valor;
    novo->next = p->top;
    p->top = novo;
}

char desempilhar(Pilha* p) {
    if (pilhaVazia(p))
        return '\0';

    NodePilha* temp = p->top;
    char valor = temp->data;
    p->top = temp->next;
    free(temp);
    return valor;
}

char topo(Pilha* p) {
    if (pilhaVazia(p))
        return '\0';
    return p->top->data;
}

bool verificarExpressao(char exp[]) {
    Pilha pilha;
    inicializarPilha(&pilha);

    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if (c == '(' || c == '[' || c == '{') {
            empilhar(&pilha, c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (pilhaVazia(&pilha))
                return false;

            char topoChar = desempilhar(&pilha);

            if ((c == ')' && topoChar != '(') ||
                (c == ']' && topoChar != '[') ||
                (c == '}' && topoChar != '{'))
                return false;
        }
    }

    if (!pilhaVazia(&pilha))
        return false;
    else
        return true;
}

typedef struct Node {
    char data;             
    double value;          
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* itens[200];
    int topo;
} PilhaNode;

void inicializarPilhaNode(PilhaNode* p) {
    p->topo = -1;
}

int pilhaNodeVazia(PilhaNode* p) {
    return (p->topo == -1);
}

void empilharNode(PilhaNode* p, Node* n) {
    p->itens[++(p->topo)] = n;
}

Node* desempilharNode(PilhaNode* p) {
    if (pilhaNodeVazia(p)) return NULL;
    return p->itens[(p->topo)--];
}

int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixParaPosfix(char infixa[], char posfixa[]) {
    Pilha pilha;
    inicializarPilha(&pilha);
    int j = 0;

    for (int i = 0; infixa[i] != '\0'; i++) {
        char c = infixa[i];
        if (isspace(c)) continue;

        if (isdigit(c)) {
            while (isdigit(infixa[i]) || infixa[i] == '.') {
                posfixa[j++] = infixa[i++];
            }
            posfixa[j++] = ' ';
            i--;
        }
        else if (c == '(') {
            empilhar(&pilha, c);
        }
        else if (c == ')') {
            while (!pilhaVazia(&pilha) && topo(&pilha) != '(') {
                posfixa[j++] = desempilhar(&pilha);
                posfixa[j++] = ' ';
            }
            if (!pilhaVazia(&pilha))
                desempilhar(&pilha);
        }
        else {
            while (!pilhaVazia(&pilha) &&
                   precedencia(topo(&pilha)) >= precedencia(c)) {
                posfixa[j++] = desempilhar(&pilha);
                posfixa[j++] = ' ';
            }
            empilhar(&pilha, c);
        }
    }

    while (!pilhaVazia(&pilha)) {
        posfixa[j++] = desempilhar(&pilha);
        posfixa[j++] = ' ';
    }

    posfixa[j] = '\0';
}

Node* novoNo(char data, double value) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

Node* construirArvore(char posfixa[]) {
    PilhaNode pilha;
    inicializarPilhaNode(&pilha);

    for (int i = 0; posfixa[i] != '\0'; i++) {
        char c = posfixa[i];
        if (isspace(c)) continue;

        if (isdigit(c)) {
            char numStr[50];
            int k = 0;

            while (isdigit(posfixa[i]) || posfixa[i] == '.') {
                numStr[k++] = posfixa[i++];
            }
            numStr[k] = '\0';

            double valor = atof(numStr);
            Node* n = novoNo('#', valor);
            empilharNode(&pilha, n);
        }
        else {
            Node* n = novoNo(c, 0.0);
            Node* direita = desempilharNode(&pilha);
            Node* esquerda = desempilharNode(&pilha);
            n->left = esquerda;
            n->right = direita;
            empilharNode(&pilha, n);
        }
    }

    return desempilharNode(&pilha);
}

Node* montarArvoreExpressao(char expressao[]) {
    if (!verificarExpressao(expressao)) {
        printf("Expressao invalida! Delimitadores incorretos.\n");
        return NULL;
    }

    char posfixa[200];
    infixParaPosfix(expressao, posfixa);

    Node* raiz = construirArvore(posfixa);
    return raiz;
}

double evaluateExpression(Node* currentNode) {
    if (currentNode == NULL)
        return 0;

    if (currentNode->data == '#')
        return currentNode->value;

    double leftValue = evaluateExpression(currentNode->left);
    double rightValue = evaluateExpression(currentNode->right);

    switch (currentNode->data) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/': return rightValue != 0 ? leftValue / rightValue : 0;
        default: return 0;
    }
}

int main() {
    char expressao[200];

    printf("Digite a expressao infixa: ");
    fgets(expressao, 200, stdin);
    expressao[strcspn(expressao, "\n")] = '\0';

    Node* raiz = montarArvoreExpressao(expressao);

    if (raiz != NULL) {
        printf("\nArvore criada com sucesso.\n");
        double resultado = evaluateExpression(raiz);
        printf("\nResultado final: %.2lf\n", resultado);
    } else {
        printf("\nNao foi possivel criar a arvore (erro na expressao).\n");
    }

    return 0;
}