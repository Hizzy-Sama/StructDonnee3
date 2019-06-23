#include <SplayTree.h>

#include <stdio.h>
#define DEBUG true

void ST_splay(Data* x)
{
    //if(DEBUG) printf("---> ST_splay : %s\n", x->word);

    while(x != x->tree->root)
    {
        // Cas 1 : zig
        if(x->parent == x->tree->root)
        {
            if(ST_isLeftChild(x))
            {
                ST_rotateRight(x);
            }
            else if (ST_isRightChild(x))
            {
                ST_rotateLeft(x);
            }
            return;
        }
        else
        {
            // Cas 2 : zig-zig
            if(ST_isLeftChild(x) && ST_isLeftChild(x->parent))
            {
                ST_rotateRight(x->parent);
                ST_rotateRight(x);
                continue;
            }
            if(ST_isRightChild(x) && ST_isRightChild(x->parent))
            {
                ST_rotateLeft(x->parent);
                ST_rotateLeft(x);
                continue;
            }
            // Cas 3 : zig-zag
            else if(ST_isLeftChild(x) && ST_isRightChild(x->parent))
            {
                ST_rotateRight(x);
                ST_rotateLeft(x);
                continue;
            }
            if(ST_isRightChild(x) && ST_isLeftChild(x->parent))
            {
                ST_rotateLeft(x);
                ST_rotateRight(x);
                continue;
            }
            else break;
        }
    }
}

Data* ST_access(char* word, SplayTree* tree)
{
    //if(DEBUG) printf("---> ST_access : %s\n", word);
    Data* x = tree->root;
    if(x == NULL) return NULL;
    
    int cmp = -1;
    while (cmp != 0)
    {
        cmp = strcmp(word, x->word);
        if(cmp < 0)
        {
            if(x->left_child != NULL)
            {
                x = x->left_child;
            }
            else
            {
                ST_splay(x);
                return NULL;
            }
        }
        if(cmp > 0)
        {
            if(x->right_child != NULL)
            {
                x = x->right_child;
            }
            else
            {
                ST_splay(x);
                return NULL;
            }
        }
    }
    
    ST_splay(x);
    return x;
}

void ST_split(char* word, SplayTree* tree, SplayTree* t1, SplayTree* t2)
{
    //if(DEBUG) printf("---> ST_split : %s\n", word);
    
    // Sort the tree
    ST_access(word, tree);

    if(tree->root != NULL)
    {
        // Split
        if(strcmp(word, tree->root->word) < 0)
        {
            t1->root = tree->root->left_child;
            if(t1->root != NULL) t1->root->parent = NULL;

            t2->root = tree->root;
            if(t2->root != NULL) t2->root->left_child = NULL;
            //if(DEBUG) printf("---> ST_split : t2 = root\n");
        }
        else if(strcmp(word, tree->root->word) > 0)
        {
            t2->root = tree->root->right_child;
            if(t2->root != NULL) t2->root->parent = NULL;

            t1->root = tree->root;
            if(t1->root != NULL) t1->root->right_child = NULL;
            //if(DEBUG) printf("---> ST_split : t1 = root\n");
        }
        else // (strcmp(word, tree->root->word) == 0)
        {
            // nothing : the entry already exists
        }
    }
}

void ST_insert(char* word, SplayTree* tree)
{
    //if(DEBUG) printf("---> ST_insert : %s\n", word);
    SplayTree* t1 = ST_init(NULL);
    SplayTree* t2 = ST_init(NULL);   
    ST_split(word, tree, t1, t2);

    if(tree->root != NULL)
    {
        if(strcmp(word, tree->root->word) == 0)
        {
            tree->root->occur++;
            //if(DEBUG) printf("--->\t%s : %d\n", tree->root->word, tree->root->occur);
            
            free(t1);
            free(t2);
            return;
        }
    }
    
    // New root
    Data* new_root = ST_newData(tree);
    strcpy(new_root->word, word);
    new_root->occur = 1;

    // Children
    new_root->left_child = t1->root;
    if(new_root->left_child != NULL)
    {
        new_root->left_child->parent = new_root;
    }
    new_root->right_child = t2->root;
    if(new_root->right_child != NULL)
    {
        new_root->right_child->parent = new_root;
    }

    // Link with the tree
    new_root->parent = NULL;
    new_root->tree = tree;
    tree->root = new_root;
    tree->size++;

    //if(DEBUG) printf("--->\tnew entry\n");
    free(t1);
    free(t2);
}

