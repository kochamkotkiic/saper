#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <getopt.h>
#include "plansza.h"
#include "interfejs.h"
#include "gra.h"

void uruchom_gre(int wiersze, int kolumny, int liczba_min, int poziom_trudnosci);
void uruchom_z_pliku(const char *sciezka);

int main(int argc, char *argv[]) {
    int wiersze=0, kolumny=0, liczba_min=0;
    int poziom_trudnosci = 0;
    int opt;
    char *sciezka = NULL;
    int wlasny_poziom=0;
    while ((opt = getopt(argc, argv, "f:d:")) != -1) {  
        switch (opt) {
        case 'f':
            sciezka = optarg; //opcjonalne-bo moze byc z pliku lub manualna gra
            break;
        case 'd':
            poziom_trudnosci = atoi(optarg);
            switch (poziom_trudnosci) {
                case 1:
                    wiersze = 9;
                    kolumny = 9;
                    liczba_min = 10;
                    break;
                case 2:
                    wiersze = 16;
                    kolumny = 16;
                    liczba_min = 40;
                    break;
                case 3:
                    wiersze = 16;
                    kolumny = 30;
                    liczba_min = 99;
                    break;
                case 4:
                    wlasny_poziom=1;
                    break;
                default:
                    fprintf(stderr, "Nieprawidłowy poziom trudności. Dostępne: 1 (łatwy), 2 (średni), 3 (trudny). 4 (wlasny poziom)\n");
                    exit(EXIT_FAILURE);
            }
            break;
        default:
            fprintf(stderr, "Użycie: %s [-r wiersze] [-c kolumny] [-m liczba_min] [-f ścieżka] [-d poziom_trudności]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if(wlasny_poziom==1){//definicja wlasnego poziomu
        printf("podaj wymiary planszy oraz liczbe min: \n");
        scanf("%d %d %d",&wiersze,&kolumny,&liczba_min);
    }
    if (sciezka) {
        uruchom_z_pliku(sciezka);
    } else if (poziom_trudnosci != 0) {
        uruchom_gre(wiersze, kolumny, liczba_min, poziom_trudnosci);
    } else {
        fprintf(stderr, "Poziom trudności musi zostać określony.\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

void uruchom_gre(int wiersze, int kolumny, int liczba_min, int poziom_trudnosci) {
        char **plansza;
        int pierwszy_ruch_x, pierwszy_ruch_y;
        int liczba_odslonietych_pol = 0;
        int liczba_odslonietych_min = 0;
        int liczba_punktow = 0;

        printf("podaj współrzędne pierwszego ruchu (x y): \n ");
        scanf("%d %d", &pierwszy_ruch_x, &pierwszy_ruch_y);
        if(pierwszy_ruch_x<0 || pierwszy_ruch_x>(wiersze-1) || pierwszy_ruch_y<0 || pierwszy_ruch_y>(kolumny-1)){ //zle podane wspolrzedne
            printf("podano nieprawidłowe współrzędne! \n");
            printf("podaj współrzędne pierwszego ruchu (x y): \n");
            scanf("%d %d", &pierwszy_ruch_x, &pierwszy_ruch_y);
        }
        
        tworzenie_planszy(&plansza, wiersze, kolumny);
        losowanie_min(plansza, wiersze, kolumny, liczba_min, pierwszy_ruch_x, pierwszy_ruch_y);
        obliczanie_sasiednich_min(plansza, wiersze, kolumny);
        odkryj_pole(plansza, wiersze, kolumny, pierwszy_ruch_x, pierwszy_ruch_y);
        wypisz_plansze(plansza, wiersze, kolumny);
        obsluga_komend(plansza, wiersze, kolumny,liczba_min, &liczba_odslonietych_pol, &liczba_odslonietych_min, &liczba_punktow, poziom_trudnosci);
    }

    void uruchom_z_pliku(const char *sciezka) { //gra z pliku z przykladowa plansza
        FILE *plik = fopen(sciezka, "r");
        if (!plik) {
            printf("nie udało się otworzyć pliku \n");
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
        int liczba_odslonietych_min=0;
        int liczba_punktow = 0;
        int poziom_trudnosci = 1; //zakładam, że moja plansza ma poziom trudności 1
        int liczba_min=10;
        //int pierwszy_x=1;
        //int pierwszy_y=1;
        while (fscanf(plik, " %c %d %d", &komenda, &x, &y) == 3) {
            /*if(pierwszy_x==1 && pierwszy_y==1){ // nie tylko dla 1 ruchu odkrywamy wiecej?
                odkryj_pole(&plansza,wiersze, kolumny,x,y);
                pierwszy_x=0;
                pierwszy_y=0;
            }*/
            if (komenda == 'f') {
                if (plansza[x][y] == 'X') {
                    plansza[x][y] = 'F';  // ustawienie flagi
                } else if (plansza[x][y] == 'F') {
                    plansza[x][y] = 'X';  // usunięcie flagi jeśli kolejny raz f na te same współrzędne
                } else if(plansza[x][y]=='*'){
                    liczba_odslonietych_min++; //odslonieto minę
                }
                liczba_poprawnych_krokow++;
            } 
            else if (komenda == 'r') { 
                if (plansza[x][y] == '*') { 
                    liczba_punktow = liczba_poprawnych_krokow * poziom_trudnosci; 
                    printf("liczba poprawnych kroków:%d,liczba punktów:%d,0-przegrana!\n", liczba_poprawnych_krokow, liczba_punktow); // niepowodzenie
                    break;
                } else { //flaga lub zakryte pole
                    plansza[x][y] = '0' + zliczanie_sasiednich_min(plansza, wiersze, kolumny, x, y);
                    liczba_poprawnych_krokow++;
                }
            }
        }
        if (liczba_odslonietych_min==liczba_min){
            liczba_punktow=liczba_poprawnych_krokow * poziom_trudnosci;
            printf("liczba poprawnych kroków:%d, liczba punktów: %d,1-wygrana! \n",liczba_poprawnych_krokow,liczba_punktow); //wygrana
        }
        fclose(plik);
    }
