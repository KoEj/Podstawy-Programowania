//
//  headers.h
//  KalkulatoRPN
//
//  Created by Paweł Niedziółka on 31/01/2019.
//  Copyright © 2019 Paweł Niedziółka. All rights reserved.
//

#ifndef headers_h
#define headers_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stos{
    int dane;
    struct stos *next;
} stos;

int pop(stos**);
int push(stos**,int);
int ktoredzialanie(char,stos**);
int znak(char);
int sprawdz(char*);

#endif /* headers_h */
