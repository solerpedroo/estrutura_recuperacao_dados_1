// Exercício 1

/*#include <stdio.h>

int soma(int n){
    if (n == 1) return 1;
    else return (n+=soma(n-1));
}

int main(){
    int n=0;

    printf("Digite um número: ");
    scanf("%d", &n);

    int sum = soma(n);

    printf("A soma dos números é: %d", sum);

    return 0;
}*/

// Exercício 2

/*#include <stdio.h>

int fatorial(int n){
    if (n == 1) return 1;
    else return (n *= fatorial(n-1));
}

int main(){
    int n;

    printf("Digite um número para fatorar: ");
    scanf("%d", &n);

    int fat = fatorial(n);

    printf("O número %d fatorado é %d", n, fat);

    return 0;
}*/

// Exercício 3

/*#include <stdio.h>
#include <stdbool.h>

bool primo1 (int numero, int divisor){
    if (divisor == 1) return true;
    if (numero % divisor == 0) return false;
    else return primo1(numero, divisor-1);
}

bool primo(int numero){
    if (numero<=2) return (numero==2);
    else return primo1(numero, numero-1);
}

int main(){
    int num;
    printf("Digite um número: ");
    scanf("%d", &num);

    if (primo(num)) printf("É primo");
    else printf("Não é");

    return 0;
}*/

// Exercício 4

/*#include <stdio.h>
#include <stdbool.h>

bool ehPrimo(int n, int divisor) {
    if (n < 2) return false;
    if (divisor * divisor > n) return true;
    if (n % divisor == 0) return false;
    return ehPrimo(n, divisor + 1);
}

int gerarPrimos(int n, int primos[], int indice) {
    if (n == 1) return indice;

    indice = gerarPrimos(n - 1, primos, indice);

    if (ehPrimo(n, 2)) {
        primos[indice] = n;
        indice++;
    }
    return indice;
}

int main() {
    int n;
    printf("Digite um número: ");
    scanf("%d", &n);

    int primos[n];
    int qtd = gerarPrimos(n, primos, 0);

    printf("Primos de 1 até %d:\n", n);
    for (int i = 0; i < qtd; i++) {
        printf("%d ", primos[i]);
    }

    printf("\n");
    return 0;
}*/

// Exercício 5

/*#include <stdio.h>

void mostrarVetor(int v[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void ordenarPasso(int v[], int tamanho) {
    if (tamanho == 1) return;

    for (int i = 0; i < tamanho - 1; i++) {
        if (v[i] > v[i + 1]) {
            int temp = v[i];
            v[i] = v[i + 1];
            v[i + 1] = temp;
        }
    }
    ordenarPasso(v, tamanho - 1);
}

void ordenarRecursivo(int v[], int tamanho) {
    if (tamanho <= 1) return;
    ordenarPasso(v, tamanho);
}

int main() {
    int v[] = {7, 2, 9, 4, 1, 5};
    int tamanho = sizeof(v) / sizeof(v[0]);

    printf("Vetor original: ");
    mostrarVetor(v, tamanho);

    ordenarRecursivo(v, tamanho);

    printf("Vetor em ordem crescente: ");
    mostrarVetor(v, tamanho);

    return 0;
}*/