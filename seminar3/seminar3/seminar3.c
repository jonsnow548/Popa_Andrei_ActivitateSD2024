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
struct Masina* citireFisier(const char* numeFisier, int* nrMasini)
{
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char sep[] = ",\n";
	struct Masina* masini = NULL;
	(*nrMasini) = 0;
	while (fgets(buffer, 100, file) != NULL)
	{
	char* element=	strtok(buffer, sep);
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
     masini = adaugareInVector(masini, m, nrMasini);
	}
	return masini;



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
int main()
{
	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini);
	afisareMasini(masini, nrMasini);
	int nrMasiniFiltrate = 0;
	struct Masina* masiniFiltrate = filtreazaMasini(masini, nrMasini, &nrMasiniFiltrate);

	printf("Masinile cu mai putin de 4 usi:\n");
	afisareMasini(masiniFiltrate, nrMasiniFiltrate);
	return 0;

}