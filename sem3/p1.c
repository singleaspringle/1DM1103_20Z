#include <stdio.h>
#include <stdlib.h> //atof jest w tej bibliotece

//argv[0] to zawsze nazwa programu
//%f - float
//cc p1.c -o p1 utworzy odrazu p1.out
/*w unixach nie ma znaczenia rozszerzenie pliku wykonywalnego 
bo on i tak sie wykona bo ma te znaczki*/
//przy uruchamianu ./p1 1 2 (podane argumenty to "1" i "2")


int main(int argc, char *argv[]){
    //int - calkowite
    //unsigned int - to liczby calkowite bez znaku
    //float - zmiennoprzecinkowe
    //double - zmiennoprzecinkowe bardziej precyzyjne
    //char - znak
    //unsigned char
    //napis to tablica znakow - char napis[255], jeden znak zarezerwowany na \0 wiec znakow znaczacych moze byc rzeczywiscie 254
    //zero "\0" oznacza koniec napisu! on jest tez elementem tej tablicy

    float v;
    float a1;
    float a2;
    a1 = atof(argv[1]); //atof przeksztalca napis na float
    a2 = atof(argv[2]);
    v = a1 + a2;
    printf("[%s] Suma: %f\n", argv[0], v);

    return 0;
}