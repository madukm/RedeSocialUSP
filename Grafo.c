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

#include "Lista.h"
#include "Grafo.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct grafo{
    LISTA* amizades[MAXN];
    LISTA* solicitacoes[MAXN];
    LISTA* all;
    int n_elementos;
};

//Inicializando o grafo.
Grafo* inicializar_grafo() {
	Grafo* a = (Grafo*) malloc(sizeof(Grafo)); //Alocando memória.
	if(a != NULL){
		a->n_elementos = 0;
    	for (int i=0; i<MAXN; i++){
        	a->amizades[i] = criar_lista(); //Inicializando uma lista para o i-ésimo elemento.
        	a->solicitacoes[i] = criar_lista();
    	}
    	a->all = criar_lista();
	}

    return a; //Retornando um ponteiro para um grafo inicializado.
}

//Free grafo.
void limpar_memoria_grafo(Grafo* a){
    for (int i=0; i<MAXN; i++){ //Percorrendo a lista de adjacência.
        limpar_lista(a->amizades[i]); //Livrando memória da i-ésima lista.
        limpar_lista(a->solicitacoes[i]); //Livrando memória da i-ésima lista.
    }

    limpar_lista(a->all); //Livrando memória da lista principal.
    free(a); //Livrando memória.
}


//Atualiza o grafo com as informações do arquivo.
void refreshGrafo(Grafo **grafo) {
	limpar_memoria_grafo(*grafo);
    *grafo = inicializar_grafo();
    carregarNaMemoria(*grafo);
}

//Carregar informações do arquivo na memória.
void carregarNaMemoria(Grafo* grafo) {
   
    int contador = 0;
    FILE *file = fopen("usuarios.txt", "r");
    char *aux_leitura; //Vai receber cada linha do arquivo.
    while((aux_leitura = readline(file)) != NULL){ 
        char *usuario = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        char *genero = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        aux_leitura = readline(file);
        char *char_idade = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        int idade = atoi(char_idade);
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
        char *char_id = getPalavra(aux_leitura, 2, getQuntidadePalavras(aux_leitura));
        int id = atoi(char_id);
        char *solicitacoes = readline(file);
        char *amizades = readline(file);
        contador++;
        grafo->n_elementos = contador;

        inserir_vertex_lista(grafo->all, criar_vertice(usuario, genero, filme_predileto, local_predileto, 
        hobby, livro, esporte, idade, id, solicitacoes, amizades)); 

        limpar_atributos(usuario, genero, filme_predileto, local_predileto, hobby, livro, 
        esporte, amizades, solicitacoes, char_idade, char_id);
    }

    ligarAmizadesPedidos(grafo);

    fclose(file);

    return;
}

//Escrever dados atualizados no arquivo.
void writeFile(Grafo *grafo) {

    FILE *bd = fopen("usuarios.txt", "r+");

    VERTICE* atual = grafo->all->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        fputs("usuario: ", bd);
        fputs(atual->usuario, bd);
        fputs("\ngenero: ", bd);
        fputs(atual->genero, bd);
        fputs("\nidade: ", bd);
        char idade[10];
        int int_idade = atual->idade;
        sprintf(idade, "%d", int_idade);
        fputs(idade, bd);
        fputs("\nfilme_predileto: ", bd);
        fputs(atual->filme_predileto, bd);
        fputs("\nlocal_predileto: ", bd);
        fputs(atual->local_predileto, bd);
        fputs("\nlivro: ", bd);
        fputs(atual->livro, bd);
        fputs("\nhobby: ", bd);
        fputs(atual->hobby, bd);
        fputs("\nesporte: ", bd);
        fputs(atual->esporte, bd);
        char id[10];
        int int_id = atual->id;
        sprintf(id, "%d", int_id);
        fputs("\nid: ", bd);
        fputs(id, bd);
        fputs("\n", bd);
        fputs(atual->solicitacoes, bd);
        fputs("\n", bd);
        fputs(atual->amizades, bd);
        if(atual->prox != NULL) fputs("\n", bd);
		atual = atual->prox; //Indo para o proximo vértice.
	}
    
    fclose(bd);
}

// Imprimir a matriz de adjacência
void print_grafo(Grafo* a) {
    for (int i=0; i<a->n_elementos; i++){
        printf("%d: ", i);
        printar_lista(a->amizades[i]); //Imprimindo a i-ésima lista.
    }
}

//TODO: Arrumar essas duas funções
//Ligar dois vértices.
void ligar_vertices(Grafo* a, VERTICE *u, VERTICE *v){
	//inserir_vertex_lista(a->v[v->id], u);  //Criando uma aresta que vai do vértice "u" até o "v".
    //inserir_vertex_lista(a->v[u->id], v); //Reciprocidade.
}

//Quebrar ligação entre dois vértices.
void desligar_vertices(Grafo* a, int u, int v){
	//excluir_lista(a->v[v], u); //Excluindo a aresta que vai do vértice "u" até o "v".
    //excluir_lista(a->v[u], v); //Reciprocidade.
}

void limpar_atributos(char *usuario, char *genero, char *filme_predileto , char *local_predileto,
char *hobby, char * livro, char *esporte, char *amigos, char *solicitacoes, char *char_idade, char *char_id){ //Limpar memória.
    free(usuario);
    free(genero);
    free(filme_predileto);
    free(local_predileto);
    free(hobby);
    free(livro);
    free(esporte);
    free(amigos);
    free(solicitacoes);
    free(char_idade);
    free(char_id);
}

