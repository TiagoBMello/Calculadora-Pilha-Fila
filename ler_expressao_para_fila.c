//Trabalho Estrutura de Dados

//Grupo: 
//Tiago Mello - 23014024
//Vinicius Nunes - 23011585

//etapa 2: transformar em fila infixa

#include <limits.h>
#include <stdio.h>
#include "ler_expressao_para_fila.h"

//função: checa se é um digito
static int eh_digito(char c) {
    if (c >= '0' && c <= '9') 
        return 1;
    else 
        return 0;
}

//função: checa se o caracter é um operador
static int eh_operador_binario(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') 
        return 1;
    else 
        return 0;
}

//função: enfilera na fila infixa
int ler_expressao_para_fila(const char *s, Fila *fila_infixa) {
    int i = 0;
    if (s == NULL) return 0;
    //loop que percorre a string 
    while (s[i] != '\0') {
        char c = s[i];
        int token_lido = 0;
        //lógica para número
        if (eh_digito(c)) {
            long val = 0;
            // Lógica: Loop interno consome todos os dígitos para formar o valor inteiro (Ex: '10' -> 10)
            while (eh_digito(s[i])) {
                val = val * 10 + (s[i] - '0');
                if (val > INT_MAX) return 0; //checa se o número é muito grande
                i = i + 1;
            }
            enfileirar(fila_infixa, (int)val);
            token_lido = 1;
        }

        //lógica para parênteses
        else if (c == '(' || c == ')') {
            //regra: enfilera o código negativo para o parêntese
            enfileirar(fila_infixa, -(int)c);
            i = i + 1;
            token_lido = 1;
        }

        //lógica para operadores
        else if (eh_operador_binario(c)) {
            //trata o - para ver se ele é unário ou binário
            if (c == '-') {
                int eh_unario = 0;
                if (i == 0) eh_unario = 1;
                else {
                    char antes = s[i - 1];
                    if (antes == '(' || eh_operador_binario(antes)) eh_unario = 1;
                }
                //negação
                if (eh_unario) {
                    int j = i + 1;
                    //precisa de um número após o -
                    if (!eh_digito(s[j])) {
                        printf("ERRO. Expressão Inválida.\n");
                        return 0;
                    } 

                    long val = 0;
                    //le o valor absoluto do número
                    while (eh_digito(s[j])) {
                        val = val * 10 + (s[j] - '0');
                        if (val > INT_MAX) return 0;
                        j = j + 1;
                    }

                    //transforma a negação -x na subtração binária 0 - x
                    enfileirar(fila_infixa, 0);
                    enfileirar(fila_infixa, -(int)'-');
                    enfileirar(fila_infixa, (int)val);
                    i = j; //avança o índice após ler o número
                    token_lido = 1;
                }
            }

            //se for um operador binário comum
            if (!token_lido) {
                //enfileira o código negativo do operador binário
                enfileirar(fila_infixa, -(int)c);
                i = i + 1;
                token_lido = 1;
            }
        }
        
        //Lógica para caracter inválido
        else {
            printf("Expressão Inválida.\n");
            return 0;
        }
        if (!token_lido) {
            i++;
        }
    }
    if (i == 0) 
        return 0;
    return 1;
}