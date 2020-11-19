#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "studenci.h"

int wczytaj(student dane[100], char *fnazwa){
    FILE *fin = fopen(fnazwa, "r");
    int count;
    char bufor[1023]; //bedziemy pod zmienna bufor przechowywac po całej linijce
    char *w;

    fgets(bufor, 1023, fin); //wczytuje pierwsza linijke
    sscanf(bufor, "%d", &count); //wczytuje pierwszego inta ktorego napotka w pierwszej linijce

    for(int i = 0; i < count; i++){
        fgets(bufor, 1023, fin); //wczytuje az nie napotka znaku nowej linii, wczytuje razem z nim
        //printf("%s", bufor); //po %s nie potrzeba \n bo wczyta z pliku znak nowej linii
        w = strtok(bufor, "|"); //podzieli bufor wzgledem znaku "|", w bedzie pierwszym napisem i zastąpi "|" znakiem "\0"
        strncpy(dane[i].imie, w, 24);

        w = strtok(NULL, "|"); //bedzie kontynuowac od poprzedniego |
        strncpy(dane[i].nazwisko, w, 49);

        w = strtok(NULL, "|");
        strncpy(dane[i].nr_albumu, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].kod_przed, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwa_przed, w, 254);

        w = strtok(NULL, "|");
        dane[i].ocena = atof(w);

        w = strtok(NULL, "|");
        dane[i].ects = atoi(w);
    }



    fclose(fin);
    return count;
}

void wypisz(student dane[100], int n){
    for (int i = 0; i < n; i++){
        printf("{ Student: %s - %s %s, z przedmiotu: [%s] %s za ECTS: %d otrzymał %.1f\n",
        dane[i].nr_albumu, dane[i].imie, dane[i].nazwisko,
        dane[i].kod_przed, dane[i].nazwa_przed, dane[i].ects, dane[i].ocena);
    }
}

int wyszukaj_studenta(char *szukany_nr, char nr_albumow[100][10], int n) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(szukany_nr, nr_albumow[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_unikalnych_studentow(char nr_albumow[100][10], student dane[100], int n) {
    int ile_znalazlem = 0;

    for (int i=0; i <n; i++) {
        if (wyszukaj_studenta(dane[i].nr_albumu, nr_albumow, ile_znalazlem ) == -1) { //jezeli nie znalazl w bazie to doda
            strncpy(nr_albumow[ile_znalazlem], dane[i].nr_albumu, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}