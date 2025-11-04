// regras_operadores.c
#include "regra_operadores.h"

int eh_operador_inteiro(int valor) {
    if (valor < 0) return 1;
    else return 0;
}

int precedencia_do_operador(char operador) {
    if (operador == '^') return 3;
    else if (operador == '*' || operador == '/') return 2;
    else if (operador == '+' || operador == '-') return 1;
    else return 0;
}
