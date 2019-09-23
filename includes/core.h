#include "grafo.h"

// #1)
void updateEdgesArr(Time *t, int edge1, int edge2);
// #2)
int checkCicle(Time *t, int position, int *visitedCtrl);
// #3)
int findBoss(Time *t, int position, int *visitedCtrl, int underAge);
// #4)
int commander(Time *t, int edge);
// #5)
int swap(Time *t, int edge1, int edge2);
// #6)
void meeting(Time *t, Pilha *p, int *visitedCtrl, int position);
// #7)
void makeInstructions(Time *t);
// #8)
void makeEmptyArrInt(int *arr, int tam);
// #9)
void printAllInformations(int N, int M, int I, int *ages, int *edges, int *instructions, int *S_C_M_instruction);
// #10)
void initProgram(FILE *file);