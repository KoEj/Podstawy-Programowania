//
//  main.c
//  Przetwarzanieobr
//
//  Created by Paweł Niedziółka on 08/11/2018.
//  Copyright © 2018 Pawel Niedziolka. All rights reserved.
//

#include <stdio.h>
int x;
int y;
int i;
int j;
int tab[10][10];


void instswitch(){                      //isnstrukcja switch
    int z;                              //tylko dla int
    int i;                              //zakladam brak mozliwosci wpisaniu innego znaku niz liczba
    z=0;

    for(i=0;i==0;){
        printf("Proste menu:\n");
        printf("1 - Pozycja pierwsza\n");
        printf("2 - Pozycja druga\n");
        printf("3 - Pozycja trzecia\n");
        printf("4 - Zakończ działanie\n");
        printf("Wybieram pozycje nr: ");
        scanf("%d",&z);
        
       
        switch(z){
            case 1:
            printf("Wybrales pozycje pierwsza\n\n");
                break;
            case 2:
            printf("Wybrales pozycja druga\n\n");
                break;
            case 3:
            printf("Wybrales pozycje trzecia\n\n");
                break;
            case 4:
             printf("Wybrales pozycje czwarta\n");
                printf("Koniec pracy programu!\n\n");
                i=1;
                break;
            default:
            printf("Podales zla liczbe\n\n");
                break;
                }
            
            
    }
}

void wypelnij(int x, int y)
{
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            tab[i][j]=i*j;
        }
    }
}

void wypisz(int x, int y)
{
    for(i=0;i<x;i++){
            for(j=0;j<y;j++){
                printf("%d\t", tab[i][j]);
            }
    printf("\n");
    }
}


void zmien_znaki(int x, int y)
{
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            if(i*j!=0)
            tab[i][j]=i*j*(-1.0);
        }
    }
}


//------------------------------------------------------

int main()
{
    //tabela dwuwymiarowa
    wypelnij(3,7);
    printf("Zawartosc oryginalna: \n");
    wypisz(3,7);
    zmien_znaki(3,7);
    printf("Wartosc po zmianie znakow: \n");
    wypisz(3,7);
    
    //instrukcja wyboru switch
    printf("\n\n\n\n");
    instswitch();
    return 0;
}
