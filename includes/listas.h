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
void printList(Lista *l);
void freeList(Lista *l);
void addItemStart(Lista *l, int item);
void addItemEnd(Lista *l, int item);
void addItemPosition(Lista *l, Item *itemPointer, int item);
int removeItemStart(Lista *l);
int removeItemEnd(Lista *l);
void removeItemPosition(Lista *l, Item *itemToRemove);
Item *findItem(Lista *l, int itemToFind);


// As funções foram desenvolvidas com base no conteúdo da matéria Estrutura de Dados feita em 2019.1