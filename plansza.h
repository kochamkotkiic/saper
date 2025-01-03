#ifndef PLANSZA_H
#define PLANSZA_H
void tworzenie_planszy(char ***plansza,int wiersze,int kolumny);
void wyczysc_plansze(char **plansza,int wiersze);
void losowanie_min(char **plansza,int wiersze,int kolumny, int liczba_min);
int zliczanie_sasiednich_min(char **plansza, int wiersze, int kolumny, int x, int y);
void obliczanie_sasiednich_min(char **plansza, int wiersze, int kolumny);
#endif 