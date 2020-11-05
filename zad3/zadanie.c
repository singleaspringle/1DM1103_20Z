#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct macierz{
    int m; //liczba wierszy
    int n; //liczba kolumn
    float tab[200][200]; //elementy
};

void wczytaj(FILE *fin, struct macierz *A){
    if(fscanf(fin, "%d", &A->m) != 1){
        printf("Liczba wierszy nie jest liczba calkowita\n");
        exit (-1);
    }
    if(fscanf(fin, "%d", &A->n) != 1){
        printf("Liczba kolumn nie jest liczba calkowita\n");
        exit (-1);
    }

    for(int i = 0; i < (*A).m; i++){
        for (int j = 0; j < (*A).n; j++){
            if(fscanf(fin, "%f", &A->tab[i][j]) != 1){
                printf("Wsrod podanych elementow znajduje sie obiekt, ktory nie jest liczba zmiennoprzecinkowa\n");
            }
        }
    }
}

struct macierz suma(struct macierz A, struct macierz B){
    struct macierz suma;
    suma.m = A.m;
    suma.n = A.n;
    for (int i = 0; i < A.m; i++){
        for (int j = 0; j < A.n; j++){
            suma.tab[i][j] = A.tab[i][j] + B.tab[i][j];
        }
    }
    return suma;
}

struct macierz iloczyn_macierzy(struct macierz A, struct macierz B){
    struct macierz wynik;
    wynik.m = A.m;
    wynik.n = B.n;

    for (int wiersz = 0; wiersz < A.m; wiersz++){
        for (int kolumna = 0; kolumna < B.n; kolumna++){
            for(int a = 0; a < A.n; a++){
                wynik.tab[wiersz][kolumna] += (A.tab[wiersz][a] * B.tab[a][kolumna]); //kiedy pojawia sie 0 to sie psuje...
            }
        }
    }
    
    return wynik;
}

struct macierz roznica(struct macierz A, struct macierz B){
    struct macierz roznica;
    roznica.m = A.m;
    roznica.n = A.n;
    for (int i = 0; i < A.m; i++){
        for (int j = 0; j < A.n; j++){
            roznica.tab[i][j] = A.tab[i][j] - B.tab[i][j];
        }
    }
    return roznica;
}

struct macierz mnozenie(float liczba, struct macierz A){
    struct macierz wynik;
    wynik.m = A.m;
    wynik.n = A.n;
    for(int i = 0; i < A.m; i++){
        for(int j = 0; j < A.n; j++){
            wynik.tab[i][j] = liczba * A.tab[i][j];
        }
    }
    return wynik;
}

float norm(struct macierz A){
    float suma = 0;
    for (int i = 0; i < A.m; i++){
        for (int j = 0; j < A.n; j++){
             suma += (A.tab[i][j]*A.tab[i][j]);
        }
    }
    return sqrt(suma); //trzeba przy kompilowaniu wpisac -lm oznacza to dolacz library o nazwie math (stąd l m)
}

void wypisz_do_pliku(char nazwa[], struct macierz A){
    FILE* fout = fopen(nazwa, "w+");
    fprintf(fout, "%d\n%d\n", A.m, A.n);

    for(int i = 0; i < A.m; i++){
        for(int j = 0; j < A.n; j++){
            fprintf(fout, "%f\n", A.tab[i][j]);
        }
    }
}

void wypisz(struct macierz A){
    printf("[");
    for(int i = 0; i < A.m; i++){
        for(int j = 0; j < A.n; j++){
            printf(" %5.2f ", A.tab[i][j]);
        }
        if(i<(A.m)-1){
            printf("\n ");
        }
    }
    printf("]\n");
}

void wypisz_do_pliku_liczbe(char nazwa[], float x){
    FILE* fout = fopen(nazwa, "w+");
    fprintf(fout, "%f\n", x);
}

int main(int argc, char *argv[]){
    struct macierz A;
    struct macierz B;
    FILE *fin1;
    FILE *fin2;

    //dodawanie
    if(strcmp(argv[1], "sum") == 0){
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        wczytaj(fin1, &A);
        wczytaj(fin2, &B);

        fclose(fin1);
        fclose(fin2);

        if(A.m == B.m && A.n == B.n){
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
    }

    //odejmowanie
    if(strcmp(argv[1], "substract") == 0){
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        wczytaj(fin1, &A);
        wczytaj(fin2, &B);

        fclose(fin1);
        fclose(fin2);

        if(A.m == B.m && A.n == B.n){
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
    }

    //iloczyn skalarny
    if(strcmp(argv[1], "prod") == 0){
        fin1 = fopen(argv[2], "r");
        fin2 = fopen(argv[3], "r");
        wczytaj(fin1, &A);
        wczytaj(fin2, &B);

        fclose(fin1);
        fclose(fin2);

        if(A.n == B.m){
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
    }

    //mnozenie przez liczbe
    if(strcmp(argv[1], "multiply") == 0){
        fin1 = fopen(argv[2], "r");
        wczytaj(fin1, &A);

        fclose(fin1);

       
        if(argc == 5){
            wypisz_do_pliku(argv[4], mnozenie(atof(argv[3]), A));
        }
        else{
            wypisz(mnozenie(atof(argv[3]), A));
        }
    }

    //norma
    if(strcmp(argv[1], "norm") == 0){
        fin1 = fopen(argv[2], "r");
        wczytaj(fin1, &A);

        fclose(fin1);

       
        if(argc == 4){
            wypisz_do_pliku_liczbe(argv[3], norm(A));
        }
        else{
            printf("%f\n", norm(A));
        }
    }


    return 0;
}