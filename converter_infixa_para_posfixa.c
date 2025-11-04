// converter_infixa_para_posfixa.c
#include <stdio.h>
#include "pilha.h"
#include "fila.h"
#include "regra_operadores.h"
#include "converter_infixa_para_posfixa.h"

int converter_infixa_para_posfixa(Fila *fila_entrada, Fila *fila_posfixa) {
    Pilha *pilha_operadores = criar_pilha();
    if (pilha_operadores == NULL) {
        return 0;
    }

    while (!fila_vazia(fila_entrada)) {
        int item = desenfileirar(fila_entrada);

        // 1. É número (>=0)
        if (item >= 0) {
            enfileirar(fila_posfixa, item);
        }
        
        // 2. É operador/parêntese (< 0)
        else {
            char operador = (char)(-item);

            // 2a. Abre parêntese: empilha
            if (operador == '(') {
                empilhar(pilha_operadores, (int)operador);
            }

            // 2b. Fecha parêntese: desempilha até achar '('
            else if (operador == ')') {
                int achou_abre = 0;
                while (!pilha_vazia(pilha_operadores)) {
                    char operador_no_topo = (char) pilha_operadores->dados[pilha_operadores->topo];
                    if (operador_no_topo == '(') {
                        (void)desempilhar(pilha_operadores); // descarta '('
                        achou_abre = 1;
                        break;
                    } else {
                        // manda operador do topo para a fila pós-fixa
                        enfileirar(fila_posfixa, -(int)operador_no_topo);
                        (void)desempilhar(pilha_operadores);
                    }
                }
                if (!achou_abre) {
                    printf("Expressão Inválida.\n");
                    liberar_pilha(pilha_operadores);
                    return 0;
                }
            }

            // 2c. Operador normal: + - * / ^
            else if (operador == '+' || operador == '-' || operador == '*' ||
                     operador == '/' || operador == '^') {

                int forca_atual = precedencia_do_operador(operador);

                // desempilha enquanto o topo for operador mais forte (ou mesma força para esquerda)
                while (!pilha_vazia(pilha_operadores)) {
                    char operador_no_topo = (char) pilha_operadores->dados[pilha_operadores->topo];

                    if (operador_no_topo == '(') {
                        break; // não atravessa '('
                    }

                    int forca_topo = precedencia_do_operador(operador_no_topo);

                    int deve_desempilhar = 0;
                    if (forca_topo > forca_atual) {
                        deve_desempilhar = 1;
                    } else if (forca_topo == forca_atual) {
                        if (operador == '^') {
                            // associatividade à DIREITA -> não desempilha quando mesma força
                            deve_desempilhar = 0;
                        } else {
                            // + - * / são à ESQUERDA -> desempilha quando mesma força
                            deve_desempilhar = 1;
                        }
                    } else {
                        deve_desempilhar = 0;
                    }

                    if (!deve_desempilhar) break;

                    // manda topo para a pós-fixa
                    enfileirar(fila_posfixa, -(int)operador_no_topo);
                    (void)desempilhar(pilha_operadores);
                }

                // empilha o operador atual
                empilhar(pilha_operadores, (int)operador);
            }
            
            // 2d. Caractere inválido
            else {
                printf("Expressão Inválida.\n");
                liberar_pilha(pilha_operadores);
                return 0;
            }
        }
    }

    // joga fora o que sobrou na pilha (só devem sobrar operadores)
    while (!pilha_vazia(pilha_operadores)) {
        char operador_no_topo = (char) pilha_operadores->dados[pilha_operadores->topo];
        (void)desempilhar(pilha_operadores);

        if (operador_no_topo == '(' || operador_no_topo == ')') {
            // parênteses desbalanceados
            printf("Expressão Inválida.\n");
            liberar_pilha(pilha_operadores);
            return 0;
        }

        enfileirar(fila_posfixa, -(int)operador_no_topo);
    }

    liberar_pilha(pilha_operadores);
    return 1;
}