#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "studenci.h"


int wyszukaj_przedmiot(char *szukany_kod, char kod_przedmiotow[100][10], int n) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(szukany_kod, kod_przedmiotow[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_przedmioty(char kod_przedmiotow[100][10], student dane[100], int n) {
    int ile_znalazlem = 0;

    for (int i=0; i <n; i++) {
        if (wyszukaj_przedmiot(dane[i].kod_przed, kod_przedmiotow, ile_znalazlem ) == -1) { //jezeli nie znalazl w bazie to doda
            strncpy(kod_przedmiotow[ile_znalazlem], dane[i].kod_przed, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}

void najtrudniejszy_przedmiot(student dane[100], int ile_rekordow) {
    char kod_przedmiotow[100][10];
    int ile_przedmiotow;
    float sumy_wazonych_ocen[100] = {0};
    int sumy_ects[100] = {0};
    int pozycja;
    int najgorsza_pozycja; 
    float najgorsza = 100000;
    char nazwa[100][50];

    ile_przedmiotow = znajdz_przedmioty(kod_przedmiotow, dane, ile_rekordow); //zwroci liczbe przedmiotow w bazie (NIE REKORDOW TYLKO przedmiotow UNIKALNYCH)

    for (int i=0; i < ile_rekordow; i++) {
        pozycja = wyszukaj_przedmiot( dane[i].kod_przed, kod_przedmiotow, ile_przedmiotow );

        
        if (pozycja >= 0){ //na wszelki wypadek
            sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
            sumy_ects[pozycja] += dane[i].ects;
            strcpy(nazwa[pozycja], dane[i].nazwa_przed);
        }
    }

    for (int i=0; i < ile_przedmiotow; i++) {
        if (najgorsza > sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najgorsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najgorsza_pozycja = i;
        }
    }

    printf("Najtrudniejszy przedmiot: %s - %s: %f \n", 
        kod_przedmiotow[najgorsza_pozycja], nazwa[najgorsza_pozycja], 
        sumy_wazonych_ocen[najgorsza_pozycja] / sumy_ects[najgorsza_pozycja]
    );

}

void najlepszy_student(student dane[100], int ile_rekordow) {
    char nr_albumow[100][10]; //maksymalnie 100 numerow albumow po 10 znakow
    int ile_studentow;
    float sumy_wazonych_ocen[100] = {0};
    int sumy_ects[100] = {0};
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 0.0f;

    ile_studentow = znajdz_unikalnych_studentow(nr_albumow, dane, ile_rekordow); //zwroci liczbe studentow w bazie (NIE REKORDOW TYLKO STUDENTOW UNIKALNYCH)

    for (int i=0; i < ile_rekordow; i++) {
        pozycja = wyszukaj_studenta( dane[i].nr_albumu, nr_albumow, ile_studentow );

        
        if (pozycja >= 0){ //na wszelki wypadek
            sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
            sumy_ects[pozycja] += dane[i].ects;
        }
    }  

    for (int i=0; i < ile_studentow; i++) {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najlepszy student: \n");
    printf("Student [%d]: %s - %f \n", 
        najlepsza_pozycja+1, nr_albumow[najlepsza_pozycja],
        sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
    );

}
