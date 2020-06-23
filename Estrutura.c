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
#include "Estrutura.h"

Grafo* inicializar (int n) { //Inicializando a matriz de adjacência.
    Grafo* a = (Grafo*) malloc(sizeof(Grafo)); //Alocando memória.
    a->n_elementos = n; //Guardando número de elementos.

    for (int i=0; i < n; i++){
        a->v[i] = criar_lista(); //Inicializando uma lista para o i-ésimo elemento.
    }

    return a; //Retornando um ponteiro para um grafo inicializado.
}

LISTA* criar_lista(){ //Inicializar uma lista.
    LISTA* list = (LISTA*)malloc(sizeof(LISTA)); //Alocando memória.
    list->inicial = NULL; 
    list->final = NULL;
    return list; //Retornando um ponteiro para uma lista inicializada.
}

VERTICE* criar_vertice(int ident){ //Inicializando um vértice.
    VERTICE* vert = (VERTICE*)malloc(sizeof(VERTICE));
    vert->id = ident;
    vert->prox = NULL;
    return vert; //Retornando um ponteiro para um vértice inicializado.
}

VERTICE* find_lista(LISTA* list, int ident){ //Procurar elemento na lista.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
		if (atual->id == ident) return atual; //Caso achemos o vértice desejado , retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

VERTICE* find_anterior_lista(LISTA* list, int ident){ //Procurar elemento anterior ao desejado, na lista.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual->prox) { //Percorrendo cada vértice da lista.
		if (atual->prox->id == ident) return atual; //Caso achemos o vértice desejado, retorna-se um ponteiro
        //para o vértice.
		atual = atual->prox; //Indo para o proximo vértice.
	}
	return NULL;
}

void inserir_lista(LISTA* list, int ident){ //Inserir elemento na lista.

    if (find_lista(list, ident) != NULL) return; //Caso o vértice já exista, não precisamos o adicionar.

    VERTICE* ver = criar_vertice(ident); //Inicializando um vértice.

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

void excluir_lista(LISTA* list, int ident){ //Excluir elemento da lista.
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

void printar_lista(LISTA* list) { //Imprimir a lista.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Enquanto existir um atual, isso é, "atual != NULL"
		printf("%d ",atual->id); //Imprimindo o vértice.
        atual = atual->prox; //Indo para o proximo vértice.
	}
    printf("\n"); //Quebra de linha.
}

void ligar_vertices(Grafo* a, int u, int v){ //Ligar dois vértices.
    inserir_lista(a->v[v], u);  //Criando uma aresta que vai do vértice "u" até o "v".
    inserir_lista(a->v[u], v); //Reciprocidade.
}

void desligar_vertices(Grafo* a, int u, int v){ //Retirar ligação entre dois vértices.
    excluir_lista(a->v[v], u); //Excluindo a aresta que vai do vértice "u" até o "v".
    excluir_lista(a->v[u], v); //Reciprocidade.
}

void print_grafo(Grafo* a) { //Imprimir a matriz de adjacência.
    for (int i=0;i<a->n_elementos;i++){
        printf("%d: ", i);
        printar_lista(a->v[i]); //Imprimindo a i-ésima lista.
    }
}

void limpar_lista(LISTA* list){ //Desalocar memória previamente alocada.
    VERTICE* atual = list->inicial; //Inicializando "atual" como o primeiro vértice da lista.
	while (atual) { //Percorrendo cada vértice da lista.
        free(atual); //Liberando memória.
        atual = atual->prox; //Indo para o próximo elemento.
	}
    atual = NULL; //Segurança.
    free(list); //Livrando memória.
    list = NULL;
}

void limpar_memoria(Grafo* a){ //Desalocar memória previamente alocada.
    for (int i=0;i<a->n_elementos;i++){ //Percorrendo a lista de adjacência.
        limpar_lista(a->v[i]); //Livrando memória da i-ésima lista.
    }
    free(a); //Livrando memória.
    a = NULL; //Segurança.
}
