#include <stdio.h>
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	if (argc != 2) /* argc deve ser igual a 2 para ./tp1 e filename.txt */ {
        printf("Erro", argv[0]);
	} else {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf( "Não foi possível abrir o arquivo!\n");
        }
        else  {
			initProgram(file);
            fclose(file);
        }
    }
	return 0; 
}