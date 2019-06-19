#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdlib.h>
#include <stdbool.h>

struct splaytree;

typedef struct donnee
{
	char* word;
	int occur;
	struct donnee* right_child;
	struct donnee* left_child;
	struct donnee* parent;
    struct splaytree* tree;
} Data;

typedef struct splaytree
{
    Data* root;
    size_t size;
} SplayTree;

void ST_splay(Data* x);
Data* ST_access(char* cle, SplayTree* tree); //nullable
SplayTree* ST_joint(SplayTree* t1, SplayTree* t2);
void ST_split(char* cle, SplayTree* tree, SplayTree* t1, SplayTree* t2);
void ST_insert(char* cle, SplayTree* tree);
void ST_delete(char* cle, SplayTree* tree);

#endif