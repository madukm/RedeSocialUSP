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
#define READLINE_BUFFER 4096

typedef struct aux{ //Vértice
    char *usuario;
    char *genero;
    char *filme_predileto;
    char *local_predileto;
    char *hobby;
    char *livro;
    char *esporte;
    int idade;
    int id;
    char *solicitacoes;
    char *amizades;
    struct aux *prox;
} VERTICE;

typedef struct { //Lista ligada
    VERTICE *inicial;
    VERTICE *final;
} LISTA;

typedef struct { //TAD Grafo.
    LISTA* v[MAXN];
    LISTA* solicitacoes[MAXN];
    LISTA* all;
    int n_elementos;
} Grafo;

char *readline(FILE *stream); //Ler e alocar memória de uma linha inputada.
LISTA* criar_lista(); //Inicializar uma lista.
VERTICE* criar_vertice(char *usuario, char *genero, char *filme_predileto , char *local_predileto,
char *hobby, char * livro, char *esporte, int idade, int id, char *solicitacoes, char *amizades); //Inicializa um vértice.
VERTICE* copy_vertice(VERTICE *vertice); //Copia os dados de um vértice.
VERTICE* find_lista(LISTA* list, int ident); //Procurar elemento na lista.
VERTICE* find_lista_name(LISTA* list, char* user); //Procurar elemento na lista pelo nome de usuário.
int lista_size(LISTA* list); //Retorna o tamanho da lista.
VERTICE* find_anterior_lista(LISTA* list, int ident); //Procurar elemento anterior ao desejado, na lista.
void inserir_lista(LISTA* list, int v); //Inserir elemento na lista.
void inserir_vertex_lista(LISTA* list, VERTICE *ver); //Inserir elemento na lista.
void excluir_lista(LISTA* list, int ident); //Excluir elemento da lista.
void printar_lista(LISTA* list); //Imprimir a lista.
void printVertice(VERTICE *vertice); //Printar as informações do vértice.
void limpar_lista(LISTA* list); //Desalocar memória previamente alocada.

Grafo* inicializar (int n); //Inicializa a lista de adjacência.
// void ligar_vertices(Grafo* a, int u, int v); //Liga dois vértices.
void ligar_vertices(Grafo* a, VERTICE *u, VERTICE *v); //Ligar dois vértices.
void desligar_vertices(Grafo* a, int u, int v); //Retira ligação entre dois vértices.
void print_grafo(Grafo* a); //Imprimir a matriz de adjacência.
void limpar_memoria(Grafo* a); //Desalocar memória previamente alocada.
char *getPalavra(char *frase, int indexPalavra, int limit);  //Retorna a palvra de número "indexPalavra".
int getQuntidadePalavras(char* frase);  //Conta quantas palavras existem ao todo na string "frase".
void limpar_atributos(char *usuario, char *genero, char *filme_predileto , char *local_predileto,
char *hobby, char * livro, char *esporte, char *amigos, char *solicitacoes); //Limpar memória.
void carregarNaMemoria(FILE *file, Grafo* grafo);  //Carregar informações do arquivo na memória.
void registrar(FILE *bd, Grafo *grafo, char **usuario); //Registar o usuário na rede social.
void ligarAmizadesPedidos(Grafo *grafo); //Criar uma aresta entre todas as amizades e entre os pedidos.
void whaitEnter(); //Standby
void sugerirAmizades(Grafo *grafo, VERTICE *vert); //Checa faz um match com usuários da rede.
void enviarSolicitacao(Grafo *grafo, int id, char* usuario, FILE *bd); //Enviar solicitação de amizade para um usuário.
void concatenar(char *dest, char *a); //Concatenar strings.
void writeFile(FILE *bd, Grafo *grafo); //Escrever dados atualizados no arquivo.

#endif
