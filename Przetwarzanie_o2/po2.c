#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "po2.h"
#include "struct.h"

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

#define DL_LINII 1024


int czytaj(FILE *plik_we,t_obraz *obraz) {
    char buf[DL_LINII];      //bufor pomocniczy do czytania naglowka i komentarzy
    int znak;                // zmienna pomocnicza do czytania komentarzy
    int koniec=0;            // czy napotkano koniec danych w pliku
    int i,j,k;
    
    //Sprawdzenie czy podano prawidłowy uchwyt pliku
    if (plik_we==NULL) {
        fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
        return(0);
    }
    
    // Sprawdzenie "numeru magicznego" - powinien być P2
    if (fgets(buf,DL_LINII,plik_we)==NULL)   // Wczytanie pierwszej linii pliku do bufora
        koniec=1;                              // Nie udalo sie? Koniec danych!
    
    if ((buf[0]!='P') || ((buf[1]!='2') && (buf[1]!='3')) || koniec){  // Czy jest magiczne "P2/P3"
        fprintf(stderr,"Blad: To nie jest plik PGM/PPM\n");
        return(0);
    }

    //sprawdzenie i zapamietanie w strukturze
   if ( (buf[0]!='P') || (buf[1]!='2') || koniec) obraz->kolor=0;
   if ( (buf[0]!='P') || (buf[1]!='3') || koniec) obraz->kolor=1;
    
    // Pominiecie komentarzy
    do {
        if ((znak=fgetc(plik_we))=='#') {
            if (fgets(buf,DL_LINII,plik_we)==NULL)
                koniec=1;
        }  else {
            ungetc(znak,plik_we);
        }
        
    } while (znak=='#' && !koniec);

    // Pobranie wymiarow obrazu i liczby odcieni szarosci
    if (fscanf(plik_we,"%d %d %d", &(obraz->wymx),&(obraz->wymy),&(obraz->szarosci))!=3) {
        fprintf(stderr,"Blad wczytywania wymiaru obrazow");
        return(0);
    }
    
    if (obraz->kolor==0){
        //zadeklarowanie tablicy dynamicznej, zalokowanie pamięci
        obraz->piksele = malloc(obraz->wymx*obraz->wymy*sizeof(int));
        int (*piksele)[obraz->wymx];
        piksele=(int(*)[obraz->wymx]) obraz->piksele;
    
        // Pobranie obrazu i zapisanie w tablicy dynamicznej piksele
        for(i=0; i < obraz->wymy; i++) {
            for(j=0; j < obraz->wymx; j++) {
            fscanf(plik_we, "%d", &(piksele[i][j]));
            }
        }
    }
    else if (obraz->kolor==1){
        //zadeklarowanie tablicy dynamicznej, zalokowanie pamięci dlaobrazu kolorowego
        obraz->piksele = malloc(3*obraz->wymx*obraz->wymy*sizeof(int));
        int (*piksele)[obraz->wymx][3];
        piksele=(int(*)[obraz->wymx][3]) obraz->piksele;
        
        // Pobranie obrazu i zapisanie w tablicy dynamicznej piksele
            for(i=0; i < obraz->wymy; i++) {
                for(j=0; j < obraz->wymx; j++) {
                    for (k=0; k<3;k++)
                    {
                    fscanf(plik_we, "%d", &(piksele[i][j][k]));
                    }
                }
            }
    }
    
    return (obraz->wymx * obraz->wymy);
}

int zapisz(FILE *plik_wy, t_obraz *obraz)
{
    int (*piksele)[obraz->wymx];
    piksele=(int(*)[obraz->wymx]) obraz->piksele;
    
    if (obraz->kolor==0) {
        fprintf(plik_wy,"P2\n%d %d\n%d\n",obraz->wymx,obraz->wymy,obraz->szarosci);
    }
    if (obraz->kolor==1) {
        fprintf(plik_wy,"P3\n%d %d\n%d\n",obraz->wymx,obraz->wymy,obraz->szarosci);
    }
    for(int i = 0; i < obraz->wymy; i++) {
        for(int j = 0; j < obraz->wymx; j++) {
            fprintf(plik_wy,"%d ",piksele[i][j]);
        }
        fprintf(plik_wy,"\n");
    }
    return 0;
}

int negatyw(t_obraz *obraz)
{
    int (*piksele)[obraz->wymx];
    piksele=(int(*)[obraz->wymx]) obraz->piksele;
    
    for (int i=0;i<obraz->wymy;i++) {
        for (int j=0;j<obraz->wymx;j++)
            piksele[i][j]=obraz->szarosci-piksele[i][j];
    }
    return 0;
}

int progowanie(t_obraz *obraz,int prog)
{
    int (*piksele)[obraz->wymx];
    piksele=(int(*)[obraz->wymx]) obraz->piksele;
    
    int p = (prog*obraz->szarosci)/100;           // dzieki temu mozemy wpisac wartosc wyrazona w  %
    for (int i=0;i<obraz->wymy;i++) {
        for (int j=0;j<obraz->wymx;j++) {
            if (piksele[i][j]<=p) piksele[i][j]=0;
            else piksele[i][j]= (obraz->szarosci);
        }
    }
    return 0;
}

int konturowanie(t_obraz *obraz)
{
    int (*piksele)[obraz->wymx];
    piksele=(int(*)[obraz->wymx]) obraz->piksele;
    
    for (int i=0;i<obraz->wymy-1;i++) {
        for (int j=0;j<obraz->wymx-1;j++) {
            int z=0;
            
            if (j+1<(obraz->wymx)) z=z+abs(piksele[i][j+1]-piksele[i][j]);  //abs - zwraca wartosc bezwzglena z int
            else z=z+(piksele[i][j]);
            if (i+1<(obraz->wymy)) z=z+abs(piksele[i+1][j]-piksele[i][j]);
            else z=z+(piksele[i][j]);
            
            piksele[i][j]=z;
        }
    }
    
    return 0;
}

