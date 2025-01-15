#include <stdio.h>
#include <stdlib.h>
#include "gra.h"
#include "plansza.h"
#include "interfejs.h"

//obsluga wyników
typedef struct Gracz {
    char imie[50];
    int punkty;
} Gracz;

int porownaj_graczy(const void *a, const void *b) {
    return ((Gracz *)b)->punkty - ((Gracz *)a)->punkty;
}

void zapisz_wynik_do_pliku(const char *imie, int punkty) {
    FILE *plik = fopen("wyniki.txt", "a");
    if (!plik) {
        printf("nie udało się otworzyć pliku wyników.\n");
        return;
    }
    fprintf(plik, "%s,%d\n", imie, punkty);
    fclose(plik);
}

void wyswietl_najlepszych_graczy() {
    FILE *plik = fopen("wyniki.txt", "r");
    if (!plik) {
        printf("nie udało się otworzyć pliku wyników.\n");
        return;
    }

    Gracz gracze[100];
    int liczba_graczy = 0;

    while (fscanf(plik, "%49[^,],%d\n", gracze[liczba_graczy].imie, &gracze[liczba_graczy].punkty) == 2) {
        liczba_graczy++;
    }
    fclose(plik);

    qsort(gracze, liczba_graczy, sizeof(Gracz), porownaj_graczy);

    printf("5 najlepszych graczy:\n");
    for (int i = 0; i < 5 && i < liczba_graczy; i++) {
        printf("%d. %s - %d pkt\n", i + 1, gracze[i].imie, gracze[i].punkty);
    }
}

void zakoncz_gre(int punkty) {
    char imie[50];

    printf("podaj swoje imię: ");
    scanf("%s", imie);

    zapisz_wynik_do_pliku(imie, punkty);
    wyswietl_najlepszych_graczy();
}


void obsluga_komend(char **plansza, int wiersze, int kolumny, int liczba_min, int *liczba_poprawnych_krokow, int *liczba_odslonietych_min, int *liczba_punktow, int poziom_trudnosci) {
    char komenda;
    int x, y;
    printf("podaj ruch:\n");
    while(scanf(" %c %d %d",&komenda,&x,&y)==3){
        if(x<0 || x>wiersze || y<0 || y>kolumny){ //zle podane wspolrzedne
            printf("podano nieprawidłowe współrzędne!");
            printf("podaj ruch:\n");
            continue;
        }
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
            printf("liczba punktow: %d, liczba min do odslonięcia: %d \n",*liczba_punktow,liczba_min-*liczba_odslonietych_min);
            wypisz_plansze(plansza, wiersze, kolumny);
        } else if (komenda == 'r') {
            if (plansza[x][y] == '*') {
                plansza[x][y] = '!'; // oznaczenie odkrytej miny
                wypisz_plansze(plansza, wiersze, kolumny);
                *liczba_punktow = (*liczba_poprawnych_krokow) * poziom_trudnosci;
                printf("niepowodzenie! Liczba punktów: %d\n", *liczba_punktow); // gra zakończona
                zakoncz_gre(*liczba_punktow);
                break;
            } else {
                //odkryj_pole(plansza,wiersze,kolumny,x,y)// bo dla kazdego ruchu moze odkryc wiecej?
                plansza[x][y] = '0' + zliczanie_sasiednich_min(plansza, wiersze, kolumny, x, y);
                (*liczba_poprawnych_krokow)++;
                *liczba_punktow = (*liczba_poprawnych_krokow) * poziom_trudnosci; //aktualny wynik gracza
                printf("liczba punktow: %d, liczba min do odslonięcia: %d \n",*liczba_punktow,liczba_min-*liczba_odslonietych_min);
                wypisz_plansze(plansza, wiersze, kolumny);
            }
        } else {
            printf("nieprawidłowa komenda! format: komenda x y\n");
        }
    if (*liczba_odslonietych_min==liczba_min){
        printf("liczba punktów:%d,1-wygrana\n",*liczba_punktow); //wygrana-koniec gry
        zakoncz_gre(*liczba_punktow);
        break;
    }
    printf("podaj ruch:\n");
    }
}
