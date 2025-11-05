#pragma once

#define TAM_MAX_PILHA 100

typedef struct {
    int topo;                 
    int dados[TAM_MAX_PILHA]; 
} Pilha;

Pilha* criar_pilha();

int pilha_vazia(Pilha *p);

int pilha_cheia(Pilha *p);

void empilhar(Pilha *p, int valor);

int desempilhar(Pilha *p);

void liberar_pilha(Pilha *p);
