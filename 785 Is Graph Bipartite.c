#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>  

typedef struct fila {
    int dado;
    struct fila *prox;
} fila;

fila *enfileira(fila *le, int x) {
    fila *novo = malloc(sizeof(fila));
    novo->dado = x;
    novo->prox = NULL;
    if (le == NULL) {
        return novo;  
    }
    fila *temp = le;
    while (temp->prox != NULL) {  
        temp = temp->prox;
    }
    temp->prox = novo;
    return le;
}

fila *desenfileira(fila *le) {
    if (le == NULL) {
        return NULL;
    }
    fila *temp = le;
    le = le->prox; 
    free(temp);  
    return le;
}

int main() {
    int num_nos; 
    int num_arestas;

    printf("Digite o numero de nos: ");
    scanf("%d", &num_nos);
    printf("Digite o numero de arestas: ");
    scanf("%d", &num_arestas);
}