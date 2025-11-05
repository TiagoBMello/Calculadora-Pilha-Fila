#pragma once

#define TAM_MAX_FILA 100

typedef struct {
    int inicio;               
    int fim;            
    int qtd;                  
    int dados[TAM_MAX_FILA];  
} Fila;

Fila* criar_fila();

int fila_vazia(Fila *f);

int fila_cheia(Fila *f);

void enfileirar(Fila *f, int valor);

int desenfileirar(Fila *f);

void liberar_fila(Fila *f);

void imprimir_fila(Fila *f);