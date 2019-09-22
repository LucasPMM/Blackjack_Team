#include "stdio.h"
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>

#define SIZE 500

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
    // Control variables to extract info:
    int x, line = 1;
    char linhaAlfanumerica[SIZE], dados[SIZE], *info;
    int charCtrl = 0, edgeCtrl = 0, instrCtrl1 = 0, instrCtrl2 = 0;

    // Variables to represente the info extracted:
    int N, M, I, *ages, *edges, *instructions, S_C_M_instruction[SIZE];
    // For instructions:
    // 0 = S --- 1 = C --- 2 = M

    // Initialize arrays with -1 and "*" to represente an empty position
    makeEmptyArrInt(S_C_M_instruction, SIZE);

    // Extract Informations:

    while(fscanf(file, "%s", linhaAlfanumerica) != EOF) {
        info = strtok(linhaAlfanumerica, " ");
        while (info != NULL) {
            if (charCtrl == 0) { // Número de pessoas na equipe (Vertices)
                N = atoi(info);
                ages = (int*)calloc(N, sizeof(int));
            }
            else if (charCtrl == 1) { // Número de relações (Arestas)
                M = atoi(info);
                edges = (int*)calloc((M * 2), sizeof(int));
            }
            else if (charCtrl == 2) { // Número de instruções (SWAP - COMMANDER -MEETING)
                I = atoi(info);
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

    printAllInformations(N, M, I, ages, edges, instructions, S_C_M_instruction);

    free(info);
    free(ages);
    free(edges);
    free(instructions);
}