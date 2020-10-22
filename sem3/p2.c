#include <stdio.h>
#include <string.h> //zawiera funkcje strcpy

int main(int argc, char *argv[]){
    char n[100];                //musze zarezerwowac pamiec dla 100 znakow (bajtow)
    strcpy(n, "Ala");           //kopiuje do tablicy n znaki po kolei
                                //napis "Ala" sklada sie z 4 bajtow: A  l  a  \0
                                //n zawiera w sobie adres do pierwszej komorki napisu
    char n2[] = "Wielki i dlugi napis"; //od razu wie ile miejsca zarezerwowac
    printf("%s, %s\n", n, n2);          //bedzie wypisywac dopoki nie napotka \0

    for (int i = 0; i<4; i++){
        printf("[%d] %c, ASCII: %d\n", i, n[i], n[i]);
    }

    char tab[10][10]; //tablica napisow
    strcpy(tab[0], "akuku");
    strcpy(tab[1], "hello");
    printf("%s, %s\n", tab[0], tab[1]);

    //argv to tablica, ktora ma tyle elementow ile wynosi argc
    //argv przechowuje informacje o tym gdzie sa napisy (adresy pierwszych liter)

    printf("Trzeci znak z pierwszego napisu w argv: %c\n", argv[0][2]);
    //wyjdzie p bo pierwszy napis w argv to nazwa programu czyli "./p2"
    //"p" to trzeci znak

    printf("Trzeci znak z drugiego napisu w argv: %c\n", argv[1][2]);
    //wyswietli sie trzeci znak tego argumentu, ktory wpisze przy otwieraniu p2


    return 0;
}