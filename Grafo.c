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
#include "Fila.h"

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

    FILE *bd = fopen("usuarios.txt", "w");

    VERTICE* atual = get_inicial(grafo->all); //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        fputs("usuario: ", bd);
        fputs(get_usuario(atual), bd);
        fputs("\ngenero: ", bd);
        fputs(get_genero(atual), bd);
        fputs("\nidade: ", bd);
        char idade[10];
        int int_idade = get_idade(atual);
        sprintf(idade, "%d", int_idade);
        fputs(idade, bd);
        fputs("\nfilme_predileto: ", bd);
        fputs(get_filme_predileto(atual), bd);
        fputs("\nlocal_predileto: ", bd);
        fputs(get_local_predileto(atual), bd);
        fputs("\nlivro: ", bd);
        fputs(get_livro(atual), bd);
        fputs("\nhobby: ", bd);
        fputs(get_hobby(atual), bd);
        fputs("\nesporte: ", bd);
        fputs(get_esporte(atual), bd);
        char id[10];
        int int_id = get_id(atual);
        sprintf(id, "%d", int_id);
        fputs("\nid: ", bd);
        fputs(id, bd);
        fputs("\n", bd);
        fputs(get_solicitacoes(atual), bd);
        fputs("\n", bd);
        fputs(get_amizades(atual), bd);
        if(get_prox(atual) != NULL) fputs("\n", bd);
		atual = get_prox(atual); //Indo para o proximo vértice.
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
    fputs("\npedidos:", bd);
    fputs("\namizades:", bd);
    
    free(genero);
    free(idade);
    free(filme_predileto);
    free(local_predileto);
    free(livro);
    free(hobby);
    free(esporte);

    printf("Registrado com sucesso!\n");
    fclose(bd);
}

// Criar uma aresta entre todas as amizades e entre os pedidos.
void ligarAmizadesPedidos(Grafo *grafo) {
	
	VERTICE* atual = get_inicial(grafo->all); //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        for (int i=1;i<=getQuntidadePalavras(get_amizades(atual))-1;i+=2){
            char *copy = malloc(strlen(get_amizades(atual)) + 1);
            char *copy2 = malloc(strlen(get_amizades(atual)) + 1);
            strcpy(copy, get_amizades(atual));
            strcpy(copy2, get_amizades(atual));
            char *vert_id = getPalavra(copy, i+1, i+1);
            char *vert_afinidade = getPalavra(copy2, i+2, i+2);
            VERTICE *aux = find_lista(grafo->all, atoi(vert_id));
            VERTICE *copy_vert = copy_vertice(aux, atoi(vert_afinidade));
            inserir_vertex_lista(grafo->amizades[get_id(atual)], copy_vert);
            free(vert_id);
            free(vert_afinidade);
        }

        for (int i=1;i<=getQuntidadePalavras(get_solicitacoes(atual))-1;i+=2){
            char *copy = malloc(strlen(get_solicitacoes(atual)) + 1);
            char *copy2 = malloc(strlen(get_solicitacoes(atual)) + 1);
            strcpy(copy, get_solicitacoes(atual));
            strcpy(copy2, get_solicitacoes(atual));
            char *vert_id = getPalavra(copy, i+1, i+1);
            char *vert_afinidade = getPalavra(copy2, i+2, i+2);
            VERTICE *aux = find_lista(grafo->all, atoi(vert_id));
            VERTICE *copy_vert = copy_vertice(aux, atoi(vert_afinidade));
            inserir_vertex_lista(grafo->solicitacoes[get_id(atual)], copy_vert);
            free(vert_id);
            free(vert_afinidade);
        }

		atual = get_prox(atual); //Indo para o proximo vértice.
	}
}

// Faz um match com usuários da rede.
void sugerirAmizades(Grafo *grafo, VERTICE *vert) {

    VERTICE* atual = get_inicial(grafo->all); //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
        int afinidade = 0;

        if(!strcmp(get_livro(atual), get_livro(vert))) afinidade++; 
        if(!strcmp(get_filme_predileto(atual), get_filme_predileto(vert))) afinidade++;
        if(!strcmp(get_local_predileto(atual), get_local_predileto(vert))) afinidade++;
        if(!strcmp(get_esporte(atual), get_esporte(vert))) afinidade++;
        if(!strcmp(get_hobby(atual), get_hobby(vert))) afinidade++;

        afinidade *= 20;

        if(afinidade >= 20){
            printf("%d - Usuário: %s\tAfinidade: %d%% \n", get_id(atual), get_usuario(atual), get_afinidade(atual));
        }

        atual = get_prox(atual); //Indo para o proximo vértice.
	}
}

