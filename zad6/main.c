#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wczyt.h"
#include "mat.h"



int main(int argc, char *argv[]){
    macierz *A;
    macierz *B;
    FILE *fin1;
    FILE *fin2;

    //dodawanie
    if(strcmp(argv[1], "sum") == 0){
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        A = wczytaj(fin1);
        B = wczytaj(fin2);

        fclose(fin1);
        fclose(fin2);

        if(A->m == B->m && A->n == B->n){
            if(argc == 5){
                wypisz_do_pliku(argv[4], suma(A, B));
            }
            else{
                wypisz(suma(A, B));
            }
        }
        else{
            printf("Macierze, ktore chcesz dodac musza byc tego samego rozmiaru\n");
        }

        zwolnij(A);
        zwolnij(B);
    }

    //odejmowanie
    if(strcmp(argv[1], "substract") == 0){
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        A = wczytaj(fin1);
        B = wczytaj(fin2);

        fclose(fin1);
        fclose(fin2);

        if(A->m == B->m && A->n == B->n){
            if(argc == 5){
                wypisz_do_pliku(argv[4], roznica(A, B));
            }
            else{
                wypisz(roznica(A, B));
            }
        }
        else{
            printf("Macierze, ktore chcesz odjac musza byc tego samego rozmiaru\n");
        }

        zwolnij(A);
        zwolnij(B);
    }

    //iloczyn skalarny
    if(strcmp(argv[1], "prod") == 0){
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        A = wczytaj(fin1);
        B = wczytaj(fin2);

        fclose(fin1);
        fclose(fin2);

        if(A->n == B->m){
            if(argc == 5){
                wypisz_do_pliku(argv[4], iloczyn_macierzy(A, B));
            }
            else{
                wypisz(iloczyn_macierzy(A, B));
            }
        }
        else{
            printf("Tych macierzy nie da sie pomnozyc w takiej kolejnosci\n");
        }

        zwolnij(A);
        zwolnij(B);
    }

    //mnozenie przez liczbe
    if(strcmp(argv[1], "multiply") == 0){
        fin1 = fopen(argv[2], "r");
        A = wczytaj(fin1);

        fclose(fin1);

       
        if(argc == 5){
            wypisz_do_pliku(argv[4], mnozenie(atof(argv[3]), A));
        }
        else{
            wypisz(mnozenie(atof(argv[3]), A));
        }

        zwolnij(A);
    }

    //norma
    if(strcmp(argv[1], "norm") == 0){
        fin1 = fopen(argv[2], "r");
        A = wczytaj(fin1);

        fclose(fin1);

       
        if(argc == 4){
            wypisz_do_pliku_liczbe(argv[3], norm(A));
        }
        else{
            printf("%f\n", norm(A));
        }

        zwolnij(A);
    }

    return 0;
}