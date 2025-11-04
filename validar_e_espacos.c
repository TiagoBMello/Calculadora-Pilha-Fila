// validar_e_espacos.c
#include <stdio.h>
#include "validar_e_espacos.h"

static int eh_digito(char c) {
    if (c >= '0' && c <= '9') return 1;
    else return 0;
}

int validar_expressao(char expressao[]) {
    int i = 0;
    int abre_parenteses = 0;
    int tem_numero = 0;
    // 0=início, 1=número, 2=operador, 3='(', 4=')'
    int estado_anterior = 0;

    while (expressao[i] != '\0') {
        char caractere = expressao[i];
        int avancou = 0;

        // caracteres permitidos
        if (!((caractere >= '0' && caractere <= '9') ||
              caractere == ' ' || caractere == '+' || caractere == '-' ||
              caractere == '*' || caractere == '/' || caractere == '^' ||
              caractere == '(' || caractere == ')')) {
            printf("ERRO. Expressão Inválida.\n");
            return 0;
        }

        // espaço (checa "10  23")
        if (caractere == ' ') {
            int j = i;
            while (expressao[j] == ' ') j++;

            if (i > 0) {
                char antes = expressao[i - 1];
                char depois = expressao[j];
                if ((antes >= '0' && antes <= '9') &&
                    (depois >= '0' && depois <= '9')) {
                    printf("ERRO. Expressão Inválida.\n"); // espaço entre dígitos é proibido
                    return 0;
                }
            }

            i = j;       // pulou os espaços
            avancou = 1; // já avançamos
        }
        else if (eh_digito(caractere)) {
            // número (engole todos os dígitos)
            tem_numero = 1;
            if (estado_anterior == 4) { printf("ERRO. Expressão Inválida.\n"); return 0; } // ")3"
            while (eh_digito(expressao[i])) {
                i++;
            }
            estado_anterior = 1; // número
            avancou = 1;
        }
        else if (caractere == '(') {
            // não pode vir depois de número ou ')'
            if (estado_anterior == 1 || estado_anterior == 4) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            abre_parenteses++;
            estado_anterior = 3; // '('
            i++;
            avancou = 1;
        }
        else if (caractere == ')') {
            // não pode vir no início, nem depois de operador, nem logo após '('
            if (estado_anterior == 0 || estado_anterior == 2 || estado_anterior == 3) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            abre_parenteses--;
            if (abre_parenteses < 0) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            estado_anterior = 4; // ')'
            i++;
            avancou = 1;
        }
        else if (caractere == '+' || caractere == '*' || caractere == '/' || caractere == '^') {
            // operador binário
            if (estado_anterior == 0 || estado_anterior == 2 || estado_anterior == 3) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            estado_anterior = 2; // operador
            i++;
            avancou = 1;
        }
        else if (caractere == '-') {
            // pode ser unário (negativo) ou binário
            if (estado_anterior == 0 || estado_anterior == 3 || estado_anterior == 2) {
                // unário: deve ter número depois (pulando espaços)
                int j = i + 1;
                while (expressao[j] == ' ') j++;
                if (!(eh_digito(expressao[j]))) {
                    printf("ERRO. Expressão Inválida.\n"); // versão simples: não aceita "-( ... )"
                    return 0; 
                }
                // deixa os dígitos para o próximo giro
                estado_anterior = 2; // conta como "veio um operador"
                i++;
                avancou = 1;
            } else {
                // binário: precisa vir depois de número ou ')'
                if (estado_anterior != 1 && estado_anterior != 4) { printf("ERRO. Expressão Inválida.\n"); return 0; }
                estado_anterior = 2; // operador
                i++;
                avancou = 1;
            }
        }

        if (!avancou) i++;
    }

    // checagens finais
    if (abre_parenteses != 0) { printf("ERRO. Expressão Inválida.\n"); return 0; }
    if (estado_anterior == 2 || estado_anterior == 3 || estado_anterior == 0) { printf("ERRO. Expressão Inválida.\n"); return 0; }
    if (!tem_numero) { printf("ERRO. Expressão Inválida.\n"); return 0; }

    return 1;
}

void remover_espacos(char expressao[]) {
    int i = 0;
    int j = 0;
    while (expressao[i] != '\0') {
        if (expressao[i] != ' ') {
            expressao[j] = expressao[i];
            j++;
        }
        i++;
    }
    expressao[j] = '\0';
}