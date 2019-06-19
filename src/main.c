#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <Splaytree.h>

#define MAXCHAR 1024

typedef struct heap_donnee {
	char* mot;
	int compte;
	struct heap_donnee* suivant;
} HEAP_DATA;

typedef struct MaxHeap {
	int size;
	int count;
	HEAP_DATA *heap;
} MaxHeap;

int HEAP_parent(int pos) {
	return (pos - 1) / 2;
}

int HEAP_leftChild(int pos) {
	return 2 * pos + 1;
}

int HEAP_rightChild(int pos) {
	return 2 * pos + 2;
}

void HEAP_initialiser(MaxHeap *h, int s) {
	h->count = 0;
	h->size = s;
	h->heap = (HEAP_DATA *)malloc(sizeof(HEAP_DATA) * s);
}

void HEAP_inserer(MaxHeap *h, HEAP_DATA v) {
	if (h->count == h->size) {
		h->size += 1;
		h->heap = realloc(h->heap, sizeof(HEAP_DATA) * h->size);
	}

    // une seule position possible : à la fin
	int index = h->count;
	h->heap[index] = v;

    // percolage
	while (index != 0) {
		if (h->heap[index].compte > h->heap[HEAP_parent(index)].compte) {

            // si le parent a un nombre d'occurence plus faible
            // que la nouvelle donnée, on les échange
			HEAP_DATA tmp = h->heap[index];
			h->heap[index] = h->heap[HEAP_parent(index)];
			h->heap[HEAP_parent(index)] = tmp;

			index = HEAP_parent(index);
		}
		else break;
	}
	h->count++;
}

void HEAP_construire(MaxHeap *h, HEAP_DATA * data, int data_length){
	h->count = 0;
	h->size = data_length;
	h->heap = (HEAP_DATA *)malloc(sizeof(HEAP_DATA) * data_length);
    for (int i = 0; i < data_length; i++)
    {
        HEAP_inserer(h, data[i]);
    }
}

void HEAP_pop(MaxHeap *h) {
	if (h->count == 0)
		return;

    // on inverse la racine
    // et la plus éloignée des feuilles
	h->heap[0] = h->heap[--(h->count)];

	int index = 0;

    // tamisage
	while (index < h->count) {
		int max = index;

		if (HEAP_leftChild(index) < h->count && h->heap[HEAP_leftChild(index)].compte > h->heap[max].compte)
		{
			max = HEAP_leftChild(index);
		}

		if (HEAP_rightChild(index) < h->count && h->heap[HEAP_rightChild(index)].compte > h->heap[max].compte)
		{
			max = HEAP_rightChild(index);
		}

		if (max != index) {
			HEAP_DATA tmp = h->heap[index];
			h->heap[index] = h->heap[max];
			h->heap[max] = tmp;
			index = max;
		}
		else break;
	}
}

HEAP_DATA HEAP_top(MaxHeap *h) {
	return h->heap[0];
}

void printWordOccur(char* word, unsigned int occurence)
{
	//max len = 16 caractères
	int word_len = strlen(word);
	printf("%s", word);
	if (word_len < 8) printf("\t");
	if (word_len < 16) printf("\t");
	printf(": %i\n", occurence);
}

void HEAP_afficherDonnees(MaxHeap *h) {
    int previous_count = h->count;
	while (h->count != 1)
	{
		HEAP_DATA d = HEAP_top(h); HEAP_pop(h);
		printWordOccur(d.mot, d.compte);
	}
    h->count = previous_count;
}

void printInfo(unsigned int taille, double remplissage, unsigned int longueurMax, double execTime)
{
	printf("\n");
	printf("============== Infos ==============\n");
	printf("Taille de la table de hachage : %i\n", taille);
	printf("Facteur de remplissage : %f\n", remplissage);
	printf("Plus longue liste : %i\n", longueurMax);
	printf("Temps d'execution : %f\n", execTime);
	printf("===================================\n");
	printf("| %i | %f | %i | %f |\n", taille, remplissage, longueurMax, execTime);
	printf("\n");
}

// test du monceau
/*
int main() {
	const int heap_size = 100;
	MaxHeap h;
    HEAP_DATA data[100];
	for (int i = 0; i <= 100; ++i)
	{
		HEAP_DATA d;
		d.compte = rand() % 10000;
		d.mot = "mot";
		data[i] = d;
	}
	HEAP_construire(&h, data, heap_size);
	HEAP_afficherDonnees(&h);
	return 0;
}
*/

#define TABLE_SIZE 2027
int main(int argc, const char* argv[])
{
	// INPUT CHECK
	if (argc < 2)
	{
		printf("wrong usage,\n use : %s <input file>\n", argv[0]);
	}
	const char* filename = argv[1];

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file %s", filename);
		return 1;
	}

	// INIT
	char str[MAXCHAR];
	char *word;
	char delimiters[] = " \n,.';!:";
	char key[16];
	time_t start, end;

	// START MEASURING TIME
    start = clock();
	// - - - - - - - - - - /

	SplayTree* tree;
	ST_init(tree);

	// DATA GATHERING -> SPLAY TREE
	while (fgets(str, MAXCHAR, fp) != NULL)
	{
		//découpe en mots
		word = strtok(str, delimiters);
		while (word != NULL)
		{
			//===================/
            strcpy(key, word);
            ST_add(key, tree);
			//===================/

			//printf("'%s'\n", word);
			word = strtok(NULL, delimiters);
		}
	}
	fclose(fp);
	/*
    //analyseHashMap(Hmap);

	// HEAP-MAX
	MaxHeap h;
	//HEAP_initialiser(&h, Hmap->n);

    for(unsigned int i = 0; i < Hmap->size; i++)
	{
		if(Hmap->table[i] != NULL)
		{
			HASHMAP_DATA* list_ptr = Hmap->table[i];
			while(list_ptr != NULL)
			{
                HEAP_DATA d;
                d.compte = list_ptr->valeur;
                d.mot = list_ptr->cle;
                HEAP_inserer(&h, d);
				if(list_ptr->suivant != NULL) list_ptr = list_ptr->suivant;
				else break;
			}
		}
	}

	// DISPLAY WORD-OCCURENCE (most used first)
	HEAP_afficherDonnees(&h);

	// STOP MEASURING TIME
	end = clock();
	// - - - - - - - - - /

	printInfo(
		Hmap->size, //Taille
		Hmap->remplissage, //remplissage
		Hmap->max_length, // longueur max
		(double)(end - start) / CLOCKS_PER_SEC // Temps d'éxec
	);
	*/

	return 0;
}
