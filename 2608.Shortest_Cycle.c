#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000

typedef struct No {
    int vertice;
    struct No* proximo;
} No;

typedef struct Grafo {
    int numVertices;
    No** listasAdjacentes;
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
    grafo->listasAdjacentes = malloc(vertices * sizeof(No*));

    for (int i = 0; i < vertices; i++) {
        grafo->listasAdjacentes[i] = NULL;
    }
    return grafo;
}

void adicionarAresta(Grafo* grafo, int src, int dest) {
    No* novoNo = criarNo(dest);
    novoNo->proximo = grafo->listasAdjacentes[src];
    grafo->listasAdjacentes[src] = novoNo;

    novoNo = criarNo(src);
    novoNo->proximo = grafo->listasAdjacentes[dest];
    grafo->listasAdjacentes[dest] = novoNo;
}

int bfs(Grafo* grafo, int inicio) {
    int* fila = malloc(MAXN * sizeof(int));
    int* profundidade = malloc(MAXN * sizeof(int));
    int* pai = malloc(MAXN * sizeof(int));
    int frente = 0, traseira = 0;

    int* visitado = calloc(grafo->numVertices, sizeof(int));
    fila[traseira++] = inicio;
    visitado[inicio] = 1;
    profundidade[inicio] = 0;
    pai[inicio] = -1;

    int menorComprimentoCiclo = INT_MAX;

    while (frente < traseira) {
        int atual = fila[frente++];
        No* temp = grafo->listasAdjacentes[atual];

        while (temp) {
            int vizinho = temp->vertice;

            if (visitado[vizinho]) {

                if (vizinho != pai[atual]) {
                    int comprimentoCiclo = profundidade[atual] + 1 + profundidade[vizinho];
                    if (comprimentoCiclo < menorComprimentoCiclo) {
                        menorComprimentoCiclo = comprimentoCiclo;
                    }
                }
            } else {
                visitado[vizinho] = 1;
                fila[traseira++] = vizinho;
                pai[vizinho] = atual;
                profundidade[vizinho] = profundidade[atual] + 1;
            }
            temp = temp->proximo;
        }
    }

    free(fila);
    free(profundidade);
    free(pai);
    free(visitado);

    return menorComprimentoCiclo;
}

int findShortestCycle(int n, int** arestas, int tamanhoArestas, int* colSizeArestas) {
    Grafo* grafo = criarGrafo(n);

    for (int i = 0; i < tamanhoArestas; i++) {
        adicionarAresta(grafo, arestas[i][0], arestas[i][1]);
    }

    int menor = INT_MAX;
    for (int i = 0; i < n; i++) {
        int comprimentoCiclo = bfs(grafo, i);
        if (comprimentoCiclo < menor) {
            menor = comprimentoCiclo;
        }
    }

    for (int i = 0; i < n; i++) {
        No* temp = grafo->listasAdjacentes[i];
        while (temp) {
            No* paraLiberar = temp;
            temp = temp->proximo;
            free(paraLiberar);
        }
    }
    free(grafo->listasAdjacentes);
    free(grafo);

    return (menor == INT_MAX) ? -1 : menor;
}