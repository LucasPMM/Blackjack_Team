
#include <stdio.h>
#include "../includes/grafo.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	if ( argc != 2 ) /* argc should be 2 for ./a.out and filename.txt */ {
        printf("usage: %s is provided,filename is not provided", argv[0]);
	} else {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf( "Could not open file\n");
        }
        else  {
            int x;
            while  ((x = fgetc(file)) != EOF) {
                printf("%c", x);
            }
            fclose(file);
        }
    }
	return 0; 
}