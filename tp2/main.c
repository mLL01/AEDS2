#include <stdio.h>
#include <stdlib.h>

typedef struct No No;
typedef struct Array Array;
typedef struct Aresta Aresta;

struct Aresta {
	Aresta *prox;
	int v_x,v_y;
	int peso_a;
	int marcado;
};

struct No{
  No* prox;
  int peso;
  int vertice_in;
	int marcado;
};

struct Array{
  No* head;
  int vertice_out;
	int marcado;
};

// Cria uma lista de adjacencia 
Array** Cria_Grafo(int n_vertices){
	Array** Lista_Adjacencia = (Array**)malloc(n_vertices * sizeof(Array*));
	for (int i = 0; i < n_vertices; i++){
		Lista_Adjacencia[i] = (Array*)malloc(sizeof(Array));
		Lista_Adjacencia[i]->head = NULL;
		Lista_Adjacencia[i]->marcado = 0;
	}
  return Lista_Adjacencia;
}
// Cria os Nos para formar a lista de adjacencia
// Cada lista está "dentro" de um elemento do Array principal
void Cria_No(Array* Lista_Adjacencia, Aresta* aresta, int edge){
	No* aux;
	No* no = (No*)malloc(sizeof(No));
	no->vertice_in = edge;
	no->peso = aresta->peso_a;
	no->marcado = 0;
	no->prox = NULL;
	if (!Lista_Adjacencia->head)
		Lista_Adjacencia->head = no;
	else {
		aux = Lista_Adjacencia->head;
		while (Lista_Adjacencia->head->prox)
			Lista_Adjacencia->head = Lista_Adjacencia->head->prox;
		Lista_Adjacencia->head->prox = no;
		Lista_Adjacencia->head = aux;
	}
}
// Aqui se forma a lista com os elemento das 
// arestas lidas do arquivo
void Cria_Lista(Array** Lista_Adjacencia, Aresta* aresta, int n_vertices){
	Aresta* aux = aresta;
	int edge;
	for (int i = 0; i < n_vertices; i++) {
		while (aresta) {
			if (aresta->v_x == Lista_Adjacencia[i]->vertice_out){
				edge = aresta->v_y;
				Cria_No(Lista_Adjacencia[i],aresta,edge);
			} else if (aresta->v_y == Lista_Adjacencia[i]->vertice_out){
				edge = aresta->v_x;
				Cria_No(Lista_Adjacencia[i],aresta,edge);
			}
			aresta = aresta->prox;
		} 
		aresta = aux;
	}
}
// Array principal que conterá as Listas
void Cria_Array(Array** Lista_Adjacencia, int n_vertices){
	for (int i = 0; i < n_vertices; i++)
		Lista_Adjacencia[i]->vertice_out = i;
}
// Listas de Arestas lidas do arquivo
void Adiciona_Aresta(Aresta* aresta, int v_i, int v_j, int peso){
	Aresta* aux = (Aresta*)malloc(sizeof(Aresta));
	aux->prox = NULL;
	aux->v_x = v_i;
	aux->v_y = v_j;
	aux->peso_a = peso;
	while (aresta->prox)
		aresta = aresta->prox;
	aresta->prox = aux;
}
// Aqui se ordena as Listas dentro de cada Array
// Inicialmente o algoritmo se assemelha ao metodo
// selecao de ordenacao
void Ordena_Lista(Array* Lista_Adjacencia){
	int cont = 0;
	No *menor,*x,*y,*z,*aux;
	aux = Lista_Adjacencia->head;
	while(aux->prox){
		menor = aux;
		while (aux) {
			if (menor->vertice_in > aux->vertice_in)
				menor = aux;
			aux = aux->prox;
		}
		// ate aqui analogo ao selecao
		// A partir daqui sao feitas mudancas nos ponteiro
		// de modo a torna-lo proprio a Listas
		x = Lista_Adjacencia->head->prox;
		if (Lista_Adjacencia->head != menor) {
			if (x != menor) {
				x = Lista_Adjacencia->head->prox;
				Lista_Adjacencia->head->prox = menor->prox;
				menor->prox = x;
				while (x->prox != menor)
					x = x->prox;
				x->prox = Lista_Adjacencia->head;
			} else if (x == menor) {
				if (menor->prox)
					Lista_Adjacencia->head->prox = menor->prox;
				else 
					Lista_Adjacencia->head->prox = NULL;
				menor->prox = Lista_Adjacencia->head;
			}
		} if (!cont) { // Servem para salvar a primeira posicao da lista
			y = menor; 
			z = menor;
		} else if (cont > 0){ // Servem para atualizar o ponteiro das i-esimas
			z->prox = menor;    // posicoes ja ordenadas
			z = menor;
		}
		cont++;
		Lista_Adjacencia->head = menor->prox;
		aux = Lista_Adjacencia->head;
	}
	Lista_Adjacencia->head = y;
}

