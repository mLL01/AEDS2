#include <stdio.h>
#include <stdlib.h>
#include "Tabuleiro.h"

int main(int argc, const char *argv[]){
	if (argc==2) 
		Cria_Matriz_Aleatoria(atoi(argv[1]));
	else 
		CriaMatriz_LeArquivo(atoi(argv[1]));
	return 0;
}

