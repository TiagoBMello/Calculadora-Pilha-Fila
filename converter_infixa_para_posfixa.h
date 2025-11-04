// converter_infixa_para_posfixa.h
#pragma once
#include "fila.h"

// Converte a Fila de ENTRADA (infixa) em Fila POS-FIXA.
// Retorna 1 (sucesso) ou 0 (erro: parênteses, etc.).
int converter_infixa_para_posfixa(Fila *fila_entrada, Fila *fila_posfixa);
