//regra que define a força dos operadores

#include "regra_operadores.h"

//função: operador ou parênteses
int eh_operador_inteiro(int valor) {
    if (valor < 0)
        return 1; //verdadeiro
    else
        return 0;
}

// função: define a força do operador
int precedencia_do_operador(char operador) {
    if (operador == '^') return 3;
    else if (operador == '*' || operador == '/') return 2;
    else if (operador == '+' || operador == '-') return 1;
    else return 0;
}