t_obraz kolor(t_obraz *obraz, int kolor)
{
    int i,j;
    t_obraz druga;  //pomocnicza druga tablica
    druga=*obraz;
    
    //deklaracja tablicy ze zmiennymi dynamicznymi
    druga.piksele = malloc(druga.wymx*druga.wymy*sizeof(int));
    int(*zdjecie)[druga.wymx];
    zdjecie=(int(*)[druga.wymx])druga.piksele;
    int(*org)[obraz->wymx][3];              //org- obrazek oryginalny
    org=(int(*)[obraz->wymx][3])obraz->piksele;
    //zapisanie obrazu do tablicy
    for (i=0;i<obraz->wymy;i++) {
        for (j=0;j<obraz->wymx;j++) {
            zdjecie[i][j] = org[i][j][kolor];
        }
    }
    return druga;
}

t_obraz konw_szarosci(t_obraz *obraz)  //konwersja szarosci
{
    int i,j;
    t_obraz druga; //pomocnicza druga tablica
    druga=*obraz;
    
    //deklaracja tablicy ze zmiennymi dynamicznymi
    druga.piksele = malloc(druga.wymx*druga.wymy*sizeof(int));
    int(*zdjecie)[druga.wymx];
    zdjecie=(int(*)[druga.wymx])druga.piksele;
    int(*org)[obraz->wymx][3];  //org - obrazek oryginalny
    org=(int(*)[obraz->wymx][3])obraz->piksele;
    //zaisanie obrazu do tablicy
    for (i=0;i<obraz->wymy;i++) {
        for (j=0;j< obraz->wymx;j++) {
            zdjecie[i][j] = (org[i][j][0] + org[i][j][1] + org[i][j][2]) / 3;
        }
    }
    return druga;
}

/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2013 ZPCiR */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/* ZRÓDŁO http://kcir.pwr.edu.pl/~mucha/PProg/PProg_lab_05/opcje.c  */
/********************************************************************/

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(w_opcje*wybor) {
    wybor->plik_we=NULL;
    wybor->plik_wy=NULL;
    wybor->negatyw=0;
    wybor->konturowanie=0;
    wybor->progowanie=0;
    wybor->wyswietlenie=0;
    wybor->konwersja=0;
}

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*    poprawnie wystapily w linii wywolania programu,                 */
/*    pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*    zwraca wartosc W_OK, gdy wywolanie bylo poprawne                */
/*    lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor, t_obraz *obraz) {
    int i, prog;
    char *nazwa_pliku_we;
    
    wyzeruj_opcje(wybor);
    wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */
    
    for (i=1; i<argc; i++) {
        if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
            return B_NIEPOPRAWNAOPCJA;
        switch (argv[i][1]) {
            case 'i': {                 /* opcja z nazwa pliku wejsciowego */
                if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
                    nazwa_pliku_we=argv[i];
                    if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
                        wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
                    else                               /* otwieramy wskazany plik   */
                        wybor->plik_we=fopen(nazwa_pliku_we,"r");
                } else
                    return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
                break;
            }
            case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
                if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
                    wybor->wyjscie=argv[i];
                    if (strcmp(wybor->wyjscie,"-")==0)/* gdy nazwa jest "-"         */
                        wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
                    else                              /* otwieramy wskazany plik    */
                        wybor->plik_wy=fopen(wybor->wyjscie,"w");
                } else
                    return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
                break;
            }
            case 'p': {
                if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if (sscanf(argv[i],"%d",&prog)==1) {
                        wybor->progowanie=1;
                        wybor->w_progu=prog;
                    } else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                break;
            }
            case 'n': {                 /* mamy wykonac negatyw */
                wybor->negatyw=1;
                break;
            }
            case 'k': {                 /* mamy wykonac konturowanie */
                wybor->konturowanie=1;
                break;
            }
            case 'd': {                 /* mamy wyswietlic obraz */
                wybor->wyswietlenie=1;
                break;
            }
            case 'm': {
                if (++i<argc) {
                    switch(argv[i][0]) {
                        case 'r': { //czerwony
                            if (obraz->kolor==1) {
                                wybor->konwersja=1;
                            }
                            else fprintf(stderr,"To nie jest obraz kolorowy!");
                            break;
                        }
                        case 'g': { //zielony
                            if (obraz->kolor==1) {
                                wybor->konwersja=2;
                            }
                            else fprintf(stderr,"To nie jest obraz kolorowy!");
                            break;
                        }
                        case 'b': { //niebieski
                            if (obraz->kolor==1) {
                                wybor->konwersja=3;
                            }
                            else fprintf(stderr,"To nie jest obraz kolorowy!");
                            break;
                        }
                        case 's': { //szarosc
                            if (obraz->kolor==1) {
                                wybor->konwersja=4;
                            }
                            else fprintf(stderr,"To nie jest obraz kolorowy!");
                            break ;
                        }
                        default:                    /* nierozpoznana opcja */
                            return B_NIEPOPRAWNAOPCJA;
                    } //koniec switcha [case m:]
                }
                else return B_BRAKWARTOSCI;
            }
            default:                    /* nierozpoznana opcja */
                return B_NIEPOPRAWNAOPCJA;
        } /*koniec switch */
    } /* koniec for */
    
    if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
        return W_OK;              //wszystko dobrze - kod wykonania programu: 0
    else
        return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}
