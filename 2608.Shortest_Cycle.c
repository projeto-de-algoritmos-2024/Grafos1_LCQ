#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void lerArestas(Grafo* grafo) {
    char entrada[1024];
    printf("Digite as arestas no formato [[0,1],[1,2],...]: ");
    scanf(" %[^\n]", entrada);

    char* token = strtok(entrada, "[],");

    int src, dest;
    while (token != NULL) {
        src = atoi(token);       
        token = strtok(NULL, "[],");
        if (token != NULL) {
            dest = atoi(token);  
            adicionarAresta(grafo, src, dest);
            token = strtok(NULL, "[],");
        }
    }
}

void bfs(Grafo* grafo, int start) {
    int* queue = malloc(grafo->numVertices * sizeof(int));
    int* visited = calloc(grafo->numVertices, sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("Visitando nos a partir do no %d: ", start);

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current); 

        No* temp = grafo->listaAdj[current];
        while (temp) {
            int neighbor = temp->vertice;

            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
            temp = temp->proximo;
        }
    }
    printf("\n");

    free(queue);
    free(visited);
}

int findShortestCycle(int n, int** arestas, int tamanhoArestas, int* colSizeArestas) {
    Grafo* grafo = criarGrafo(n);

    for (int i = 0; i < tamanhoArestas; i++) {
        adicionarAresta(grafo, arestas[i][0], arestas[i][1]);
    }

    //chama bfs 

    return -1;
}


int main() {
    int n;
    
    printf("Digite o numero de vertices: ");
    scanf("%d", &n);

    Grafo* grafo = criarGrafo(n);

    lerArestas(grafo);

    printf("Grafo:\n");
    imprimirGrafo(grafo);

    printf("Executando BFS:\n");
    
    for(int v = 0; v < n; v++){
        bfs(grafo, v);
    }
    

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