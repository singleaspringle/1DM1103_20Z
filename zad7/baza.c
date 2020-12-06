#include "baza.h"

Student * wczytaj_studentow(FILE *fin) {
    char bufor[255];
    int n, i;
    char *s;
    Student *last_student = NULL;
    Student *glowa = NULL;
    fgets(bufor, 254, fin); //wczytuje cala linijke: 254 znaki i \0
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;

        if (last_student == NULL)
            glowa = stud;
        else
            last_student->nast = stud;
        last_student = stud;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        stud->imie = (char*) malloc( sizeof(char) * (strlen(s) + 1)); // + jedno miejsce na \0
        strcpy(stud->imie, s);

        s = strtok(NULL, ";");
        stud->nazwisko = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nazwisko, s);

        s = strtok(NULL, ";");
        stud->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nr_albumu, s);

        s = strtok(NULL, "\n");
        stud->email = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->email, s);
    }

    return glowa;
}

int ile_studentow(SBaza *baza) {
    int n = 0;
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        n++;
        stud = stud->nast;
    }
    return n;
}

Przedmiot * wczytaj_przedmioty(FILE *fin, SBaza * baza){
    char bufor [255];
    int n;
    char *temp;
    Przedmiot *glowa = NULL;
    Przedmiot *poprzedni = NULL;

    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n); //zapisuje w n ile przedmiotow jest

    for(int i = 0; i < n; i++){
        Przedmiot *p = (Przedmiot*) malloc(sizeof(Przedmiot));
        p->nast = NULL;

        if(poprzedni == NULL)
            glowa = p;
        else
            poprzedni->nast = p; //jezeli byl jakis we wczesniejszym czlonie listy, to informuje go, ze nastepny jest ten przedmiot p
        poprzedni = p;

        fgets(bufor, 254, fin);
        temp = strtok(bufor, ";");
        p->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(p->kod_przedmiotu, temp);

        temp = strtok(NULL, ";");
        p->nazwa = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(p->nazwa, temp);

        temp = strtok(NULL, "\n");
        p->semestr = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(p->semestr, temp);        
    }

    return glowa;
}

int ile_przedmiotow(SBaza *baza) {
    int n = 0;
    Przedmiot * p = baza->lista_przedmiotow;
    while (p != NULL) {
        n++;
        p = p->nast;
    }
    return n;
}

Ocena * wczytaj_oceny(FILE *fin, SBaza * baza){
    char bufor [255];
    int n;
    char *temp;
    float a = 0;
    Ocena *glowa = NULL;
    Ocena *poprzednia = NULL;

    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n); //zapisuje w n ile ocen jest


    for(int i = 0; i < n; i++){
        Ocena * o = (Ocena*) malloc(sizeof(Ocena));
        o->nast = NULL;

        if(poprzednia == NULL)
            glowa = o;
        else
            poprzednia->nast = o;
        poprzednia = o;

        fgets(bufor, 254, fin);
        temp = strtok(bufor, ";");
        o->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(o->kod_przedmiotu, temp);

        temp = strtok(NULL, ";");
        o->nr_albumu = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(o->nr_albumu, temp);

        temp = strtok(NULL, ";");
        if(strcmp(temp, " ") != 0){
            sscanf(temp, "%f", &a);
            o->ocena = a;
        }
        else
            o->ocena = 0;
        

        temp = strtok(NULL, "\n");
        o->komentarz = (char*) malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(o->komentarz, temp);        
    }

    return glowa;
}

int ile_studentow_na_przedmiocie(SBaza *baza) { //wyswietli ile jest elementow na liscie ocen
    int n = 0;
    Ocena *o = baza->lista_ocen;
    while (o != NULL) {
        n++;
        o = o->nast;
    }
    return n;
}

int ile_ocen(SBaza *baza) { //wyswietli ile jest wystawionych ocen w bazie
    int n = 0;
    Ocena *o = baza->lista_ocen;
    while (o != NULL) {
        if(o->ocena != 0)
            n++;
        o = o->nast;
    }
    return n;
}

