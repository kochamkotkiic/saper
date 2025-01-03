#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plansza.h"
void tworzenie_planszy(char ***plansza,int wiersze,int kolumny){
    *plansza=malloc(wiersze * sizeof(char *));
    for (int i=0;i<wiersze;i++){
        (*plansza)[i]=malloc(kolumny * sizeof(char));
        for(int j=0;j<kolumny;j++){
            (*plansza)[i][j]="."; //oznacza nieodkryte pole
        }
    }
}
void wyczysc_plansze(char **plansza,int wiersze){
    for(int i=0;i<wiersze;i++){
        free(plansza[i]);
    }
    free(plansza);
}

void losowanie_min(char **plansza,int wiersze,int kolumny, int liczba_min){
    srand(time(NULL));
    int naniesione=0;
    while(naniesione<liczba_min){
        int x = rand() % wiersze;
        int y = rand() % kolumny;

        if (plansza[x][y] != '*') { // oznacza minę
            plansza[x][y] = '*';
            naniesione++;
        }
    }
}
int zliczanie_sasiednich_min(char **plansza, int wiersze, int kolumny, int x, int y) {
    int licznik = 0;

    for (int dx = -1; dx <= 1; dx++) {  // w dół, ten sam wiersz, lub w góre
        for (int dy = -1; dy <= 1; dy++) { //analogicznie zmiant
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < wiersze && ny >= 0 && ny < kolumny && plansza[nx][ny] == '*') {
                licznik++;
            }
        }
    }

    return licznik;
}

void obliczanie_sasiednich_min(char **plansza, int wiersze, int kolumny) {
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            if (plansza[i][j] != '*') {
                plansza[i][j] = '0' + zliczanie_sasiednich_min(plansza, wiersze, kolumny, i, j);
            }
        }
    }
}
