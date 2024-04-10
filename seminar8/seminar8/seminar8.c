#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
//heap - folosit pentru cozi de prioritate
typedef struct Mail Mail;
typedef struct Heap Heap;

struct Mail {
	char* text;
	int prioritate;
};

struct Heap
{
	Mail* vector;
	int dimensiune;
};

Heap initializareHeap(int dimensiune)
{
	Heap heap;
	heap.vector = (Mail*)malloc(sizeof(Mail) * dimensiune);
	heap.dimensiune = dimensiune;
	return heap;
}

Mail initializareMail(const char* text, int prioritate)
{
	Mail mail;
	mail.text = (char*)malloc(strlen(text) + 1);
	strcpy(mail.text, text);
	mail.prioritate = prioritate;
	return mail;
}

void afisareMail(Mail mail)
{
	printf("Mailul cu textul %s si cu prioritatea %d\n", mail.text, mail.prioritate);
}

void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.dimensiune; i++)
	{
		afisareMail(heap.vector[i]);
	}
}

void filtrare(Heap heap, int pozRad)
{
	int fs = pozRad * 2 + 1;
	int fd = pozRad * 2 + 2;
	int pozMax = pozRad;


	if (fs < heap.dimensiune && heap.vector[pozMax].prioritate < heap.vector[fs].prioritate)
	{
		pozMax = fs;
	}

	if (fd < heap.dimensiune && heap.vector[pozMax].prioritate < heap.vector[fd].prioritate)
	{
		pozMax = fd;
	}

	if (pozMax != pozRad) {
		if (heap.vector[pozRad].prioritate < heap.vector[pozMax].prioritate)
		{
			Mail aux;
			aux = heap.vector[pozRad];
			heap.vector[pozRad] = heap.vector[pozMax];
			heap.vector[pozMax] = aux;

			if (pozMax < (heap.dimensiune - 2) / 2)
			{
				filtrare(heap, pozMax);
			}
		}
	}
}


Mail extragereMax(Heap* heap)
{
	if (heap->dimensiune > 0)
	{
		Mail extras = (*heap).vector[0];
		Mail* aux = (Mail*)(malloc(sizeof(Mail) * ((*heap).dimensiune - 1)));
		for (int i = 1; i < heap->dimensiune; i++)
		{
			aux[i - 1] = heap->vector[i];
		}

		free(heap->vector);
		heap->vector = aux;
		heap->dimensiune--;
		for (int i = (heap->dimensiune - 2) / 2; i >= 0; i--)
		{
			filtrare((*heap), i);
		}

		return extras;
	}
}

void inserareMailInHeap(Heap* heap, Mail mail)
{
	Mail* aux = (Mail*)(malloc(sizeof(Mail) * (heap->dimensiune + 1)));
	aux[0] = mail;
	for (int i = 1; i < heap->dimensiune + 1; i++)
	{
		aux[i] = heap->vector[i - 1];
	}

	free(heap->vector);
	heap->vector = aux;
	heap->dimensiune++;

	filtrare((*heap), 0);
}

void dezalocareHeap(Heap* heap)
{
	for (int i = 0; i < heap->dimensiune; i++)
	{
		free(heap->vector[i].text);
	}

	free(heap->vector);
	heap->vector = NULL;
	heap->dimensiune = 0;
}



void main()
{
	Heap heap = initializareHeap(6);

	heap.vector[0] = initializareMail("Salut1", 7);
	heap.vector[1] = initializareMail("Salut2", 9);
	heap.vector[2] = initializareMail("Salut3", 3);
	heap.vector[3] = initializareMail("Salut4", 8);
	heap.vector[4] = initializareMail("Salut5", 6);
	heap.vector[5] = initializareMail("Salut6", 10);
	afisareHeap(heap);
	printf("\n");

	for (int i = (heap.dimensiune - 2) / 2; i >= 0; i--)
	{
		filtrare(heap, i);
	}

	afisareHeap(heap);
	printf("\n");

	printf("\Elemente extrase: \n");
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));

	printf("Inserare elemente: \n");
	inserareMailInHeap(&heap, initializareMail("Salut7", 4));
	afisareHeap(heap);

	dezalocareHeap(&heap);
}