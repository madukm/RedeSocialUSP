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
#include "Estrutura.h"

//Lê e guarda a linha do que esta sendo inputado pelo teclado. A cada novo caractere mais memória 
//é alocada ao buffer que guarda a leitura.
char *readline(FILE *stream) { 
	char *string = 0;
	int pos = 0;
	do {
        if (pos % READLINE_BUFFER == 0) {
            string = (char *) realloc(string, (pos / READLINE_BUFFER + 1) * READLINE_BUFFER);
        }
	    string[pos] = (char) fgetc(stream);
	} while (string[pos++] != '\n' && !feof(stream));
	string[pos-1] = '\0';
	string = (char *) realloc(string, pos);
	if(pos==1){
	    free(string);
	}
	return (pos == 1)? NULL:string;
}

Grafo* inicializar (int n) { //Inicializando a lista de adjacência.
    Grafo* a = (Grafo*) malloc(sizeof(Grafo)); //Alocando memória.
    a->n_elementos = 0; //Guardando número de elementos.

    for (int i=0; i < n; i++){
        a->v[i] = criar_lista(); //Inicializando uma lista para o i-ésimo elemento.
        a->solicitacoes[i] = criar_lista();
    }
    a->all = criar_lista();

    return a; //Retornando um ponteiro para um grafo inicializado.
}

LISTA* criar_lista(){ //Inicializar uma lista.
    LISTA* list = (LISTA*)malloc(sizeof(LISTA)); //Alocando memória.
    list->inicial = NULL; 
    list->final = NULL;
    return list; //Retornando um ponteiro para uma lista inicializada.
}

VERTICE* criar_vertice(char *usuario, char *genero, char *filme_predileto , char *local_predileto,
char *hobby, char * livro, char *esporte, int idade, int id, char *solicitacoes, char *amizades){ 
    //Inicializando um vértice.
    VERTICE* vert = (VERTICE*)malloc(sizeof(VERTICE));
    vert->usuario = (char*) malloc(sizeof(char) * (strlen(usuario) + 1));
    strcpy(vert->usuario, usuario);
    vert->genero = (char*) malloc(sizeof(char) * (strlen(genero) + 1));
    strcpy(vert->genero, genero);
    vert->filme_predileto = (char*) malloc(sizeof(char) * (strlen(filme_predileto) + 1));
    strcpy(vert->filme_predileto, filme_predileto);
    vert->local_predileto = (char*) malloc(sizeof(char) * (strlen(local_predileto) + 1));
    strcpy(vert->local_predileto, local_predileto);
    vert->hobby = (char*) malloc(sizeof(char) * (strlen(hobby) + 1));
    strcpy(vert->hobby, hobby);
    vert->livro = (char*) malloc(sizeof(char) * (strlen(livro) + 1));
    strcpy(vert->livro, livro);
    vert->esporte = (char*) malloc(sizeof(char) * (strlen(esporte) + 1));
    strcpy(vert->esporte, esporte);
    vert->idade = idade;
    vert->id = id;
    vert->solicitacoes = (char*) malloc(sizeof(char) * (strlen(solicitacoes) + 1));
    strcpy(vert->solicitacoes, solicitacoes);
    vert->amizades = (char*) malloc(sizeof(char) * (strlen(amizades) + 1));
    strcpy(vert->amizades, amizades);
    vert->prox = NULL;
    return vert; //Retornando um ponteiro para um vértice inicializado.
}

VERTICE* copy_vertice(VERTICE *vertice){ //Copia os dados de um vértice.
    VERTICE* vert = (VERTICE*)malloc(sizeof(VERTICE));
    vert->usuario = (char*) malloc(sizeof(char) * (strlen(vertice->usuario) + 1));
    strcpy(vert->usuario, vertice->usuario);
    vert->genero = (char*) malloc(sizeof(char) * (strlen(vertice->genero) + 1));
    strcpy(vert->genero, vertice->genero);
    vert->filme_predileto = (char*) malloc(sizeof(char) * (strlen(vertice->filme_predileto) + 1));
    strcpy(vert->filme_predileto, vertice->filme_predileto);
    vert->local_predileto = (char*) malloc(sizeof(char) * (strlen(vertice->local_predileto) + 1));
    strcpy(vert->local_predileto, vertice->local_predileto);
    vert->hobby = (char*) malloc(sizeof(char) * (strlen(vertice->hobby) + 1));
    strcpy(vert->hobby, vertice->hobby);
    vert->livro = (char*) malloc(sizeof(char) * (strlen(vertice->livro) + 1));
    strcpy(vert->livro, vertice->livro);
    vert->esporte = (char*) malloc(sizeof(char) * (strlen(vertice->esporte) + 1));
    strcpy(vert->esporte, vertice->esporte);
    vert->idade = vertice->idade;
    vert->id = vertice->id;
    vert->solicitacoes = (char*) malloc(sizeof(char) * (strlen(vertice->solicitacoes) + 1));
    strcpy(vert->solicitacoes, vertice->solicitacoes);
    vert->amizades = (char*) malloc(sizeof(char) * (strlen(vertice->amizades) + 1));
    strcpy(vert->amizades, vertice->amizades);
    vert->prox = NULL;
    return vert; //Retornando um ponteiro para um vértice inicializado.
}

