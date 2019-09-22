#include "stdio.h"
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>

#define LINHA_TAM 500
#define NUM_TAM 500

void initProgram(FILE *file) {
    int x, line = 1;
    char linhaAlfanumerica[LINHA_TAM], dados[NUM_TAM], *info;
    int N, M, I, charCtrl = 0;

    // Extract Informations:

    while(fscanf(file, "%s", linhaAlfanumerica) != EOF) {
        info = strtok(linhaAlfanumerica, " ");
        while (info != NULL) {
            // printf("Olha o carcatere %s\n", info);
            printf("Info - %s\n", info);

            if (charCtrl == 0) { N = atoi(info); } // Número de pessoas na equipe (Vertices)
            if (charCtrl == 1) { M = atoi(info); } // Número de relações (Arestas)
            if (charCtrl == 2) { I = atoi(info); } // Número de instruções (SWAP - COMMANDER -MEETING)

            charCtrl++;
            info = strtok(NULL, " ");
        }

    }
    printf("NMI %d%d%d", N,M,I);

}