// Marca as posicoes que formam uma aresta identica a uma ja existente
void Marca_Complemento_2(Array** Lista_Adjacencia, int vertice_out, int n_vertices, int elemento, int valor){
	for (int i = 0; i < n_vertices; i++) {
		No* aux = Lista_Adjacencia[i]->head;
		if (Lista_Adjacencia[i]->vertice_out == vertice_out) {
			while (Lista_Adjacencia[i]->head->vertice_in != elemento)
				Lista_Adjacencia[i]->head = Lista_Adjacencia[i]->head->prox;
			Lista_Adjacencia[i]->head->marcado = valor;
		} 
		Lista_Adjacencia[i]->head = aux;
	}
}
// Conta o numero de arestas na arvore geradora minima
int Cont_Arestas(Array** Lista_Adjacencia, int n_vertices){
	No* aux;
	int cont = 0;
	for (int i = 0; i < n_vertices; i++){
		aux = Lista_Adjacencia[i]->head;
		while (Lista_Adjacencia[i]->head) {
			if (Lista_Adjacencia[i]->marcado == 1 && Lista_Adjacencia[i]->head->marcado == 1){
				Marca_Complemento_2(Lista_Adjacencia,Lista_Adjacencia[i]->head->vertice_in,n_vertices,Lista_Adjacencia[i]->vertice_out,-1);
				cont++;
			}
			Lista_Adjacencia[i]->head = Lista_Adjacencia[i]->head->prox;
		}
		Lista_Adjacencia[i]->head = aux;
	}
	return cont;
}
// imprime a arvore geradora minima em um arquivo
void imprime(Array** Lista_Adjacencia, int n_vertices, int n_arestas, FILE* out){
	No* aux;
	fprintf(out,"%d %d\n",n_vertices,n_arestas);
	for (int i = 0; i < n_vertices; i++){
		aux = Lista_Adjacencia[i]->head;
		while (Lista_Adjacencia[i]->head) {
			if (Lista_Adjacencia[i]->marcado == 1 && Lista_Adjacencia[i]->head->marcado == 1){
				if (Lista_Adjacencia[i]->vertice_out < Lista_Adjacencia[i]->head->vertice_in)
					fprintf(out,"%d %d %d\n",Lista_Adjacencia[i]->vertice_out,Lista_Adjacencia[i]->head->vertice_in,Lista_Adjacencia[i]->head->peso);
				else 
					fprintf(out,"%d %d %d\n",Lista_Adjacencia[i]->head->vertice_in, Lista_Adjacencia[i]->vertice_out, Lista_Adjacencia[i]->head->peso);
			}
			Lista_Adjacencia[i]->head = Lista_Adjacencia[i]->head->prox;
		}
		Lista_Adjacencia[i]->head = aux;
	}
}
//Verifica se totas as arestas do grafo inicial foram marcadas
// e, portanto, a arvore geradora minima eta completa
int Verifica_Final(Array** Lista_Adjacencia, int n_vertices){
	No* aux; int cont = 0, total = 0;
	for (int i = 0; i < n_vertices; i++){
		aux = Lista_Adjacencia[i]->head;
		while (Lista_Adjacencia[i]->head) {
			if (Lista_Adjacencia[i]->head->marcado)
				cont++;
			total++;
			Lista_Adjacencia[i]->head = Lista_Adjacencia[i]->head->prox;
		}
		Lista_Adjacencia[i]->head = aux;
	}
	return cont == total ? 1 : 0;
}

