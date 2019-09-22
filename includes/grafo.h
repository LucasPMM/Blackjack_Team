#include "listas.h"

// Foi definido uma estrutura baseada em uma lista de adjacências para representar as arestas do grafo,
// dessa forma, temos um vetor de listas.

typedef struct {
    int *ages;
    Lista *edges;
    int *edgesArr;
    int N; // Número de membros do time
    int M; // Número de relações
    int I; // Número de instruções

    int *instructionsCode; // 0 = S --- 1 = C --- 2 = M
    int *instructionsDecode; // Vértices nos quais devem ser aplicados as instruções
} Time;

void makeEmptyGraph(Time *t, int N, int M, int I, int *ages, int *edges, int *instructions, int *S_C_M_instruction);
void insertEdges(Time *t);
void freeGraph(Time *t);
void printGraph(Time *t);

// As funções foram desenvolvidas com base no conteúdo da matéria Estrutura de Dados feita em 2019.1