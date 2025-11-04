// ler_expressao_para_fila.c
#include <limits.h>
#include <stdio.h>
#include "ler_expressao_para_fila.h"

static int eh_digito(char c) {
    if (c >= '0' && c <= '9') return 1;
    else return 0;
}

static int eh_operador_binario(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return 1;
    else return 0;
}

int ler_expressao_para_fila(const char *s, Fila *fila_infixa) {
    int i = 0;
    if (s == NULL) return 0;

    while (s[i] != '\0') {
        char c = s[i];
        int token_lido = 0;

        // 1) número
        if (eh_digito(c)) {
            long val = 0;
            while (eh_digito(s[i])) {
                val = val * 10 + (s[i] - '0');
                if (val > INT_MAX) return 0;
                i = i + 1;
            }
            enfileirar(fila_infixa, (int)val);
            token_lido = 1;
        }

        // 2) parênteses
        else if (c == '(' || c == ')') {
            enfileirar(fila_infixa, -(int)c);
            i = i + 1;
            token_lido = 1;
        }

        // 3) operadores
        else if (eh_operador_binario(c)) {

            // trata '-' unário: início, ou após '(' ou após operador
            if (c == '-') {
                int eh_unario = 0;
                if (i == 0) eh_unario = 1;
                else {
                    char antes = s[i - 1];
                    if (antes == '(' || eh_operador_binario(antes)) eh_unario = 1;
                }
                
                // Trata o Unário
                if (eh_unario) {
                    int j = i + 1;
                    
                    // Deve haver um dígito após o '-' (versão simplificada)
                    if (!eh_digito(s[j])) {
                        printf("ERRO. Expressão Inválida.\n");
                        return 0;
                    } 

                    long val = 0;
                    while (eh_digito(s[j])) {
                        val = val * 10 + (s[j] - '0');
                        if (val > INT_MAX) return 0;
                        j = j + 1;
                    }

                    // Enfileira como "0 - val" para negação
                    enfileirar(fila_infixa, 0);
                    enfileirar(fila_infixa, -(int)'-');
                    enfileirar(fila_infixa, (int)val);

                    i = j;
                    token_lido = 1;
                }
            }

            // Se não foi unário (ou foi outro operador), trata como binário comum
            if (!token_lido) {
                enfileirar(fila_infixa, -(int)c);
                i = i + 1;
                token_lido = 1;
            }
        }
        
        // 4) caractere inválido
        else {
            printf("Expressão Inválida.\n");
            return 0;
        }
        
        // Garante que a variável 'i' avançou para evitar loop infinito
        if (!token_lido) {
            i++;
        }
    }

    if (i == 0) return 0; // expressão vazia
    return 1;
}