#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Masina
{
    int id;
    char* producator;
    int nrUsi;
    float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini)
{
    struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasini + 1));
    for (int i = 0; i < *nrMasini; i++)
    {
        aux[i] = masini[i];
    }
    aux[*nrMasini] = m;
    (*nrMasini)++;
    if (masini != NULL)
    {
        free(masini);
    }
    return aux;
}

void citireMatrice(const char* numeFisier, struct Masina** matrice, int nrLinii, int* nrCol)
{
    FILE* file = fopen(numeFisier, "r");
    char buffer[100];
    char sep[] = ",\n";
    while (fgets(buffer, 100, file) != NULL)
    {
        char* element = strtok(buffer, sep);
        struct Masina m;

        m.id = atoi(element);
        element = strtok(NULL, sep);
        m.producator = malloc(strlen(element) + 1);
        strcpy(m.producator, element);
        element = strtok(NULL, sep);
        m.nrUsi = atoi(element);
        element = strtok(NULL, sep);
        m.pret = atof(element);
        element = strtok(NULL, sep);
        matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrCol[m.nrUsi - 2]));
    }
    fclose(file);
}

struct Masina* filtreazaMasini(struct Masina* masini, int nrMasini, int* nrMasiniFiltrate)
{
    struct Masina* masiniFiltrate = NULL;
    (*nrMasiniFiltrate) = 0;
    for (int i = 0; i < nrMasini; i++)
    {
        if (masini[i].nrUsi < 4)
        {
            masiniFiltrate = adaugareInVector(masiniFiltrate, masini[i], nrMasiniFiltrate);
        }
    }
    return masiniFiltrate;
}

void afisareMasini(struct Masina* masini, int nrMasini)
{
    for (int i = 0; i < nrMasini; i++)
    {
        printf("ID: %d\n", masini[i].id);
        printf("Producator: %s\n", masini[i].producator);
        printf("Numar usi: %d\n", masini[i].nrUsi);
        printf("Pret: %.2f\n\n", masini[i].pret);
    }
}

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol)
{
    for (int i = 0; i < nrLinii; i++)
    {
        printf("Linia %d:\n", i + 1);
        for (int j = 0; j < nrCol[i]; j++)
        {
            printf("Masina %d:\n", j + 1);
            afisareMasini(matrice[i], nrCol[i]);
        }
    }
}

float pretMediu(struct Masina** matrice, int nrLinii, int* nrCol, int nrUsi)
{
    if (nrUsi < 2 || nrUsi > 4)
    {
        return 0;
    }

    float pret_total = 0;
    int nr_Masini = 0;
    int index = nrUsi - 2;
    if (nrCol[index] == 0)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < nrCol[index]; i++)
        {
            pret_total = pret_total + matrice[index][i].pret;
        }
        return pret_total / nrCol[index];
    }
}

struct Masina cautaMasinaID(struct Masina** matrice, int nrLinii, int* nrCol, int id)
{
    for (int i = 0; i < nrLinii; i++)
    {
        for (int j = 0; j < nrCol[i]; j++)
        {
            if (matrice[i][j].id == id)
                return matrice[i][j];
        }
    }
    struct Masina m;
    m.id = -1;
    m.producator = NULL;
    m.pret = -1;
    m.nrUsi = -1;
    return m;
}

void dezalocareMatrice(struct Masina** matrice, int nrLinii, int* nrCol)
{
    for (int i = 0; i < nrLinii; i++)
    {
        for (int j = 0; j < nrCol[i]; j++)
        {
            free(matrice[i][j].producator);
        }
        free(matrice[i]); // Corrected the order of freeing memory
    }
    free(nrCol); // No need for dereferencing here
    free(matrice);
}


int main()
{
    struct Masina** matrice;
    int nrLinii = 3;
    int* nrCol;
    nrCol = (int*)malloc(sizeof(int) * nrLinii);
    matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
    for (int i = 0; i < nrLinii; i++)
    {
        nrCol[i] = 0;
        matrice[i] = NULL;
    }
    citireMatrice("masini.txt", matrice, nrLinii, nrCol);
    afisareMatrice(matrice, nrLinii, nrCol);
    printf("Pretul mediu este: %.2f\n", pretMediu(matrice, nrLinii, nrCol, 3));

    struct Masina masina_cautata;
    masina_cautata = cautaMasinaID(matrice, nrLinii, nrCol, 2);

    if (masina_cautata.id != -1)
    {
        printf("Masina cu ID-ul cautat este:\n");
        printf("ID: %d\n", masina_cautata.id);
        printf("Producator: %s\n", masina_cautata.producator);
        printf("Numar usi: %d\n", masina_cautata.nrUsi);
        printf("Pret: %.2f\n", masina_cautata.pret);
    }
    else
    {
        printf("Masina cu ID-ul cautat nu a fost gasita.\n");
    }

    dezalocareMatrice(matrice, nrLinii, nrCol);

    return 0;
}
