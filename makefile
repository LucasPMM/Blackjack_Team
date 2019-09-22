all: src/main.o src/grafo.o src/listas.o
	gcc -O3 src/main.o src/grafo.o src/listas.o -o tp1
	make clean
	clear

grafo.o: src/grafo.c includes/grafo.h
	gcc -O3 -c src/grafo.c

listas.o: src/listas.c includes/listas.h
	gcc -O3 -c src/listas.c

main.o: src/main.c
	gcc -O3 -c src/main.c

clean:
	rm src/*.o