#include <stdio.h>
#include "interfejs.h"

void wypisz_plansze(char **plansza, int wiersze, int kolumny) {
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            if (plansza[i][j] == 'X') {
                printf("? ");  // zakryte pole
            } 
            else if (plansza[i][j] == 'F') {
                printf("F ");  // flaga
            } 
            else {
                printf("%c ", plansza[i][j]);  // odkryte pole z liczbą lub miną
            }
        }
        printf("\n");
    }
}

void zaktualizuj_plansze(char **plansza, int wiersze, int kolumny, int x, int y, char znak) {
    plansza[x][y] = znak; //aktualizacja o dany znak
    wypisz_plansze(plansza, wiersze, kolumny);  /