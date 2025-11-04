// ler_expressao_para_fila.h
#pragma once
#include "fila.h"

// Lê a STRING (já sem espaços) e monta a FILA INFIXA.
// Regras:
// - números: enfileirar como >= 0
// - operadores e parênteses: enfileirar como -(int)caractere
// - '-' unário (ex.: -3) vira "0 - 3" na fila
// Retorna 1 (ok) ou 0 (erro).
int ler_expressao_para_fila(const char *texto_sem_espacos, Fila *fila_infixa);
