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

#ifndef ESTRUTURA_H_
#define ESTRUTURA_H_

#define MAXN 110

typedef struct aux{ //Vértice
    int id;
    struct aux *prox;
} VERTICE;

typedef struct { //Lista ligada
    VERTICE *inicial;
    VERTICE *final;
} LISTA;

typedef struct { //TAD Grafo.
    LISTA* v[MAXN];
    int n_elementos;
} Grafo;

LISTA* criar_lista(); //Inicializar uma lista.
VERTICE* criar_vertice(); //Inicializando um vértice.
VERTICE* find_lista(LISTA* list, int ident); //Procurar elemento na lista.
VERTICE* find_anterior_lista(LISTA* list, int ident); //Procurar elemento anterior ao desejado, na lista.
void inserir_lista(LISTA* list, int v); //Inserir elemento na lista.
void excluir_lista(LISTA* list, int ident); //Excluir elemento da lista.
void printar_lista(LISTA* list); //Imprimir a lista.
void limpar_lista(LISTA* list); //Desalocar memória previamente alocada.

Grafo* inicializar (int n); //Inicializa a lista de adjacência.
void ligar_vertices(Grafo* a, int u, int v); //Liga dois vértices.
void desligar_vertices(Grafo* a, int u, int v); //Retira ligação entre dois vértices.
void print_grafo(Grafo* a); //Imprimir a matriz de adjacência.
void limpar_memoria(Grafo* a); //Desalocar memória previamente alocada.

#endif
