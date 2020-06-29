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

/**
 * TAD Lista
 */

#include "Lista.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vertice{
    char *usuario;
    char *genero;
    char *filme_predileto;
    char *local_predileto;
    char *hobby;
    char *livro;
    char *esporte;
    int idade;
    int id;
    int afinidade;
    char *solicitacoes;
    char *amizades;
    struct Vertice *prox;
};

struct Lista{
    VERTICE *inicial;
    VERTICE *final;
};

//Inicializa uma lista.
LISTA* criar_lista() {
    LISTA* list = (LISTA*)malloc(sizeof(LISTA));
    if(list != NULL){
		list->inicial = NULL; 
    	list->final = NULL;
	}
	return list; //Retornando um ponteiro para uma lista inicializada.
}

//Retorna o tamanho da lista.
int lista_size(LISTA* list){
    int cont = 0;
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        cont++;
        atual = atual->prox; //Indo para o proximo vértice.
	}
	return cont;
}

//Excluir elemento da lista a partir do id.
void excluir_lista(LISTA* list, int ident){
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

//Imprimir a lista.
void printar_lista(LISTA* list) {

    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
		printf("--------------------------------------\n");
		printf("Usuário: %s\n",atual->usuario);
		printf("Gênero: %s\n",atual->genero);
		printf("Filme predileto: %s\n",atual->filme_predileto);
		printf("Local predileto: %s\n",atual->local_predileto);
		printf("Hobby: %s\n",atual->hobby);
		printf("Livro: %s\n",atual->livro);
		printf("Esporte: %s\n",atual->esporte);
		printf("Idade: %d\n",atual->idade);
		printf("%s\n",atual->solicitacoes);
		// printf("id: %d\n",atual->id);
        atual = atual->prox; //Indo para o proximo vértice.
	}
    printf("\n");
}


//Free lista.
void limpar_lista(LISTA* list){
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        free(atual->usuario);
        free(atual->genero);
        free(atual->filme_predileto);
        free(atual->local_predileto);
        free(atual->hobby);
        free(atual->livro);
        free(atual->esporte);
        free(atual->solicitacoes);
        free(atual->amizades);
		VERTICE *aux = atual->prox;
		free(atual);
		atual = aux;	
	}
    free(list); //Livrando memória.
}

//Copia os dados de um vértice.
VERTICE* copy_vertice(VERTICE *vertice, int afinidade){
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
    vert->afinidade = afinidade;
    vert->solicitacoes = (char*) malloc(sizeof(char) * (strlen(vertice->solicitacoes) + 1));
    strcpy(vert->solicitacoes, vertice->solicitacoes);
    vert->amizades = (char*) malloc(sizeof(char) * (strlen(vertice->amizades) + 1));
    strcpy(vert->amizades, vertice->amizades);
    vert->prox = NULL;
    return vert; //Retornando um ponteiro para um vértice inicializado.
}

//Procurar elemento na lista.
VERTICE* find_lista(LISTA* list, int ident){
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
		if (atual->id == ident) return atual; //Caso achemos o vértice desejado , retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

//Procurar elemento na lsita pelo nome de usuário.
VERTICE* find_lista_name(LISTA* list, char* user){
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
		if (strcmp(atual->usuario, user)==0) return atual; //Caso achemos o vértice desejado , retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

//Procurar elemento anterior ao desejado, na lista.
VERTICE* find_anterior_lista(LISTA* list, int ident){
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual->prox) { //Percorrendo cada vértice da lista.
		if (atual->prox->id == ident) return atual; //Caso achemos o vértice desejado, retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

//Inserir elemento na lista.
void inserir_lista(LISTA* list, int ident){
    VERTICE *aux_ver = find_lista(list, ident);
    if (aux_ver != NULL) return; //Caso o vértice já exista, não precisamos o adicionar.

    VERTICE* ver = copy_vertice(aux_ver, -1); //Inicializando um vértice.

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

//Inserir elemento na lista.
void inserir_vertex_lista(LISTA* list, VERTICE *ver){
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

//Printar as informações do vértice.
void printVertice(VERTICE *vertice){
    printf("Usuário: %s\n",vertice->usuario);
    printf("Gênero: %s\n",vertice->genero);
    printf("Filme predileto: %s\n",vertice->filme_predileto);
    printf("Local predileto: %s\n",vertice->local_predileto);
    printf("Hobby: %s\n",vertice->hobby);
    printf("Livro: %s\n",vertice->livro);
    printf("Esporte: %s\n",vertice->esporte);
    printf("Idade: %d\n",vertice->idade);
}

//Cria um vértice.
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
    vert->afinidade = -1;
    vert->solicitacoes = (char*) malloc(sizeof(char) * (strlen(solicitacoes) + 1));
    strcpy(vert->solicitacoes, solicitacoes);
    vert->amizades = (char*) malloc(sizeof(char) * (strlen(amizades) + 1));
    strcpy(vert->amizades, amizades);
    vert->prox = NULL;
    return vert; //Retornando um ponteiro para um vértice inicializado.
}

//GETTERS
VERTICE *get_inicial(LISTA *list){
	return list->inicial;
}

VERTICE *get_final(LISTA *list){
	return list->final;
}

int get_id(VERTICE *vert){
	return vert->id;
}

char *get_usuario(VERTICE *vert){
	return vert->usuario;
}

char *get_livro(VERTICE *vert){
	return vert->livro;
}

char *get_genero(VERTICE *vert){
	return vert->genero;
}

char *get_filme_predileto(VERTICE *vert){
	return vert->filme_predileto;
}

char *get_local_predileto(VERTICE *vert){
	return vert->local_predileto;
}

char *get_hobby(VERTICE *vert){
	return vert->hobby;
}

char *get_esporte(VERTICE *vert){
	return vert->esporte;
}

int get_idade(VERTICE *vert){
	return vert->idade;
}

int get_afinidade(VERTICE *vert){
	return vert->afinidade;
}

char *get_amizades(VERTICE *vert){
	return vert->amizades;
}

char *get_solicitacoes(VERTICE *vert){
	return vert->solicitacoes;
}

VERTICE *get_prox(VERTICE *vert){
	return vert->prox;
}

void set_amizades(VERTICE *vert, char *amizades){
    vert->amizades = amizades;
	// strcpy(vert->amizades, amizades);
}

void set_solicitacoes(VERTICE *vert, char *solicitacoes){
    vert->solicitacoes = solicitacoes;
}
