#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no {
    int valor;
    struct no *prox;
} no;

typedef struct pilha {
    no *topo;
    int contador;
} pilha;

void inicializar_pilha(pilha *p) {
    p->topo = NULL;
    p->contador = 0;
}

void inserir_na_pilha(pilha *p, int x) {
    no *novo = malloc(sizeof(no));
    novo->valor = x;
    novo->prox = p->topo;
    p->topo = novo;
    p->contador++;
}