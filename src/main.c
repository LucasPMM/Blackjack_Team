#include <stdio.h>
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>
// #include <time.h>

int main(int argc, char const *argv[]) {
	if (argc != 2) /* argc deve ser igual a 2 para ./tp1 e filename.txt */ {
        printf("Insira o nome do arquivo como parâmetro");
	} else {
        // Código utilizado para a marcação do tempo de execução:
        // int clk = 0;
        // for (clk = 0; clk < 20; clk++) {
        //     clock_t tempoInicial;
        //     clock_t tempoFinal;
        //     tempoInicial = clock();

            FILE *file = fopen(argv[1], "r");
            if (!file) {
                printf( "Não foi possível abrir o arquivo!\n");
            }
            else  {
                initProgram(file);
                fclose(file);
            }
            // tempoFinal = clock(); 
            // printf("\nTempo:%f\n",(tempoFinal- tempoInicial) * 1000.0 / CLOCKS_PER_SEC);
        // }

    }
	return 0; 
}