//Registra o usuário na rede social.
void registrar(Grafo *grafo, char **usuario){
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
    
    FILE *bd = fopen("usuarios.txt", "a");
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

// Criar uma aresta entre todas as amizades e entre os pedidos.
void ligarAmizadesPedidos(Grafo *grafo) {
	
	VERTICE* atual = grafo->all->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        for (int i=1;i<=getQuntidadePalavras(atual->amizades)-1;i+=2){
            char *copy = malloc(strlen(atual->amizades) + 1);
            char *copy2 = malloc(strlen(atual->amizades) + 1);
            strcpy(copy, atual->amizades);
            strcpy(copy2, atual->amizades);
            char *vert_id = getPalavra(copy, i+1, i+1);
            char *vert_afinidade = getPalavra(copy2, i+2, i+2);
            VERTICE *aux = find_lista(grafo->all, atoi(vert_id));
            VERTICE *copy_vert = copy_vertice(aux, atoi(vert_afinidade));
            inserir_vertex_lista(grafo->amizades[atual->id], copy_vert);
            free(vert_id);
            free(vert_afinidade);
        }

        for (int i=1;i<=getQuntidadePalavras(atual->solicitacoes)-1;i+=2){
            char *copy = malloc(strlen(atual->solicitacoes) + 1);
            char *copy2 = malloc(strlen(atual->solicitacoes) + 1);
            strcpy(copy, atual->solicitacoes);
            strcpy(copy2, atual->solicitacoes);
            char *vert_id = getPalavra(copy, i+1, i+1);
            char *vert_afinidade = getPalavra(copy2, i+2, i+2);
            VERTICE *aux = find_lista(grafo->all, atoi(vert_id));
            VERTICE *copy_vert = copy_vertice(aux, atoi(vert_afinidade));
            inserir_vertex_lista(grafo->solicitacoes[atual->id], copy_vert);
            free(vert_id);
            free(vert_afinidade);
        }

		atual = atual->prox; //Indo para o proximo vértice.
	}
}

// Faz um match com usuários da rede.
void sugerirAmizades(Grafo *grafo, VERTICE *vert) {

    VERTICE* atual = grafo->all->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
        int afinidade = 0;

        if(!strcmp(atual->livro, vert->livro)) afinidade++; 
        if(!strcmp(atual->filme_predileto, vert->filme_predileto)) afinidade++;
        if(!strcmp(atual->local_predileto, vert->local_predileto)) afinidade++;
        if(!strcmp(atual->esporte, vert->esporte)) afinidade++;
        if(!strcmp(atual->hobby, vert->hobby)) afinidade++;

        afinidade *= 20;

        if(afinidade >= 20){
            printf("%d - Usuário: %s\tAfinidade: %d%% \n", atual->id, atual->usuario, afinidade);
        }

        atual = atual->prox; //Indo para o proximo vértice.
	}
}

//Enviar solicitação de amizade para um usuário.
void enviarSolicitacao(Grafo *grafo, int id, char* usuario) {

    VERTICE *user = find_lista_name(grafo->all, usuario);
    VERTICE *atual = grafo->all->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
        if(atual->id == id){
            if(find_lista_name(grafo->solicitacoes[id], usuario)!=NULL){
                printf("Você já enviou uma solicitação para essa pessoa.\n");
                whaitEnter();
                return;
            }
            char aux_char[10];
            sprintf(aux_char, " %d", user->id);
            atual->solicitacoes = concatenar(atual->solicitacoes, aux_char);

            int afinidade = 0;
            if(!strcmp(atual->livro, user->livro)) afinidade++; 
            if(!strcmp(atual->filme_predileto, user->filme_predileto)) afinidade++;
            if(!strcmp(atual->local_predileto, user->local_predileto)) afinidade++;
            if(!strcmp(atual->esporte, user->esporte)) afinidade++;
            if(!strcmp(atual->hobby, user->hobby)) afinidade++;
            afinidade *= 20;

            sprintf(aux_char, " %d", afinidade);
            atual->solicitacoes = concatenar(atual->solicitacoes, aux_char);
            inserir_vertex_lista(grafo->solicitacoes[id], copy_vertice(user, afinidade));
        }

        atual = atual->prox; //Indo para o proximo vértice.
	}

    writeFile(grafo);
    printf("Solicitação enviada :)\n");
    whaitEnter();

}

void printSolicitacoes(Grafo *grafo, int id){ //Printar as solicitações de amizade ao usuário.
    int contador = 0;
    VERTICE* atual = grafo->solicitacoes[id]->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
        contador++;
		printf("%d - Usuário: %s\tAfinidade: %d%%\n",contador, atual->usuario, atual->afinidade);
        atual = atual->prox; //Indo para o proximo vértice.
	}
}

void aceitarSolicitacao(int id, int index, Grafo *grafo){ //Aceitar uma solicitação de amizade.
    int contador = 0;
    VERTICE *usuario_ver = find_lista(grafo->all, id);
    VERTICE *atual = grafo->solicitacoes[id]->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (contador != index-1) { //Enquanto existir um atual, isso é, "atual != NULL"
        contador++;
        atual = atual->prox; //Indo para o proximo vértice.
	}

    index *= 2;

    char aux_char[20];
    sprintf(aux_char, " %d %d", atual->id, atual->afinidade);

    usuario_ver->solicitacoes = apagarPalavra(index, index+1, usuario_ver->solicitacoes);
    usuario_ver->amizades = concatenar(usuario_ver->amizades, aux_char);


    sprintf(aux_char, " %d %d", usuario_ver->id, atual->afinidade);

    atual = find_lista(grafo->all, atual->id);
    atual->amizades = concatenar(atual->amizades, aux_char);

    writeFile(grafo);
}

//GETTERS
LISTA *get_all(Grafo *g){
	return g->all;
}

LISTA *get_amizades(Grafo *g, int i){
	return g->amizades[i];
}

LISTA *get_solicitacoes(Grafo *g, int i){
	return g->solicitacoes[i];
}
