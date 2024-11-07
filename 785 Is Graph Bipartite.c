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

    printf("Caminho feito: ");

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
    printf("\n");
}

int main() {
    int num_vertices, num_arestas, no_inicio;;

    printf("numero de nos: ");
    scanf("%d", &num_vertices);

    int *lista_adj = malloc(num_vertices * num_vertices * sizeof(int));
    for (int i = 0; i < num_vertices * num_vertices; i++) {
        lista_adj[i] = 0;
    }

    printf("numero de arestas: ");
    scanf("%d", &num_arestas);
    
    printf("Digite as arestas:\n");
    for (int i = 0; i < num_arestas; i++) {
        int v1, v2;
        printf("Aresta %d: ", i + 1);
        scanf("%d %d", &v1, &v2);

        lista_adj[v1 * num_vertices + v2] = 1;
        lista_adj[v2 * num_vertices + v1] = 1;
    }
    
    printf("no inicial: ");
    scanf("%d", &no_inicio);

    BFS(lista_adj, no_inicio, num_vertices);

    return 0;
}
