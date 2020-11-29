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
