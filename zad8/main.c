#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

//UWAGA, puste pola musialem zastapic spacjami, bo funkcja strtok nie umiala zapisac do zmiennej pomocniczej pustego znaku (albo traktowala dwa ";" jako jeden rozgranicznik ";")
//brak oceny zapisywalem jako ocena 0 i nie byla ona brana pod uwage przy obliczaniu sredniej studenta (przy zapisywaniu bazy, spacje w ocenie program zastępował zerem więc tak przyjąłęm)
//dodawanie studenta do przedmiotu traktowalem jako dodanie pozycji w ocenach z oceną 0
//0 nie jest liczone jako ocena, jest tylko jako informacje ze dany student jest zapisany na ten przedmiot. Dodanie oceny dla tego studenta na tym przedmiocie usunie ocene 0

int main(int argc, char ** argv) {
    SBaza *baza;
    baza = wczytaj_baze(argv[1]);

    if (strcmp("list_students", argv[2]) == 0) {
        listuj_studentow(baza);
    } else if (strcmp("count_students", argv[2]) == 0) {
        printf("Liczba studentów: %d\n", ile_studentow(baza));
    } else if (strcmp("list_grades", argv[2]) == 0) {
        listuj_oceny(baza);
    } else if (strcmp("list_courses", argv[2]) == 0) {
        listuj_przedmioty(baza);
    } else if (strcmp("add_course", argv[2]) == 0){
        dodaj_przedmiot(baza, argv[3], argv[4], argv[5]);
    } else if (strcmp("add_student", argv[2]) == 0){
        dodaj_studenta(baza, argv[3], argv[4], argv[5], argv[6]);
    } else if (strcmp("set_grade", argv[2]) == 0){
        dodaj_ocene(baza, argv[3], argv[4], atof(argv[5]), argv[6]);
    } else if (strcmp("count_courses", argv[2]) == 0) {
        printf("Liczba przedmiotow: %d\n", ile_przedmiotow(baza));
    } else if (strcmp("count_grades", argv[2]) == 0) {
        printf("Liczba wystawionych ocen: %d\n", ile_ocen(baza));
    } else if (strcmp("add_student_to_course", argv[2]) == 0) {
        dodaj_studenta_do_przedmiotu(baza, argv[3], argv[4]);
    } else if (strcmp("student_average", argv[2]) == 0) {
        printf("%f\n", oblicz_srednia(baza, argv[3]));
    } else if (strcmp("list_students_on_course", argv[2]) == 0) {
        wyswietl_studentow_na_przedmiocie(baza, argv[3]);
    } else if (strcmp("course_average", argv[2]) == 0) {
        printf("Średnia ocen na przedmiocie %s wynosi: %f\n", argv[3], srednia_przedmiotu(baza, argv[3]));
    } else if (strcmp("course_grades", argv[2]) == 0) {
        printf("Na przedmiocie %s jest wystawionych %d ocen.\n", argv[3], ile_ocen_na_przedmiocie(baza, argv[3]));
    } else if (strcmp("list_course_grades", argv[2]) == 0) {
        listuj_oceny_na_przedmiocie(baza, argv[3]);
    } else if (strcmp("list_student_grades", argv[2]) == 0) {
        listuj_oceny_studenta(baza, argv[3]);
    } 
    
    zapisz_baze(argv[1], baza);

    if (strcmp("list_students_alphabetically", argv[2]) == 0) {
        wyswietl_alfabetycznie(sortuj_przez_wybieranie_stud(baza->lista_studentow));
    } else if (strcmp("list_students_reverse", argv[2]) == 0) {
        wyswietl_od_tylu(sortuj_przez_wybieranie_stud(baza->lista_studentow));
    } else if (strcmp("list_courses_by_code", argv[2]) == 0) {
        wyswietl_przedmiot(sortuj_przed_po_kodzie(baza->lista_przedmiotow));
    } else if (strcmp("list_courses_by_name", argv[2]) == 0) {
        wyswietl_przedmiot(sortuj_przed_po_nazwie(baza->lista_przedmiotow));
    }

    zwolnij(baza);
    return 0;
}