#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    float a = atof(argv[1]);
    printf("Wartość %f do kwadratu to %f.\n", a, a*a);

    return 0;
}