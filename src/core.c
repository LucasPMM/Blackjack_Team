#include <stdio.h>
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE 500

void updateEdgesArr(Time *t, int edge1, int edge2) {
    int i;
    for (i = 0; i < t->M * 2; i += 2) {
        if (t->edgesArr[i] == edge1 && t->edgesArr[i + 1] == edge2) {
            t->edgesArr[i] = edge2;
            t->edgesArr[i + 1] = edge1;
        }
    }
}

// Retorna 1 caso tenha um ciclo no grafo e 0 caso contrário
// Quando chegamos no node e estamos ainda estamos processando ele é marcado como 1
// Quando o seu processamento acaba marcamos ele com 2,
int checkCicle(Time *t, int position, int *visitedCtrl) {
    Item *item = t->edges[position].inicio->prox;   
    visitedCtrl[position] = 1;
    // Implementação recursiva da uma DFS
    while (item != NULL) {
	    if (visitedCtrl[item->item] == 1 || checkCicle(t, item->item, visitedCtrl)) {
            return 1; 
        }
        item = item->prox;
    }
    visitedCtrl[position] = 2;
    return 0;
}


// Retorna a idade do chefe mais novo ou -1 caso o vértice não tenha nenhum chefe
int findBoss(Time *t, int position, int *visitedCtrl, int underAge) {
    // Encontra a menor idade do item presente no componente fortemente conectado em questão:

    Item *item = t->edges[position].inicio->prox;   

    visitedCtrl[position] = 1;
    // Implementação recursiva da uma DFS
    while (item != NULL) {
	    if (!visitedCtrl[item->item]) {
            if (underAge > t->ages[item->item]) { underAge = t->ages[item->item]; }
            return findBoss(t, item->item, visitedCtrl, underAge);
        }
        item = item->prox;
    }
    visitedCtrl[position] = 2;
    return underAge;
}

// Retorna -1 caso não encontre o commander e a idade caso contrário
int commander(Time *t, int edge) {
    // Gerar um grafo t2 que tenha as arestas invertidas em relação a t1 (transformar comandados em comandantes e vice versa)
    // Rodar um DFS a partir do vértice V e achar o "chefe mais novo que ele comanda"
    int *inversedEdges, i;
    inversedEdges = (int*) calloc(t->M * 2, sizeof(int));

    for(i = 0; i < t->M * 2; i++) {
        inversedEdges[i] = t->edgesArr[t->M * 2 - i - 1];
    }

    Time t2;
    makeEmptyGraph(&t2, t->N, t->M, t->I, t->ages, inversedEdges, t->instructionsCode, t->instructionsDecode);

    int *visitedCtrl;
    visitedCtrl = (int*) calloc(t->N, sizeof(int));
    int youngestBoss = findBoss(&t2, edge, visitedCtrl, INT_MAX);
    free(inversedEdges);
    free(visitedCtrl);
    return youngestBoss == INT_MAX ? -1 : youngestBoss;
}

// Retorna 1 caso um ciclo ocorra ou não seja possível fazer o SWAP e 0 caso o SWAP seja bem sucedido
int swap(Time *t, int edge1, int edge2) {
    int v1 = edge1, v2 = edge2;
    // Tenta encontrar uma aresta da edge1 para a edge2. Caso não encontre, tenta encontrar uma areseta da edge2 para a edge1
    Item *item = findItem(&t->edges[v1], v2);
    if (item == NULL) {
        Item *item = findItem(&t->edges[v2], v1);
        if (item == NULL) {
            return 1;
        } else { v1 = v2; v2 = v1; }
    }

    // Remove a aresta que liga v1 a v2
    removeItemPosition(&t->edges[v1], item);
    // Adicionar a aresta que liga v2 a v1
    addItemEnd(&t->edges[v2], v1);

    // Caso ocorra um ciclo o SWAP é desfeito
    int i, *visitedCtrl;
    visitedCtrl = (int*) calloc(t->N, sizeof(int));

    for (i = 0; i < t->N; i++) {
        if (visitedCtrl[i] == 0 && checkCicle(t, i, visitedCtrl)) {
            // Remover a aresta que acabou de ser adicionada no final da lista de adjacências de v2
            removeItemEnd(&t->edges[v2]);
            // Adicionar novamente a aresta que liga v1 a v2 (não importa a posição)
            addItemEnd(&t->edges[v1], v2);
            return 1;
        }
    }
    // Atualizar o vetor de arestas
    updateEdgesArr(t, v1 + 1, v2 + 1);
    free(visitedCtrl);
    return 0;
}

void meeting(Time *t, Pilha *p, int *visitedCtrl, int position) {
    // Faz uma DFS a partir do vértice inicial e armazena na lista, com o uma ideia de fila, o vértices quando os mesmos terminarem
    Item *item = t->edges[position].inicio->prox;   
    visitedCtrl[position] = 1;
    // Implementação recursiva da uma DFS
    while (item != NULL) {
	    if (!visitedCtrl[item->item]) {
            meeting(t, p, visitedCtrl, item->item);
        }
        item = item->prox;
    }
    visitedCtrl[position] = 2;
    pushStack(position, p);
}

