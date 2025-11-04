// regras_operadores.h
#pragma once

// Diz se um inteiro representa OPERADOR na nossa convenção (operadores são negativos)
int eh_operador_inteiro(int valor);

// Força do operador para decidir desempilhar na conversão:
// ^ = 3,  * e / = 2,  + e - = 1,  outros = 0
int precedencia_do_operador(char operador);
