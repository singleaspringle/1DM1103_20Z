#include "wczyt.h"

macierz* wczytaj(FILE *fin){
    macierz* A; 

    A = (macierz*) malloc(sizeof(macierz));

    if(fscanf(fin, "%d", &(A->m)) != 1){
        printf("Liczba wierszy nie jest liczba calkowita\n");
        exit (-1);
    }
    if(fscanf(fin, "%d", &(A->n)) != 1){
        printf("Liczba kolumn nie jest liczba calkowita\n");
        exit (-1);
    }

    A->tab = (float**) malloc(sizeof(float*) * A->m);
    for(int i = 0; i < A->m; i++){
        A->tab[i] = (float*) malloc(sizeof(float) * A->n);
        for (int j = 0; j < A->n; j++){
            if(fscanf(fin, "%f", &(A->tab[i][j])) != 1){
                printf("Wsrod podanych elementow znajduje sie obiekt, ktory nie jest liczba zmiennoprzecinkowa\n");
            }
        }
    }

    return A;
}

void wypisz_do_pliku(char nazwa[], macierz *A){
    FILE* fout = fopen(nazwa, "w+");
    fprintf(fout, "%d\n%d\n", A->m, A->n);

    for(int i = 0; i < A->m; i++){
        for(int j = 0; j < A->n; j++){
            fprintf(fout, "%5.2f ", A->tab[i][j]);
        }
        fprintf(fout, "\n");
    }
}

void wypisz(macierz *A){
    printf("[");
    for(int i = 0; i < A->m; i++){
        for(int j = 0; j < A->n; j++){
            printf(" %5.2f ", A->tab[i][j]);
        }
        if(i < A->m - 1){
            printf("\n ");
        }
    }
    printf("]\n");
}

void wypisz_do_pliku_liczbe(char nazwa[], float x){
    FILE* fout = fopen(nazwa, "w+");
    fprintf(fout, "%f\n", x);
}

void zwolnij(macierz *A){
    for(int i = 0; i < A->m; i++){
        free(A->tab[i]);
    }
    free(A->tab);
    free(A);
}