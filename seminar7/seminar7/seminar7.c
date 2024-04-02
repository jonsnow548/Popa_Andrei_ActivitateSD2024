#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Galerie Galerie;
struct Galerie
{
	int cod;
	char* nume;
	float pretIntrare;

};

typedef struct nod nod;
struct nod {
	Galerie info;
	nod* next;
};
typedef struct hashTable HashTable;
struct hashTable
{
	nod** vector;
	int dim;
};
HashTable initializareHashtable(int dimensiune)
{
	HashTable hash;
	hash.dim = dimensiune;
	hash.vector = (nod**)malloc(sizeof(nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++)
	{
		hash.vector[i] = NULL;
	}
	return hash;
}
Galerie initGalerie(int cod, const char* nume, float pret)
{
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(g.nume, nume);
	g.pretIntrare = pret;
	return g;
}
int calculHash(int cod,const char* nume, int dimensiune)
{
	if (dimensiune > 0)
	{
		int rez = cod * strlen(nume);
		return rez % dimensiune;
	}
	return -1;

}
void inserareLaFinal(nod** cap, Galerie galerie)
{
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = galerie;
	nou->next = NULL;
	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		nod* temp = *cap;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void inserareGalerieInTabela(HashTable hash, Galerie galerie)
{
	if (hash.dim > 0)
	{
		int pozitie = calculHash(galerie.cod, galerie.nume, hash.dim);
		if (hash.vector[pozitie] != NULL)
		{
			inserareLaFinal(&hash.vector[pozitie], galerie);
		}
		else
		{
			inserareLaFinal(&hash.vector[pozitie], galerie);
			
		}
	}

}
void afisareGalerie(Galerie galerie)
{
	printf("Cod: %d, Nume: %s, Pret: %f\n", galerie.cod, galerie.nume, galerie.pretIntrare);
}
void afisareLista(nod* cap)
{
	nod* temp = cap;
	while (temp)
	{
		afisareGalerie(temp->info);
		temp = temp->next;
	}
}
void afisareTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if(tabela.vector[i]!=NULL)
		{
			printf("Pozitia %d in tabela hash:\n", (i+1));
			afisareLista(tabela.vector[i]);
		}
	}
   }
Galerie cautaGalerieDupaCheie(HashTable tabela, int cod, const char* nume)
{
	if (tabela.dim > 0)
	{
		int pozitie = calculHash(cod, nume, tabela.dim);
		if (tabela.vector[pozitie] != NULL)
		{
			nod* temp = tabela.vector[pozitie];
			while (temp)
			{
				if (temp->info.cod == cod && strcmp(temp->info.nume, nume) == 0)
				{
					return temp->info;
				}
				temp = temp->next;
			}
		}
	}
	Galerie g;
	g.cod = -1;
	g.nume = NULL;
	g.pretIntrare = -1;
	return g;
}
void main()
{   
	Galerie g1,g2,g3,g4,g5,g6;
	g1 = initGalerie(1, "Orizont", 10);
	g2 = initGalerie(2, "Cercul armatei", 6);
	g3 = initGalerie(3, "Louvre", 30);
	g4 = initGalerie(4, "AAA", 20);
	g5 = initGalerie(5, "BBB", 15);
	g6 = initGalerie(6, "CCC", 17);

	HashTable tabela = initializareHashtable(5);
	inserareGalerieInTabela(tabela, g1);
	inserareGalerieInTabela(tabela, g2);
	inserareGalerieInTabela(tabela, g3);
	inserareGalerieInTabela(tabela, g4);
	inserareGalerieInTabela(tabela, g5);
	inserareGalerieInTabela(tabela, g6);
	afisareTabela(tabela);
	Galerie gasit = cautaGalerieDupaCheie(tabela, 3, "Louvre");
	if (gasit.cod != -1)
	{
		printf("Galeria a fost gasita:\n");
		afisareGalerie(gasit);
	}
	else
	{
		printf("Galeria nu a fost gasita\n");
	}

}
