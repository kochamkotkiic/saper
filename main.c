#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "plansza.h"
#include "interfejs.h"

void uruchom_gre(int wiersze, int kolumny, int liczba_min);
void uruchom_z_pliku(const char *sciezka);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("brak argumentu. Użyj -f <ścieżka do pliku> lub uruchom grę w trybie normalnym.\n");
        return 1;
    }

    if (strcmp(argv[1], "-f") == 0 && argc == 3) {
        // uruchomienie gry z pliku
        uruchom_z_pliku(argv[2]);
    } else {
        // normalne uruchomienie gry
        int poziom_trudnosci;
        printf("wybierz poziom trudności (1 - łatwy, 2 - średni, 3 - trudny): ");
        scanf("%d", &poziom_trudnosci);

        int wiersze, kolumny, liczba_min;

        switch (poziom_trudnosci) {
            case 1:
                wiersze = 9; kolumny = 9; liczba_min = 10; break;
            case 2:
                wiersze = 16; kolumny = 16; liczba_min = 40; break;
            case 3:
                wiersze = 16; kolumny = 30; liczba_min = 99; break;
            default:
                printf("nieprawidłowy poziom trudności.\n");
                return 1;
        }

        uruchom_gre(wiersze, kolumny, liczba_min);
    }

    return 0;
}

void uruchom_gre(int wiersze, int kolumny, int liczba_min) {
    char **plansza;
    int pierwszy_ruch_x, pierwszy_ruch_y;

    printf("podaj współrzędne pierwszego ruchu (x y): ");
    scanf("%d %d", &pierwszy_ruch_x, &pierwszy_ruch_y);

    tworzenie_planszy(&plansza, wiersze, kolumny);
    losowanie_min(plansza, wiersze, kolumny, liczba_min, pierwszy_ruch_x, pierwszy_ruch_y);
    obliczanie_sasiednich_min(plansza, wiersze, kolumny);
    wypisz_plansze(plansza, wiersze, kolumny);

    // Dalsza logika gry (np. wczytywanie ruchów gracza i aktualizacja planszy)
    // Na przykład możesz tu wprowadzić pętlę do przyjmowania komend
}

void uruchom_z_pliku(const char *sciezka) {
    FILE *plik = fopen(sciezka, "r");
    if (!plik) {
        printf("nie udało się otworzyć pliku.\n");
        return;
    }

    int wiersze, kolumny;
    fscanf(plik, "%d %d\n", &wiersze, &kolumny);

    char **plansza;
    tworzenie_planszy(&plansza, wiersze, kolumny);

    // odczytujemy planszę z pliku
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            fscanf(plik, " %c", &plansza[i][j]);
        }
    }

    // odczytujemy ruchy i aktualizujemy planszę
    char komenda;
    int x, y;
    int liczba_poprawnych_krokow=0;
    int liczba_punktow = 0;
    int poziom_trudnosci = 1; //zakładam, że moja plansza ma poziom trudności 1

    while (fscanf(plik, " %c %d %d", &komenda, &x, &y) == 3) {
        if (komenda == 'f') {
            if (plansza[x][y] == 'X') {
                plansza[x][y] = 'F';  // ustawienie flagi
            } else if (plansza[x][y] == 'F') {
                plansza[x][y] = 'X';  // usunięcie flagi jeśli kolejny raz f na te same współrzędne
            }
            wypisz_plansze(plansza, wiersze, kolumny);
            liczba_poprawnych_krokow++;
        } 
        else if (komenda == 'r') { 
            if (plansza[x][y] == '*') {
                wypisz_plansze(plansza, wiersze, kolumny);
                liczba_punktow = liczba_poprawnych_krokow * poziom_trudnosci; 
                printf("%d,%d,0 .\n", liczba_poprawnych_krokow, liczba_punktow); // niepowodzenie
                break;
            } else { //flaga lub zakryte pole
                plansza[x][y] = '0' + zliczanie_sasiednich_min(plansza, wiersze, kolumny, x, y);
                wypisz_plansze(plansza, wiersze, kolumny);
                liczba_poprawnych_krokow++;
    }
}

    }
    liczba_punktow=liczba_poprawnych_krokow * poziom_trudnosci;
    printf("%d,%d,1 .\n",liczba_poprawnych_krokow,liczba_punktow); //wygrana
    fclose(plik);
}
