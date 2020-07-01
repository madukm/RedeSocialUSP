#ifndef _H_GRAFO
#define _H_GRAFO

#include "Lista.h"
#include "Fila.h"

#define AFFINITY_COEFFICIENT 70

//TAD para a estrutura da Rede Social

typedef struct grafo Grafo;

//Grafo
Grafo* inicializar_grafo(); //Inicializa a lista de adjacência.
void limpar_memoria_grafo(Grafo *a); //Free grafo.
void refreshGrafo(Grafo **grafo);  //Atualiza o grafo com as informações do arquivo.
void carregarNaMemoria(Grafo* grafo);  //Carregar informações do arquivo na memória.
void writeFile(Grafo *grafo); //Escrever dados atualizados no arquivo.
void print_grafo(Grafo* a); //Imprimir a matriz de adjacência.

//Vértices e ligações
void limpar_atributos(char *usuario, char *genero, char *filme_predileto , char *local_predileto,
char *hobby, char * livro, char *esporte, char *amigos, char *solicitacoes, char *char_idade, char *char_id); //Limpar memória.

//Algoritmos
void dfs(Grafo *g);
void visita_dfs(Grafo *g);

//Features rede social
void registrar(Grafo *grafo, char **usuario); //Registar o usuário na rede social.
void ligarAmizadesPedidos(Grafo *grafo); //Criar uma aresta entre todas as amizades e entre os pedidos.
void sugerirAmizades(Grafo *grafo, VERTICE *vert); //Checa faz um match com usuários da rede.
void enviarSolicitacao(Grafo *grafo, int id, char* usuario); //Enviar solicitação de amizade para um usuário.
void printSolicitacoes(Grafo *grafo, int id); //Printar as solicitações de amizade ao usuário.
void aceitarSolicitacao(int id, int index, Grafo *grafo); //Aceitar uma solicitação de amizade.
void rejeitarSolicitacao(int id, int index, Grafo *grafo); //Rejeitar uma solicitação de amizade.
int enviarSolicitacaoNome(char *user, char *target, Grafo *grafo); //Enviar solicitação pelo nome do usuário.
void atualizarPerfil(Grafo *grafo, char *usuario); //Atualiza perfil do usuário. 
void dfsExtroIntro(Grafo *grafo, int id_usuario, int **visitados, int **max, int **trueFriends);
void bfsSugestao(Grafo *grafo, QUEUE *q, int id_usuario, int **visitados); //Realiza busca em largura para poder sugerir amizades ao usuário.
void checarAmizades(Grafo *grafo, char *name); //Printar amigos e alertar nivel de afinidade alarmante.
void excluirAmizade(Grafo *grafo, int index, int id_usuario); //Desfazer amizade.

LISTA *get_all(Grafo *g);
LISTA *get_lista_amizades(Grafo *g, int i);
LISTA *get_lista_solicitacoes(Grafo *g, int i);


#endif

