#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "po2.h"
#include "struct.h"

#define DL_LINII 1024
t_obraz obraz;

void wyswietl(char *n_pliku) {
    char polecenie[DL_LINII];
    
    strcpy(polecenie,"display ");
    strcat(polecenie,n_pliku);
    strcat(polecenie," &");
    printf("%s\n",polecenie);
    system(polecenie);
}


int main(int argc, char ** argv)
{
    int odczytano=0;
    w_opcje opcje;
    
    printf("\nKod wykonania programu: %d\n", przetwarzaj_opcje(argc,argv,&opcje,&obraz));

        if (opcje.plik_we != NULL) {
            odczytano = czytaj(opcje.plik_we,&obraz);
            fclose(opcje.plik_we);
        }
        
        if ((opcje.plik_we != NULL)  && (odczytano!=0)) {
            if (opcje.negatyw==1) {
                negatyw(&obraz);
            }
            if (opcje.progowanie==1) {
                progowanie(&obraz, opcje.w_progu);
            }
            if (opcje.konturowanie==1) {
                konturowanie(&obraz);
            }
            if ((opcje.konwersja==1) || (opcje.konwersja==2) || (opcje.konwersja==3)) {
                kolor(&obraz,opcje.konwersja-1);
            }
            if (opcje.konwersja==4) {
                konw_szarosci(&obraz);
            }
        }
            zapisz(opcje.plik_wy,&obraz);
    

        fclose(opcje.plik_wy);
        if (opcje.plik_we != NULL) {
            if (opcje.wyswietlenie==1) {
            wyswietl(opcje.wyjscie);}

            free(obraz.piksele);
            return odczytano;
        }
}
