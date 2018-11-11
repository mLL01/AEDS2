#ifndef Cabecalho_h
#define Cabecalho_h

typedef struct{
	int n_linhas;
	int n_colunas;
	char matriz[10][10];
}Tabuleiro;

void SetTamanho(Tabuleiro *T, int n);
void SetElemento(Tabuleiro *T, int i, int j, char c);
char GetElemento(Tabuleiro *T, int i, int j);
void MarcaTodos(Tabuleiro *T, char c);
int TestaLinha(Tabuleiro T, int i, char c);
int TestaColuna(Tabuleiro T, int j, char c);
int TestaDiagonalED(Tabuleiro T, char c);
int TestaDiagonalDE(Tabuleiro T, char c);
int TestaDiferente(Tabuleiro T, int i);
void Imprime(Tabuleiro T);
int VerificaPosicao(Tabuleiro T, int i, int j);
void CriaMatriz_LeArquivo(int tamanho);
void Cria_Matriz_Aleatoria(int tamanho);
void Cria_Velha(int modo);

#endif
