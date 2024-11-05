#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int vertice;
    struct No* proximo;
} No;

typedef struct Grafo {
    int numVertices;
    No** listaAdj;
} Grafo;

No* criarNo(int vertice) {
    No* novoNo = malloc(sizeof(No));
    novoNo->vertice = vertice;
    novoNo->proximo = NULL;
    return novoNo;
}

Grafo* criarGrafo(int vertices) {
    Grafo* grafo = malloc(sizeof(Grafo));
    grafo->numVertices = vertices;
    grafo->listaAdj = malloc(vertices * sizeof(No*));

    for (int i = 0; i < vertices; i++) {
        grafo->listaAdj[i] = NULL;
    }
    return grafo;
}

void adicionarAresta(Grafo* grafo, int src, int dest) {
    No* novoNo = criarNo(dest);
    novoNo->proximo = grafo->listaAdj[src];
    grafo->listaAdj[src] = novoNo;

    novoNo = criarNo(src);
    novoNo->proximo = grafo->listaAdj[dest];
    grafo->listaAdj[dest] = novoNo;
}

void imprimirGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        No* temp = grafo->listaAdj[i];
        printf("Vertice %d:", i);
        while (temp) {
            printf(" -> %d", temp->vertice);
            temp = temp->proximo;
        }
        printf("\n");
    }
}

int main() {
    int n = 7;  
    int arestas[7][2] = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 6}, {6, 3}};
    int tamanhoArestas = sizeof(arestas) / sizeof(arestas[0]);

    Grafo* grafo = criarGrafo(n);

    for (int i = 0; i < tamanhoArestas; i++) {
        adicionarAresta(grafo, arestas[i][0], arestas[i][1]);
    }

    imprimirGrafo(grafo);

    for (int i = 0; i < n; i++) {
        No* temp = grafo->listaAdj[i];
        while (temp) {
            No* paraLiberar = temp;
            temp = temp->proximo;
            free(paraLiberar);
        }
    }
    free(grafo->listaAdj);
    free(grafo);

    return 0;
}