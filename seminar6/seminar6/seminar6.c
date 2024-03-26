#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Santier Santier;
typedef struct NodLdi NodLdi;

struct Santier {
    char* nume_proiect;
    int nrMuncitori;
    float suprafata;
};

struct NodLdi {
    Santier info;
    NodLdi* next;
    NodLdi* prev;
};

typedef struct ListaDubla {
    NodLdi* prim;
    NodLdi* ultim;
} ListaDubla;

Santier initializeazaSantier(const char* nume_proiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.nume_proiect = (char*)malloc(strlen(nume_proiect) + 1);
    strcpy(santier.nume_proiect, nume_proiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;
    return santier;
}

void inserareInceput(ListaDubla* lista, Santier s) {
    NodLdi* aux = (NodLdi*)malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;
    if (lista->prim != NULL) {
        lista->prim->prev = aux;
    }
    else {
        lista->ultim = aux;
    }
    lista->prim = aux;
}

void afisareSantier(Santier s) {
    printf("%s %d %.2f\n", s.nume_proiect, s.nrMuncitori, s.suprafata);
}

void afisareLista(ListaDubla lista) {
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next) {
        afisareSantier(nod->info);
    }
}

void stergeSantier(ListaDubla* lista, const char* nume) {
    NodLdi* nod = lista->prim;

    
    while (nod != NULL) {
       
        if (strcmp(nod->info.nume_proiect, nume) == 0) {
            if (nod == lista->prim) {
                lista->prim = nod->next;
                if (lista->prim != NULL) {
                    lista->prim->prev = NULL;
                }
                else {
                    lista->ultim = NULL;
                }
            }
            else {
                nod->prev->next = nod->next;
                if (nod->next != NULL) {
                    nod->next->prev = nod->prev;
                }
                else {
                    lista->ultim = nod->prev;
                }
            }
            free(nod->info.nume_proiect);
            free(nod);
            printf("Santierul %s a fost sters.\n", nume);
            return;
        }
        nod = nod->next;
    }

    
    printf("Nu s-a gasit niciun santier cu numele %s.\n", nume);
}
void stergeListaCompleta(ListaDubla* lista) {
    NodLdi* nod = lista->prim;
    while (nod != NULL) {
        NodLdi* temp = nod;
        nod = nod->next;
        free(temp->info.nume_proiect);
        free(temp);
    }
    lista->prim = NULL;
    lista->ultim = NULL;
}
int numarTotalMuncitori(ListaDubla lista) {
    int totalMuncitori = 0;
    NodLdi* nod = lista.prim;
    while (nod != NULL) {
        totalMuncitori += nod->info.nrMuncitori;
        nod = nod->next;
    }
    return totalMuncitori;
}
int calcNrMuncitoriSuprafata(ListaDubla lista, float suprafataMax) {
    int totalMuncitori = 0;
    NodLdi* nod = lista.prim;

    while (nod != NULL) {
        if (nod->info.suprafata < suprafataMax) {
            totalMuncitori += nod->info.nrMuncitori;
        }
        nod = nod->next;
    }

    return totalMuncitori;
}



int main() {
    Santier s1, s2, s3;
    s1 = initializeazaSantier("Santier1", 10, 300);
    s2 = initializeazaSantier("Santier2", 20, 400);
    s3 = initializeazaSantier("Santier3", 30, 500);

    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;

    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);

    afisareLista(lista);
    int nrMuncitori = numarTotalMuncitori(lista);
    printf("%d", nrMuncitori);
    printf("\n");
  
    stergeSantier(&lista, "Santier1");
    afisareLista(lista);
    stergeListaCompleta(&lista);
    
    return 0;
}
