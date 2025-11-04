// pilha.c
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* criar_pilha(void) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro de memoria na pilha\n");
        exit(1);
    }
    p->topo = -1;
    return p;
}

int pilha_vazia(Pilha *p) {
    if (p->topo == -1) {
        return 1;
    } else {
        return 0;
    }
}

int pilha_cheia(Pilha *p) {
    if (p->topo == TAM_MAX_PILHA - 1) {
        return 1;
    } else {
        return 0;
    }
}

void empilhar(Pilha *p, int valor) {
    if (pilha_cheia(p)) {
        printf("Pilha cheia\n");
        exit(1);
    } else {
        p->topo = p->topo + 1;
        p->dados[p->topo] = valor;
    }
}

int desempilhar(Pilha *p) {
    int valor;
    if (pilha_vazia(p)) {
        printf("Pilha vazia\n");
        exit(1);
    } else {
        valor = p->dados[p->topo];
        p->topo = p->topo - 1;
        return valor;
    }
}

void liberar_pilha(Pilha *p) {
    if (p != NULL) {
        free(p);
    }
}
