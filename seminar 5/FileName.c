#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cafenea Cafenea;
typedef struct Nod Nod;

struct Cafenea {
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct Nod {
    Cafenea info;
    Nod* next;
};

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);

    return cafenea;
}

Nod* inserareInceput(Cafenea c, Nod* cap) {
    Nod* nou = malloc(sizeof(Nod));
    nou->next = cap;
    nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
    return nou;
}

void afisareCafenea(Cafenea c) {
    printf("\nDenumire: %s , Nr scaune: %d , Suprafata: %.2f\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareCafenele(Nod* lista) {
    while (lista != NULL) {
        afisareCafenea(lista->info);
        lista = lista->next;
    }
}

//numele cafenelei care are densitatea cea mai mica
char* numeCafeneaDensitateMinima(Nod* lista) {
    if (lista != NULL) {
        if (lista->info.suprafata != 0) {
            float minim = lista->info.nrLocuri / lista->info.suprafata;
            Nod* adresa = lista;
            lista = lista->next;
            while (lista != NULL) {
                if (lista->info.nrLocuri / lista->info.suprafata < minim) {
                    minim = lista->info.nrLocuri / lista->info.suprafata;
                    adresa = lista;
                }
                lista = lista->next;
            }
            char* nume;
            nume = malloc(sizeof(char) * (strlen(adresa->info.nume) + 1));
            strcpy(nume, adresa->info.nume);
            return nume;
        }
    }
    return NULL;
}

void stergereLista(Nod** nod) {
    while (*nod != NULL) {
        Nod* aux;
        aux = *nod;
        *nod = (*nod)->next;
        free(aux->info.nume);
        free(aux);
    }
    *nod = NULL;
}

void inserareFinal(Nod** lista, Cafenea c) {
    if ((*lista) == NULL) {
        (*lista) = inserareInceput(c, *lista);
    }
    else {
        Nod* curent = (*lista);
        while (curent->next != NULL) {
            curent = curent->next;
        }
        Nod* n = (Nod*)malloc(sizeof(Nod));
        n->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
        n->next = NULL;
        curent->next = n;
    }
}

void main() {
    Nod* cap = NULL;
    Cafenea cafenea1 = initializareCafenea("Tucano", 12, 20);
    Cafenea cafenea2 = initializareCafenea("Teds", 17, 17.3);
    Cafenea cafenea3 = initializareCafenea("Urban", 65, 33);
    Cafenea sb = initializareCafenea("Starbucks", 25, 43);
    cap = inserareInceput(cafenea1, cap);
    cap = inserareInceput(cafenea2, cap);
    cap = inserareInceput(cafenea3, cap);
    afisareCafenele(cap);
    char* numeMinim = numeCafeneaDensitateMinima(cap);
    printf("\nCafenea cu densitatea minima: %s", numeMinim);
    inserareFinal(&cap, sb);
    afisareCafenele(cap);
    stergereLista(&cap);

    afisareCafenele(cap);
    free(cafenea1.nume);
    cafenea1.nume = NULL;

    free(cafenea2.nume);
    cafenea2.nume = NULL;

    free(cafenea3.nume);
    cafenea3.nume = NULL;

    free(numeMinim);
    numeMinim = NULL;
}