void makeInstructions(Time *t) {
    int i, instructionsCtrl = 0;
    for (i = 0; i < t->I; i++) {
        switch (t->instructionsCode[i]) {
            case 0: { // SWAP
                // Realiza a operação de SWAP.
                // Se gerar ciclo realiza a operação de SWAP novamente.
                // Verificação de ciclo com DFS: caso a visita ocorra em um vertice previamente visitado tem um ciclo.
                if (swap(t, t->instructionsDecode[instructionsCtrl] - 1, t->instructionsDecode[instructionsCtrl + 1] - 1)) {
                    printf("S N\n");
                }
                else { printf("S T\n"); }
                instructionsCtrl += 2;
                break;
            } 

            case 1: { // COMMANDER
                // Rodar a DFS e encontrar o vertice com a menor idade que alcança o vértice desejado.
                int boss = commander(t, t->instructionsDecode[instructionsCtrl] - 1);
                if (boss != -1) { printf("C %d\n", boss); }
                else { printf("C *\n"); }
                instructionsCtrl++;
                break;
            }

            case 2: { // MEETING
                // Rodar DFS e guardar os tempos de término
                // Quando um vértice terminar, o mesmo é inserido em uma pilha
                // A lista gerada será um DAG e, por conseguinte, a ordem de fala dos membros do time
                Pilha p;
                int i, *visitedCtrl;
                visitedCtrl = (int*) calloc(t->N, sizeof(int));
                makeEmptyStack(&p);
                for (i = 0; i < t->N; i++) {
                    if (visitedCtrl[i] == 0) {
                        meeting(t, &p, visitedCtrl, i);
                    }
                }

                printf("M ");
                printStack(&p);
                freeStack(&p);
                free(visitedCtrl);
                break;
            }
            
            default:
                break;
        }
    }
}

void makeEmptyArrInt(int *arr, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        arr[i] = -1;
    }
}

void printAllInformations(int N, int M, int I, int *ages, int *edges, int *instructions, int *S_C_M_instruction) {
    int i, j = 0;

    printf("\nTotal de integrantes: %d", N);
    printf("\nTotal de relações: %d", M);
    printf("\nTotal de instruções: %d\n", I);

    printf("\nIdades:\t");
    for (i = 0; i < N; i++) {
        printf("%d\t", ages[i]);
    }
    printf("\n");

    printf("Arestas:\n");
    for (i = 0; i < M * 2; i += 2) {
        printf("%d %d\n", edges[i], edges[i + 1]);
    }

    printf("Instruções:\n");
    for (i = 0; i < I; i++) {
        if (instructions[i] == 0) {
            printf("S\t");
            printf("%d %d", S_C_M_instruction[j], S_C_M_instruction[j + 1]);
            j += 2;
        } else if (instructions[i] == 1) {
            printf("C\t");
            printf("%d", S_C_M_instruction[j]);
            j++;
        } else if (instructions[i] == 2) {
            printf("M\t");
        }
        printf("\n");
    }
}

void initProgram(FILE *file) {
    // Variaveis de controle para extração da informação:
    int x, line = 1;
    char linhaAlfanumerica[SIZE], dados[SIZE], *info;
    int charCtrl = 0, edgeCtrl = 0, instrCtrl1 = 0, instrCtrl2 = 0;

    // Variaveis que representam a informação extraida:
    int N, M, I, *ages, *edges, *instructions, S_C_M_instruction[SIZE];
    // Decodificação das instruções:
    // 0 = S --- 1 = C --- 2 = M

    // Inicializando o array com -1 and "*" para representar as posições vazias
    makeEmptyArrInt(S_C_M_instruction, SIZE);

    // Extração de informações:

    while(fscanf(file, "%s", linhaAlfanumerica) != EOF) {
        info = strtok(linhaAlfanumerica, " ");
        while (info != NULL) {
            if (charCtrl == 0) { // Número de pessoas na equipe (Vertices)
                N = atoi(info);
                if (!N) { return; }
                ages = (int*)calloc(N, sizeof(int));
            }
            else if (charCtrl == 1) { // Número de relações (Arestas)
                M = atoi(info);
                if (!M) { return; }
                edges = (int*)calloc((M * 2), sizeof(int));
            }
            else if (charCtrl == 2) { // Número de instruções (SWAP - COMMANDER -MEETING)
                I = atoi(info);
                if (!I) { return; }
                instructions = (int*)malloc(I * sizeof(int));
            }
            else if (charCtrl > 2 && charCtrl <= 2 + N) { // Idades dos N membros
                ages[N - 1 - ((2 + N) - charCtrl)] = atoi(info);
            }
            else if (charCtrl > 2 + N && charCtrl <= 2 + N + M * 2) { // Pares de arestas a serem colocadas
                edges[edgeCtrl] = atoi(info);
                edgeCtrl++;
            }
            else { // Instruções
                if (!strcmp(info, "S") || !strcmp(info, "C") || !strcmp(info, "M")) {
                    if (!strcmp(info, "S")) { instructions[instrCtrl1] = 0; }
                    else if (!strcmp(info, "C")) { instructions[instrCtrl1] = 1; }
                    else if (!strcmp(info, "M")) { instructions[instrCtrl1] = 2; }
                    instrCtrl1++;
                } else {
                    S_C_M_instruction[instrCtrl2] = atoi(info);
                    instrCtrl2++;
                }
            }
            charCtrl++;
            info = strtok(NULL, " ");
        }

    }

    // printAllInformations(N, M, I, ages, edges, instructions, S_C_M_instruction);

    // --------------------------------------------------------------------------------------------------------------- // 

    Time t;
    // Criação do grafo e inserção das informações coletadas acima
    makeEmptyGraph(&t, N, M, I, ages, edges, instructions, S_C_M_instruction);

    // Executa as instruções:
    makeInstructions(&t);

    // Liberação de memória
    freeGraph(&t);
    free(info);
    free(ages);
    free(edges);
    free(instructions);
}