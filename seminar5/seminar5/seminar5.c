#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Santier Santier;
typedef struct Nod Nod;

struct Santier {
    char* nume_proiect;
    int nrMuncitori;
    float suprafata;
};

struct Nod {
    Santier santier;
    Nod* next;
};

Santier initializeazaSantier(const char* nume_proiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.nume_proiect = (char*)malloc(strlen(nume_proiect) + 1);
    strcpy(santier.nume_proiect, nume_proiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;
    return santier;
}

Nod* inserareInceput(Nod* lista, Santier s) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->next = lista;
    nou->santier = s;
    return nou;
}

void afisareLista(Nod* lista) {
    Nod* temp = lista;
    while (temp != NULL) {
        printf("Nume proiect: %s, Numar muncitori: %d, Suprafata: %.2f\n",
            temp->santier.nume_proiect, temp->santier.nrMuncitori, temp->santier.suprafata);
        temp = temp->next;
    }
}

int sumaMuncitori(Nod* lista) {
    int suma = 0;
    Nod* temp = lista;
    while (temp != NULL) {
        suma += temp->santier.nrMuncitori;
        temp = temp->next;
    }
    return suma;
}
void stergere(Nod** lista) {
    while (*lista != NULL) {
        Nod* temp = *lista;
        *lista = (*lista)->next;
        free(temp->santier.nume_proiect);
        free(temp);

    }
    (*lista) = NULL;
}
//numele santierului cu densitatea cea mai mare de muncitori pe m^2

char* Densitate(Nod* lista) {
    float densitatemax = 0;
    char* numeProiectMax = NULL;

    while (lista != NULL) {
        if (lista->santier.suprafata != 0) {
            float densitate = lista->santier.nrMuncitori / lista->santier.suprafata;
            if (densitate > densitatemax) {
                densitatemax = densitate;
                numeProiectMax = lista->santier.nume_proiect;
            }
        }
        lista = lista->next;
    }
    return numeProiectMax;
}
int main() {
    Nod* lista = NULL;
    Santier s1, s2, s3;
    s1 = initializeazaSantier("Santier1", 10, 300);
    s2 = initializeazaSantier("Santier2", 20, 400);
    s3 = initializeazaSantier("Santier3", 30, 500);

    lista = inserareInceput(lista, s3);
    lista = inserareInceput(lista, s2);
    lista = inserareInceput(lista, s1);

    printf("Lista santierelor:\n");
    afisareLista(lista);

    printf("\nSuma muncitorilor pe toate santierele: %d\n", sumaMuncitori(lista));

    char* nume = Densitate(lista);
    if (nume != NULL)
        printf("\nNumele santierului cu densitatea cea mai mare de muncitori pe m^2: %s\n", nume);
    else
        printf("\nNEGATIV\n");

    
    stergere(&lista);

    return 0;
}

