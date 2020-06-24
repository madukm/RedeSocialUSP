/*
*   Modelagem Computacional em Grafos
*
*   Aluno: Matheus Barcellos de Castro Cunha
*   NUSP: 11208238
*
*	Aluna: Maria Eduarda Kawakami Moreira
*	NUSP: 11218751
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "Estrutura.h"

int main () {

    printf("Bem vindx ao FacebUSP\n");
    printf("Escolha uma opção: \n");
    printf("1 - Login \n");
    printf("2 - Registrar \n");

    int operacao = 0;

    while (operacao != 1 && operacao != 2){
        scanf("%d", &operacao);
        if(operacao != 1 && operacao != 2){
            printf("Opção inválida, porfavor digite novamente\n");
        }
    }

    char *usuario;
    FILE *bd = fopen("usuarios.txt", "r");
    Grafo *grafo = inicializar(100);
    carregarNaMemoria(bd, grafo);
    ligarAmizadesPedidos(grafo);
    fclose(bd);

    if(operacao == 1){
        do{
            printf("Digite o seu usuário: ");
            scanf("\n");

            usuario = readline(stdin);
            if(find_lista_name(grafo->all, usuario) != NULL) break;

            printf("Usuário inválido\n");
        } while (1);
        printf("Logado com sucesso!\n");
        // printar_lista(grafo->all);

    } else if(operacao == 2) {
        registrar(bd, grafo, &usuario);
    }



    return 0; //Sucesso :)
}
