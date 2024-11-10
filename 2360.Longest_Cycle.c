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
    if (pilhaVazia(p)) {
        return -1;
    }
    no *aux = p->topo;
    int valor = aux->valor;
    p->topo = aux->prox;
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

    while (!pilhaVazia(&p)) {
        int atual = desempilhar(&p);
        printf("%d ", atual);

        int prox = aresta[atual];
        if (prox != -1 && !visitado[prox]) {
            empilhar(&p, prox);
            visitado[prox] = 1;
        }
    }
}

int longestCycle(int *edges, int edgesSize) {
    int ciclo_longo = -1;
    int *visitado = (int *)calloc(edgesSize, sizeof(int));  
    int *mapa_profun = (int *)malloc(edgesSize * sizeof(int));  

    for (int i = 0; i < edgesSize; i++) {
        if (visitado[i] != 0) continue;  

        int no = i;
        int passo = 0;

        while (no != -1) {
            if (visitado[no] == 2) break;  
            if (visitado[no] == 1) {       
                int tam_ciclo = passo - mapa_profun[no]; 
                if (tam_ciclo > ciclo_longo) {
                    ciclo_longo = tam_ciclo;        
                }
                break;
            }

            visitado[no] = 1;
            mapa_profun[no] = passo++;
            no = edges[no];
        }

        no = i;
        while (no != -1 && visitado[no] == 1) {
            visitado[no] = 2;
            no = edges[no];
        }
    }
    return ciclo_longo;
}