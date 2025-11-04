// fila.h
#pragma once

#define TAM_MAX_FILA 100

typedef struct {
    int inicio;               // posição do primeiro
    int fim;                  // posição do último
    int qtd;                  // quantos elementos tem
    int dados[TAM_MAX_FILA];  // guarda números OU operadores (int)
} Fila;

// cria e devolve uma fila vazia
Fila* criar_fila(void);

// retorna 1 se vazia, senão 0
int fila_vazia(Fila *f);

// retorna 1 se cheia, senão 0
int fila_cheia(Fila *f);

// coloca um valor no fim (erro e encerra se cheia)
void enfileirar(Fila *f, int valor);

// remove e retorna o primeiro (erro e encerra se vazia)
int desenfileirar(Fila *f);

// libera a memória da fila
void liberar_fila(Fila *f);
