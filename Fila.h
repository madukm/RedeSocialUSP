#ifndef _H_FILA
#define _H_FILA

typedef struct Element ELEMENT;
typedef struct Queue QUEUE;

ELEMENT *criar_elemento(int id, int camada); //Aloca memória para um "ELEMENTO".
QUEUE *criar_queue(); //Aloca memória para uma "QUEUE"(Fila).
void limpar_fila(QUEUE *q); //Desalocar memória.
void print_queue(QUEUE *q); //Função criada para debugar.
void insert(QUEUE *q, int id, int camada); //Inserir um elemento na fila.
void pop_first(QUEUE *q); //Excluir o primeiro elemento da fila.

//GETERS
ELEMENT *getNextElement(QUEUE *q); //Retorna segundo elemento da lista.
int getFirstID(QUEUE *q); //Retorna o ID do primeiro elemento.
int getFirstLayer(QUEUE *q); //Retorna a camada do primeiro elemento.

#endif
