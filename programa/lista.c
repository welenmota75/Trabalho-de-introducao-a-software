/*Programa��o em C - Lista encadeada (linked list)
	Funcionalidades:
		1) - Criar lista
		2) - Adicionar na lista
		3) - Listar os elementos da lista
		4) - Verificar se a lista est� vazia
		5) - Buscar elemento na lista
		6) - Remover elemento da lista
		7) - Verificar o tamanho da lista
*/

#include <stdio.h>
#include <stdlib.h>

// struct "exemplo" possui dois campos
typedef struct exemplo
{
	int v; // inteiro "v"
	struct exemplo *prox; // ponteiro para o pr�ximo elemento
} t_exemplo;


// vari�veis ponteiros globais que guardam refer�ncia
// para a cabe�a da lista e para o n� corrente
// cabeca da lista encadeada (come�a com NULL)
t_exemplo *cabeca = NULL;
t_exemplo *corrente = NULL;


// fun��o para criar uma lista
// recebe um valor inteiro e retorna um ponteiro do tipo t_exemplo
t_exemplo * criar_lista(int valor)
{
	// aloca espa�o em mem�ria
	t_exemplo * p = (t_exemplo*)malloc(sizeof(t_exemplo));

	// verifica se houve falha na aloca��o de mem�ria
	if(p == NULL)
	{
		printf("\nFalha ao alocar memoria\n");
		return NULL;
	}

	// se chegou aqui � porque foi feita a aloca��o com sucesso
	p->v = valor; // atribui o valor passado
	p->prox = NULL; // o pr�ximo � NULL

	// faz a cabeca e o corrente apontar para p
	cabeca = corrente = p;
	// retorna o ponteiro alocado
	return p;
}


// fun��o que adiciona um elemento � lista
// recebe a cabeca e o elemento a ser adicionado
// o elemento � inserido no FINAL da lista
t_exemplo* adicionar_lista(int v)
{
	// verifica se a cabeca � NULL (lista vazia), se for NULL,
	// ent�o retorna o retorno da fun��o criar_lista
	if(cabeca == NULL)
	{
		return criar_lista(v);
	}

	// se chegou aqui � porque a lista N�O � vazia
	// aloca espa�o em mem�ria
	t_exemplo * p = (t_exemplo*)malloc(sizeof(t_exemplo));

	// verifica se houve falha na aloca��o de mem�ria
	if(p == NULL)
	{
		printf("\nFalha ao alocar memoria\n");
		return NULL;
	}

	// atribui valores
	p->v = v;
	p->prox = NULL;

	// insere no FINAL da lista (obs.: tamb�m poderia ser no in�cio)
	// aqui ser� feita a inser��o no final,
	// a inser��o no in�cio fica como um desafio ;-)
	// para inser��o no final, fazemos com que o pr�ximo do n�
	// corrente aponte para o "p"
	corrente->prox = p;
	// o corrente passar a ser o "p"
	corrente = p;

	// retorna o ponteiro alocado
	return p;
}


// fun��o que imprime a lista
void imprimir_lista()
{
	// vari�vel ponteiro "aux" para percorrer a lista
	// inicialmente aponta para a "cabeca"
	t_exemplo *aux = cabeca;

	// enquanto "aux" for diferente de NULL
	while(aux != NULL)
	{
		// imprime o valor
		printf("%d\n", aux->v);
		// aponta para o pr�ximo elemento da lista
		aux = aux->prox;
	}
}


// fun��o para verificar se a lista est� vazia
// retorna 1 se estiver vazia e 0 caso contr�rio
int lista_vazia()
{
	// se cabeca for NULL, ent�o a lista est� vazia
	if(cabeca == NULL)
		return 1;
	return 0;
}


// fun��o para buscar um elemento na lista
// essa fun��o recebe o valor a ser buscado e um ponteiro para ponteiro "ant"
// o "ant" servir� para guardarmos o anterior do elemento encontrado, pois
// iremos utilizar na remo��o, assim fica mais otimizado para n�o ter que
// percorrer a lista novamente pois precisa-se do elemento anterior ao elemento
// que ir� ser removido para ajustar corretamente a lista
// retorna o ponteiro para o elemento encontrado ou NULL se n�o encontrar
t_exemplo * buscar_elemento(int v, t_exemplo **ant)
{
	// se a lista estiver vazia, ent�o n�o possui elementos,
	// portanto, retorna 0 indicando que N�O achou.
	if(lista_vazia() == 1)
		return NULL;

	// vari�vel "p" para percorrer a lista
	t_exemplo *p = cabeca;
	// vari�vel "aux_ant" para guardar o anterior
	t_exemplo *aux_ant = NULL;
	// flag "achou" que indica se achou o elemento
	int achou = 0;

	// percorre a lista
	while(p != NULL)
	{
		// se achou, ent�o retorna 1
		if(p->v == v)
		{
			achou = 1;
			break;
		}
		// atualiza o "aux_ant"
		aux_ant = p;
		// aponta para o pr�ximo
		p = p->prox;
	}

	// verifica se achou
	if(achou == 1)
	{
		// se "ant" for diferente de NULL
		if(ant)
			*ant = aux_ant; // guarda "aux_ant"
		return p;
	}

	// se chegou aqui, ent�o n�o achou
	return NULL;
}