VERTICE* find_lista(LISTA* list, int ident){ //Procurar elemento na lista.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
		if (atual->id == ident) return atual; //Caso achemos o vértice desejado , retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

VERTICE* find_lista_name(LISTA* list, char* user){ //Procurar elemento na lista pelo nome de usuário.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
		if (strcmp(atual->usuario, user)==0) return atual; //Caso achemos o vértice desejado , retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

int lista_size(LISTA* list){ //Retorna o tamanho da lista.
    int cont = 0;
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        cont++;
        atual = atual->prox; //Indo para o proximo vértice.
	}
	return cont;
}

VERTICE* find_anterior_lista(LISTA* list, int ident){ //Procurar elemento anterior ao desejado, na lista.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual->prox) { //Percorrendo cada vértice da lista.
		if (atual->prox->id == ident) return atual; //Caso achemos o vértice desejado, retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

void inserir_lista(LISTA* list, int ident){ //Inserir elemento na lista.
    VERTICE *aux_ver = find_lista(list, ident);
    if (aux_ver != NULL) return; //Caso o vértice já exista, não precisamos o adicionar.

    VERTICE* ver = copy_vertice(aux_ver); //Inicializando um vértice.

    if (list->inicial==NULL){ //Caso não exista elementos na lista.
        list->inicial = ver;
        list->final = ver;
    } else if (list->inicial==list->final){ //Caso exista apenas um elemento na lista.
        list->final = ver;
        list->inicial->prox = ver;
    } else { //Caso exista mais de um elemento na lista.
        list->final->prox = ver;
        list->final = ver;
    }

    return;
}

void inserir_vertex_lista(LISTA* list, VERTICE *ver){ //Inserir elemento na lista.
    if (find_lista(list, ver->id) != NULL) return; //Caso o vértice já exista, não precisamos o adicionar.

    if (list->inicial==NULL){ //Caso não exista elementos na lista.
        list->inicial = ver;
        list->final = ver;
    } else if (list->inicial==list->final){ //Caso exista apenas um elemento na lista.
        list->final = ver;
        list->inicial->prox = ver;
    } else { //Caso exista mais de um elemento na lista.
        list->final->prox = ver;
        list->final = ver;
    }

    return;
}

void excluir_lista(LISTA* list, int ident){ //Excluir elemento da lista.
    VERTICE* ver = find_lista(list, ident); //Procurando o vértice na listsa.
    if (ver == NULL) return; //Caso o vértice não exista, não precisamos o excluir.

    if (list->inicial==list->final){ //Caso haja apenas um elemento na lista.
        list->final = NULL;
        list->inicial = NULL;
    } else if (ver == list->inicial){ //Caso o elemento a ser excluido seja o primeiro.
        list->inicial = list->inicial->prox;
    } else if (ver == list->final){ //Caso o elemento a ser excluido seja o último.
        list->final = find_anterior_lista(list, ident);
        list->final->prox = NULL;
    } else{ //Caso seja um elemento no meio da lista.
        VERTICE* ver_ant = find_anterior_lista(list, ident);
        ver_ant->prox = ver->prox;
    }

    free(ver); //Livrando memória do vértice excluido.

}

void printar_lista(LISTA* list) { //Imprimir a lista.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
		printf("usuario: %s\n",atual->usuario);
		printf("genero: %s\n",atual->genero);
		printf("filme_predileto: %s\n",atual->filme_predileto);
		printf("local_predileto: %s\n",atual->local_predileto);
		printf("hobby: %s\n",atual->hobby);
		printf("livro: %s\n",atual->livro);
		printf("esporte: %s\n",atual->esporte);
		printf("idade: %d\n",atual->idade);
		printf("id: %d\n",atual->id);
		printf("--------------------------------------\n");
        atual = atual->prox; //Indo para o proximo vértice.
	}
    printf("\n"); //Quebra de linha.
}

// void ligar_vertices(Grafo* a, int u, int v){ //Ligar dois vértices.
//     inserir_lista(a->v[v], u);  //Criando uma aresta que vai do vértice "u" até o "v".
//     inserir_lista(a->v[u], v); //Reciprocidade.
// }

void ligar_vertices(Grafo* a, VERTICE *u, VERTICE *v){ //Ligar dois vértices.
    inserir_vertex_lista(a->v[v->id], u);  //Criando uma aresta que vai do vértice "u" até o "v".
    inserir_vertex_lista(a->v[u->id], v); //Reciprocidade.
}

void desligar_vertices(Grafo* a, int u, int v){ //Retirar ligação entre dois vértices.
    excluir_lista(a->v[v], u); //Excluindo a aresta que vai do vértice "u" até o "v".
    excluir_lista(a->v[u], v); //Reciprocidade.
}

void print_grafo(Grafo* a) { //Imprimir a matriz de adjacência.
    for (int i=0;i<a->n_elementos;i++){
        printf("%d: ", i);
        printar_lista(a->v[i]); //Imprimindo a i-ésima lista.
    }
}

void limpar_lista(LISTA* list){ //Desalocar memória previamente alocada.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        free(atual); //Liberando memória.
        atual = atual->prox; //Indo para o próximo elemento.
	}
    atual = NULL; //Segurança.
    free(list); //Livrando memória.
    list = NULL;
}

