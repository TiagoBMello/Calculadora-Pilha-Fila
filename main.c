// main.c
#include <stdio.h>

#include "fila.h"
#include "validar_e_espacos.h"
#include "ler_expressao_para_fila.h"
#include "converter_infixa_para_posfixa.h"
#include "avaliar_expressao_posfixa.h"

int main() {
    char linha[1024];
    int repetir;      // 1 = pede de novo; 0 = encerra
    int resultado;    // guarda o resultado final

    printf("======================\n");
    printf("Calculadora (Pilha e Fila)\n");
    printf("Operadores: + - * / ^   Parenteses: ( )\n");
    printf("Aceita - unario (ex.: -3). Divisao inteira.\n\n");

    repetir = 1;
    while (repetir == 1) {
        printf("\nExpressao: ");

        // lê a linha inteira até '\n' (permite espaços)
        if (scanf(" %1023[^\n]", linha) != 1) {
            return 0; // fim da entrada
        }
     
        // 1) Validar
        if (validar_expressao(linha)) {

            // 2) Remover espacos (in-place)
            remover_espacos(linha);
            printf("--- Etapa 1 ---\n");
            printf("Expressao sem espacos: %s\n", linha); // Mostra sem espaços

            // 3) Criar filas
            Fila *fila_infixa  = criar_fila();
            Fila *fila_posfixa = criar_fila();

            if (fila_infixa != NULL && fila_posfixa != NULL) {

                // 4) String -> Fila infixa
                if (ler_expressao_para_fila(linha, fila_infixa)) {
                    printf("Fila Infixa (Tokens): "); 
                    imprimir_fila(fila_infixa);
                    printf("\n");

                    // 5) Infixa -> Pos-fixa
                    if (converter_infixa_para_posfixa(fila_infixa, fila_posfixa)) {
                        printf("--- Etapa 2 ---\n");
                        printf("Fila Pos-fixa (RPN): "); 
                        imprimir_fila(fila_posfixa);
                        printf("\n");

                        // 6) Avaliar pos-fixa
                        if (avaliar_expressao_posfixa(fila_posfixa, &resultado)) {
                            printf("--- Etapa 3 ---\n");
                            printf("Resultado Final: %d\n", resultado);
                            repetir = 0; // deu certo, pode encerrar
                        } else {
                            // Erro interno (avaliação) - Funções internas imprimem "ERRO. Expressão Inválida."
                            printf("Digite novamente.\n");
                        }
                    } else {
                        // Erro interno (conversão) - Funções internas imprimem "ERRO. Expressão Inválida."
                        printf("Digite novamente.\n");
                    }
                } else {
                    // Erro interno (leitura/tokenização) - Funções internas imprimem "ERRO. Expressão Inválida."
                    printf("Digite novamente.\n");
                }
            } else {
                // Falha na criação das filas
                printf("ERRO. Expressão Inválida.\n");
                printf("Digite novamente.\n");
            }

            // libera filas se foram criadas
            if (fila_infixa  != NULL) liberar_fila(fila_infixa);
            if (fila_posfixa != NULL) liberar_fila(fila_posfixa);
        } else {
            // validação falhou - Funções internas imprimem "ERRO. Expressão Inválida."
            printf("Digite novamente.\n");
        }
    }

    return 0;
}