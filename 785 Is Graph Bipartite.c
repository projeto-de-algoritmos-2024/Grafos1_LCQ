#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct fila {
    int dado;
    struct fila *prox;
} fila;

fila *enfileira(fila *fi, int x) {
    fila *novo = malloc(sizeof(fila));
    novo->dado = x;
    novo->prox = NULL;
    if (fi == NULL) {
        return novo;  
    }
    fila *aux = fi;
    while (aux->prox != NULL) {  
        aux = aux->prox;
    }
    aux->prox = novo;
    return fi;
}

fila *desenfileira(fila *fi) {
    if (fi == NULL) {
        return NULL;
    }
    fila *aux = fi;
    fi = fi->prox;   
    free(aux);  
    return fi;
}

bool fila_vazia(fila *fi) {
    return fi == NULL;
}

void BFS(int *lista_adj, int no_inicio, int num_vertices) {
    bool visitado[1000] = {false};

    fila *fila = NULL;
    fila = enfileira(fila, no_inicio);
    visitado[no_inicio] = true;

    while (!fila_vazia(fila)) {
        int vertice = fila->dado;
        printf("%d ", vertice);
        fila = desenfileira(fila);

        for (int i = 0; i < num_vertices; i++) {
            if (lista_adj[vertice * num_vertices + i] == 1 && !visitado[i]) {
                fila = enfileira(fila, i);
                visitado[i] = true;
            }
        }
    }
}

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* cores = malloc(graphSize * sizeof(int));  

    for (int i = 0; i < graphSize; i++) {
        cores[i] = -1; 
    }

    fila* fila = NULL;

    for (int i = 0; i < graphSize; i++) {
        if (cores[i] == -1) {  
            fila = enfileira(fila, i);
            cores[i] = 0; 

            while (!fila_vazia(fila)) {
                int vertice = fila->dado;
                fila = desenfileira(fila);

                for (int j = 0; j < graphSize; j++) {
                    if (graph[vertice][j] == 1) {  
                        if (cores[j] == -1) {  
                            cores[j] = 1 - cores[vertice];  
                            fila = enfileira(fila, j);
                        } else if (cores[j] == cores[vertice]) {
                            free(cores);
                            return false;  
                        }
                    }
                }
            }
        }
    }
    free(cores);
    return true;  
}

int main() {
    int tamanhodografo = 4;
    int colunas[4] = {4, 4, 4, 4};  
    int graph[4][4] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int** teste = malloc(tamanhodografo * sizeof(int*));
    for (int i = 0; i < tamanhodografo; i++) {
        teste[i] = graph[i];
    }

    bool resultado = isBipartite(teste, tamanhodografo, colunas);
    if (resultado == true) {
        printf("O grafo é bipartido.\n");
    } else {
        printf("O grafo não é bipartido.\n");
    }

    return 0;
}
