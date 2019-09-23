struct item{
	int item;
	struct item *prox;
};
typedef struct item Item;

typedef struct{
    Item *inicio;
    Item *fim;
} Lista;

// #1)
int isListEmpty(Lista *l);
// #2)
void makeEmptyList(Lista *l);
// #3)
void printList(Lista *l);
// #4)
void freeList(Lista *l);
// #5)
void addItemStart(Lista *l, int item);
// #6)
void addItemEnd(Lista *l, int item);
// #7)
int removeItemEnd(Lista *l);
// #8)
void removeItemPosition(Lista *l, Item *itemToRemove);
// #9)
Item *findItem(Lista *l, int itemToFind);


// As funções foram desenvolvidas com base no conteúdo da matéria Estrutura de Dados feita em 2019.1