//
//  main.c
//  KalkulatoRPN
//
//  Created by Paweł Niedziółka on 28/01/2019.
//  Copyright © 2019 Paweł Niedziółka. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int main( int argc, char** argv )
{
    int i, pom, stoss = 0;
    stos* gora = NULL;
    
    if(argc!=1)
    {
        for(i=1;i<argc;i++) {
            char* av=argv[i];
            char dzialanie;
        
            if(sprawdz(av)) {
                pom=atoi(av);
                push(&gora,pom);
                ++stoss;
            }
            else {
            if(strlen(av)!=1) {
                fprintf(stderr,"Argv jest za duzy");
                
            }
            dzialanie=av[0];
            if(stoss<znak(dzialanie)) {
                fprintf(stderr,"Za malo argumentow");
                return 1;
            }
            push(&gora,ktoredzialanie(dzialanie,&gora));
            stoss-=znak(dzialanie)-1;
            }
        }
    
        if(stoss!=1) {
            fprintf(stderr,"Za dużo argumentów");
            return 1;
        }
    
        printf("Wynik: %i\n",gora->dane);
        return 0;
        
    }
    else return 1;
}
