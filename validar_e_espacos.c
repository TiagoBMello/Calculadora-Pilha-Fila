//Trabalho Estrutura de Dados

//Grupo: 
//Tiago Mello - 23014024
//Vinicius Nunes - 23011585

//etapa 1:  validar e remover os espaços
//aqui ta a logica que aceita - unario
#include <stdio.h>
#include "validar_e_espacos.h"

//função: verificar se é um digito
static int eh_digito(char c) {
    if (c >= '0' && c <= '9') 
        return 1;
    else 
        return 0;
}

//funçao: validar a sintaxe
int validar_expressao(char expressao[]) {
    int i = 0;
    int abre_parenteses = 0;
    int tem_numero = 0;
    int estado_anterior = 0;

    //loop que percorre a string de entrada
    while (expressao[i] != '\0') {
        char caractere = expressao[i];
        int avancou = 0;

        //checa se o caractere é permitido
        if (!((caractere >= '0' && caractere <= '9') || caractere == ' ' || caractere == '+' || caractere == '-' || caractere == '*' || caractere == '/' || caractere == '^' || caractere == '(' || caractere == ')')) {
            printf("Expressão Inválida.\n");
            return 0;
        }

        //lógica para os espaços
        if (caractere == ' ') {
            int j = i;
            while (expressao[j] == ' ') j++; //avança por todos os espaços
            //verifica se tem espaço entre os dígitos
            if (i > 0) {
                char antes = expressao[i - 1];
                char depois = expressao[j];
                if ((eh_digito(antes)) && (eh_digito(depois))) {
                    printf("Expressão Inválida.\n");
                    return 0;
                }
            }

            i = j;
            avancou = 1;
        }
        
        //lógica para números
        else if (eh_digito(caractere)) {
            tem_numero = 1;
            //o número não pode vir logo depois de fehcar um parêntese
            if (estado_anterior == 4) { printf("Expressão Inválida.\n"); 
                return 0; } 
            //loop para comer o número inteiro
            while (eh_digito(expressao[i])) {
                i++;
            }
            estado_anterior = 1;
            avancou = 1;
        }
        
        //lógica para quando abre parênteses
        else if (caractere == '(') {
            //não pode vir depois de número ou )
            if (estado_anterior == 1 || estado_anterior == 4) {
                printf("Expressão Inválida.\n"); 
                return 0; 
            }
            abre_parenteses++;
            estado_anterior = 3;
            i++;
            avancou = 1;
        }
        
        //lógica para qunado fecha parênteses
        else if (caractere == ')') {
            //não pode vir no início, nem depois de operador, nem depois de (
            if (estado_anterior == 0 || estado_anterior == 2 || estado_anterior == 3) {
                printf("ERRO. Expressão Inválida.\n"); 
                return 0; 
            }
            abre_parenteses--;
            if (abre_parenteses < 0) { 
                printf("ERRO. Expressão Inválida.\n"); 
                return 0; 
            }
            estado_anterior = 4;
            i++;
            avancou = 1;
        }
        
        //lógica para os operadores
        else if (caractere == '+' || caractere == '*' || caractere == '/' || caractere == '^') {
            //os operadores binários não podem vir no início, nem depois de outro operador, nem depois de (
            if (estado_anterior == 0 || estado_anterior == 2 || estado_anterior == 3) { 
                printf("Expressão Inválida.\n"); 
                return 0; 
            }
            estado_anterior = 2; 
            i++;
            avancou = 1;
        }
        
        //lógica para a subtração
        // - quando é unário 
        else if (caractere == '-') {
            if (estado_anterior == 0 || estado_anterior == 3 || estado_anterior == 2) {
                int j = i + 1;
                while (expressao[j] == ' ') j++;
                if (!(eh_digito(expressao[j]))) {
                    printf("Expressão Inválida.\n"); 
                    return 0; 
                }
                estado_anterior = 2;
                i++;
                avancou = 1;
            } 
            
            // - qunado é binário
            else {
                //precisa vir depois de número ou parênteses
                if (estado_anterior != 1 && estado_anterior != 4) { 
                    printf("Expressão Inválida.\n"); 
                    return 0; 
                }
                estado_anterior = 2;
                i++;
                avancou = 1;
            }
        }
        if (!avancou) i++;
    }

    //ultima checagem
    //parênteses balanceados
    if (abre_parenteses != 0) { 
        printf("Expressão Inválida.\n"); 
        return 0; 
    }
    //expressão não pode terminar em operador, (, ou estar vazia
    if (estado_anterior == 2 || estado_anterior == 3 || estado_anterior == 0) { 
        printf("Expressão Inválida.\n"); 
        return 0; 
    }
    //deve ter tido pelo menos um número
    if (!tem_numero) { 
        printf("Expressão Inválida.\n"); 
        return 0; 
    }

    return 1;
}


//função: remove todos os espaços, deixa a expressão grudada
//lógica: dopia o caractere 'i' para a posição 'j' apenas se não for espaço.
void remover_espacos(char expressao[]) {
    int i = 0; //ponteiro de leitura
    int j = 0; //ponteiro de escrita
    while (expressao[i] != '\0') {
        if (expressao[i] != ' ') {
            expressao[j] = expressao[i];
            j++;
        }
        i++;
    }
    expressao[j] = '\0';
}