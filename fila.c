// fila.c
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criar_fila(void) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f == NULL) {
        printf("Erro de memoria na fila\n");
        exit(1);
    }
    f->inicio = 0;
    f->fim = -1;
    f->qtd = 0;
    return f;
}

int fila_vazia(Fila *f) {
    if (f->qtd == 0) {
        return 1;
    } else {
        return 0;
    }
}

int fila_cheia(Fila *f) {
    if (f->qtd == TAM_MAX_FILA) {
        return 1;
    } else {
        return 0;
    }
}

void enfileirar(Fila *f, int valor) {
    if (fila_cheia(f)) {
        printf("Fila cheia\n");
        exit(1);
    } else {
        f->fim = (f->fim + 1) % TAM_MAX_FILA;
        f->dados[f->fim] = valor;
        f->qtd = f->qtd + 1;
    }
}

int desenfileirar(Fila *f) {
    int valor;
    if (fila_vazia(f)) {
        printf("Fila vazia\n");
        exit(1);
    } else {
        valor = f->dados[f->inicio];
        f->inicio = (f->inicio + 1) % TAM_MAX_FILA;
        f->qtd = f->qtd - 1;
        return valor;
    }
}

void liberar_fila(Fila *f) {
    if (f != NULL) {
        free(f);
    }
}

void imprimir_fila(Fila *f) {
    if (fila_vazia(f)) {
        printf("(vazia)");
        return;
    }
    
    int i = f->inicio;
    int contador = 0;
    
    while (contador < f->qtd) {
        int item = f->dados[i];
        
        if (item >= 0) {
            // É número
            printf("%d", item);
        } else {
            // É operador (negativo)
            printf("%c", (char)(-item));
        }
        
        // Se não for o último item, imprime a vírgula e espaço
        if (contador < f->qtd - 1) {
            printf(", ");
        }
        
        i = (i + 1) % TAM_MAX_FILA;
        contador++;
    }
}