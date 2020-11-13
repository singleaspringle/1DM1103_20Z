#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//mamy baze studentów (tabele ze studentami, przedmiotami i ocenami)
//cel: obliczyc ranking studentow.

typedef struct _student{
    char imie [25];
    char nazwisko [50];
    char nr_albumu [10];
    char kod_przed [10];
    char nazwa_przed [255];
    float ocena;
    int ects;
}student, *pstudent; //nie bedziemy musieli pisac struct _student bo zrobilismy typedef i teraz "student" bedzie zastepowane automatycznie "struct _student"

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

int znajdz(char *szukany_kod, char kod_przedmiotow[100][10], int n) {
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
        if (znajdz(dane[i].kod_przed, kod_przedmiotow, ile_znalazlem ) == -1) { //jezeli nie znalazl w bazie to doda
            strncpy(kod_przedmiotow[ile_znalazlem], dane[i].kod_przed, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}


void najlepszy_przedmiot(student dane[100], int ile_rekordow) {
    char kod_przedmiotow[100][10];
    int ile_przedmiotow;
    float sumy_wazonych_ocen[100] = {0};
    int sumy_ects[100] = {0};
    int pozycja;
    int najlepsza_pozycja;
    int najgorsza_pozycja; 
    float najlepsza = 0;
    float najgorsza = 100000;
    char nazwa[100][50];

    ile_przedmiotow = znajdz_przedmioty(kod_przedmiotow, dane, ile_rekordow); //zwroci liczbe przedmiotow w bazie (NIE REKORDOW TYLKO przedmiotow UNIKALNYCH)

    for (int i=0; i < ile_rekordow; i++) {
        pozycja = znajdz( dane[i].kod_przed, kod_przedmiotow, ile_przedmiotow );

        
        if (pozycja >= 0){ //na wszelki wypadek
            sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
            sumy_ects[pozycja] += dane[i].ects;
            strcpy(nazwa[pozycja], dane[i].nazwa_przed);
        }
    }    

   /* for (int i=0;i<ile_przedmiotow; i++) 
        printf("Przedimot [%d]: %s - %f:%d - %f \n", i+1, kod_przedmiotow[i], 
        sumy_wazonych_ocen[i], sumy_ects[i], sumy_wazonych_ocen[i] / sumy_ects[i]); */

    for (int i=0; i < ile_przedmiotow; i++) {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
        if (najgorsza > sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najgorsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najgorsza_pozycja = i;
        }
    }

    printf("Najlepsza średnia: %s - %s: %f \n", 
        kod_przedmiotow[najlepsza_pozycja], nazwa[najlepsza_pozycja], 
        sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
    );

    printf("Najgorsza średnia: %s - %s: %f \n", 
        kod_przedmiotow[najgorsza_pozycja], nazwa[najgorsza_pozycja], 
        sumy_wazonych_ocen[najgorsza_pozycja] / sumy_ects[najgorsza_pozycja]
    );

}


int main(int argc, char *argv[]){
    student dane[100]; //maksymalnie 100 rekordów w pliku
    int ile;

    ile = wczytaj(dane, argv[1]); //dane = &dane[0] wiec przekazujemy adres tablicy dane, wczytaj zwraca liczbe rekordow
    
    //wypisz(dane, ile); //wypisze tyle rekordow "ile" wczytał

    najlepszy_przedmiot(dane, ile);

    return 0;
}

