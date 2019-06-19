#ifndef SPLAYTREE_H
#define SPLAYTREE_H

typedef struct donnee
{
	char* cle;
	int valeur;
	struct donnee* suivant;
} Data;

typedef struct splaytree
{
    Data root;
    size_t size;
} SplayTree;

void ST_splay(Data* x);
Data* ST_access(char* cle, SplayTree* tree); //nullable
SplayTree* ST_joint(SplayTree* t1, SplayTree* t2);
void ST_split(char* cle, SplayTree* tree, SplayTree* t1, SplayTree* t2);
void ST_insert(char* cle, SplayTree* tree);
void ST_delete(char* cle, SplayTree* tree);

#endif