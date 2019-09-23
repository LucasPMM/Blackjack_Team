#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/grafo.h"

#define SIZE 500

void copyArr(int *origin, int *destiny, int tam) {
    int i;
    for(i = 0; i < tam; i++) {
        destiny[i] = origin[i];
    }
}

void makeEmptyGraph(Time *t, int N, int M, int I, int *ages, int *edges, int *instructions, int *S_C_M_instruction) {
    int i = 0;
    t->ages = (int*) calloc(N, sizeof(int));
    t->edgesArr = (int*) calloc(M * 2, sizeof(int));
    t->instructionsCode = (int*) calloc(I, sizeof(int));
    t->instructionsDecode = (int*) calloc(SIZE, sizeof(int));
    t->edges = (Lista*) malloc(N * sizeof(Lista));

    for (i = 0; i < N; i++) {
        makeEmptyList(&t->edges[i]);
    }
    t->N = N;
    t->M = M;
    t->I = I;
    copyArr(ages, t->ages, t->N);
    copyArr(edges, t->edgesArr, t->M * 2);
    copyArr(instructions, t->instructionsCode, I);
    copyArr(S_C_M_instruction, t->instructionsDecode, SIZE);

    insertEdges(t);
    // printGraph(t);
}

void printGraph(Time *t) {
    int i, j = 0;

    printf("\nTotal de integrantes: %d", t->N);
    printf("\nTotal de relações: %d", t->M);
    printf("\nTotal de instruções: %d\n", t->I);

    printf("\nIdades:\t");
    for (i = 0; i < t->N; i++) {
        printf("%d\t", t->ages[i]);
    }
    printf("\n");

    printf("Arestas:\n");
    for (i = 0; i < t->M * 2; i += 2) {
        printf("%d %d\n", t->edgesArr[i], t->edgesArr[i + 1]);
    }

    printf("Instruções:\n");
    for (i = 0; i < t->I; i++) {
        if (t->instructionsCode[i] == 0) {
            printf("S\t");
            printf("%d %d", t->instructionsDecode[j], t->instructionsDecode[j + 1]);
            j += 2;
        } else if (t->instructionsCode[i] == 1) {
            printf("C\t");
            printf("%d", t->instructionsDecode[j]);
            j++;
        } else if (t->instructionsCode[i] == 2) {
            printf("M\t");
        }
        printf("\n");
    }

    printf("\nArestas (+1):\n");
    for (i = 0; i < t->N; i++){
        printf("Vértice %d:\n", i + 1);
        printList(&t->edges[i]);
    }
}

void insertEdges(Time *t) {
    int i = 0;
    for (i = 0; i < t->M * 2; i += 2) {
        int origin = t->edgesArr[i] - 1;
        int destiny = t->edgesArr[i + 1] - 1;
        addItemEnd(&t->edges[origin], destiny);
    }
}

void freeGraph(Time *t) {
    free(t->ages);
    free(t->instructionsCode);
    freeList(t->edges);
}