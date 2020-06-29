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
#include "Fila.h"
#include "Grafo.h"

struct Queue { //Estrutura criada para representar a fila.
	int size;
	ELEMENT *inicial;
	ELEMENT *final;
};

struct Element{ //Estrutura criada para armazenar elementos da matriz na fila.
	int id;
	int camada;
    struct Element *prox;
};

ELEMENT *criar_elemento(int id, int camada){ //Aloca memória para um "ELEMENTO".
	ELEMENT *aux = (ELEMENT*)malloc(sizeof(ELEMENT));
	aux->id = id;
	aux->camada = camada;
	aux->prox = NULL;

	return aux;
} 

QUEUE *criar_queue(){ //Aloca memória para uma "QUEUE"(Fila).
	QUEUE *aux = (QUEUE*)malloc(sizeof(QUEUE));
	aux->size = 0;
	aux->inicial = NULL;
	aux->final = NULL;

	return aux;
}

void limpar_fila(QUEUE *q){ //Desalocar memória.
	ELEMENT *aux = q->inicial;
	while(aux){
		ELEMENT *aux2 = aux->prox;
		free(aux);
		aux = aux2;
	}
	free(q);
}

void print_queue(QUEUE *q){ //Função criada para debugar.
	ELEMENT *aux = q->inicial;
	while(aux){
		printf("ID: %d||camada: %d\n", aux->id, aux->camada);
		aux = aux->prox;
	}

	return;
}

void insert(QUEUE *q, int id, int camada){ //Inserir um elemento na fila.
	ELEMENT *aux = criar_elemento(id ,camada);

	if(q->size == 0){
		q->inicial = aux;
		q->final = aux;
	} else {
		q->final->prox = aux;
		q->final = aux;
	}

	q->size = q->size + 1;

	return;
}

void pop_first(QUEUE *q){ //Excluir o primeiro elemento da fila.

	if(q->size >= 1){
		if(q->size == 1){
			free(q->inicial);
			q->inicial = NULL;
			q->final = NULL;
		} else {
			ELEMENT *aux = q->inicial->prox;
			free(q->inicial);
			q->inicial = aux;
		}

		q->size = q->size - 1;	
	}

	return;
}

//GETERS
ELEMENT *getNextElement(QUEUE *q){ //Retorna segundo elemento da lista.
	return q->inicial->prox;
}

int getFirstID(QUEUE *q){ //Retorna o ID do primeiro elemento.
	return q->inicial->id;
}

int getFirstLayer(QUEUE *q){ //Retorna a camada do primeiro elemento.
	return q->inicial->camada;
}

int getSize(QUEUE *q){ //Retorna o tamanho da queue.
	return q->size;
}