void limpar_memoria(Grafo* a){ //Desalocar memória previamente alocada.
    for (int i=0;i<a->n_elementos;i++){ //Percorrendo a lista de adjacência.
        limpar_lista(a->v[i]); //Livrando memória da i-ésima lista.
    }
    free(a); //Livrando memória.
    a = NULL; //Segurança.
}

char *getPalavra(char *frase, int indexPalavra, int limit) { //Retorna a palvra de número "indexPalavra".

    char* palavraFinal = NULL;
    char* palavra; //Guarda a posição da palavra.
    int contadorPalavras = 0; //Indicador no número de palavras.
    int flag = 0; //Indica se começou uma palavra.
    for(int i=0;i<strlen(frase);i++){
        if(frase[i] != ' ' && flag==0){ //Caso seja um caractero válido, e ainda não tenha contabilizado a palavra
        //em questão.
            contadorPalavras++; //Soma-se a quantidade de palavras da frase.
            flag = 1; //Indica que a palavra em questão ja foi contabilizada.
            if(contadorPalavras==indexPalavra){
                flag = 2;
                palavra = &frase[i]; //Guardando a posição da palavra.
            } else if(contadorPalavras > indexPalavra){
                flag = 2;
            }
        } else if (frase[i] == ' ' && flag==1) { //Caso saia de uma palavra.
            flag = 0; //Indica que não está percorrendo uma palavra.
        } else if(frase[i] == ' ' && flag==2){ //Quando achar o final da palavra.
            if(contadorPalavras == limit){
                frase[i]='\0'; //Mudando o fim da palavra.
                palavraFinal = (char*) malloc(sizeof(char)* (strlen(palavra) + 1));
                strcpy(palavraFinal, palavra);
                frase[i]=' '; //Retornando a palavra final ao normal.
                free(frase);
                break;
            }
            flag = 0;
        } 
        
        if(i+1 == strlen(frase) && flag == 2){ //Caso seja a ultima palavra da frase.
            palavraFinal = (char*) malloc(sizeof(char)* (strlen(palavra) + 1));
            strcpy(palavraFinal, palavra);
            free(frase);
            break;
        }
    }

    return palavraFinal;
}

int getQuntidadePalavras(char* frase){  //Conta quantas palavras existem ao todo na string "frase".
    int contadorPalavras = 0; //Indicador no número de palavras.
    int flag = 0; //Indica se começou uma palavra.
    for(int i=0;i<strlen(frase);i++){
        if(frase[i] != ' ' && flag==0){ //Caso seja um caractero válido, e ainda não tenha contabilizado a palavra
        //em questão.
            contadorPalavras++; //Soma-se a quantidade de palavras da frase.
            flag = 1; //Indica que a palavra em questão ja foi contabilizada.
        } else if (frase[i] == ' ') { //Caso seja saia de uma palavra.
            flag = 0; //Indica que não está percorrendo uma palavra.
        }
    }
    return contadorPalavras; //Retornando a quantidade de palavras da frase.
}

void limpar_atributos(char *usuario, char *genero, char *filme_predileto , char *local_predileto,
char *hobby, char * livro, char *esporte, char *amigos, char *solicitacoes){ //Limpar memória.
    free(usuario);
    free(genero);
    free(filme_predileto);
    free(local_predileto);
    free(hobby);
    free(livro);
    free(esporte);
    free(amigos);
    free(solicitacoes);
}

