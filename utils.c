#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Lê e guarda a linha do que esta sendo inputado pelo teclado. A cada novo caractere mais memória 
//é alocada ao buffer que guarda a leitura.
char *readline(FILE *stream) { 

	char *string = 0;
	int pos = 0;
	do {
        if (pos % READLINE_BUFFER == 0) {
            string = (char *) realloc(string, (pos / READLINE_BUFFER + 1) * READLINE_BUFFER);
        }
	    string[pos] = (char) fgetc(stream);
	} while (string[pos++] != '\n' && !feof(stream));
	string[pos-1] = '\0';
	string = (char *) realloc(string, pos);
	if(pos==1){
	    free(string);
	}
	return (pos == 1)? NULL:string;

}

char *getPalavra(char *frase, int indexPalavra, int limit) { //Retorna a palvra de número "indexPalavra".

    char* palavraFinal = NULL;
    char* palavra; //Guarda a posição da palavra.
    int contadorPalavras = 0; //Indicador no número de palavras.
    int flag = 0; //Indica se começou uma palavra.
    for(int i=0;i<strlen(frase);i++){
        if(frase[i] != ' ' && flag==0){ //Caso seja um caractero válido, e ainda não tenha contabilizado a palavra
        //em questão.
            contadorPalavras++; //Soma-se a quantidade de palavras da frase.
            flag = 1; //Indica que a palavra em questão ja foi contabilizada.
            if(contadorPalavras==indexPalavra){
                flag = 2;
                palavra = &frase[i]; //Guardando a posição da palavra.
            } else if(contadorPalavras > indexPalavra){
                flag = 2;
            }
        } else if (frase[i] == ' ' && flag==1) { //Caso saia de uma palavra.
            flag = 0; //Indica que não está percorrendo uma palavra.
        } else if(frase[i] == ' ' && flag==2){ //Quando achar o final da palavra.
            if(contadorPalavras == limit){
                frase[i]='\0'; //Mudando o fim da palavra.
                palavraFinal = (char*) malloc(sizeof(char)* (strlen(palavra) + 1));
                strcpy(palavraFinal, palavra);
                frase[i]=' '; //Retornando a palavra final ao normal.
                free(frase);
                break;
            }
            flag = 0;
        } 
        
        if(i+1 == strlen(frase) && flag == 2){ //Caso seja a ultima palavra da frase.
            palavraFinal = (char*) malloc(sizeof(char)* (strlen(palavra) + 1));
            strcpy(palavraFinal, palavra);
            free(frase);
            break;
        }
    }

    return palavraFinal;
}

//Conta quantas palavras existem ao todo na string "frase".
int getQuntidadePalavras(char* frase) {

	int contadorPalavras = 0; //Indicador no número de palavras.
    int flag = 0; //Indica se começou uma palavra.
    for(int i=0;i<strlen(frase);i++){
        if(frase[i] != ' ' && flag==0){ //Caso seja um caractero válido, e ainda não tenha contabilizado a palavra
        //em questão.
            contadorPalavras++; //Soma-se a quantidade de palavras da frase.
            flag = 1; //Indica que a palavra em questão ja foi contabilizada.
        } else if (frase[i] == ' ') { //Caso seja saia de uma palavra.
            flag = 0; //Indica que não está percorrendo uma palavra.
        }
    }
    return contadorPalavras; //Retornando a quantidade de palavras da frase.

}

//Standby
void whaitEnter() {

    printf("\nPressione ENTER para voltar a pagina inicial\n");
    getchar();
    getchar();

}

// Concatenar strings
char *concatenar(char *dest, char *a) {
 
	dest = (char *) realloc(dest, sizeof(char) * (strlen(a) + strlen(dest) + 1));
    strcat(dest, a);
    return dest;

}

char *apagarPalavra(int indexPalavra, int limit, char *frase) { //Apaga a palavra de uma frase.
    char* palavra; //Guarda a posição da palavra.
    int contadorPalavras = 0; //Indicador no número de palavras.
    int flag = 0; //Indica se começou uma palavra.
    int tamanho_frase = strlen(frase);
    for(int i=0;i<strlen(frase);i++){
        if(frase[i] != ' ' && flag==0){ //Caso seja um caractero válido, e ainda não tenha contabilizado a palavra
        //em questão.
            contadorPalavras++; //Soma-se a quantidade de palavras da frase.
            flag = 1; //Indica que a palavra em questão ja foi contabilizada.
            if(contadorPalavras==indexPalavra){
                flag = 2;
                palavra = &frase[i]; //Guardando a posição da palavra.
            } else if(contadorPalavras > indexPalavra){
                flag = 2;
            }
        } else if (frase[i] == ' ' && flag==1) { //Caso saia de uma palavra.
            flag = 0; //Indica que não está percorrendo uma palavra.
        } else if(frase[i] == ' ' && flag==2){ //Quando achar o final da palavra.
            if(contadorPalavras == limit){
                frase[i]='\0'; //Mudando o fim da palavra.
                palavra[0]='\0';
                char *aux_cpy = (char*) malloc(sizeof(char) * (strlen(&frase[i+1]) + 1));
                strcpy(aux_cpy, &frase[i+1]);
                frase = (char*) realloc(frase, sizeof(char) * (strlen(frase) + strlen(aux_cpy) + 1));
                strcat(frase, aux_cpy);
                free(aux_cpy);
                return frase;
            }
            flag = 0;
        } 
        
        if(i+1 == strlen(frase) && flag == 2){ //Caso seja a ultima palavra da frase.
            int tamanho_palavras = strlen(palavra);
            frase = (char*) realloc(frase, sizeof(char) * (tamanho_frase-tamanho_palavras+1));
            frase[tamanho_frase-tamanho_palavras] = '\0';
            return frase;
        }
    }

    return NULL;
}
