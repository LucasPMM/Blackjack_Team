#include <stdio.h>
#include "../includes/core.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	if (argc != 2) /* argc should be 2 for ./tp1 and filename.txt */ {
        printf("usage: %s is provided,filename is not provided", argv[0]);
	} else {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf( "Could not open file\n");
        }
        else  {
			initProgram(file);
            fclose(file);
        }
    }
	return 0; 
}