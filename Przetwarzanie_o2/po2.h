#include "struct.h"

int czytaj(FILE*,t_obraz *obraz);
int zapisz(FILE*,t_obraz *obraz);
int negatyw(t_obraz *obraz);
int progowanie(t_obraz *obraz,int);
int konturowanie(t_obraz *obraz);
int przetwarzaj_opcje(int, char**, w_opcje *wybor, t_obraz *obraz);
void wyzeruj_opcje(w_opcje *wybor);
t_obraz kolor(t_obraz *obraz, int);
t_obraz konw_szarosci(t_obraz *obraz);
