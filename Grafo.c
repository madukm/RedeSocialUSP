/**
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

/**
 * Funções em relação direta com a Rede Socia (FEATURES)
 */

//Registra o usuário na rede social.
void registrar(Grafo *grafo, char **usuario){
   	while(1){
		int exist = 0;
		printf("Escolha um nome de usuário: ");
   		scanf("\n");
   		*usuario = readline(stdin);
		VERTICE *curr = get_inicial(grafo->all);
		while(curr!=NULL){
			if(!strcmp(*usuario, get_usuario(curr))){
				exist = 1;
				printf("Nome de usuário já existe.\n");
				break;
			}
			curr = get_prox(curr);
		}
		if(exist == 0) break;
		free(curr);
	}

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
            set_solicitacoes(atual, concatenar(get_solicitacoes(atual), aux_char));

			int afinidade = 0;
	        if(!strcmp(get_livro(atual), get_livro(user))) afinidade++; 
    	    if(!strcmp(get_filme_predileto(atual), get_filme_predileto(user))) afinidade++;
       		if(!strcmp(get_local_predileto(atual), get_local_predileto(user))) afinidade++;
        	if(!strcmp(get_esporte(atual), get_esporte(user))) afinidade++;
        	if(!strcmp(get_hobby(atual), get_hobby(user))) afinidade++;

            afinidade *= 20;

            sprintf(aux_char, " %d", afinidade);
            set_solicitacoes(atual, concatenar(get_solicitacoes(atual), aux_char));
            inserir_vertex_lista(grafo->solicitacoes[id], copy_vertice(user, afinidade));
        }
        atual = get_prox(atual); //Indo para o proximo vértice.
	}

    writeFile(grafo);
    printf("Solicitação enviada :)\n");
    whaitEnter();
}

//Printar as solicitacoes de amizade ao usuário.
void printSolicitacoes(Grafo *grafo, int id){
    int contador = 0;
    VERTICE* atual = get_inicial(grafo->solicitacoes[id]); //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
        contador++;
		printf("%d - Usuário: %s\tAfinidade: %d%%\n",contador, get_usuario(atual), get_afinidade(atual));
        atual = get_prox(atual); //Indo para o proximo vértice.
	}
}

//Aceitar uma solicitação de amizade.
void aceitarSolicitacao(int id, int index, Grafo *grafo){
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

    set_solicitacoes(usuario_ver, apagarPalavra(index, index+1, get_solicitacoes(usuario_ver)));
    set_amizades((usuario_ver), concatenar(get_amizades(usuario_ver), aux_char));


    sprintf(aux_char, " %d %d", get_id(usuario_ver), get_afinidade(atual));

    atual = find_lista(grafo->all, get_id(atual));
    set_amizades(atual, concatenar(get_amizades(atual), aux_char));

    writeFile(grafo);
}

//Rejeitar uma solicitação de amizade.
void rejeitarSolicitacao(int id, int index, Grafo *grafo){
    int contador = 0;
    VERTICE *usuario_ver = find_lista(grafo->all, id);
    VERTICE *atual = get_inicial(grafo->solicitacoes[id]); //Inicializando "atual" como o primeiro vértice da lista.
    while (contador != index-1) { //Enquanto existir um atual, isso é, "atual != NULL"
        contador++;
        atual = get_prox(atual); //Indo para o proximo vértice.
    }

    index *= 2;

    set_solicitacoes(usuario_ver, apagarPalavra(index, index+1, get_solicitacoes(usuario_ver)));

    writeFile(grafo);
}

//Enviar solicitação pelo nome do usuário.
int enviarSolicitacaoNome(char *user,char *target, Grafo *grafo){
    VERTICE *aux;
    if((aux = find_lista_name(grafo->all, target)) == NULL) return 1;

    enviarSolicitacao(grafo, get_id(aux), user);

    return 0;
}

//Atualiza o perfil do usuário.
void atualizarPerfil(Grafo *grafo, char *usuario){
	system("clear");
	VERTICE *user = find_lista_name(grafo->all, usuario);
	printf("-----ATUALIZAR PERFIL-----\n");
	printf("1 - Filme predileto\n2 - Local predileto\n3 - Hobby\n4 - Livro\n5 - Esporte\n6 - Idade\n7 - Genero\n");
	int op;
	char *aux = NULL;
	int idade;
	scanf("%d", &op);
	switch(op){
		case 1:
			printf("Escreva seu novo filme predileto.\n");
			scanf("\n");
			aux = readline(stdin);
			set_filme_predileto(user, aux);
			break;				
		case 2:
			printf("Escreva seu novo local predileto.\n");
			scanf("\n");
			aux = readline(stdin);
			set_local_predileto(user, aux);
			break;
		case 3:
			printf("Escreva seu novo hobby.\n");
			scanf("\n");
			aux = readline(stdin);
			set_hobby(user, aux);
			break;
		case 4:
		   	printf("Escreva seu novo livro.\n");
			scanf("\n");
		   	aux = readline(stdin);
		   	set_livro(user, aux);
			break;
		case 5:
			printf("Escreva seu novo esporte.\n");
			scanf("\n");
			aux = readline(stdin);
			set_esporte(user, aux);
			break;
		case 6:
		   	printf("Escreve sua idade.\n");
			scanf("%d", &idade);
		   	set_idade(user, idade);
			break;	
		case 7:
			printf("Escreva seu novo genêro.\n");
			scanf("\n");
			aux = readline(stdin);
			set_genero(user, aux);
			break;
		default:
		    printf("Opção não válida.\n");
			break;
	}
	writeFile(grafo);
	return;
}

