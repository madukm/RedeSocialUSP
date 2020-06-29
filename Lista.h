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

#ifndef _H_LISTA
#define _H_LISTA

#define MAXN 110
#define READLINE_BUFFER 4096

typedef struct Vertice VERTICE;
typedef struct Lista LISTA;

//Lista
LISTA* criar_lista(); //Inicializar uma lista.
void limpar_lista(LISTA* list); //Desalocar memória previamente alocada.
void excluir_lista(LISTA* list, int ident); //Excluir elemento da lista.
void printar_lista(LISTA* list); //Imprimir a lista.
int lista_size(LISTA* list); //Retorna o tamanho da lista.

//Vertice
VERTICE* criar_vertice(char *usuario, char *genero, char *filme_predileto , char *local_predileto, char *hobby, char * livro, char *esporte, int idade, int id, char *solicitacoes, char *amizades); //Inicializa um vértice.
VERTICE* copy_vertice(VERTICE *vertice, int afinidade); //Copia os dados de um vértice.
VERTICE* find_lista(LISTA* list, int ident); //Procurar elemento na lista.
VERTICE* find_lista_name(LISTA* list, char* user); //Procurar elemento na lista pelo nome de usuário.
VERTICE* find_anterior_lista(LISTA* list, int ident); //Procurar elemento anterior ao desejado, na lista.
void inserir_lista(LISTA* list, int v); //Inserir elemento na lista pelo id.
void inserir_vertex_lista(LISTA* list, VERTICE *ver); //Inserir elemento na lista pelo vertice.
void printVertice(VERTICE *vertice); //Printar as informações do vértice.

//Getters e Setters
VERTICE *get_inicial(LISTA *list);
VERTICE *get_final(LISTA *list);

VERTICE *get_prox(VERTICE *vert);
int get_id(VERTICE *vert);
char *get_usuario(VERTICE *vert);
char *get_livro(VERTICE *vert);
char *get_genero(VERTICE *vert);
char *get_filme_predileto(VERTICE *vert);
char *get_local_predileto(VERTICE *vert);
char *get_hobby(VERTICE *vert);
char *get_esporte(VERTICE *vert);
int get_idade(VERTICE *vert);
int get_afinidade(VERTICE *vert);
char *get_amizades(VERTICE *vert);
char *get_solicitacoes(VERTICE *vert);	

void set_filme_predileto(VERTICE *vert, char *filme);
void set_local_predileto(VERTICE *vert, char *local);
void set_hobby(VERTICE *vert, char *hobby);
void set_esporte(VERTICE *vert, char *esporte);
void set_livro(VERTICE *vert, char *livro);
void set_genero(VERTICE *vert, char *genero);
void set_idade(VERTICE *vert, int idade);
void set_solicitacoes(VERTICE *vert, char *solicitacoes);
void set_amizades(VERTICE *vert, char *amizades);

#endif