SplayTree* ST_join(SplayTree* t1, SplayTree* t2)
{
    //if(DEBUG) printf("---> ST_join\n");
    
    // Sort t1
    Data* ptr = t1->root;
    while(ptr->right_child != NULL) ptr = ptr->right_child;
    ST_splay(ptr);

    // Join
    if(t1->root->right_child == NULL)
    {
        t1->root->right_child = t2->root;
        t2->root->parent = t1->root;

        t1->root->parent = NULL;
    }
    else
    {
        // should not happend
    }

    free(t2);
    return t1;
}

void ST_delete(char* word, SplayTree* tree)
{
    //if(DEBUG) printf("---> ST_delete\n");
    Data* entry = ST_access(word, tree);
    
    if(entry != NULL)
    {
        SplayTree* t1 = ST_init(entry->left_child);
        SplayTree* t2 = ST_init(entry->right_child);
        
        free(entry);
        tree->size--;
        
        ST_join(t1, t2);

        tree->root = t1->root;
    }
}

Data* ST_rotateLeft(Data* x)
{    
    Data* y = x->parent;
    //if(DEBUG) printf("---> ST_rotateLeft : x = %s, y = %s\n", x->word, y->word);

    // child swap
    if(x->left_child != NULL)
    {
        x->left_child->parent = y;
        y->right_child = x->left_child;
    }
    else y->right_child = NULL;

    // parent swap
    x->parent = y->parent;
    if(y == x->tree->root)
    {
        x->tree->root = x;
        x->parent = NULL;
    }
    else if(ST_isLeftChild(y))
    {
        y->parent->left_child = x;
    }
    else if(ST_isRightChild(y))
    {
        y->parent->right_child = x;
    }

    x->left_child = y;
    y->parent = x;

    return x;
}

Data* ST_rotateRight(Data* x)
{
    Data* y = x->parent;
    //if(DEBUG) printf("---> ST_rotateRight : x = %s, y = %s\n", x->word, y->word);

    // child swap
    if(x->right_child != NULL)
    {
        x->right_child->parent = y;
        y->left_child = x->right_child;
    }
    else y->left_child = NULL;

    // parent swap
    x->parent = y->parent;
    if(y == x->tree->root)
    {
        x->tree->root = x;
        x->parent = NULL;
    }
    else if(ST_isLeftChild(y))
    {
        y->parent->left_child = x;
    }
    else if(ST_isRightChild(y))
    {
        y->parent->right_child = x;
    }

    x->right_child = y;
    y->parent = x;

    return x;
}

bool ST_isRightChild(Data* d)
{
    if(d->parent == NULL) return false;
    if(d->parent->right_child == NULL) return false;
    return (d == d->parent->right_child);
}

bool ST_isLeftChild(Data* d)
{
    if(d->parent == NULL) return false;
    if(d->parent->left_child == NULL) return false;
    return (d == d->parent->left_child);
}

Data* ST_newData(SplayTree* tree)
{
    //if(DEBUG) printf("---> ST_newData\n");
    Data* data = malloc(sizeof(Data));
    data->word = malloc(sizeof(char[16]));
    data->occur = 0;
    data->left_child = NULL;
    data->right_child = NULL;
    data->parent = NULL;
    data->tree = tree;

    return data;
}

SplayTree* ST_init(Data* root)
{
    //if(DEBUG) printf("---> ST_init\n");
    SplayTree* tree = malloc(sizeof(SplayTree));
    tree->root = root;
    tree->size = (root == NULL) ? 0 : 1;
    return tree;
}

void pp(Data* d, void(*operation)(Data*));
void pp(Data* d, void(*operation)(Data*))
{
    if(d->left_child != NULL)
        pp(d->left_child, operation);
    (*operation)(d);
    if(d->right_child != NULL)
        pp(d->right_child, operation);
}

void parcoursProfondeur(SplayTree* tree, void(*operation)(Data*))
{
    pp(tree->root, operation);
}

void operation1(Data* d)
{
	if(ST_isRightChild(d)) printf("(%s)\\", (d->parent == NULL) ? "null" : d->parent->word);

    printf(" %s ", d->word);
	
	if(ST_isLeftChild(d)) printf("/(%s)", (d->parent == NULL) ? "null" : d->parent->word);
}