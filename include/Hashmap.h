#include <stdlib.h>
#include <string.h>
#include <tchar.h>

typedef struct donnee
{
	char* cle;
	int valeur;
	struct donnee* suivant;
} HASHMAP_DATA;

typedef struct hashMap
{
	unsigned size; // taille de la table de hachage
	unsigned n; // nombre d'élément
	unsigned max_length; // longueur maximale d'une liste chainée
	float remplissage; // n / size
	HASHMAP_DATA** table;
} HashMap;

HashMap* newHashMap(unsigned size);
unsigned int fonctionDeHashage(HashMap* hashMap, char* cle);
void HASHMAP_inserer(HashMap *map, char* cle, int valeur);
HASHMAP_DATA* HASHMAP_rechercher(HashMap* map, char* cle);
void analyseHashMap(HashMap* map);
