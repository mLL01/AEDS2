#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tabuleiro.h"

int VerificaPosicao(Tabuleiro T, int i, int j){
	if (i <= T.n_linhas && j<= T.n_colunas)
		return 1;
	return 0;
}

void SetTamanho(Tabuleiro *T, int n){
	T->n_linhas = n;
	T->n_colunas = n;
}

void SetElemento(Tabuleiro *T, int i, int j, char c){
	if (VerificaPosicao((*T),i,j))
		T->matriz[i][j] = c;
}

char GetElemento(Tabuleiro *T, int i, int j){
	if (VerificaPosicao((*T),i,j))
		return T->matriz[i][j];
	return '\0';
}

void MarcaTodos(Tabuleiro *T, char c){
	for (int i = 0; i < T->n_linhas; i++) {
		for (int j = 0; j < T->n_colunas ; j++) { 
			T->matriz[i][j] = c;
		}
	}
}

int TestaLinha(Tabuleiro T, int i, char c){
	for (int j = 0; j < T.n_colunas; j++) 
		if (T.matriz[i][j]!=c) 
			return 0;
	return 1;
}

int TestaColuna(Tabuleiro T, int j, char c){
	for (int i = 0; i < T.n_linhas; i++)
		if (T.matriz[i][j]!=c)
			return 0;
	return 1;
}

int TestaDiagonalED(Tabuleiro T, char c){
	for (int i = 0; i < T.n_linhas; i++) {
		for (int j = 0; j < T.n_colunas; j++) {
			if (i==j)
				if (T.matriz[i][j]!=c)
					return 0;
		}
	}
	return 1;
}

int TestaDiagonalDE(Tabuleiro T, char c){
	for (int i = T.n_linhas-1; i >= 0 ; i--) {
		for (int j = T.n_colunas-1; i >= 0; i--) {
			if (i==j)
				if (T.matriz[i][j]!=c)
					return 0;
		}
	}
	return 1;
}

int TestaDiferente(Tabuleiro T, int i){
	int test;
	for (int k = 0; k < T.n_colunas; k++) {
		test = T.matriz[i][k];
		for (int j = 0; j < T.n_colunas; j++) {
			if (k!=j)
				if (test == T.matriz[i][j])
					return 0;
		}
	}
	return 1;
}

int DiagonalED_Diferente(Tabuleiro T){
	char c = T.matriz[0][0];
	int i,j;
	for (i = 0, j = 0; i < T.n_linhas, j < T.n_colunas; i++, j++)
		if (c != T.matriz[i][j])
			return 0;
	return 1;
}

int DiagonalED_DiferenteV(Tabuleiro T){
	char c = T.matriz[0][0];
	int i,j;
	for (i = 0, j = 0; i < 3, j < 3; i++, j++)
		if (c != T.matriz[i][j])
			return 0;
	return 1;
}


int DiagonalDE_Diferente(Tabuleiro T){
	char c = T.matriz[0][T.n_colunas-1];
	int i,j;
	for (i = 0, j = T.n_colunas-1; i < T.n_linhas, j >= 0; i++, j--)
		if (c != T.matriz[i][j])
			return 0;
	return 1;
}

int DiagonalDE_DiferenteV(Tabuleiro T){
	char c = T.matriz[0][2];
	int i,j;
	for (i = 0, j = 2; i < 3, j >= 0; i++, j--)
		if (c != T.matriz[i][j])
			return 0;
	return 1;
}


void Matriz_aleatoria(Tabuleiro *T){
	srand(time(NULL));
	char vector[5] = {'@','#','*','%','?'};
	for (int i = 0; i < T->n_linhas; i++) {
		for (int j = 0; j < T->n_colunas; j++) {
			T->matriz[i][j] = vector[rand()%5];
		}
	}
}	

int Linha_Igual(Tabuleiro T, int i){
	char c = T.matriz[i][0];
	for (int j = 0; j < T.n_colunas; j++)
		if (T.matriz[i][j] != c)
			return 0;
	return 1;
} 

int Coluna_Igual(Tabuleiro Velha, int j){
	char c = Velha.matriz[0][j];
	for (int i = 0; i < 3; i++)
		if (Velha.matriz[i][j] != c)
			return 0;
	return 1;
}

void TestaBingo(Tabuleiro T, int i){
	if (Linha_Igual(T,i)) {
			printf("Bingo !!!\n");
		} else if (DiagonalED_Diferente(T)) {
			printf("Bingo !!!\n");
		} else if (DiagonalDE_Diferente(T)) {
			printf("Bingo !!!\n");
		} else printf("Tente Outra Vez!\n");
}