void carregarNaMemoria(FILE *file, Grafo* grafo) { //Carregar informações do arquivo na memória.
    char *aux_leitura; //Vai receber cada linha do arquivo.
    while((aux_leitura = readline(file)) != NULL){ 

        char *usuario = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        char *genero = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        int idade = atoi(getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura)));
        aux_leitura = readline(file);
        char *filme_predileto = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        char *local_predileto = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        char *livro = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        char *hobby = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        char *esporte = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        int id = atoi(getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura)));
        char *solicitacoes = readline(file);
        char *amizades = readline(file);

        inserir_vertex_lista(grafo->all, criar_vertice(usuario, genero, filme_predileto, local_predileto, 
        hobby, livro, esporte, idade, id, solicitacoes, amizades)); 
        // for (int i=0;i<getQuntidadePalavras(solicitacoes)-1;i++){
        //     char *copy = malloc(strlen(solicitacoes) + 1);
        //     strcpy(copy, solicitacoes);
        // }

        // for (int i=1;i<=getQuntidadePalavras(amizades)-1;i++){
        //     char *copy = malloc(strlen(amizades) + 1);
        //     strcpy(copy, amizades);
        //     atoi(getPalavra(copy, i+1, i+1));
        //     find_lista();
        //     inserir_vertex_lista();
        // }
        limpar_atributos(usuario, genero, filme_predileto, local_predileto, hobby, livro, 
        esporte, amizades, solicitacoes);
    }

    return;
}

void registrar(FILE *bd, Grafo *grafo, char **usuario){ //Registar o usuário na rede social.
    printf("Escolha um nome de usuário: ");
    scanf("\n");
    *usuario = readline(stdin);

    printf("Qual o seu gênero? ");
    scanf("\n");
    char *genero = readline(stdin);
    
    printf("Qual a sua idade? ");
    scanf("\n");
    char *idade = readline(stdin);
    
    printf("Qual o seu filme predileto? ");
    scanf("\n");
    char *filme_predileto = readline(stdin);
    
    printf("Qual o seu local predileto? ");
    scanf("\n");
    char *local_predileto = readline(stdin);

    printf("Digite um livro que você gosta: ");
    scanf("\n");
    char *livro = readline(stdin);
    
    printf("Digite um hobby: ");
    scanf("\n");
    char *hobby = readline(stdin);
    
    printf("Digite um esporte que você gosta: ");
    scanf("\n");
    char *esporte = readline(stdin);
    
    bd = fopen("usuarios.txt", "a");
    fputs("\nusuario: ", bd);
    fputs(*usuario, bd);
    fputs("\ngenero: ", bd);
    fputs(genero, bd);
    fputs("\nidade: ", bd);
    fputs(idade, bd);
    fputs("\nfilme_predileto: ", bd);
    fputs(filme_predileto, bd);
    fputs("\nlocal_predileto: ", bd);
    fputs(local_predileto, bd);
    fputs("\nlivro: ", bd);
    fputs(livro, bd);
    fputs("\nhobby: ", bd);
    fputs(hobby, bd);
    fputs("\nesporte: ", bd);
    fputs(esporte, bd);
    char id[10];
    int int_id = lista_size(grafo->all) + 1;
    sprintf(id, "%d", int_id);
    fputs("\nid: ", bd);
    fputs(id, bd);
    fputs("\npedidos: ", bd);
    fputs("\namizades: ", bd);
    
    printf("Registrado com sucesso!\n");
    fclose(bd);
}

void ligarAmizadesPedidos(Grafo *grafo){ //Criar uma aresta entre todas as amizades e entre os pedidos.

    VERTICE* atual = grafo->all->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        for (int i=1;i<=getQuntidadePalavras(atual->amizades)-1;i++){
            char *copy = malloc(strlen(atual->amizades) + 1);
            strcpy(copy, atual->amizades);
            inserir_vertex_lista(grafo->v[atual->id], copy_vertice(find_lista(grafo->all, 
            atoi(getPalavra(copy, i+1, i+1)))));
        }

        for (int i=1;i<=getQuntidadePalavras(atual->solicitacoes)-1;i++){
            char *copy = malloc(strlen(atual->solicitacoes) + 1);
            strcpy(copy, atual->solicitacoes);
            inserir_vertex_lista(grafo->solicitacoes[atual->id], copy_vertice(find_lista(grafo->all, 
            atoi(getPalavra(copy, i+1, i+1)))));
        }
        
		atual = atual->prox; //Indo para o proximo vértice.
	}

}
