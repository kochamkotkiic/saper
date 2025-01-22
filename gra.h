#ifndef GRA_H
#define GRA_H

void obsluga_komend(char **plansza, int wiersze, int kolumny,int liczba_min, int *liczba_odslonietych_pol, int *liczba_odslonietych_min, int *liczba_punktow, int poziom_trudnosci, int **odkryte);
void zapisz_wynik_do_pliku(const char *imie, int punkty);
void wyswietl_najlepszych_graczy();
void zakoncz_gre(int punkty);

#endif