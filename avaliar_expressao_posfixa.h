// avaliar_expressao_posfixa.h
#pragma once
#include "fila.h"

// Lê a FILA POS-FIXA e calcula o resultado inteiro.
// Retorna 1 (sucesso) e preenche *resultado.
// Retorna 0 (erro), por exemplo: falta/sobra de operandos, divisão por zero, expoente negativo.
int avaliar_expressao_posfixa(Fila *fila_posfixa, int *resultado);
