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
    int subOperacao = 0;

    while (operacao != 1 && operacao != 2){
        scanf("%d", &operacao);
        if(operacao != 1 && operacao != 2){
            printf("Opção inválida, porfavor digite novamente\n");
        }
    }

    char *usuario;
    Grafo *grafo = inicializar();
    carregarNaMemoria(grafo);

    if(operacao == 1){
        do{
            printf("Digite o seu usuário: ");
            scanf("\n");

            usuario = readline(stdin);
            if(find_lista_name(grafo->all, usuario) != NULL) break;

            printf("Usuário inválido\n");
        } while (1);
        printf("Logado com sucesso!\n");

    } else if(operacao == 2) {
        registrar(grafo, &usuario);
    }

    int flag_loged = 0;

    while(usuario!=NULL){
        // system("clear");
        if(!flag_loged) {
            printf("Olá %s, escolha uma das opções:\n", usuario);
            flag_loged = 1;
        } else {
            printf("Escolha uma das opções:\n");
        }

        refreshGrafo(&grafo);
        printf("1 - Listar estudantes\n");
        printf("2 - Sugerir amizades\n");
        printf("3 - Checar amizades\n");
        printf("4 - Solicitações\n");
        printf("5 - Mostrar meu perfil\n");
        printf("6 - Logoff\n");
        printf("7 - Sair\n");
        scanf("%d", &operacao);

        if(operacao == 1){ //Listar estudantes.
            system("clear");
            printar_lista(grafo->all);
            whaitEnter();

        } else if(operacao == 2){ //Sugerir amizades.
            system("clear");
            sugerirAmizades(grafo, find_lista_name(grafo->all, usuario));
            printf("\nOpções:\n");
            printf("1 - Adicionar alguem\n");
            printf("2 - Voltar para o menu\n");
            scanf("%d", &subOperacao);
            if(subOperacao == 1){
                int index;
                printf("Digite o ID da pessoa que você quer adicionar: ");
                scanf("%d", &index);
                enviarSolicitacao(grafo, index, usuario);
                // printar_lista(grafo->all);
            }
        } else if(operacao == 4){
            system("clear");
            VERTICE *user_vertice = find_lista_name(grafo->all, usuario);
            printSolicitacoes(grafo, user_vertice->id);
            printf("\nOpções:\n");
            printf("1 - Adicionar alguem\n");
            printf("2 - Voltar para o menu\n");
            scanf("%d", &subOperacao);
            if(subOperacao == 1){
                int index;
                printf("Digite o índice correspondente a pessoa que você quer adicionar: ");
                scanf("%d", &index);
                aceitarSolicitacao(user_vertice->id, index, grafo);
                whaitEnter();
                // enviarSolicitacao(grafo, index, usuario);
                // printar_lista(grafo->all);
            }
        } else if(operacao == 5){ //Mostrar o perfil.
            system("clear");
            printVertice(find_lista_name(grafo->all, usuario));
            whaitEnter();

        } else if(operacao == 7){ //Fechar execução.
            printf("Tchau %s, até a próxima ;)\n", usuario);
            return 0;
        }
    }

    return 0; //Sucesso :)
}
