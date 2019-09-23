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
int emptyList(Lista *l);
// #2)
void makeEmptyList(Lista *l);
// #3)
void printList(Lista *l);
// #4)
void freeList(Lista *l);
// #5)
void addItemEnd(Lista *l, int item);
// #6)
int removeItemEnd(Lista *l);
// #7)
void removeItemPosition(Lista *l, Item *itemToRemove);
// #8)
Item *findItem(Lista *l, int itemToFind);


typedef struct {
    Item *fundo, *topo;
    int tamanho;
} Pilha;

// #1:
int emptyStack(Pilha *p);
// #2
void makeEmptyStack(Pilha *p);
// #3
void pushStack (int item, Pilha *p);
// #4
int stackSize(Pilha *p);
// #5
void freeStack(Pilha *p);


// Funções desenvolvidas de acordo com o material da disciplina de Estrutura de Dados