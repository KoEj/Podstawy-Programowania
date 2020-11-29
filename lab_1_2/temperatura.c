//
//  temperatura.c
//  Studia
//
//  Created by Paweł Niedziółka on 13/10/2018.
//  Copyright © 2018 Pawel Niedziolka. All rights reserved.
//

#include <stdio.h>

int main()
{
    float x;
    printf("* Jezeli chcesz podac dokladna wartosc temperatury pamietaj o kropce (np. 36.6)\n");
    printf("Podaj aktualna temperature we Wroclawiu: ");
    scanf("%f", &x);
    
    if (x<-30) printf("Naprawde jest tak zimno? Sprawdz czy dobrze wpisales temperature!");
    if (-30<=x && x<=-10) printf("Dzisiaj jest naprawde zimno");
    if (-10<x && x<=10) printf("Dzisiaj jest dosyc chlodno");
    if (10<x && x<=25) printf("Dzisiaj jest bardzo przyjemnie");
    if (25<x && x<=40) printf("Dzisiaj jest upalnie, pamietaj wez ze soba butelke wody");
    if (x>40) printf("Na pewno wpisales dobra tempereture? To malo prawdopodobne aby bylo az tak goraco!");
    
    
    
}
