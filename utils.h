#ifndef _H_UTILS
#define _H_UTILS

#include <stdio.h>

#define MAXN 110
#define READLINE_BUFFER 4096

char *readline(FILE *stream); //Ler e alocar memória de uma linha inputada.
char *getPalavra(char *frase, int indexPalavra, int limit);  //Retorna a palavra de número "indexPalavra".
char *apagarPalavra(int indexPalavra, int limit, char *frase); //Apaga a palavra de uma frase. 
int getQuntidadePalavras(char* frase);  //Conta quantas palavras existem ao todo na string "frase".
void whaitEnter(); //Standby
char *concatenar(char *dest, char *a); //Concatenar strings.

#endif
