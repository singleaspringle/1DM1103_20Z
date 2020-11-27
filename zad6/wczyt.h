#include <stdio.h>
#include <stdlib.h>

typedef struct _macierz{
    int m; //liczba wierszy
    int n; //liczba kolumn
    float **tab;
} macierz;

macierz* wczytaj(FILE *fin);

void wypisz_do_pliku(char nazwa[], macierz *A);

void wypisz(macierz *A);

void wypisz_do_pliku_liczbe(char nazwa[], float x);

void zwolnij(macierz *A);