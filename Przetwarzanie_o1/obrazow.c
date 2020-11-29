//
//  main.c
//  Odczytywanie obrazow funkcje
//
//  Created by Paweł Niedziółka on 23/11/2018.
//  Copyright © 2018 Paweł Niedziółka. All rights reserved.
//
 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */
#define KONIEC 99

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy                                                *
 *                                            *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM                *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz            *
 * \param[out] wymx szerokosc obrazka                            *
 * \param[out] wymy wysokosc obrazka                            *
 * \param[out] szarosci liczba odcieni szarosci                        *
 * \return liczba wczytanych pikseli                            *
 ************************************************************************************/


int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
    char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
    int znak;                /* zmienna pomocnicza do czytania komentarzy */
    int koniec=0;            /* czy napotkano koniec danych w pliku */
    int i,j;
    
    /*Sprawdzenie czy podano prawidłowy uchwyt pliku */
    if (plik_we==NULL) {
        fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
        return(0);
    }
    
    /* Sprawdzenie "numeru magicznego" - powinien być P2 */
    if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
        koniec=1;                              /* Nie udalo sie? Koniec danych! */
    
    if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
        fprintf(stderr,"Blad: To nie jest plik PGM\n");
        return(0);
    }
    
    /* Pominiecie komentarzy */
    do {
        if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
            if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
                koniec=1;                   /* Zapamietaj ewentualny koniec danych */
        }  else {
            ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
        }                                         /* nie jest '#' zwroc go                 */
    } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
    /* i nie nastapil koniec danych         */
    
    /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
    if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
        fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
        return(0);
    }
    /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
    for (i=0;i<*wymy;i++) {
        for (j=0;j<*wymx;j++) {
            if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
                fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
                return(0);
            }
        }
    }
    return *wymx**wymy;
}


int zapisz(FILE *plik_wy, int obraz_pgm[][MAX], int wymx, int wymy, int szarosci)
{
    fprintf(plik_wy,"P2\n%d %d\n%d\n",wymx,wymy,szarosci);
    for(int i=0;i<wymy;i++) {
        for(int j=0;j<wymx;j++) {
            fprintf(plik_wy,"%d ",obraz_pgm[i][j]);
        }
        fprintf(plik_wy,"\n");
    }
    return 0;
}

int negatyw(int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci)
{
    for (int i=0;i<*wymy;i++) {
        for (int j=0;j<*wymx;j++)
            obraz_pgm[i][j]=*szarosci-obraz_pgm[i][j];
    }
    return 0;
}

int progowanie(int obraz_pgm[][MAX], int *wymx, int *wymy, int *szarosci,int prog)
{  
    int p = (prog**szarosci)/100;           // dzieki temu mozemy wpisac wartosc wyrazona w  %
    for (int i=0;i<*wymy;i++) {
        for (int j=0;j<*wymx;j++) {
            if (obraz_pgm[i][j]<=p) obraz_pgm[i][j]=0;
            else obraz_pgm[i][j]=*szarosci;
        }
    }
    return 0;
}

int konturowanie(int obraz_pgm[][MAX],int *wymx, int *wymy, int *szarosci)
{
    for (int i=0;i<*wymy-1;i++) {
        for (int j=0;j<*wymx-1;j++) {
            int z=0;
            
            if (j+1<*wymx) z=z+abs(obraz_pgm[i][j+1]-obraz_pgm[i][j]);  //abs - zwraca wartosc bezwzglena z int
            else z=z+obraz_pgm[i][j];
            if (i+1<*wymy) z=z+abs(obraz_pgm[i+1][j]-obraz_pgm[i][j]);
            else z=z+obraz_pgm[i][j];
            
            obraz_pgm[i][j]=z;
        }
    }
    
    return 0;
}

void wyswietl(char *n_pliku) {
    char polecenie[DL_LINII];
    
    strcpy(polecenie,"display ");
    strcat(polecenie,n_pliku);
    strcat(polecenie," &");
    printf("%s\n",polecenie);
    system(polecenie);
}


int wybor()                                            //zalozenie z->integer - dziala tylko dla liczb
{
    int z;
    z=0;
    printf("Proste menu:\n");
    printf("1 - Oryginalny obraz\n");
    printf("2 - Negatyw\n");
    printf("3 - Progowanie\n");
    printf("4 - Konturowanie\n");
    printf("5 - Koniec pracy programu\n");
    printf("Wybieram pozycje nr: ");
    scanf("%d",&z);
        
    switch(z){
        case 1:
            printf("Wybrales pozycje 1 - oryginalny obraz\n\n");
            return z;
            break;
        case 2:
            printf("Wybrales pozycja 2 - negatyw\n");
            return z;
            break;
        case 3:
            printf("Wybrales pozycje 3 - progowanie\n");
            return z;
            break;
        case 4:
            printf("Wybrales pozycje 4 - konturowanie\n");
            return z;
            break;
        case 5:
            printf("Wybrales pozycje 5\n");
            printf("Koniec pracy programu!\n");
            return z;
            break;
        default:
            printf("Podales zla liczbe\n");
            break;
    }
    return 0;
}

int main()
{
    int obraz[MAX][MAX];
    int wymx,wymy,odcieni,a,prog;
    int odczytano = 0;
    int k=0;
    FILE *plik;
    char nazwa[100];
    
    printf("Podaj nazwe pliku:\n");
    scanf("%s",nazwa);
    do {
        plik=fopen(nazwa,"r");
    
        if (plik != NULL) {
            odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
            fclose(plik);
        }
        
        plik=fopen("nazwa_zapis.pgm","w");
    
        if ((plik != NULL) && (odczytano!=0)) {
            a=wybor();
            if (a==1) {
                wyswietl(nazwa);
                getchar();
            }
            if (a==2) {
                negatyw(obraz, &wymx, &wymy, &odcieni);
                getchar();
            }
            if (a==3) {
	        prog=0;
	        printf("Jaki prog? [w %%] ");
	        scanf("%d",&prog);
                progowanie(obraz, &wymx, &wymy, &odcieni, prog);
                getchar();
            }
            if (a==4) {
                konturowanie(obraz, &wymx, &wymy, &odcieni);
                getchar();
            }
            if (a==5)  k=KONIEC;
	    
            zapisz(plik,obraz,wymx,wymy,odcieni);
            fclose(plik);
        }
        else {
            printf("Nie ma takiego pliku!\n");
            return KONIEC;                              //jezeli nie odczytano prawidlowo pliku program zwroci wartosc KONIEC -> 99
        }
    
        if ((odczytano != 0) && (a!=1) && (a!=5)) {     //dwa ostatnie warunki zapobiegają wyświetlaniu się nowego zdj w 1. i 5. opcji
            wyswietl("nazwa_zapis.pgm");
            printf("Kliknij dowolny przycisk");
            getchar();
        }
    }
    while (k!=KONIEC);
    
    return odczytano;
}