SBaza * wczytaj_baze(char *nazwa_pliku) {
    FILE *fin = fopen(nazwa_pliku, "r");
    if (fin == NULL) {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SBaza *baza = (SBaza*) malloc( sizeof(SBaza) );
    baza->lista_studentow = wczytaj_studentow(fin); //zwroci poiter do glowy listy studentow
    baza->lista_przedmiotow = wczytaj_przedmioty(fin, baza);
    baza->lista_ocen = wczytaj_oceny(fin, baza);

    fclose(fin);
    return baza;
}

void zapisz_baze(char *nazwa_pliku, SBaza * baza) {
    FILE *fout = fopen(nazwa_pliku, "w+");
    fprintf(fout, "%d", ile_studentow(baza));
    fprintf(fout, "\n");

    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        fprintf(fout, "%s;%s;%s;%s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }

    fprintf(fout, "%d", ile_przedmiotow(baza));
    fprintf(fout, "\n");
    Przedmiot * p = baza->lista_przedmiotow;
    while (p != NULL) {
        fprintf(fout, "%s;%s;%s\n", p->kod_przedmiotu, p->nazwa, p->semestr);
        p = p->nast;
    }

    fprintf(fout, "%d", ile_studentow_na_przedmiocie(baza));
    fprintf(fout, "\n");
    Ocena * o = baza->lista_ocen;
    while (o != NULL) {
        fprintf(fout, "%s;%s;%f;%s\n", o->kod_przedmiotu, o->nr_albumu, o->ocena, o->komentarz);
        o = o->nast;
    }
}

void dodaj_przedmiot(SBaza * baza, char *kod, char* nazwa, char* semestr){
    Przedmiot *p = (Przedmiot*) malloc(sizeof(Przedmiot));

    p->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(kod) + 1));
    strcpy(p->kod_przedmiotu, kod);
    
    p->nazwa = (char*) malloc(sizeof(char) * (strlen(nazwa) + 1));
    strcpy(p->nazwa, nazwa);

    p->semestr = (char*) malloc(sizeof(char) * (strlen(semestr) + 1));
    strcpy(p->semestr, semestr);


    Przedmiot *x = baza->lista_przedmiotow;    
    for(int i = 0; i < ile_przedmiotow(baza); i++){
        if(x->nast != NULL)
            x = x->nast;
        else
            x->nast = p;
    }
}

void dodaj_studenta(SBaza * baza, char *imie, char* nazwisko, char* nr_albumu, char* email){
    Student *s = (Student*) malloc(sizeof(Student));

    s->imie = (char*) malloc(sizeof(char) * (strlen(imie) + 1));
    strcpy(s->imie, imie);
    
    s->nazwisko = (char*) malloc(sizeof(char) * (strlen(nazwisko) + 1));
    strcpy(s->nazwisko, nazwisko);

    s->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(s->nr_albumu, nr_albumu);

    s->email = (char*) malloc(sizeof(char) * (strlen(email) + 1));
    strcpy(s->email, email);


    Student *x = baza->lista_studentow; //glowa    
    for(int i = 0; i < ile_studentow(baza); i++){
        if(x->nast != NULL)
            x = x->nast;
        else
            x->nast = s;
    }
}

void dodaj_ocene(SBaza * baza, char *kod_przedmiotu, char* nr_albumu, float ocena, char* komentarz){ //w liscie ocen dodaje pierwsza albo kolejna ocene
    Ocena *o = (Ocena*) malloc(sizeof(Ocena));

    o->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(kod_przedmiotu) + 1));
    strcpy(o->kod_przedmiotu, kod_przedmiotu);
    
    o->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(o->nr_albumu, nr_albumu);

    o->ocena = ocena;

    o->komentarz = (char*) malloc(sizeof(char) * (strlen(komentarz) + 1));
    strcpy(o->komentarz, komentarz);


    Ocena *x = baza->lista_ocen; //glowa    
    int k = 0;
    Ocena *ostatni = NULL;
    for(int i = 0; i < ile_studentow_na_przedmiocie(baza); i++){
        if(x->nast == NULL){
            ostatni = x;
        }
        if(strcmp(x->kod_przedmiotu, kod_przedmiotu) == 0 && strcmp(x->nr_albumu, nr_albumu) == 0 && x->ocena == 0){
            x->ocena = o->ocena;
            strcpy(x->komentarz, o->komentarz);
            k++;
            break;
        }
        if(ostatni == NULL)
            x = x->nast;
    }
    if(k == 0)
        ostatni->nast = o;

}

void dodaj_studenta_do_przedmiotu(SBaza *baza, char *nr_albumu, char* kod){ //dodaje "ocene" z wartoscia 0 czyli dodaje studenta do przedmiotu
    Ocena *o = (Ocena*) malloc(sizeof(Ocena));

    o->kod_przedmiotu = (char*) malloc(sizeof(char) * (strlen(kod) + 1));
    strcpy(o->kod_przedmiotu, kod);
    
    o->nr_albumu = (char*) malloc(sizeof(char) * (strlen(nr_albumu) + 1));
    strcpy(o->nr_albumu, nr_albumu);

    o->ocena = 0;

    o->komentarz = (char*) malloc(sizeof(char));
    strcpy(o->komentarz, " ");


    Ocena *x = baza->lista_ocen;    
    for(int i = 0; i < ile_studentow_na_przedmiocie(baza); i++){
        if(x->nast != NULL)
            x = x->nast;
        else
            x->nast = o;
    }
}

