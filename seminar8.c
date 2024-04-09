#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mail {
    char* text;
    int prioritate;
} Mail;

typedef struct Heap {
    Mail* vector;
    int dim;
} Heap;

Heap initializareHeap(int dim) {
    Heap heap;
    heap.vector = (Mail*)malloc(sizeof(Mail) * dim);
    heap.dim = dim;
    return heap;
}

Mail initializareMail(const char* text, int prioritate) {
    Mail mail;
    mail.text = (char*)malloc(strlen(text) + 1);
    strcpy(mail.text, text);
    mail.prioritate = prioritate;
    return mail;
}

void filtrare(Heap* heap, int pozRad) {
    int fs = pozRad * 2 + 1;
    int fd = pozRad * 2 + 2;
    int pozMax = pozRad;
    if (fs < heap->dim && heap->vector[pozMax].prioritate < heap->vector[fs].prioritate) {
        pozMax = fs;
    }
    if (fd < heap->dim && heap->vector[pozMax].prioritate < heap->vector[fd].prioritate) {
        pozMax = fd;
    }
    if (pozMax != pozRad) {
        if (heap->vector[pozRad].prioritate > heap->vector[pozMax].prioritate) {
            Mail aux = heap->vector[pozRad];
            heap->vector[pozRad] = heap->vector[pozMax];
            heap->vector[pozMax] = aux;

            if (pozMax < (heap->dim - 2) / 2) {
                filtrare(heap, pozMax);
            }
        }
    }
}

Mail extragereMax(Heap* heap) {
    Mail maxMail = heap->vector[0]; // Extrage elementul maxim (primul element al vectorului)

    // Aloc� memorie pentru un nou vector cu o dimensiune redus�
    Mail* aux = (Mail*)malloc(sizeof(Mail) * (heap->dim - 1));

    // Copiaz� toate elementele din vector, cu excep?ia primului element, �n noul vector
    for (int i = 1; i < heap->dim; i++) {
        aux[i - 1] = heap->vector[i];
    }

    // Elibereaz� memoria alocat� pentru vectorul vechi
    free(heap->vector);

    // Actualizeaz� vectorul din structura Heap cu noul vector ?i scade dimensiunea heap-ului
    heap->vector = aux;
    heap->dim--;

    // Rearanjeaz� heap-ul pentru a men?ine proprietatea de max-heap
    for (int i = (heap->dim - 2) / 2; i >= 0; i--) {
        filtrare(heap, i);
    }

    // Returneaz� elementul maxim extras
    return maxMail;
}

void afisareMail(Mail mail) {
    printf("Mail cu textul %s si grad de prioritate %d\n", mail.text, mail.prioritate);
}

void afisareHeap(Heap heap) {
    for (int i = 0; i < heap.dim; i++) {
        afisareMail(heap.vector[i]);
    }
}
void inserareMailInHeap(Heap* heap, Mail mail) {
    // Realoc� memoria pentru a include un nou element �n vector
    heap->vector = (Mail*)realloc(heap->vector, sizeof(Mail) * (heap->dim + 1));
    heap->dim++; // Increment�m dimensiunea heap-ului

    // Adaug� noul element la sf�r?itul vectorului
    heap->vector[heap->dim - 1] = mail;

    // Rearanjeaz� heap-ul pentru a men?ine proprietatea de heap maxim
    int index = heap->dim - 1;
    while (index > 0 && heap->vector[index].prioritate > heap->vector[(index - 1) / 2].prioritate) {
        // Schimb� elementul cu p�rintele s�u p�n� c�nd este �n locul potrivit �n heap
        Mail temp = heap->vector[index];
        heap->vector[index] = heap->vector[(index - 1) / 2];
        heap->vector[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

int main(void) {
    Heap heap;
    heap = initializareHeap(6);
    heap.vector[0] = initializareMail("Salut1", 7);
    heap.vector[1] = initializareMail("Salut2", 9);
    heap.vector[2] = initializareMail("Salut3", 3);
    afisareHeap(heap);
    printf("\n");

    Mail maxMail = extragereMax(&heap);
    afisareMail(maxMail);
    printf(" a fost extras din heap.\n");

    afisareHeap(heap);

    for (int i = 0; i < heap.dim; i++) {
        free(heap.vector[i].text);
    }
    free(heap.vector);

    return 0;
}

