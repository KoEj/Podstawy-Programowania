#plik makefile
all:a.out

po2.o:po2.c po2.h struct.h
	gcc -Wall -c po2.c

main.o:po2main.c po2.h struct.h
	gcc -Wall -c po2main.c

a.out:main.o po2.o po2.h struct.h
	gcc po2main.o po2.o
