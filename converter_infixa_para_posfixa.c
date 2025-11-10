//Trabalho Estrutura de Dados

//Grupo: 
//Tiago Mello - 23014024
//Vinicius Nunes - 23011585

//etapa 3: converter a expressão infixa para pós-fixa

#include <stdio.h>
#include "pilha.h"
#include "fila.h"
#include "regra_operadores.h"
#include "converter_infixa_para_posfixa.h"

//função: converter infixa -> pós-fixa
int converter_infixa_para_posfixa(Fila *fila_entrada, Fila *fila_posfixa) {
    //cria a pilha que será usada para armazenar os operadores
    Pilha *pilha_operadores = criar_pilha();
    if (pilha_operadores == NULL) {
        return 0;
    }

    //loop que processa cada item da fila infixa
    while (!fila_vazia(fila_entrada)) {
        int item = desenfileirar(fila_entrada);
        //se for número
        if (item >= 0) {
            enfileirar(fila_posfixa, item);
        }
        
        //se for caractere
        else {
            char operador = (char)(-item);
            //lógica de abrir parênteses
            if (operador == '(') {
                //sempre que abrir parêntese é empilhado.
                empilhar(pilha_operadores, operador);
            }

            //lógica de fechar parênteses
            else if (operador == ')') {
                int achou_abre = 0;
                //desempilha e enfileira tudo até achar o parênteses que abre
                while (!pilha_vazia(pilha_operadores)) {
                    char operador_no_topo = pilha_operadores->dados[pilha_operadores->topo];
                    if (operador_no_topo == '(') {
                        desempilhar(pilha_operadores); // descarta (
                        achou_abre = 1;
                        break;
                    } 
                    else {
                        //operador do topo para a fila pós-fixa
                        enfileirar(fila_posfixa, -(int)operador_no_topo);
                        desempilhar(pilha_operadores);
                    }
                }
                //validacão se não achar o parênteses que abre
                if (!achou_abre) {
                    printf("ERRO. Expressão Inválida.\n");
                    liberar_pilha(pilha_operadores);
                    return 0;
                }
            }

            //lógica dos operadores normais
            else if (operador == '+' || operador == '-' || operador == '*' || operador == '/' || operador == '^') {
                int forca_atual = precedencia_do_operador(operador);

                //compara a força do operador atual com o operador no topo
                while (!pilha_vazia(pilha_operadores)) {
                    char operador_no_topo = pilha_operadores->dados[pilha_operadores->topo];
                    if (operador_no_topo == '(') {
                        break;
                    }
                    int forca_topo = precedencia_do_operador(operador_no_topo);
                    int deve_desempilhar = 0;

                    //se o do topo for mais forte, desempilha
                    if (forca_topo > forca_atual) {
                        deve_desempilhar = 1;
                    } 
                    //se tiverem a mesma força
                    else if (forca_topo == forca_atual) {
                        if (operador == '^') {
                            //não desempilha, ^ é do número da direita
                            deve_desempilhar = 0;
                        } else {
                            //desempilha, eles são do número da esquerda
                            deve_desempilhar = 1;
                        }
                    } 
                    else {
                        deve_desempilhar = 0;
                    }
                    if (!deve_desempilhar) 
                        break;

                    //desempilha o operador do topo para a fila pós-fixa
                    enfileirar(fila_posfixa, -(int)operador_no_topo);
                    desempilhar(pilha_operadores);
                }

                // empilha o operador atual
                empilhar(pilha_operadores, (int)operador);
            }
            else {
                printf("Expressão Inválida.\n");
                liberar_pilha(pilha_operadores);
                return 0;
            }
        }
    }

    //joga o que sobrou na pilha para a fila de pós-fixa
    while (!pilha_vazia(pilha_operadores)) {
        char operador_no_topo = (char) pilha_operadores->dados[pilha_operadores->topo];
        desempilhar(pilha_operadores);
        if (operador_no_topo == '(' || operador_no_topo == ')') {
            printf("Expressão Inválida.\n");
            liberar_pilha(pilha_operadores);
            return 0;
        }
        //operador restante para o final da fila pós-fixa
        enfileirar(fila_posfixa, -(int)operador_no_topo);
    }

    liberar_pilha(pilha_operadores);
    return 1;
}