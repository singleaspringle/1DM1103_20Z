typedef struct _student{
    char imie [25];
    char nazwisko [50];
    char nr_albumu [10];
    char kod_przed [10];
    char nazwa_przed [255];
    float ocena;
    int ects;
}student, *pstudent;

int wczytaj(student dane[100], char *fnazwa); //wczytuje z pliku dane

void wypisz(student dane[100], int n);

int wyszukaj_studenta(char *szukany_nr, char nr_albumow[100][10], int n); //podaje pozycje studenta na liscie unikalnych studentow

int znajdz_unikalnych_studentow(char nr_albumow[100][10], student dane[100], int n); //tworzy liste unikalnych studentow