// fun��o que remove um elemento da lista
// retorna 1 se conseguiu remover e 0 caso contr�rio
int remover_elemento(int v)
{
	// vari�vel que guarda a refer�ncia para o elemento anterior
	// do elemento que vai ser removido
	t_exemplo *ant = NULL;

	// busca pelo elemento a ser removido
	// passa a refer�ncia para o "ant" (ponteiro para ponteiro)
	// "elem" � o elemento que ser� removido
	t_exemplo * elem = buscar_elemento(v, &ant);

	// se for NULL, � porque n�o existe, ent�o retorna 0
	if(elem == NULL)
		return 0;

	// se chegou aqui, � porque o elemento existe e ser� removido

	// se o anterior for diferente de NULL, ent�o
	// faz o pr�ximo do anterior apontar para o pr�ximo
	// do elemento que ser� removido
	if(ant != NULL)
		ant->prox = elem->prox;

	// se o elemento a ser removido � igual ao corrente, ou seja,
	// � o �ltimo elemento, ent�o faz o corrente apontar para o anterior
	if(elem == corrente)
		corrente = ant;

	// se o elemento a ser removido � igual a cabeca, ou seja,
	// � o primeiro elemento, ent�o faz a cabeca apontar para o pr�ximo
	// do elemento a ser removido
	if(elem == cabeca)
		cabeca = elem->prox;

	// por �ltimo, d� um free no elemento a ser removido "elem" e coloca para NULL
	free(elem);
	elem = NULL;

	// retorna 1 indicando que removeu com sucesso
	return 1;
}

// fun��o que retorna o tamanho da lista
int tamanho_lista()
{
	if(lista_vazia())
		return 0;

	t_exemplo *aux = cabeca;
	int tam = 0;

	while(aux != NULL)
	{
		tam++;
		aux = aux->prox;
	}
	return tam;
}

// fun��o principal
int main(int argc, char * argv[])
{
	// fun��o que verifica se a lista est� vazia
	if(lista_vazia() == 0)
		printf("A lista NAO esta vazia!!\n\n");
	else
		printf("Lista vazia!!\n\n");
	
	printf("Tamanho da lista: %d\n\n", tamanho_lista());

	// cria uma lista passando o valor
	printf("Criando uma lista...\n\n");
	criar_lista(10);

	// adiciona outros elementos � lista
	printf("Adicionando elementos na lista...\n\n");
	adicionar_lista(20);
	adicionar_lista(30);
	adicionar_lista(40);
	adicionar_lista(50);

	// chama a fun��o para imprimir a lista
	printf("Imprimindo os elementos da lista:\n");
	imprimir_lista();

	if(lista_vazia() == 0)
		printf("\nA lista NAO esta vazia!!\n");
	else
		printf("\nLista vazia!!\n");
	
	printf("\nTamanho da lista: %d\n", tamanho_lista());

	// buscando um elemento na lista
	// retorna diferente de NULL se achou e NULL caso contr�rio
	if(buscar_elemento(10, NULL) != NULL)
		printf("\nElemento 10 encontrado!\n");
	else
		printf("\nElemento 10 NAO encontrado.\n");

	if(buscar_elemento(100, NULL) != NULL)
		printf("\nElemento 100 encontrado!\n");
	else
		printf("\nElemento 100 NAO encontrado.\n");

	// removendo um elemento 30 da lista
	// a fun��o retorna 1 se conseguiu remover e 0 caso contr�rio
	if(remover_elemento(30))
		printf("\nElemento 30 removido com sucesso!\n");
	else
		printf("\nNAO foi possivel remover o elemento 30.\n");

	printf("\nImprimindo os elementos da lista:\n");
	imprimir_lista();
	
	printf("\nTamanho da lista: %d\n", tamanho_lista());

	return 0;
}