int Testa_Velha(Tabuleiro Velha, char jogador, char pc){
	for (int i = 0; i < 3; i++) {
		if (Linha_Igual(Velha,i)){
			if (Velha.matriz[i][0] == jogador){
				printf("O vencedor foi %c\n",jogador);
				return 1;
			} else if (Velha.matriz[i][0] == pc){
				printf("O vencedor foi  %c\n",pc);
				return 1;
			}
		}
	}
	for (int j = 0; j < 3; j++) {
		if (Coluna_Igual(Velha,j)){
			if (Velha.matriz[0][j] == jogador){
				printf("O vencedor foi %c\n",jogador);
				return 1;
			} else if (Velha.matriz[0][j] == pc){
				printf("O vencedor foi  %c\n",pc);
				return 1;
			}
		}
	} if (DiagonalED_DiferenteV(Velha)) {
		if (Velha.matriz[0][0] == jogador){
			printf("O vencedor foi %c\n",jogador);
			return 1;
		} else if (Velha.matriz[0][0] == pc){
				printf("O vencedor foi %c\n",pc);
			return 1;
		}
	} if (DiagonalDE_DiferenteV(Velha)) {
		if (Velha.matriz[0][2] == jogador){
			printf("O vencedor foi %c\n",jogador);
			return 1;
		} else if (Velha.matriz[0][2] == pc){
			printf("O vencedor foi %c\n",pc);
			return 1;
		}
	}
	return 0;
}

void Imprime(Tabuleiro T){
	for (int i = 0; i < T.n_linhas; i++) {
		for (int j = 0; j < T.n_colunas; j++) {
			printf("%c ",T.matriz[i][j]);
		}
		printf("\n");
	}
}

void CriaMatriz_LeArquivo(int tamanho){
	if (tamanho <= 10){
		Tabuleiro T;
		int linha_central = tamanho/2;
		int i = 0, j = 0;
		char c;
		FILE *arq = fopen("dados.txt","r");
		SetTamanho(&T,tamanho);
		do{
			c = getc(arq);
			if (c != ' '){
				SetElemento(&T,i,j,c);
				j++;
				if (j == T.n_colunas){
					j = 0;
					i++;
					c = getc(arq); // le a quebra de linha '\n'
				}
			}
		}while(c != EOF);
	
		Imprime(T);
		TestaBingo(T,linha_central);
	}
}

void Cria_Matriz_Aleatoria(int tamanho){
	if (tamanho <= 10){
		Tabuleiro T;
		int linha_central = tamanho/2 ;
		SetTamanho(&T,tamanho);
		Matriz_aleatoria(&T);
		Imprime(T);
		TestaBingo(T,linha_central);
	}
}

void modoPC(Tabuleiro *T, char pc){
	int i,j,r;
	srand(time(NULL));
	while (1) {
		i = rand() % 3;
		j = rand() % 3;
		if (T->matriz[i][j] == '_') {
			T->matriz[i][j] = pc;
			break;
		}
	}
}

int Teste_deu_velha(Tabuleiro Velha){
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if(Velha.matriz[i][j] == '_')
				return 1;
		}
	}
	return 0;
}

int PreencheJogador(Tabuleiro *Velha, int i, int j, char c){
	if (i < Velha->n_linhas && j < Velha->n_colunas) {
		if (Velha->matriz[i][j] == '_') {
			Velha->matriz[i][j] = c;
			return 1;
		}
	}
	return 0;
}

void Jogador_Escolhe(Tabuleiro *Velha, char c){
	int i,j;
	printf("Insira o numero da linha e da coluna: \n");
	scanf("%d %d",&i,&j);
	while (!(PreencheJogador(Velha,i,j,c))){
		printf("A posicao escolhida já esta preenchida ou nao existe\n");
		printf("Por gentileza, escolha outra posicao\n");
		scanf("%d %d",&i,&j);
	}
}

void Preenche_(Tabuleiro *T){
	for (int i = 0; i < T->n_linhas; i++) {
		for (int j = 0; j < T->n_colunas; j++) {
			T->matriz[i][j] = '_';
		}
	}
}

int Quem_Comeca(){
	srand(time(NULL));
	int r = rand() % 100;
	if (!(r%2))
		return 1; // jogador comeca
	return 0; // maquina comeca
}

void Escolhe_SimboloJP(char *jogador, char *pc){
	char j1;
	printf("Bem vindo ao JOGO DA VELHA\n\n\n");
	printf("Escolha seu simbolo (X,O): \n");
	while(1) {
		scanf(" %c",&j1);
		if (j1 == 'X') {
			(*jogador) = j1;
			(*pc) = 'O';
			break;
		} else if (j1 == 'O'){
			(*jogador) = 'O';
			(*pc) = 'X';
			break;
		} else 
			printf("Caracter invalido, favor inserir 'X' ou 'O'\n");
	}
}

void Cria_Velha(int modo){
	char jogador,pc;
	int rodada;
	Tabuleiro Velha;
	SetTamanho(&Velha,3);
	Preenche_(&Velha);
	if (modo == 1){
		Escolhe_SimboloJP(&jogador,&pc);
		if (Quem_Comeca())
			rodada = 0;
		else rodada = 1;
		while (1) {
			if (!(rodada%2)){
				Jogador_Escolhe(&Velha,jogador);
				rodada++;
			}
			Imprime(Velha);
			printf("\n\n");
			if(Testa_Velha(Velha,jogador,pc))
				break;
			if(!(Teste_deu_velha(Velha))){
				printf("Deu Velha!\n");
				break;
			} 
			rodada++;
			modoPC(&Velha,pc);
			Imprime(Velha);
			printf("\n\n");
			if(Testa_Velha(Velha,jogador,pc))
				break;
			if(!(Teste_deu_velha(Velha))){
				printf("Deu Velha!\n");
				break;
			} 
		}
	}
}
