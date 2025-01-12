#include <stdio.h>
#include <stdlib.h>
#include "plansza.h"

void obsluga_komend(char **plansza, int wiersze, int kolumny, int liczba_min, int *liczba_poprawnych_krokow, int *liczba_odslonietych_min, int *liczba_punktow, int poziom_trudnosci) {
    char komenda;
    int x, y;
    while(scanf(" %c %d %d",&komenda,&x,&y)==3){
        if (komenda == 'f') {
            if (plansza[x][y] == 'X') {
                plansza[x][y] = 'F';  // ustawienie flagi
            } else if (plansza[x][y] == 'F') {
                plansza[x][y] = 'X';  // usunięcie flagi
            } else if (plansza[x][y] == '*') {
                (*liczba_odslonietych_min)++; // odsłonięto minę
                plansza[x][y] = 'F';  // ustawienie flagi
            }
            (*liczba_poprawnych_krokow)++;
            *liczba_punktow = (*liczba_poprawnych_krokow) * poziom_trudnosci; //aktualny wynik gracza
            printf("liczba punktow: %d, liczba min do odslonięcia: %d",*liczba_punktow,liczba_min-*liczba_odslonietych_min);
            wypisz_plansze(plansza, wiersze, kolumny);
        } else if (komenda == 'r') {
            if (plansza[x][y] == '*') {
                plansza[x][y] = '!'; // oznaczenie odkrytej miny
                wypisz_plansze(plansza, wiersze, kolumny);
                *liczba_punktow = (*liczba_poprawnych_krokow) * poziom_trudnosci;
                printf("niepowodzenie! Liczba punktów: %d\n", *liczba_punktow); // gra zakończona
                break;
            } else {
                plansza[x][y] = '0' + zliczanie_sasiednich_min(plansza, wiersze, kolumny, x, y);
                (*liczba_poprawnych_krokow)++;
                *liczba_punktow = (*liczba_poprawnych_krokow) * poziom_trudnosci; //aktualny wynik gracza
                printf("liczba punktow: %d, liczba min do odslonięcia: %d",*liczba_punktow,liczba_min-*liczba_odslonietych_min);
                wypisz_plansze(plansza, wiersze, kolumny);
            }
        } else {
            printf("nieprawidłowa komenda! format: komenda x y\n");
        }
    if (*liczba_odslonietych_min==liczba_min){
        printf("%d,1 .\n",*liczba_punktow); //wygrana-koniec gry
        break;
    }
    }
}
