//
//  headers.c
//  KalkulatoRPN
//
//  Created by Paweł Niedziółka on 31/01/2019.
//  Copyright © 2019 Paweł Niedziółka. All rights reserved.
//

#include "header.h"

int pop(stos **gora) {
    if(*gora!=NULL) {
        stos* top = *gora;
        int wartosc = top->dane;
        *gora = top->next;
        free(top);
        return wartosc;
    }
    else {
        fprintf(stderr,"Koniec stosu");
        return 1;
    }
    return 0;
}

int push(stos **gora,int wartosc) {
    stos* next=malloc(sizeof(stos)); //next - nowy element do dodania na stosie
    if(next!=NULL) {
        next->dane = wartosc;
        next->next = *gora;
        *gora = next;
    }
    else {
        fprintf(stderr,"Brakuje pamieci");
        return 1;
    }
    return 0;
}

int ktoredzialanie(char dzialanie,stos** gora) {
    int pom;
    switch(dzialanie) {
        case '+': return pop(gora) + pop(gora);
        case '*': return pop(gora) * pop(gora);  //tu musi sie wywalac program. pytanie czemu?
        case '-': pom = pop(gora); return pop(gora) - pom;
        case '/': pom = pop(gora); return pop(gora) / pom;
    }
    return 0;
}

int znak(char dzialanie) {
    switch(dzialanie) {
        case '+':
        case '*':
        case '-':
        case '/': return 2;
        default:
            fprintf(stderr,"Zly znak");
            return 1;
    }
    return 0;
}

int sprawdz(char* liczba) {
    for(;*liczba!=0;liczba++) {
        if(*liczba<'0'||*liczba>'9') {
            return 0;
        }
    }
    return 1;
}
