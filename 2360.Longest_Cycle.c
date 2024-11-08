#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Estrutura de no da pilha
typedef struct no {
    int valor;
    struct no *prox;
} no;

// Estrutura de pilha
typedef struct pilha {
    no *topo;
    int contador;
} pilha;

// Função para inicializar a pilha
void inicializar_pilha(pilha *p) {
    p->topo = NULL;
    p->contador = 0;
}

// Função para inserir um elemento na pilha
void inserir_na_pilha(pilha *p, int x) {
    no *novo = malloc(sizeof(no));
    novo->valor = x;
    novo->prox = p->topo;
    p->topo = novo;
    p->contador++;
}