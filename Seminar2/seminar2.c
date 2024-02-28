#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
struct Farmacie {
    int id;
    char* nume;
    float suprafata;
};
struct Farmacie initializareFarmacie(int id, const char* nume, float suprafata)
{
    struct Farmacie f;
    f.id = id;
    f.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(f.nume, nume);
    f.suprafata = suprafata;
    return f;
}
void afisarefarmacie(struct Farmacie farmacie)
{
    printf("%d. %s are o suprafata de %5.2f\n", farmacie.id, farmacie.nume, farmacie.suprafata);
}
void afisarevector(struct Farmacie* farmacii, int nrFarmacii)
{
    for (int i = 0; i < nrFarmacii; i++)
    {
        afisarefarmacie(farmacii[i]);
    }
}
struct Farmacie* copiazaNElemente(struct Farmacie* vector, int nrFarmacii, int nrObiecteCopiate)
{
    if (nrObiecteCopiate <= nrFarmacii && nrObiecteCopiate > 0)
    {
        struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecteCopiate);
        for (int i = 0; i < nrObiecteCopiate; i++)
        {
            copiat[i] = initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
        }
        return copiat;
    }
    else
        return NULL;
}
struct Farmacie* copiazaFarmaciiMici(struct Farmacie* farmacii, int nrFarmacii, float pragSuprafata, int* nrFarmaciiMici)
{
    *nrFarmaciiMici = 0;
    for (int i = 0; i < nrFarmacii; i++)
    {
        if (farmacii[i].suprafata < pragSuprafata)
        {
            (*nrFarmaciiMici)++;

        }
    }
    struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici));
    int k = 0;
    for (int i = 0; i < nrFarmacii; i++)
    {
        if (farmacii[i].suprafata < pragSuprafata)
        {
            vector[k++] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
        }

    }
    return vector;
}
void dezalocareVectorFarmacii(struct Farmacie** vector, int* nrFarmacii)
{
    for (int i = 0; i < *nrFarmacii; i++)
    {
        free((*vector)[i].nume);

    }
    free(*vector);
    *nrFarmacii = 0;
}
struct Farmacie getFarmacieByID(struct Farmacie* vector, int nrFarmacii, int idCautat)
{
    for (int i = 0; i <= nrFarmacii; i++)
    {
        if (vector[i].id == idCautat)
        {
            return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);

        }
    }
    return initializareFarmacie(0, "N/A", 0);

}
int main()
{
    int nrFarmacii = 4;
    struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);
    for (int i = 0; i < nrFarmacii; i++)
    {
        farmacii[i] = initializareFarmacie(i + 1, "Farmacie", 30 * i + 10);
    }
    afisarevector(farmacii, nrFarmacii);
    int nrObiecteCopiate = 2;
    struct Farmacie* farmaciiCopiate = copiazaNElemente(farmacii, nrFarmacii, nrObiecteCopiate);
    printf("\n\n");
    afisarevector(farmaciiCopiate, nrObiecteCopiate);
    int nrFarmaciiMici = 0;
    farmacii[3].suprafata = 20;
    struct Farmacie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, 50, &nrFarmaciiMici);
    printf("\n\n");
    afisarevector(farmaciiMici, nrFarmaciiMici);
    printf("\n\n");
    struct Farmacie farmacieCautata = getFarmacieByID(farmacii, nrFarmacii, 7);
    afisarefarmacie(farmacieCautata);
    free(farmacieCautata.nume);

    dezalocareVectorFarmacii(&farmacii, &nrFarmacii);
    dezalocareVectorFarmacii(&farmaciiCopiate, &nrObiecteCopiate);


    return 0;

}
