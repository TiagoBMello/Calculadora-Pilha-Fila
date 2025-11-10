//Trabalho Estrutura de Dados

//Grupo: 
//Tiago Mello - 23014024
//Vinicius Nunes - 23011585

#include <stdio.h>
#include "fila.h"
#include "validar_e_espacos.h"
#include "ler_expressao_para_fila.h"
#include "converter_infixa_para_posfixa.h"
#include "avaliar_expressao_posfixa.h"

int main() {
    char linha[1024];
    int repetir;
    int resultado;

    printf("======================\n");
    printf("Trabalho Estrutura de Dados - Calculadora\n");


    //loop principal, se errar na digitação ele pede pra escrever de novo 
    repetir = 1;
    while (repetir == 1) {
        printf("\nExpressao: ");
        //le a linha inteira até '\n', permitindo espaços tb
        if (scanf(" %1023[^\n]", linha) != 1) {
            return 0;
        }
     
        //1ª etapa: validar
        if (validar_expressao(linha)) {
            //remover espacos
            remover_espacos(linha);
            printf("======================\n");
            printf("ETAPA 1 \n\n");
            printf("Expressao sem espacos: %s\n", linha);

            //criar as filas
            Fila *fila_infixa  = criar_fila();
            Fila *fila_posfixa = criar_fila();
            if (fila_infixa != NULL && fila_posfixa != NULL) {
                //transformar a expressão ainda string em fila infixa
                if (ler_expressao_para_fila(linha, fila_infixa)) {
                    printf("Fila Infixa: "); 
                    imprimir_fila(fila_infixa);
                    printf("\n");

                    //2ª etapa: tranformar fila infixa em pós fixa
                    if (converter_infixa_para_posfixa(fila_infixa, fila_posfixa)) {
                        printf("======================\n");
                        printf("ETAPA 2 \n\n");
                        printf("Fila Pos-fixa: "); 
                        imprimir_fila(fila_posfixa);
                        printf("\n");

                        //3ª etapa: avaliar a fila pos-fixa
                        if (avaliar_expressao_posfixa(fila_posfixa, &resultado)) {
                            printf("======================\n");
                            printf("ETAPA 3 \n\n");
                            printf("Resultado Final: %d\n", resultado);
                            repetir = 0; //deu certo, encerra
                        } 

                        //fechando todos os elses dos ifs que abrimos, todos eles são para caso a expressão esteja errada
                        else {
                            printf("Digite novamente.\n");
                        }
                    } 
                    else {
                        printf("Digite novamente.\n");
                    }
                } 
                else {
                    printf("Digite novamente.\n");
                }
            } 
            else {
                printf("Expressão Inválida.\n");
                printf("Digite novamente.\n");
            }

            //libera filas se foram criadas
            if (fila_infixa  != NULL) 
                liberar_fila(fila_infixa);
            if (fila_posfixa != NULL) 
                liberar_fila(fila_posfixa);
        } 
        else {
            printf("Digite novamente.\n");
        }
    }
    return 0;
}