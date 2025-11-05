//etapa 3: calcular a expressão pós-fixa

#include <stdio.h>
#include "pilha.h"
#include "fila.h"
#include "regra_operadores.h"
#include "avaliar_expressao_posfixa.h"


//funcão: calcula a potência
int potencia_inteira_simples(int base, int expoente) {
    //expoente não pode ser negativo
    if (expoente < 0) return 0;
    int acumulador = 1;
    int contador = 0;
    //logica para calular potência
    while (contador < expoente) {
        acumulador = acumulador * base;
        contador = contador + 1;
    }
    return (int)acumulador;
}


//função: faz o cálculo da expressão
int avaliar_expressao_posfixa(Fila *fila_posfixa, int *resultado) { 
    //cria a pilha que será usada para armazenar os números/resultados
    Pilha *pilha_valores = criar_pilha();
    if (pilha_valores == NULL) {
        printf("Expressão Inválida.\n");
        return 0;
    }
    //loop que processa cada item da fila pós-fixa
    while (!fila_vazia(fila_posfixa)) {
        int item = desenfileirar(fila_posfixa);
        if (item >= 0) {
            //se o item é um número, empilha
            empilhar(pilha_valores, item);
        } 
        else {
            //se o item é um caractere
            char operador = (char)(-item); //converte o valor negativo para o caractere
            //validacão
            if (pilha_vazia(pilha_valores)) { 
                printf("Expressão Inválida.\n"); 
                liberar_pilha(pilha_valores); 
                return 0; 
            }
            //desempilha
            int numero_b = desempilhar(pilha_valores); //operando da direita  
            //validação
            if (pilha_vazia(pilha_valores)) { 
                printf("Expressão Inválida.\n");
                liberar_pilha(pilha_valores); 
                return 0; 
            }
            int numero_a = desempilhar(pilha_valores); //operando da esquerda
            int resultado_parcial = 0;

            //executa o cálculo com base no operador
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
                //validar divisão por 0
                if (numero_b == 0) { 
                    printf("Expressão Inválida.\n"); 
                    liberar_pilha(pilha_valores);
                    return 0;
                }
                resultado_parcial = numero_a / numero_b;
            }
            else if (operador == '^') {
                // Validar expoente negativo
                if (numero_b < 0) { 
                    printf("Expressão Inválida.\n"); 
                    liberar_pilha(pilha_valores);
                    return 0;
                }
                resultado_parcial = potencia_inteira_simples(numero_a, numero_b);
            }
            else {
                //da erro se não for nenhum dos operadores
                printf("Expressão Inválida.\n"); 
                liberar_pilha(pilha_valores);
                return 0;
            }
            empilhar(pilha_valores, resultado_parcial);
        }
    }
    //ultima verificação, a pilha deve ter só 1 número no final 
    if (pilha_vazia(pilha_valores)) {
        printf("Expressão Inválida.\n");
        liberar_pilha(pilha_valores);
        return 0;
    }
    
    //pega o resultado
    int valor_final = desempilhar(pilha_valores);
    if (!pilha_vazia(pilha_valores)) {
        printf("Expressão Inválida.\n");
        liberar_pilha(pilha_valores);
        return 0;
    }
    *resultado = valor_final;
    liberar_pilha(pilha_valores);
    return 1;
}