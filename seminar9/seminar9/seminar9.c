#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elev {
    int id;
    int nrMedii;
    float* medii;
} Elev;

typedef struct Nod {
    Elev info;
    struct Nod* st, * dr;
} Nod;

void inserareArbore(Nod** radacina, Elev elev) {
    if (*radacina == NULL) {
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        if (nou == NULL) {
         
            return;
        }
        nou->info = elev;
        nou->st = nou->dr = NULL;
        *radacina = nou;
    }
    else if (elev.id < (*radacina)->info.id) {
        inserareArbore(&((*radacina)->st), elev);
    }
    else if (elev.id > (*radacina)->info.id) {
        inserareArbore(&((*radacina)->dr), elev);
    }
}

Elev citireElev(FILE* fp) {
    Elev e;
    fscanf(fp, "%d", &e.id);
    fscanf(fp, "%d", &e.nrMedii);
    e.medii = (float*)malloc(e.nrMedii * sizeof(float));
    if (e.medii == NULL) {
        e.nrMedii = 0; 
        return e;
    }
    for (int i = 0; i < e.nrMedii; i++) {
        fscanf(fp, "%f", &e.medii[i]);
    }
    return e;
}

Nod* citireFisier(char* numeFisier) {
    Nod* arbore = NULL;
    FILE* fp = fopen(numeFisier, "r");
    if (!fp) {
        perror("Error opening file");
        return NULL;
    }
    int nrElevi;
    fscanf(fp, "%d", &nrElevi);
    for (int i = 0; i < nrElevi; i++) {
        Elev e = citireElev(fp);
        inserareArbore(&arbore, e);
    }
    fclose(fp);
    return arbore;
}

void afisareElev(Elev e) {
    printf("Elevul cu id-ul %d are mediile: ", e.id);
    for (int i = 0; i < e.nrMedii; i++) {
        printf("%5.2f ", e.medii[i]);
    }
    printf("\n");
}

void afisareInOrder(Nod* arbore) {
    if (arbore != NULL) {
        afisareInOrder(arbore->st);
        afisareElev(arbore->info);
        afisareInOrder(arbore->dr);
    }
}
float calculeazaMediaTotala(Nod* arbore, int* totalNote, float* sumaNote) {
    if (arbore == NULL) {
        return 0;
    }

    calculeazaMediaTotala(arbore->st, totalNote, sumaNote);

    for (int i = 0; i < arbore->info.nrMedii; i++) {
        *sumaNote += arbore->info.medii[i];
        (*totalNote)++;
    }
    calculeazaMediaTotala(arbore->dr, totalNote, sumaNote);

    
    if (*totalNote > 0) {
        return *sumaNote / *totalNote;
    }
    else {
        return 0; 
    }
}

float calculeazaMediaGenerala(Nod* arbore) {
    int totalNote = 0;
    float sumaNote = 0.0;
    return calculeazaMediaTotala(arbore, &totalNote, &sumaNote);
}

int main() {
    Nod* arbore = citireFisier("fisier.txt");
    if (arbore != NULL) {
        afisareInOrder(arbore);
    }
    else {
        printf("Failed to create binary tree.\n");
    }
    return 0;
}

