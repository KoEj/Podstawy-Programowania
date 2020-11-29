//
//  main.c
//  tetno
//
//  Created by Paweł Niedziółka on 26/10/2018.
//  Copyright © 2018 Pawel Niedziolka. All rights reserved.
//
 
#include <stdio.h>
#include <math.h>

#define sort 99   // ilosc liczb w grupie
#define koniec 99
#define lmin -10
#define lmax 10
#define czestmax 14
#define czestmin 8

int main()
{
    float liczba1; //liczba wprowadzana
    float liczba2; //przechowuje wartosc poprzedniej liczby potrzebnej do sprawdzenia znaku
    int czest;
    int numer;
    liczba1=liczba2=czest=numer=0;
    
    while(liczba1!=koniec){
        scanf ("%f", &liczba1);
        ++numer;
        
        if((liczba1<=lmax) && liczba1>=lmin){ //warunek prawidlowej liczby
            if (liczba1*liczba2<0)        // sprawdzenie czy rozne znaki
                ++czest;
            if (liczba1!=0)
                liczba2=liczba1;
        }
        
        if (numer==sort){
            { //printf(" ddsdasd:   %d ",czest);
                // powyzsza linijka sluzyla do testow
                if((czest<=czestmax) && (czest>=czestmin)) //warunek prawidlowej czestotliwosci
                    printf("Liczba przeciec zera: %d\n",czest);
                else
                    printf("Zla czestotliwosc!\n");
            }
            numer=0;
            czest=0;
            liczba2=0;      // reset 
        }
    }
}

