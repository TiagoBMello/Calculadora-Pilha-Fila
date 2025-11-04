// avaliar_expressao_posfixa.c
#include <stdio.h>
#include "pilha.h"
#include "fila.h"
#include "regra_operadores.h"
#include "avaliar_expressao_posfixa.h"

int potencia_inteira_simples(int base, int expoente) {
    if (expoente < 0) return 0; // versão simples não aceita expoente negativo
    int acumulador = 1;
    int contador = 0;
    while (contador < expoente) {
        acumulador = acumulador * base;
        contador = contador + 1;
    }
    return (int)acumulador;
}

int avaliar_expressao_posfixa(Fila *fila_posfixa, int *resultado) {
    Pilha *pilha_valores = criar_pilha();
    if (pilha_valores == NULL) {
        printf("Expressão Inválida.\n");
        return 0;
    }

    while (!fila_vazia(fila_posfixa)) {
        int item = desenfileirar(fila_posfixa);

        if (item >= 0) {
            // é número
            empilhar(pilha_valores, item);
        } else {
            // é operador: recuperar o caractere
            char operador = (char)(-item);

            // precisamos de dois operandos na pilha: numero_a (esquerda) e numero_b (direita)
            if (pilha_vazia(pilha_valores)) { 
                printf("Expressão Inválida.\n"); 
                liberar_pilha(pilha_valores); 
                return 0; 
            }
            int numero_b = desempilhar(pilha_valores);
            
            if (pilha_vazia(pilha_valores)) { 
                printf("Expressão Inválida.\n"); 
                liberar_pilha(pilha_valores); 
                return 0; 
            }
            int numero_a = desempilhar(pilha_valores);

            int resultado_parcial = 0;

            if (operador == '+') {
                resultado_parcial = numero_a + numero_b;
            }
            else if (operador == '-') {
                resultado_parcial = numero_a - numero_b;
            }
            else if (operador == '*') {
                resultado_parcial = numero_a * numero_b;
            }
            else if (operador == '/') {
                if (numero_b == 0) { // divisão por zero → erro
                    printf("Expressão Inválida.\n"); 
                    liberar_pilha(pilha_valores);
                    return 0;
                }
                resultado_parcial = numero_a / numero_b; // divisão inteira
            }
            else if (operador == '^') {
                if (numero_b < 0) { // expoente negativo não suportado
                    printf("Expressão Inválida.\n"); 
                    liberar_pilha(pilha_valores);
                    return 0;
                }
                resultado_parcial = potencia_inteira_simples(numero_a, numero_b);
            }
            else {
                // operador inválido (não era pra acontecer)
                printf("ERRO. Expressão Inválida.\n"); 
                liberar_pilha(pilha_valores);
                return 0;
            }

            empilhar(pilha_valores, resultado_parcial);
        }
    }

    // no fim deve sobrar exatamente 1 valor
    if (pilha_vazia(pilha_valores)) {
        printf("ERRO. Expressão Inválida.\n");
        liberar_pilha(pilha_valores);
        return 0;
    }
    int valor_final = desempilhar(pilha_valores);
    if (!pilha_vazia(pilha_valores)) {
        // sobrou lixo → expressão malformada
        printf("ERRO. Expressão Inválida.\n");
        liberar_pilha(pilha_valores);
        return 0;
    }

    *resultado = valor_final;
    liberar_pilha(pilha_valores);
    return 1;
}