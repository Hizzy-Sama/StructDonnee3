#include <SplayTree.h>

#include <stdio.h>
#define DEBUG false

void ST_splay(Data* x)
{
    //if(DEBUG) printf("---> ST_splay : %s\n", x->word);

    while(x != x->tree->root)
    {
        // Cas 1 : zig
        if(x->parent == x->tree->root)
        {
            ST_rotate(x);
            return;
        }
        else
        {
            // Cas 2 : zig-zig
            if((ST_isLeftChild(x) && ST_isLeftChild(x->parent))
                || (ST_isRightChild(x) && ST_isRightChild(x->parent)))
            {
                ST_rotate(x->parent);
                ST_rotate(x);
                continue;
            }
            // Cas 3 : zig-zag
            else if((ST_isLeftChild(x) && ST_isRightChild(x->parent))
                || (ST_isRightChild(x) && ST_isLeftChild(x->parent)))
            {
                ST_rotate(x);
                ST_rotate(x);
                continue;
            }
            else break;
        }
    }
}

Data* ST_access(char* word, SplayTree* tree)
{
    //if(DEBUG) printf("---> ST_access\n");
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
    }
    else
    {
        // should not happend
    }

    free(t2);
    return t1;
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

            t2->root = tree->root;
            t2->root->left_child = NULL;
        }
        else if(strcmp(word, tree->root->word) > 0)
        {
            t1->root = tree->root;
            t1->root->right_child = NULL;

            t2->root = tree->root->right_child;
        }
        else // (strcmp(word, tree->root->word) == 0)
        {
            // should not happend
        }
    }
}

void ST_insert(char* word, SplayTree* tree)
{
    if(DEBUG) printf("---> ST_insert\n");
    Data* entry = ST_access(word, tree);

    if(entry != NULL)
    {
        if(DEBUG) printf("---> ST_insert : ++\n");
        entry->occur++;
    }
    else
    {
        if(DEBUG) printf("---> ST_insert : new entry\n");
        SplayTree* t1 = ST_init(NULL);
        SplayTree* t2 = ST_init(NULL);
        ST_split(word, tree, t1, t2);

        Data* new_root = ST_newData(tree);
        new_root->word = malloc(sizeof(char[16]));
        strcpy(new_root->word, word);
        new_root->occur = 1;

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

        new_root->tree = tree;
        tree->root = new_root;
        tree->size++;

        free(t1);
        free(t2);
    }

    /*
    if(strcmp(word, "platform") != 0)
    {
        void (*op)(Data*) = &operation1;
        printf("\n");
        parcoursLargeur(tree, op);
        printf("\n");
    }
    */
}

void ST_delete(char* word, SplayTree* tree)
{
    if(DEBUG) printf("---> ST_delete\n");
    Data* entry = ST_access(word, tree);
    
    if(entry != NULL)
    {
        SplayTree* t1 = ST_init(entry->left_child);
        SplayTree* t2 = ST_init(entry->right_child);
        
        free(entry);
        tree->size--;
        
        ST_join(t1, t2);
    }
}

Data* ST_newData(SplayTree* tree)
{
    //if(DEBUG) printf("---> ST_newData\n");
    Data* data = malloc(sizeof(Data));
    data->word = "";
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

Data* ST_rotate(Data* x)
{
    if(ST_isLeftChild(x))
    {
        x = ST_rotateRight(x);
    }
    else if (ST_isRightChild(x))
    {
        x = ST_rotateLeft(x);
    }
    return x;
}

Data* ST_rotateLeft(Data* x)
{
    if(DEBUG) printf("---> ST_rotateLeft : %s\n", x->word);
    
    Data* y = x->parent;

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
    if(DEBUG) printf("---> ST_rotateRight : %s\n", x->word);
    
    Data* y = x->parent;

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

void pp(Data* d, void(*operation)(Data*));
void pp(Data* d, void(*operation)(Data*))
{
    (*operation)(d);
    if(d->left_child != NULL)
        pp(d->left_child, operation);
    if(d->right_child != NULL)
        pp(d->right_child, operation);
}

void parcoursProfondeur(SplayTree* tree, void(*operation)(Data*))
{
    pp(tree->root, operation);
}