//Printa os usuários considerados extrovertidos e introvertidos da sua lista de amigos e de amigos de amigos e assim em diante.
//Utiliza uma busca em profundidade.
void dfsExtroIntro(Grafo *grafo, int id_usuario, int **visitados, int **max, int **trueFriends){
	
	(*visitados)[id_usuario] = 1;
	
	VERTICE *curr = get_inicial(grafo->amizades[id_usuario]);
		
	while(curr!=NULL){	
	
		if(get_afinidade(curr) >= 70)
			(*trueFriends)[id_usuario]++;
		(*max)[id_usuario]++;
		
		if((*visitados)[get_id(curr)] == 0)
			dfsExtroIntro(grafo, get_id(curr), visitados, max, trueFriends);

		curr = get_prox(curr);
	}

	VERTICE *user = find_lista(grafo->all, id_usuario);

	if((*max)[id_usuario] == 0 || (float)(*trueFriends)[id_usuario]/(*max)[id_usuario] <= 0.2){
		printf("%s: INTROVERTIDO(A)\n", get_usuario(user));
	}
	else if((float)(*trueFriends)[id_usuario]/(*max)[id_usuario] >= 0.8){
		printf("%s: EXTROVERTIDO(A)\n", get_usuario(user));
	}
	else{
		printf("%s: AMBIVERTIDO(A)\n", get_usuario(user));
	}	

	return;
}

//Realiza busca em largura para poder sugerir amizades ao usuário.
void bfsSugestao(Grafo *grafo, QUEUE *q, int id_usuario, int **visitados) {

    VERTICE *atual = get_inicial(grafo->amizades[getFirstID(q)]);
    if((*visitados)[getFirstID(q)] == 0) {
        (*visitados)[getFirstID(q)] = 1;
        while(atual){
            if((*visitados)[get_id(atual)] == 0) insert(q, get_id(atual), getFirstLayer(q)+1);
            atual = get_prox(atual);
        }

        if(getFirstLayer(q) > 1 && find_lista(grafo->solicitacoes[getFirstID(q)], id_usuario) == NULL){ //Ignorar caso seja o proprio usuário ou seus amigos.
            VERTICE *user = find_lista(grafo->all, id_usuario);
            VERTICE *comparador = find_lista(grafo->all, getFirstID(q));

            int afinidade = 0;
            if(!strcmp(get_livro(comparador), get_livro(user))) afinidade++; 
            if(!strcmp(get_filme_predileto(comparador), get_filme_predileto(user))) afinidade++;
            if(!strcmp(get_local_predileto(comparador), get_local_predileto(user))) afinidade++;
            if(!strcmp(get_esporte(comparador), get_esporte(user))) afinidade++;
            if(!strcmp(get_hobby(comparador), get_hobby(user))) afinidade++;

            afinidade *= 20;

            if(afinidade >= 0){
                printf("ID: %d\tUsuário: %s\tAfinidade: %d%%\tCamada: %d\n", get_id(comparador), get_usuario(comparador), 
                afinidade, getFirstLayer(q));
            }
        }

        pop_first(q); //Excluindo o primeiro elemento da fila para poder percorrer os outros.

        if(getSize(q) == 0) return; //Condição de parada.

        bfsSugestao(grafo, q, id_usuario, visitados); //Recursão.
    }

    return;
}

void checarAmizades(Grafo *grafo, char *name){ //Printar amigos e alertar nivel de afinidade alarmante.
    VERTICE *user = find_lista_name(grafo->all, name);

    VERTICE *atual = get_inicial(grafo->amizades[get_id(user)]);

    if(atual == NULL){
        printf("Você não tem amigos :(\n");
    } else {

        printf("Amizades:\n");
        int index = 0;
        while(atual){
            index++;
            int afinidade = 0;
            if(!strcmp(get_livro(atual), get_livro(user))) afinidade++; 
            if(!strcmp(get_filme_predileto(atual), get_filme_predileto(user))) afinidade++;
            if(!strcmp(get_local_predileto(atual), get_local_predileto(user))) afinidade++;
            if(!strcmp(get_esporte(atual), get_esporte(user))) afinidade++;
            if(!strcmp(get_hobby(atual), get_hobby(user))) afinidade++;
            afinidade *= 20;

            printf("%d - \tUsuário: %s\tAfinidade: %d%%", index, get_usuario(atual), 
            afinidade);
            if(get_afinidade(atual) < AFFINITY_COEFFICIENT){
                printf(" (Biaxo nivel de afinidade!)\n");
            } else {
                printf("\n");
            }
            atual = get_prox(atual);
        }

        printf("Opções: \n");
        printf("1 - Exlcuir amizade :(\n");
        printf("2 - Voltar ao menu\n");

        int opcao;
        scanf("%d", &opcao);

        if(opcao == 1){
            printf("Digite o índice da pessoa com que você quer desfazer amizade: ");
            scanf("%d", &index);
            excluirAmizade(grafo, index, get_id(user));
        }
    }
}

void excluirAmizade(Grafo *grafo, int index, int id_usuario){ //Desfazer amizade.
    VERTICE *usuario_ver = find_lista(grafo->all, id_usuario);

    index *= 2;
    set_amizades(usuario_ver, apagarPalavra(index, index+1, get_amizades(usuario_ver)));

    writeFile(grafo);
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

