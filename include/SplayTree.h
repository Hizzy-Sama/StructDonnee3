#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct splaytree;

typedef struct donnee
{
	char* word;
	unsigned int occur;
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
Data* ST_access(char* word, SplayTree* tree); //nullable
void ST_split(char* word, SplayTree* tree, SplayTree* t1, SplayTree* t2);
void ST_insert(char* word, SplayTree* tree);
SplayTree* ST_join(SplayTree* t1, SplayTree* t2);
void ST_delete(char* word, SplayTree* tree);

Data* ST_rotateLeft(Data*);
Data* ST_rotateRight(Data*);
bool ST_isRightChild(Data*);
bool ST_isLeftChild(Data*);

Data* ST_newData();
SplayTree* ST_init(Data* root);

void parcoursProfondeur(SplayTree* tree, void(*operation)(Data*));
void operation1(Data* d);

#endif