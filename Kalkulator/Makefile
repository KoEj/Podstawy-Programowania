#plik makefile
all:a.out

kalkulator.o:kalkulator.c header.h
	gcc -Wall -c kalkulator.c

main.o:main.c header.h
	gcc -Wall -c main.c

a.out:main.o kalkulator.o
	gcc main.o kalkulator.o
