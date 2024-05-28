#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef struct Metrou Metrou;
struct Metrou
{
	int serie;
	int nrStatii;
	char* magistrala;
};
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;
struct NodSecundar
{
	NodSecundar* next;
	NodPrincipal* nod;
};
struct NodPrincipal
{
	NodPrincipal* next;
	Metrou info;
	NodSecundar* vecin;

};



Metrou creareMetrou(int serie, int nrStatii, const char* magistrala)
{
	Metrou m;
	m.serie = serie;
	m.nrStatii = nrStatii;
	m.magistrala = (char*)malloc(sizeof(char) * (strlen(magistrala) + 1));
	strcpy(m.magistrala, magistrala);
	return m;
}
//inserare la inceput
void inserareInceput(NodPrincipal** cap, Metrou m)
{
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->vecin = NULL;
	nou->next = *cap;
	*cap = nou;
}
// cautare nod dupa serie
NodPrincipal* cautareNodDupaSerie(NodPrincipal* cap, int serie)
{
	NodPrincipal* temp = cap;
	while (temp)
	{
		if (temp->info.serie == serie)
			return temp;
		temp = temp->next;
	}
	return NULL;
}
//inserare la final in lista secundara
NodSecundar* inserareListaSecundara(NodSecundar* cap, NodPrincipal* nod)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = nod;
	nou->next = NULL;
	if (cap)
	{
		NodSecundar* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	else
		cap = nou;
	return cap;
}
//inserare muchie
void inserareMuchie(NodPrincipal* graf, int serieStart, int serieFinal)
{
	NodPrincipal* nodStart = cautareNodDupaSerie(graf, serieStart);
	NodPrincipal* nodFinal = cautareNodDupaSerie(graf, serieFinal);
	if (nodStart && nodFinal)
	{
		nodStart->vecin = inserareListaSecundara(nodStart->vecin, nodFinal);
		nodFinal->vecin = inserareListaSecundara(nodFinal->vecin, nodStart);
	}
}
void afisareMetrou(Metrou m)
{
	printf("Metroul %s are %d statii si serie %d\n", m.magistrala, m.nrStatii, m.serie);
}
void afisareGraf(NodPrincipal* graf)
{
	NodPrincipal* temp = graf;
	while (temp)
	{
		afisareMetrou(temp->info);
		NodSecundar* tempSec = temp->vecin;
		while (tempSec)
		{
			afisareMetrou(tempSec->nod->info);
			tempSec = tempSec->next;
		}
		temp = temp->next;
	}
}
#pragma region Coada
typedef struct NodCoada;
struct NodCoada
{
	int serie;
	NodCoada* next;
};
void inserareCoada(NodCoada** cap, int serie)
{
	NodCoada* nodNou = (NodCoada*)malloc(sizeof(NodCoada));
	nodNou->serie = serie;
	nodNou->next = NULL;
	if (*cap)
	{
		NodCoada* aux = (*cap);
		while (aux->next!=NULL)
		{
			aux = aux->next;

		}
		aux->next = nodNou;
	}
	else
	{
		*cap = nodNou;
	}
}

int extragereCoada(NodCoada** cap)
{
	if (*cap)
	{
		int rezultat = (*cap)->serie;
		NodCoada* aux = (*cap);
		*cap = aux->next;
		free(aux);
	}

	else return -1;
}

#pragma endregion
//afisare parcuregere in latime
int numarNoduri(NodPrincipal* graf)
{
	int nr = 0;
	while (graf)
	{
		nr++;
		graf = graf->next;
	}
	return nr;
}


void afisareParcurgereLatime(NodPrincipal* graf, int serie)
{
	NodCoada* coada = NULL;
	int nrNoduri = numarNoduri(graf);
	char* vizitate = (char*)malloc(nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	inserareCoada(&coada, serie);
	vizitate[serie] = 1;
	while (coada)
	{
		int serieNoua= extragereCoada(&coada);
		NodPrincipal* nou = cautareNodDupaSerie(graf, serieNoua);
		afisareMetrou(nou->info);
		NodSecundar* temp = nou->vecin;
		while (temp)
		{
			if (vizitate[temp->nod->info.serie] == 0)
			{
				vizitate[temp->nod->info.serie] = 1;
				inserareCoada(&coada, temp->nod->info.serie);
			}
			temp = temp->next;

		}

	}
	if (vizitate)
	{
		free(vizitate);
	}

}

//functie de dezalocare
void dezalocaregrafic(NodPrincipal** graf)
{
	while (*graf)
	{
		NodPrincipal* aux = *graf;
		free(aux->info.magistrala);
		while (aux->vecin)
		{
			NodSecundar* temp = aux->vecin;
			aux->vecin= temp->next;
			free(temp);
		}
		*graf = aux->next;
		free(aux);
	}
}
void main()
{
	NodPrincipal* graf = NULL;
	Metrou m1 = creareMetrou(1, 10, "M1");
	Metrou m2 = creareMetrou(2, 15, "M2");
	Metrou m3 = creareMetrou(3, 20, "M3");
	inserareInceput(&graf, m1);
	inserareInceput(&graf, m2);
	inserareInceput(&graf, m3);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 3);
	inserareMuchie(graf, 1, 3);
	afisareGraf(graf);
	afisareParcurgereLatime(graf, 0);
}