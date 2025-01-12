#include <stdio.h>
#include "interfejs.h"


void wypisz_plansze(char **plansza, int wiersze, int kolumny) {
    // indeksy kolumn
    printf("   ");
    for (int j = 0; j < kolumny; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < wiersze; i++) {
        // indeksy wiersza
        printf("%2d ", i);

        for (int j = 0; j < kolumny; j++) {
            if (plansza[i][j] == 'X') {
                printf("? ");  // zakryte pole
            } else if (plansza[i][j] == 'F') {
                printf("F ");  // flaga
            } else if (plansza[i][j] == '*') {
                printf("? ");  // mina ale nie odkryta wiec nie pokazujemy
            } else if(plansza[i][j]=='!'){ //odkryta mina wiec pokazujemy
                printf("* ");
            } else {
                printf("%c ", plansza[i][j]);  // odkryte pole z liczbą
            }
        }
        printf("\n");
    }
}