//Enviar solicitação de amizade para um usuário.
void enviarSolicitacao(Grafo *grafo, int id, char* usuario) {

    VERTICE *user = find_lista_name(grafo->all, usuario);
    VERTICE *atual = get_inicial(grafo->all); //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
        if(get_id(atual) == id){
            if(find_lista_name(grafo->solicitacoes[id], usuario)!=NULL){
                printf("Você já enviou uma solicitação para essa pessoa.\n");
                whaitEnter();
                return;
            } else if(find_lista_name(grafo->amizades[id], usuario)!=NULL){
                printf("Você já é amigo dessa pessoa :P\n");
                whaitEnter();
                return;
            } else if(find_lista(grafo->solicitacoes[get_id(user)], id)!=NULL){
                printf("Essa pessoa já lhe enviou uma solicitação :0\n");
                whaitEnter();
                return;
            } else if(id == get_id(user)){
                printf("Você não pode adicionar você mesmo >:C\n");
                whaitEnter();
                return;
            }
            char aux_char[10];
            sprintf(aux_char, " %d", get_id(user));
            strcpy(get_solicitacoes(atual), concatenar(get_solicitacoes(atual), aux_char));

			int afinidade = 0;
	        if(!strcmp(get_livro(atual), get_livro(user))) afinidade++; 
    	    if(!strcmp(get_filme_predileto(atual), get_filme_predileto(user))) afinidade++;
       		if(!strcmp(get_local_predileto(atual), get_local_predileto(user))) afinidade++;
        	if(!strcmp(get_esporte(atual), get_esporte(user))) afinidade++;
        	if(!strcmp(get_hobby(atual), get_hobby(user))) afinidade++;

            afinidade *= 20;

            sprintf(aux_char, " %d", afinidade);
            strcpy(get_solicitacoes(atual), concatenar(get_solicitacoes(atual), aux_char));
            inserir_vertex_lista(grafo->solicitacoes[id], copy_vertice(user, afinidade));
        }

        atual = get_prox(atual); //Indo para o proximo vértice.
	}

    writeFile(grafo);
    printf("Solicitação enviada :)\n");
    whaitEnter();
}

void printSolicitacoes(Grafo *grafo, int id){ //Printar as solicitações de amizade ao usuário.
    int contador = 0;
    VERTICE* atual = get_inicial(grafo->solicitacoes[id]); //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
        contador++;
		printf("%d - Usuário: %s\tAfinidade: %d%%\n",contador, get_usuario(atual), get_afinidade(atual));
        atual = get_prox(atual); //Indo para o proximo vértice.
	}
}

void aceitarSolicitacao(int id, int index, Grafo *grafo){ //Aceitar uma solicitação de amizade.
    int contador = 0;
    VERTICE *usuario_ver = find_lista(grafo->all, id);
    VERTICE *atual = get_inicial(grafo->solicitacoes[id]); //Inicializando "atual" como o primeiro vértice da lista.
	while (contador != index-1) { //Enquanto existir um atual, isso é, "atual != NULL"
        contador++;
        atual = get_prox(atual); //Indo para o proximo vértice.
	}

    index *= 2;

    char aux_char[20];
    sprintf(aux_char, " %d %d", get_id(atual), get_afinidade(atual));

    strcpy(get_solicitacoes(usuario_ver), apagarPalavra(index, index+1, get_solicitacoes(usuario_ver)));
    strcpy(get_amizades(usuario_ver), concatenar(get_amizades(usuario_ver), aux_char));


    sprintf(aux_char, " %d %d", get_id(usuario_ver), get_afinidade(atual));

    atual = find_lista(grafo->all, get_id(atual));
    strcpy(get_amizades(atual), concatenar(get_amizades(atual), aux_char));

    writeFile(grafo);
}

void rejeitarSolicitacao(int id, int index, Grafo *grafo){ //Rejeitar uma solicitação de amizade.
    int contador = 0;
    VERTICE *usuario_ver = find_lista(grafo->all, id);
    VERTICE *atual = get_inicial(grafo->solicitacoes[id]); //Inicializando "atual" como o primeiro vértice da lista.
    while (contador != index-1) { //Enquanto existir um atual, isso é, "atual != NULL"
        contador++;
        atual = get_prox(atual); //Indo para o proximo vértice.
    }

    index *= 2;

    strcpy(get_solicitacoes(usuario_ver), apagarPalavra(index, index+1, get_solicitacoes(usuario_ver)));

    writeFile(grafo);
}

int enviarSolicitacaoNome(char *user,char *target, Grafo *grafo){ //Enviar solicitação pelo nome do usuário.
    VERTICE *aux;
    if((aux = find_lista_name(grafo->all, target)) == NULL) return 1;

    enviarSolicitacao(grafo, get_id(aux), user);

    return 0;
}

//Printa os usuários considerados extrovertidos e introvertidos da sua lista de amigos e de amigos de amigos..
void extroIntro(Grafo *grafo){
	VERTICE *curr = get_inicial(grafo->all);
	while(curr!=NULL){
		VERTICE *aux = get_inicial(grafo->amizades[get_id(curr)]);
		int trueFriends = 0;
		int max = 0;
		while(aux!=NULL){
			if(get_afinidade(aux) >= 70)
				trueFriends++;
			max++;
			aux = get_prox(aux);
		}
		if((float)trueFriends/max >= 0.8){
			printf("%s: EXTROVERTIDO(A)\n", get_usuario(curr));
		}
		if((float)trueFriends/max <= 0.2){
			printf("%s: INTROVERTIDO(A)\n", get_usuario(curr)); 
		}
		curr = get_prox(curr);
	}
	printf("\n");
}


void bfsSugetao(Grafo *grafo, QUEUE *q) {

    VERTICE *atual = grafo->amizades[getFirstID(q)]->inicial;
    while(atual){
        insert(q, get_id(atual), getFirstLayer(q));
        atual = atual->prox;
    }

    pop_first(q); //Excluindo o primeiro elemento da fila para poder percorrer os outros.

    if(q->size == 0) return; //Condição de parada.

    wavefront(mat, q->inicial->x, q->inicial->y, q); //Recursão.

    return;
}

//GETTERS
LISTA *get_all(Grafo *g){
	return g->all;
}

LISTA *get_lista_amizades(Grafo *g, int i){
	return g->amizades[i];
}

LISTA *get_lista_solicitacoes(Grafo *g, int i){
	return g->solicitacoes[i];
}

int get_n_elementos(Grafo *g){
	return g->n_elementos;
}
