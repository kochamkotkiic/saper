#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plansza.h"
#include <string.h>
void tworzenie_planszy(char ***plansza,int wiersze,int kolumny){
    *plansza=malloc(wiersze * sizeof(char *));
    for (int i=0;i<wiersze;i++){
        (*plansza)[i]=malloc(kolumny * sizeof(char));
        for(int j=0;j<kolumny;j++){
            (*plansza)[i][j]='X'; //oznacza nieodkryte pole
        }
    }
}
void wyczysc_plansze(char **plansza,int wiersze){
    for(int i=0;i<wiersze;i++){
        free(plansza[i]);
    }
    free(plansza);
}
void losowanie_min(char **plansza, int wiersze, int kolumny, int liczba_min, int pierwszy_ruch_x, int pierwszy_ruch_y) {
    srand(time(NULL));
    int naniesione = 0;
    
    while (naniesione < liczba_min) {
        int x = rand() % wiersze;
        int y = rand() % kolumny;

        // sprawdzamy czy nie umieszczamy miny na pierwszym ruchu
        if ((x != pierwszy_ruch_x || y != pierwszy_ruch_y) && plansza[x][y] != '*') {
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

void obliczanie_sasiednich_min(char **plansza, int wiersze, int kolumny, int x, int y) {
    if (plansza[x][y] != '*') {
        plansza[x][y] = '0' + zliczanie_sasiednich_min(plansza, wiersze, kolumny, x, y);
    }
}
void odkryj_pole(char **plansza, int wiersze, int kolumny, int x, int y, int **odkryte) {
    // gdy współrzędne nie są w granicach planszy lub pole jest zakryte lub odkryte
    if (x < 0 || x >= wiersze || y < 0 || y >= kolumny || odkryte[x][y] == 1 || plansza[x][y] == 'F') {
        return;
    }
    odkryte[x][y] = 1;
    if (plansza[x][y] != '*') {
        obliczanie_sasiednich_min(plansza,wiersze,kolumny, x, y);
    }

    if (plansza[x][y]!= '0') {
        return;
    }
  
     // jeśli nie ma sąsiednich min to odkrywa sąsiednie pola rekurencyjnie
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx != 0 || dy != 0) { 
                odkryj_pole(plansza, wiersze, kolumny, x + dx, y + dy, odkryte);
            }
        }
    }
    return;
}
