// pilha.h
#pragma once

#define TAM_MAX_PILHA 100

typedef struct {
    int topo;                 // posição do topo (-1 quando vazia)
    int dados[TAM_MAX_PILHA]; // armazena números OU códigos (int)
} Pilha;

// cria e devolve uma pilha vazia (topo = -1)
Pilha* criar_pilha(void);

// retorna 1 se vazia, senão 0
int pilha_vazia(Pilha *p);

// retorna 1 se cheia, senão 0
int pilha_cheia(Pilha *p);

// coloca um valor no topo (erro e encerra se cheia)
void empilhar(Pilha *p, int valor);

// remove e retorna o topo (erro e encerra se vazia)
int desempilhar(Pilha *p);

// libera a memória da pilha
void liberar_pilha(Pilha *p);
