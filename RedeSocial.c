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
#include "Grafo.h"
#include "Lista.h"
#include "utils.h"

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
		printf("6 - Listar extrovertidos e introvertidos\n");
		printf("7 - Logoff\n");
        printf("8 - Sair\n");
		scanf("%d", &operacao);
		switch(operacao){
			case 1:
				system("clear");
            	printar_lista(get_all(grafo));
            	whaitEnter();
				break;
			case 2:
				system("clear");
            	sugerirAmizades(grafo, find_lista_name(get_all(grafo), usuario));
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
				break;
			case 4:
				system("clear");
            	VERTICE *user_vertice = find_lista_name(get_all(grafo), usuario);
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
				break;
			case 5:
				system("clear");
            	printVertice(find_lista_name(get_all(grafo), usuario));
            	whaitEnter();
				break;
			case 6:
				system("clear");
				extroIntro(grafo);
				break;
			case 8:
				printf("Tchau %s, até a próxima ;)\n", usuario);
            	free(usuario);
            	limpar_memoria_grafo(grafo);
            	return 0;
			default:
				break;
		}		
    }

    return 0; //Sucesso :)
}
