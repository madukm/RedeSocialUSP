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
#include <string.h>

#include "Grafo.h"
#include "Lista.h"
#include "Fila.h"
#include "utils.h"

int main () {

    while(1){
        system("clear");
        printf("Bem vindx ao FacebUSP\n");
        printf("Escolha uma opção: \n");
        printf("1 - Login \n");
        printf("2 - Registrar \n");

        int operacao = 0;
        int subOperacao = 0;

        while (operacao != 1 && operacao != 2){
            scanf("%d", &operacao);
            if(operacao != 1 && operacao != 2){
                printf("Opção inválida, por favor digite novamente\n");
            }
        }

        char *usuario;
        Grafo *grafo = inicializar_grafo();
        carregarNaMemoria(grafo);

        if(operacao == 1){
            do{
                printf("Digite o seu usuário: ");
                scanf("\n");

                usuario = readline(stdin);
                if(find_lista_name(get_all(grafo), usuario) != NULL) break;

                printf("Usuário inválido\n");
            } while (1);
            printf("Logado com sucesso!\n");

        } else if(operacao == 2) {
            registrar(grafo, &usuario);
        }

        int flag_loged = 0;

        while(usuario != NULL){
            system("clear");
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
            printf("5 - Adicionar amigo\n");
            printf("6 - Mostrar meu perfil\n");
            printf("7 - Atualizar perfil\n");
			printf("8 - Listar extrovertidos e introvertidos\n");
            printf("9 - Logoff\n");
            printf("10 - Sair\n");
            scanf("%d", &operacao);
            switch(operacao){
                case 1:
                    system("clear");
                    printar_lista(get_all(grafo));
                    whaitEnter();
                    break;
                case 2:{
                    system("clear");
                    int id_user = get_id(find_lista_name(get_all(grafo), usuario));
                    int *visitados = (int *) calloc(MAXN, sizeof(int));
                    QUEUE *q = criar_queue();
                    insert(q, id_user, 0);
                    bfsSugestao(grafo, q, id_user, &visitados);
                    limpar_fila(q);
                    free(visitados);
                    printf("\nOpções:\n");
                    printf("1 - Adicionar alguem\n");
                    printf("2 - Voltar para o menu\n");
                    scanf("%d", &subOperacao);
                    if(subOperacao == 1){
                        int index;
                        printf("Digite o ID da pessoa que você quer adicionar: ");
                        scanf("%d", &index);
                        enviarSolicitacao(grafo, index, usuario);
                    }
                    break;
                }
                case 3:{
                    system("clear");
                    checarAmizades(grafo, usuario);
                    whaitEnter();
                    break;
                }
                case 4:{
                    system("clear");
                    VERTICE *user_vertice = find_lista_name(get_all(grafo), usuario);
                    printSolicitacoes(grafo, get_id(user_vertice));
                    printf("\nOpções:\n");
                    printf("1 - Aceitar solicitação\n");
                    printf("2 - Rejeitar solicitação\n");
                    printf("3 - Voltar para o menu\n");
                    scanf("%d", &subOperacao);
                    if(subOperacao == 1){
                        int index;
                        printf("Digite o índice correspondente a pessoa que você quer adicionar: ");
                        scanf("%d", &index);
                        aceitarSolicitacao(get_id(user_vertice), index, grafo);
                        whaitEnter();
                        // enviarSolicitacao(grafo, index, usuario);
                        // printar_lista(grafo->all);
                    } else if(subOperacao == 2){
                        int index;
                        printf("Digite o índice correspondente a solicitação que você deseja rejeitar: ");
                        scanf("%d", &index);
                        rejeitarSolicitacao(get_id(user_vertice), index, grafo);
                        whaitEnter();
                    }
                    break;
                }
                case 5:{
                    while(1) {
                        system("clear");
                        printf("Opções:\n");
                        printf("1 - Voltar para a tela inicial\n");
                        printf("Digite o nome do usuário que deseja adicionar: ");
                        scanf(" ");
                        char *target = readline(stdin);
                        if(strcmp(target, "1")==0){
                            free(target);
                            break;
                        } else if(!enviarSolicitacaoNome(usuario, target, grafo)){
                            free(target);
                            break;
                        }
                        free(target);
                        printf("Usuário invalido!\n");
                    }
                    break;
                }
                case 6:
                    system("clear");
                    printVertice(find_lista_name(get_all(grafo), usuario));
                    whaitEnter();
                    break;
				case 7:{
			   	   	system("clear");
					int op;
					while(1){
	                    printf("\nOpções:\n");
    	                printf("1 - Atualizar algo do perfil\n");
        	            printf("2 - Voltar para o menu\n");
 						scanf("%d", &op);
						if(op == 1)
							atualizarPerfil(grafo, usuario);
						else break;
					}
					break;
				}
				case 8:{
                    system("clear");
                    int id_user = get_id(find_lista_name(get_all(grafo), usuario));
                    int *visitados = (int *) calloc(MAXN, sizeof(int));
                    int *max = (int *) calloc(MAXN, sizeof(int));
                    int *trueFriends = (int *) calloc(MAXN, sizeof(int));
                    dfsExtroIntro(grafo, id_user, &visitados, &max, &trueFriends);
                    free(visitados);
                    free(max);
                    free(trueFriends);
                    whaitEnter();
                    break;
                }
                case 9:
                    free(usuario);
                    limpar_memoria_grafo(grafo);
                    usuario = NULL;
                    break;
                case 10:
                    printf("Tchau %s, até a próxima ;)\n", usuario);
                    free(usuario);
                    limpar_memoria_grafo(grafo);
                    return 0;
                default:
                    break;
            }       
        }
    }

    return 0; //Sucesso :)
}
