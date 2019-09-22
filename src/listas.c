
#include <stdio.h>
#include "../includes/listas.h"
#include <stdlib.h>
#include <string.h>

int isListEmpty(Lista *l) { return (l->inicio == l->fim); }

void makeEmptyList(Lista *l) {
    l->inicio = (Item*) malloc(sizeof(Item));
    l->fim = l->inicio;
    l->inicio->prox = NULL;
}

void addItem(Lista *l, int item) {
    l->fim->prox = (Item*) malloc(sizeof(Item));
    l->fim = l->fim->prox;
    l->fim->item = item;
    l->fim->prox = NULL;
}


void removeItem(Lista *l, Item *item){  
    if (item != NULL) {
        Item *item = item->prox;
        if (item == l->fim) { l->fim = item; }
        item->prox = item->prox;
        free(item);
    }
}

void printList(Lista *l) {
    Item *item = l->inicio->prox;
    while (item != NULL) {
        printf("%d ", item->item + 1);
        item = item->prox;
    }
    printf("\n");
}

void freeList(Lista *l) {
    Item *item = l->inicio;
    while (item != NULL) {
        l->inicio = item->prox;
        free(item);
        item = l->inicio;
    }
}