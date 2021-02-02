CC=gcc
FLAGS=-Wall -Werror -g

all : 	prog

prog :	spa.o main.o
		$(CC) spa.o main.o -o prog -lm

fonctions.o:	spa.c spa.h
		$(CC) -c spa.c $(FLAGS) -o spa.o


clean :
		rm -f *.o
		rm -f prog