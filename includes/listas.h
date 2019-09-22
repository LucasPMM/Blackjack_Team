struct item{
	int item;
	struct item *prox;
};
typedef struct item Item;

typedef struct{
    Item *inicio;
    Item *fim;
} Lista;

int isListEmpty(Lista *l);
void makeEmptyList(Lista *l);
void addItem(Lista *l, int Item);
void removeItem(Lista *l, Item *item);
void printList(Lista *l);
void freeList(Lista *l);


// As funções foram desenvolvidas com base no conteúdo da matéria Estrutura de Dados feita em 2019.1