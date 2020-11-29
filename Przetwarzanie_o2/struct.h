//
//  struct.h
//  Odczytywanie obrazów oddzielne
//
//  Created by Paweł Niedziółka on 13/01/2019.
//  Copyright © 2019 Paweł Niedziółka. All rights reserved.
//

#ifndef struct_h
#define struct_h
typedef struct {
    int wymx, wymy, odcieni,szarosci;
    void *piksele;
    int kolor; //jeżeli obraz kolorowy =1 / w przeciwnym przypadku (P2) kolor =0
}   t_obraz;

typedef struct {
    FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
    int negatyw,progowanie,konturowanie,wyswietlenie;      /* opcje */
    int w_progu;              /* wartosc progu dla opcji progowanie */
    char *wyjscie;
    int konwersja;  //1-red   2-green   3-blue   4-szarosci
} w_opcje;
#endif /* struct_h */
