#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studenci.h"
#include "dziekanat.h"

int main(int argc, char *argv[]){
    student dane[100]; //maksymalnie 100 rekordów w pliku
    int ile;

    ile = wczytaj(dane, argv[1]);

    if(strcmp(argv[2], "przedmiot") == 0)
        najtrudniejszy_przedmiot(dane, ile);
    if(strcmp(argv[2], "student") == 0)
        najlepszy_student(dane, ile);

    return 0;
}

