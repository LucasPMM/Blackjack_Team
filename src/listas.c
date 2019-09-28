#include <stdio.h>
#include "../includes/listas.h"
#include <stdlib.h>
#include <string.h>

int emptyList (Lista *l) { return (l->inicio == l->fim); }

void makeEmptyList (Lista *l) {
    l->inicio = (Item*) malloc(sizeof(Item));
    l->fim = l->inicio;
    l->inicio->prox = NULL;
}

void printList (Lista *l) {
    Item *item = l->inicio->prox;
    while (item != NULL) {
        printf("%d ", item->item + 1);
        item = item->prox;
    }
    printf("\n");
}

void freeList (Lista *l) {
    Item *item = l->inicio;
    while (item != NULL) {
        l->inicio = item->prox;
        free(item);
        item = l->inicio;
    }
}

void addItemEnd (Lista *l, int item) {
    l->fim->prox = (Item*) malloc(sizeof(Item));
    l->fim = l->fim->prox;
    l->fim->item = item;
    l->fim->prox = NULL;
}

int removeItemEnd (Lista *l) {
    if (emptyList(l)) { return 0; }
    Item *item = l->inicio;
    while(item->prox != l->fim){ item = item->prox; }
    l->fim = item;
    item = item->prox;
    free(item);
    l->fim->prox = NULL;
    return 1;
}

void removeItemPosition (Lista *l, Item *itemToRemove){  
    if (itemToRemove != NULL) {
        Item *item = itemToRemove->prox;
        if (item == l->fim)
            l->fim = itemToRemove;
            
        itemToRemove->prox = item->prox;
        free(item);
    }
}

Item *findItem (Lista *l, int itemToFind) {
    Item *item = l->inicio;
    while (item->prox != NULL) {
        if (item->prox->item == itemToFind) {
            return item;
        }
        item = item->prox;
    }
    return NULL;
}

// ----------- Funções de Pilha ----------- //

int stackSize (Pilha *p) { return p->tamanho; }

int emptyStack (Pilha *p) { return p->topo == p->fundo; }

void makeEmptyStack (Pilha *p) {
    p->topo = (Item*) malloc(sizeof(Item));
    p->fundo = p->topo;
    p->topo->prox = NULL;
    p->tamanho = 0;
}

void pushStack (int item, Pilha *p) {
    Item *new;
    new = (Item*) malloc(sizeof(Item));
    p->topo->item = item;
    new->prox = p->topo;
    p->topo = new;
    p->tamanho++;
}

void printStack (Pilha *p) {
    Item *item = p->topo->prox;
    while (item != NULL) {
        printf("%d ", item->item + 1);
        item = item->prox;
    }
    printf("\n");
}

void freeStack (Pilha *p) {
    Item *item = p->topo;
    while (item != NULL) {
        p->topo = item->prox;
        free(item);
        item = p->topo;
    }
}


// Funções desenvolvidas de acordo com o material da disciplina de Estrutura de Dados