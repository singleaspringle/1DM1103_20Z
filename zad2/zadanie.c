#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//iloczyn macierzy przez wektor(macierz jednowymiarowa)

void wczytaj(FILE *fin, int *wiersze, int *kolumny, float macierz[100][100]){
    float liczba = 0;

    if(fscanf(fin, "%d", wiersze) != 1){
        printf("Pierwszy napis nie jest liczba calkowita i nie moze byc liczba wierszy.\n");
        exit(-1);
    }
    if(fscanf(fin, "%d", kolumny) != 1){
        printf("Drugi napis nie jest liczba calkowita i nie moze byc liczba kolumn.\n");
        exit(-1);
    }

    for(int i=0; i<*wiersze; i++){
        for (int j=0; j<*kolumny; j++){
            if (fscanf(fin, "%f", &liczba) != 1){
                printf("Liczba podana jako element macierzy nie jest liczba zmiennoprzecinkowa.\n");
                exit (-2);
            }
            macierz[i][j] = liczba;
        }
    }
}

void wypisz_macierz(int *wiersze, int *kolumny, float macierz[100][100]){
    int i, j;
    for (i = 0; i <*wiersze; i++){
        printf("[");
        for (j = 0; j<*kolumny; j++){
            printf("%f ", macierz[i][j]);
        }
        printf("]\n");
    }
}

void iloczyn_macierzy(int *wiersze1, int *kolumny1, int *wiersze2, int *kolumny2, int *wiersze3, int *kolumny3, float macierz1[100][100], float macierz2[100][100], float macierz3[100][100]){
    if(*kolumny1 != *wiersze2){
        printf("Tych macierzy nie da sie pomnozyc w tej kolejnosci\n");
        exit(-3);
    }
    else
    {
        *wiersze3 = *wiersze1;
        *kolumny3 = *kolumny2;
        int a = 0;
        for (int i=0; i<*wiersze3; i++){\
            int b = 0;
            for(; a<*wiersze1 && b<*wiersze2;){
                macierz3[i][0] += macierz1[a][b] * macierz2[b][0];
                b++;
            }
            a++;
        }
    }
    
}

int main(int argc, char *argv[]){
    FILE *fin;
    int wiersze1 = 100; //deklaruje w mainie zeby moc pozniej zmieniac wartosci w funkcjach globalnie, zawsze bede wczytywal macierz o rozmiarach 100x100 bo inaczej poprzestawiaja sie elementy
    int kolumny1 = 100;
    int wiersze2 = 100;
    int kolumny2 = 100;
    int wiersze3 = 100;
    int kolumny3 = 100;
    float macierz1[100][100];
    float macierz2[100][100];
    float macierz3[100][100];
    

    
    fin = fopen(argv[1], "r");
    wczytaj(fin, &wiersze1, &kolumny1, macierz1);

    fin = fopen(argv[2], "r");
    wczytaj(fin, &wiersze2, &kolumny2, macierz2);
    
    if (kolumny2 != 1){
        printf("Druga macierz musi byc jednowymiarowa.\n");
    }
    else{
        iloczyn_macierzy(&wiersze1, &kolumny1, &wiersze2, &kolumny2, &wiersze3, &kolumny3, macierz1, macierz2, macierz3);

        wypisz_macierz(&wiersze3, &kolumny3, macierz3);
    }

    return 0;
}