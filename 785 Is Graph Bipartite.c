#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct fila {
    int dado;
    struct fila *prox;
} fila;

fila* enfileira(fila *fi, int x) {
    fila *novo = malloc(sizeof(fila));
    novo->dado = x;
    novo->prox = NULL;
    if (fi == NULL) {
        return novo;
    }
    fila *aux = fi;
    while (aux->prox) aux = aux->prox;
    aux->prox = novo;
    return fi;
}

fila* desenfileira(fila *fi) {
    if (!fi) return NULL;
    fila *aux = fi;
    fi = fi->prox;
    free(aux);
    return fi;
}

bool fila_vazia(fila *fi) {
    return fi == NULL;
}

bool bfs(int vertice, int** graph, int* graphColSize, int cores[]) {
    fila *fila = NULL;
    fila = enfileira(fila, vertice);
    cores[vertice] = 0;

    while (!fila_vazia(fila)) {
        int atual = fila->dado;
        fila = desenfileira(fila);

        for (int i = 0; i < graphColSize[atual]; i++) {
            int vizinho = graph[atual][i];
            if (cores[vizinho] == -1) {
                cores[vizinho] = 1 - cores[atual];
                fila = enfileira(fila, vizinho);
            } else if (cores[vizinho] == cores[atual]) {
                return false;
            }
        }
    }
    return true;
}

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int cores[graphSize];
    for (int i = 0; i < graphSize; i++) {
        cores[i] = -1;
    }

    for (int i = 0; i < graphSize; i++) {
        if (cores[i] == -1) {
            if (!bfs(i, graph, graphColSize, cores)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    char input[1000];
    printf("Digite:\n");
    fgets(input, sizeof(input), stdin);

    int tamanho_do_grafo = 0;
    int graphColSize[100];
    int** grafo = malloc(100 * sizeof(int*));

    int vertice = 0; 
    for (int i = 0; input[i]; i++) {
        if (input[i] == '[') {
            int i = 0;
            while (input[++i] != ']') {
                if (input[i] >= '0' && input[i] <= '9') {
                    grafo[vertice] = realloc(grafo[vertice], ++i * sizeof(int));
                    grafo[vertice][i - 1] = input[i] - '0';
                }
            }
            graphColSize[vertice] = i;
            vertice++;
        }
    }

    tamanho_do_grafo = vertice;

    if (isBipartite(grafo, tamanho_do_grafo, graphColSize)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}
