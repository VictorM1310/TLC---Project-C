all: ProyectoTC

ProyectoTC: ProyectoTC.c ArregloTokens.o
	gcc -Wall -g -I ./ -o ProyectoTC ProyectoTC.c ArregloTokens.o

ArregloTokens.o: ArregloTokens.c ArregloTokens.h
	gcc -Wall -g -I ./ -c ArregloTokens.c

clean:
	rm *.o ProyectoTC
