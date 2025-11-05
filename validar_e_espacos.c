// validar_e_espacos.c

// MÓDULO: ETAPA 1 - VALIDA E REMOVE ESPAÇOS.
// Responsabilidade: Garante que a expressão tem sintaxe válida ANTES de ser tokenizada.

#include <stdio.h>
#include "validar_e_espacos.h"

// Função auxiliar: Checa se o caractere é um dígito (0-9)
static int eh_digito(char c) {
    if (c >= '0' && c <= '9') return 1;
    else return 0;
}

// Funcao: Valida a sintaxe da expressão, garantindo que os tokens estejam na ordem correta.
// Usa o conceito de "estado anterior" para saber o que é permitido em seguida.
int validar_expressao(char expressao[]) {
    int i = 0;
    int abre_parenteses = 0; // Contador de parênteses abertos
    int tem_numero = 0;      // Flag para garantir que a expressão não está vazia ou só tem operadores
    
    // Lógica de Máquina de Estados Simplificada:
    // 0=início, 1=número, 2=operador (ou unário), 3='(', 4=')'
    int estado_anterior = 0;

    // Loop principal: Percorre a string de entrada
    while (expressao[i] != '\0') {
        char caractere = expressao[i];
        int avancou = 0;

        // 1. Validação inicial: Checa se o caractere é permitido (dígito, espaço, operador ou parêntese)
        if (!((caractere >= '0' && caractere <= '9') ||
              caractere == ' ' || caractere == '+' || caractere == '-' ||
              caractere == '*' || caractere == '/' || caractere == '^' ||
              caractere == '(' || caractere == ')')) {
            printf("ERRO. Expressão Inválida.\n");
            return 0;
        }

        // 2. Lógica para ESPAÇOS
        if (caractere == ' ') {
            int j = i;
            while (expressao[j] == ' ') j++; // Avança por todos os espaços

            // Regra: Verifica se há espaço entre dígitos (Ex: 10 20)
            if (i > 0) {
                char antes = expressao[i - 1];
                char depois = expressao[j];
                if ((eh_digito(antes)) && (eh_digito(depois))) {
                    printf("ERRO. Expressão Inválida.\n"); // Espaço entre dígitos é proibido
                    return 0;
                }
            }

            i = j;       // Atualiza o índice 'i' para pular os espaços
            avancou = 1; // Marca que o 'i' já foi movido
        }
        
        // 3. Lógica para NÚMERO (Dígitos)
        else if (eh_digito(caractere)) {
            tem_numero = 1;
            // Regra: Número não pode vir logo após um parêntese fechado (Ex: ")3")
            if (estado_anterior == 4) { printf("ERRO. Expressão Inválida.\n"); return 0; } 
            
            // Loop interno para "comer" o número inteiro
            while (eh_digito(expressao[i])) {
                i++;
            }
            estado_anterior = 1; // Novo estado: Número
            avancou = 1;
        }
        
        // 4. Lógica para ABRE PARÊNTESE '('
        else if (caractere == '(') {
            // Regra: Não pode vir depois de número ou ')' (Ex: "3(" ou ")(")
            if (estado_anterior == 1 || estado_anterior == 4) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            abre_parenteses++;
            estado_anterior = 3; // Novo estado: Abre Parêntese
            i++;
            avancou = 1;
        }
        
        // 5. Lógica para FECHA PARÊNTESE ')'
        else if (caractere == ')') {
            // Regra: Não pode vir no início, nem depois de operador, nem logo após '('
            if (estado_anterior == 0 || estado_anterior == 2 || estado_anterior == 3) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            abre_parenteses--;
            // Regra: Parêntese fechado sem correspondente aberto (Ex: "3)")
            if (abre_parenteses < 0) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            estado_anterior = 4; // Novo estado: Fecha Parêntese
            i++;
            avancou = 1;
        }
        
        // 6. Lógica para OPERADORES BINÁRIOS (+, *, /, ^)
        else if (caractere == '+' || caractere == '*' || caractere == '/' || caractere == '^') {
            // Regra: Operador binário não pode vir no início, nem depois de outro operador, nem após '('
            if (estado_anterior == 0 || estado_anterior == 2 || estado_anterior == 3) { printf("ERRO. Expressão Inválida.\n"); return 0; }
            estado_anterior = 2; // Novo estado: Operador
            i++;
            avancou = 1;
        }
        
        // 7. Lógica para HÍFEN/SUBTRAÇÃO '-' (Pode ser Binário ou Unário)
        else if (caractere == '-') {
            
            // Hífen Unário (Ex: -3, (-3), 5*-3)
            if (estado_anterior == 0 || estado_anterior == 3 || estado_anterior == 2) {
                // Versão simplificada (Requisito): Só aceita se houver um número logo depois
                int j = i + 1;
                while (expressao[j] == ' ') j++; // Pula espaços
                if (!(eh_digito(expressao[j]))) {
                    printf("ERRO. Expressão Inválida.\n"); 
                    return 0; 
                }
                estado_anterior = 2; // É um operador (unário)
                i++;
                avancou = 1;
            } 
            
            // Hífen Binário (Subtração: Ex: 5-3, (3+2)-5)
            else {
                // Regra: Precisa vir depois de número ou ')'
                if (estado_anterior != 1 && estado_anterior != 4) { printf("ERRO. Expressão Inválida.\n"); return 0; }
                estado_anterior = 2; // É um operador (binário)
                i++;
                avancou = 1;
            }
        }

        // Lógica de segurança: Garante que 'i' avance se o token lido não for tratado acima (não deve ocorrer)
        if (!avancou) i++;
    }

    // 8. Checagens Finais (Após varrer toda a string)
    // Parênteses balanceados
    if (abre_parenteses != 0) { printf("ERRO. Expressão Inválida.\n"); return 0; }
    // Expressão não pode terminar em operador, '(' ou estar vazia
    if (estado_anterior == 2 || estado_anterior == 3 || estado_anterior == 0) { printf("ERRO. Expressão Inválida.\n"); return 0; }
    // Deve ter tido pelo menos um número
    if (!tem_numero) { printf("ERRO. Expressão Inválida.\n"); return 0; }

    return 1;
}


// Funcao: Remove todos os espaços em branco da string, "in-place" (na própria string).
// Lógica: Copia o caractere 'i' para a posição 'j' apenas se não for espaço.
void remover_espacos(char expressao[]) {
    int i = 0; // Ponteiro de leitura
    int j = 0; // Ponteiro de escrita
    while (expressao[i] != '\0') {
        if (expressao[i] != ' ') {
            expressao[j] = expressao[i];
            j++;
        }
        i++;
    }
    expressao[j] = '\0'; // Finaliza a nova string sem espaços
}