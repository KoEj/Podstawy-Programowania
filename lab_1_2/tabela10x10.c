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


