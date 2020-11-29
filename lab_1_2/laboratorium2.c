//
//  tabela10x10.c
//  Studia
//
//  Created by Paweł Niedziółka on 13/10/2018.
//  Copyright © 2018 Pawel Niedziolka. All rights reserved.
//

#include <stdio.h>

int main()
{
    int i=0;
    int j=0;
    int k=1;
    

    
        for(i=0;i<10;i++)
        {
            for(j=0;j<10;j++)
            {
            
            printf("\t%i",k);
                k=k+1;
                if(k==100) break;
            }
        printf(" \n");
            j=0;
        }
}


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
//
//  main.c
//  parametr (-5,5) do 99
//
//  Created by Paweł Niedziółka on 13/10/2018.
//  Copyright © 2018 Pawel Niedziolka. All rights reserved.
//

#include <stdio.h>

int main()
{
int i=1;
int x;

    for(i;i>0;i++)                  // nieskonczona petla, mozna zamienic na
    {                               // while(i<...) aby ograniczyc program do ... liczb
        printf("Podaj %d. wartosc parametru: ",i);
    scanf("%d",&x);
                                    // wtedy tu musimy dodac i=i+1
        if (x==99) {
            printf("Koniec pracy programu");
            break;
        }
        else
        {
            if (x>=-5 && x<=5)      
            {
                printf("Aktualna wartosc parametru wynosi: %d\n",x);
            }
            else printf("Bledna wartosc parametru!\n");
        }
    }
}
