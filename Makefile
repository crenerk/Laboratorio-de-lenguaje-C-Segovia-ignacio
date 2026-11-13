CC = gcc
CFLAGS = -Wall -g
OBJS = main.o simulador.o validaciones.o

artemis: $(OBJS)
	$(CC) $(CFLAGS) -o artemis $(OBJS) -lm

main.o: main.c simulador.h validaciones.h
simulador.o: simulador.c simulador.h
validaciones.o: validaciones.c validaciones.h

clean:
	del *.o artemis.exe