Student *znajdz_studenta(SBaza *baza, char *nr_albumu){
    Student *s = baza->lista_studentow;
    while(s != NULL){
        if(strcmp(s->nr_albumu, nr_albumu) == 0)
            break;
        else
            s = s->nast;
    }
    return s;
}

void wyswietl_studenta(Student *stud){
    printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
}

void wyswietl_studentow_na_przedmiocie(SBaza *baza, char* kod) {
    Ocena *o = baza->lista_ocen;
    Student *s = NULL;
    while (o != NULL) {
        if(strcmp(kod, o->kod_przedmiotu) == 0){
            s = znajdz_studenta(baza, o->nr_albumu);
            wyswietl_studenta(s);
        }
        o = o->nast;
    }
}

float oblicz_srednia(SBaza *baza, char *nr_albumu){
    int k = 0;
    float suma = 0;
    Ocena *o = baza->lista_ocen;
    for(int i = 0; i<ile_studentow_na_przedmiocie(baza); i++){
        if(strcmp(nr_albumu, o->nr_albumu) == 0 && o->ocena != 0){ //ocene 0 traktujemy jako brak oceny
            suma += o->ocena;
            k++;
        }
        o = o->nast;
    }

    return suma/k;
}

float srednia_przedmiotu(SBaza *baza, char *kod){
    int k = 0;
    float suma = 0;
    Ocena *o = baza->lista_ocen;
    for(int i = 0; i<ile_studentow_na_przedmiocie(baza); i++){
        if(strcmp(kod, o->kod_przedmiotu) == 0 && o->ocena != 0){ //ocene 0 traktujemy jako brak oceny
            suma += o->ocena;
            k++;
        }
        o = o->nast;
    }

    return suma/k;
}

int ile_ocen_na_przedmiocie(SBaza *baza, char*kod){
    int k = 0;
    Ocena *o = baza->lista_ocen;
    while(o != NULL){
        if(strcmp(o->kod_przedmiotu, kod) == 0 && o->ocena != 0)
            k++;
        o = o->nast;
    }
    
    return k;
}

void listuj_studentow(SBaza *baza) {
    Student * stud = baza->lista_studentow;
    printf("Studenci:\n");
    while (stud != NULL) {
        printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
}

void listuj_przedmioty(SBaza *baza) {
    Przedmiot *p = baza->lista_przedmiotow;
    printf("Przedmioty:\n");
    while(p != NULL){
        printf("%s %s %s\n", p->kod_przedmiotu, p->nazwa, p->semestr);
        p = p->nast;
    }
}

void listuj_oceny(SBaza *baza) {
    Ocena *o = baza->lista_ocen;
    printf("Studenci na przedmiotach:\n");
    while(o != NULL){
        printf("%s %s %f %s\n", o->kod_przedmiotu, o->nr_albumu, o->ocena, o->komentarz);
        o = o->nast;
    }
}

void zwolnij_student(Student *s) {
    free(s->imie);
    free(s->nazwisko);
    free(s->nr_albumu);
    free(s->email);
    free(s);
}

void zwolnij_przedmiot(Przedmiot *p) {
    free(p->kod_przedmiotu);
    free(p->nazwa);
    free(p->semestr);
    free(p);
}

void zwolnij_ocene(Ocena *o) {
    free(o->kod_przedmiotu);
    free(o->nr_albumu);
    free(o->komentarz);
    free(o);
}

void zwolnij_liste_studentow(Student *s) {
    Student *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_student(s);
        s = n;
    }
}

void zwolnij_liste_przedmiotow(Przedmiot *p) {
    Przedmiot *n;
    while (p != NULL) {
        n = p->nast;
        zwolnij_przedmiot(p);
        p = n;
    }
}

void zwolnij_liste_ocen(Ocena *o) {
    Ocena *n;
    while (o != NULL) {
        n = o->nast;
        zwolnij_ocene(o);
        o = n;
    }
}

void zwolnij(SBaza *baza) {
    zwolnij_liste_studentow(baza->lista_studentow);
    zwolnij_liste_przedmiotow(baza->lista_przedmiotow);
    zwolnij_liste_ocen(baza->lista_ocen);
    free(baza);
}