// Essa funcao verifica se pode-se marcar determinado No de "uma aresta" de forma recursiva
// basicamente quando se quer marcar um elemento Y de uma lista do Array X
// se procura o elemento X dentro de uma outras listas que nao seja a com o Array indexado por Y
// se acharmos o X, entao ele forma um laco e nao pode ser marcado
// caso nao achemos ele pode ser marcado -> forma uma aresta com Y
int Busca_Array(Array** Lista_Adjacencia, int elemento_in, int elemento_out, int n_vertices, int anterior){
	for (int j = 0; j < n_vertices; j++) {
		No* aux = Lista_Adjacencia[j]->head;
		if (Lista_Adjacencia[j]->vertice_out == elemento_in) {
			if (Lista_Adjacencia[j]->marcado == 1){
				while (Lista_Adjacencia[j]->head) {
					if (Lista_Adjacencia[j]->head->marcado == 1) {
						if (Lista_Adjacencia[j]->head->vertice_in != anterior){
							if (Lista_Adjacencia[j]->head->vertice_in == elemento_out) {
								Lista_Adjacencia[j]->head = aux;
								return 1;
							}	else {
								if (Busca_Array(Lista_Adjacencia,Lista_Adjacencia[j]->head->vertice_in,elemento_out,n_vertices,Lista_Adjacencia[j]->vertice_out)){
									Lista_Adjacencia[j]->head = aux;
									return 1;
								}
							}
						}
					}
					Lista_Adjacencia[j]->head = Lista_Adjacencia[j]->head->prox;
				}
			}	
		}
		Lista_Adjacencia[j]->head = aux;
	}
	return 0;
}
// Analogo ao Marca_Complemento_2
void Marca_Complemento(Array** Lista_Adjacencia, int vertice_out, int n_vertices, int elemento, int valor){
	for (int i = 0; i < n_vertices; i++) {
		No* aux = Lista_Adjacencia[i]->head;
		if (Lista_Adjacencia[i]->vertice_out == vertice_out) {
			while (Lista_Adjacencia[i]->head->vertice_in != elemento)
				Lista_Adjacencia[i]->head = Lista_Adjacencia[i]->head->prox;
			Lista_Adjacencia[i]->marcado = valor;
			Lista_Adjacencia[i]->head->marcado = valor;
		}
		Lista_Adjacencia[i]->head = aux;
	}
}
// Procura-se o No com menor peso
No* Menor_Peso(Array** Lista_Adjacencia, int n_vertices, int* linha){
	No* aux;
	No* menor = (No*)malloc(sizeof(No));
	menor->peso = 10000000; //valor aleatorio muito grande
	for (int i = 0; i < n_vertices; i++) {
		aux = Lista_Adjacencia[i]->head;
		while (Lista_Adjacencia[i]->head) {
			if (menor->peso > Lista_Adjacencia[i]->head->peso)
				if (!(Lista_Adjacencia[i]->head->marcado)){
					menor = Lista_Adjacencia[i]->head;
					(*linha) = i;
				}
			Lista_Adjacencia[i]->head = Lista_Adjacencia[i]->head->prox;
		}
		Lista_Adjacencia[i]->head = aux;
	}
	return menor;
}
// Marca com 1 os Nos que formam arestas quem irao compor a arvore geradora minima
// Marca com -1 os Nos que formam arestas ja marcadas
void Marca_No(Array** Lista_Adjacencia, int n_vertices){
	int linha; No *menor;
	menor = Menor_Peso(Lista_Adjacencia,n_vertices, &linha);
	int i = linha;
	No* aux = Lista_Adjacencia[i]->head;
	while (Lista_Adjacencia[i]->head) {
		if (Lista_Adjacencia[i]->head->vertice_in == menor->vertice_in){
			if(!(Busca_Array(Lista_Adjacencia,menor->vertice_in,Lista_Adjacencia[i]->vertice_out, n_vertices,Lista_Adjacencia[i]->vertice_out))){
				menor->marcado = 1;
				Lista_Adjacencia[i]->marcado = 1;
				Marca_Complemento(Lista_Adjacencia,menor->vertice_in,n_vertices,Lista_Adjacencia[i]->vertice_out,1);
				Lista_Adjacencia[i]->head = aux;
				return;
			} else {
				menor->marcado = -1;
				menor = Menor_Peso(Lista_Adjacencia, n_vertices, &linha);
				Lista_Adjacencia[i]->head = aux;
				i = linha;
				menor->marcado = -1;
				return;	
			}
		}
		Lista_Adjacencia[i]->head = Lista_Adjacencia[i]->head->prox;
	}
	Lista_Adjacencia[i]->head = aux;
}
// Chama cada lista para ser Ordenada
void Ordena(Array** Lista_Adjacencia, int n_vertices){
	for (int i = 0; i < n_vertices; i++)
		Ordena_Lista(Lista_Adjacencia[i]);
}
//Processa o arquivo com os dados para criarmos a arvore geradora minima
void Processa_Arquivo(const char **argv){
	int peso,vertice_i,vertice_j,n_arestas,n_vertices;
	FILE *arq = fopen(argv[1],"r");
	FILE *out = fopen(argv[2],"a");
	Aresta* aresta = (Aresta*)malloc(sizeof(Aresta));
	aresta->prox = NULL;
	fscanf(arq,"%d %d",&n_vertices,&n_arestas);
	Array** Lista_Adjacencia = Cria_Grafo(n_arestas);
	Cria_Array(Lista_Adjacencia,n_vertices);
	fscanf(arq,"%d %d %d", &vertice_i, &vertice_j, &peso);
	aresta->v_x = vertice_i; aresta->v_y = vertice_j; aresta->peso_a = peso;
	while (fscanf(arq,"%d %d %d", &vertice_i, &vertice_j, &peso)!=EOF)
		Adiciona_Aresta(aresta,vertice_i,vertice_j,peso);
	Cria_Lista(Lista_Adjacencia,aresta,n_vertices);
	while (!(Verifica_Final(Lista_Adjacencia,n_vertices)))
		Marca_No(Lista_Adjacencia,n_vertices);
	Ordena(Lista_Adjacencia,n_vertices);
	n_arestas = Cont_Arestas(Lista_Adjacencia,n_vertices);
	imprime(Lista_Adjacencia,n_vertices,n_arestas,out);
}

int main(int argc, char const* argv[]){
	Processa_Arquivo(argv);
	return 0;
}
