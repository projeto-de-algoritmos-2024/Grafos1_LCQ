#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
} no;

typedef struct pilha {
    no *topo;
    int cont;
} pilha;

void criandoPilha(pilha *p) {
    p->topo = NULL;
    p->cont = 0;
}

int pilhaVazia(pilha *p) {
    return p->topo == NULL;
}

void empilhar(pilha *p, int x) {
    no *novo = (no *)malloc(sizeof(no));
    novo->valor = x;
    novo->prox = p->topo;
    p->topo = novo;
    p->cont++;
}

int desempilhar(pilha *p) {
    if (pilha_vazia(p)) {
        return -1;
    }
    no *aux = p->topo;
    int valor = aux->valor;
    p->topo = aux->prox;
    free(aux);
    p->cont--;
    return valor;
}

void dfs(int *aresta, int numVertices, int inicio) {
    pilha p;
    criandoPilha(&p);

    int *visitado = (int *)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) visitado[i] = 0;

    empilhar(&p, inicio);
    visitado[inicio] = 1;

    while (!pilha_vazia(&p)) {
        int atual = desempilhar(&p);
        printf("%d ", atual);

        int prox = aresta[atual];
        if (prox != -1 && !visitado[prox]) {
            empilhar(&p, prox);
            visitado[prox] = 1;
        }
    }
}

int main() {
    int numVertices = 6;
    int aresta[] = {-1, 2, 3, -1, 5, -1}; 

    int inicio = 1; 
    dfs(aresta, numVertices, inicio);

    return 0;
}
