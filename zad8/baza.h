#ifndef _BAZA_H
#define _BAZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Student {
    char * imie;
    char * nazwisko;
    char * nr_albumu;
    char * email;

    struct _Student *poprz;
    struct _Student *nast; //znacznik do nastepnego studenta na liscie
} Student;

typedef struct _Przedmiot {
    char * kod_przedmiotu;
    char * nazwa;
    char * semestr;

    struct _Przedmiot *poprz;
    struct _Przedmiot *nast;
} Przedmiot;

typedef struct _Ocena {
    char * nr_albumu;
    char * kod_przedmiotu;
    float ocena;
    char * komentarz;

    struct _Ocena *poprz;
    struct _Ocena *nast;
} Ocena;


typedef struct _SBaza {
    Student *lista_studentow; /* Głowa listy! */
    Przedmiot *lista_przedmiotow;
    Ocena *lista_ocen;
} SBaza;

Student * ostatni_stud(Student *glowa);
Przedmiot * ostatni_przed(Przedmiot *glowa);
Ocena * ostatnia_oc(Ocena *glowa);
SBaza * wczytaj_baze(char *nazwa_pliku);
void zapisz_baze(char *nazwa_pliku, SBaza * baza);
void listuj_studentow(SBaza *baza);
void listuj_przedmioty(SBaza *baza);
void listuj_oceny(SBaza *baza);
int ile_przedmiotow(SBaza *baza);
int ile_studentow(SBaza *baza);
int ile_studentow_na_przedmiocie(SBaza *baza);
int ile_ocen(SBaza *baza);
void dodaj_przedmiot(SBaza * baza, char *kod, char* nazwa, char* semestr);
void dodaj_studenta(SBaza * baza, char *imie, char* nazwisko, char* nr_albumu, char* email);
void dodaj_ocene(SBaza * baza, char *kod_przedmiotu, char* nr_albumu, float ocena, char* komentarz);
void dodaj_studenta_do_przedmiotu(SBaza *baza, char *nr_albumu, char* kod);
float oblicz_srednia(SBaza *baza, char *nr_albumu);
float srednia_przedmiotu(SBaza *baza, char *kod);
Student *znajdz_studenta(SBaza *baza, char *nr_albumu);
int ile_ocen_na_przedmiocie(SBaza *baza, char*kod);
void wyswietl_studenta(Student *stud);
void wyswietl_studentow_na_przedmiocie(SBaza *baza, char* kod);
void zwolnij(SBaza *baza);
Student * sortuj_przez_wybieranie_stud(Student *glowa);
Przedmiot * sortuj_przed_po_kodzie(Przedmiot *glowa);
Przedmiot * sortuj_przed_po_nazwie(Przedmiot *glowa);
void listuj_oceny_studenta(SBaza *baza, char* nr_albumu);
void listuj_oceny_na_przedmiocie(SBaza *baza, char *kod);
void wyswietl_alfabetycznie(Student *glowa);
void wyswietl_od_tylu(Student *glowa);
void wyswietl_przedmiot(Przedmiot *glowa);

#endif