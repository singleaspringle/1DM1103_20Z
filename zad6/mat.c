#include <math.h>
#include "wczyt.h"

macierz* suma(macierz *A,  macierz *B){
    macierz* suma;
    suma = (macierz*) malloc(sizeof(macierz));
    suma->m = A->m;
    suma->n = A->n;
    
    suma->tab = (float**) malloc(sizeof(float*) * suma->m);
    for (int i = 0; i < suma->m; i++){
        suma->tab[i] = (float*) malloc(sizeof(float) * suma->n);
        for (int j = 0; j < suma->n; j++){
            suma->tab[i][j] = A->tab[i][j] + B->tab[i][j];
        }
    }
    return suma;
}

macierz* iloczyn_macierzy(macierz *A,  macierz *B){
    macierz* wynik;
    wynik = (macierz*) malloc(sizeof(macierz));
    wynik->m = A->m;
    wynik->n = B->n;

    wynik->tab = (float**) malloc(sizeof(float*) * wynik->m);
    for (int wiersz = 0; wiersz < A->m; wiersz++){
        wynik->tab[wiersz] = (float*) malloc(sizeof(float) * wynik->n);
        for (int kolumna = 0; kolumna < B->n; kolumna++){
            for(int a = 0; a < A->n; a++){
                wynik->tab[wiersz][kolumna] += (A->tab[wiersz][a] * B->tab[a][kolumna]); //kiedy pojawia sie 0 to sie psuje...
            }
        }
    }
    
    return wynik;
}

macierz* roznica(macierz *A,  macierz *B){
    macierz* roznica;
    roznica = (macierz*) malloc(sizeof(macierz));
    roznica->m = A->m;
    roznica->n = A->n;

    roznica->tab = (float**) malloc(sizeof(float*) * roznica->m);
    for (int i = 0; i < A->m; i++){
        roznica->tab[i] = (float*) malloc(sizeof(float) * roznica->n);
        for (int j = 0; j < A->n; j++){
            roznica->tab[i][j] = A->tab[i][j] - B->tab[i][j];
        }
    }
    return roznica;
}

macierz* mnozenie(float liczba,  macierz *A){
    macierz* wynik;
    wynik = (macierz*) malloc(sizeof(macierz));
    wynik->m = A->m;
    wynik->n = A->n;

    wynik->tab = (float**) malloc(sizeof(float*) * wynik->m);
    for(int i = 0; i < A->m; i++){
        wynik->tab[i] = (float*) malloc(sizeof(float) * wynik->n);
        for(int j = 0; j < A->n; j++){
            wynik->tab[i][j] = liczba * A->tab[i][j];
        }
    }
    return wynik;
}

float norm(macierz *A){
    float suma = 0;
    for (int i = 0; i < A->m; i++){
        for (int j = 0; j < A->n; j++){
             suma += (A->tab[i][j]*A->tab[i][j]);
        }
    }
    return sqrt(suma); //trzeba przy kompilowaniu wpisac -lm oznacza to dolacz library o nazwie math (stąd l m)
}