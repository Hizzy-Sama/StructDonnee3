#include <SplayTree.h>

Data* ST_newData()
{
    Data* data = malloc(sizeof(Data));
    data->word = "";
    data->occur=0;
    data->left_child = NULL;
    data->right_child = NULL;
    data->parent = NULL;
    data->tree = NULL;
}

SplayTree* ST_init(Data* root)
{
    SplayTree* tree = malloc(sizeof(SplayTree));
    tree->root = root;
    return tree;
}

void ST_rotate(Data* x, Data* y)
{
    if(y == x->right_child)
    {
        ST_rotateLeft(x, y);
    }
    if(y == x->left_child)
    {
        ST_rotateRight(x, y);
    }
    if(x == y->right_child)
    {
        ST_rotateLeft(y, x);
    }
    if(x == y->left_child)
    {
        ST_rotateRight(y, x);
    }
}

void ST_rotateLeft(Data* x, Data* y)
{
    x->right_child = y->left_child;
    if(y->left_child != NULL)
    {
        y->left_child->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL)
    {
        x->tree->root = y;
    }
    else if(ST_isLeftChild(x))
    {
        x->parent->left_child = y;
    }
    else
    {
        x->parent->right_child = y;
    }
    y->left_child = x;
    x->parent = y;
}
void ST_rotateRight(Data* x, Data* y)
{
    x->left_child = y->right_child;
    if(y->right_child != NULL)
    {
        y->right_child->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL)
    {
        x->tree->root = y;
    }
    else if(ST_isRightChild(x))
    {
        x->parent->right_child = y;
    }
    else
    {
        x->parent->left_child = y;
    }
    y->right_child = x;
    x->parent = y;
}

bool ST_isRightChild(Data* d)
{
    return (d == d->parent->right_child);
}
bool ST_isLeftChild(Data* d)
{
    return (d == d->parent->left_child);
}

void ST_splay(Data* x)
{
    while(x != x->tree->root)
    {
        // Cas 1 : zig
        if(x->parent == x->tree->root)
        {
            ST_rotate(x, x->parent);
            return;
        }
        else
        {
            // Cas 2 : zig-zig
            if((ST_isLeftChild(x) && ST_isLeftChild(x->parent))
                || (ST_isRightChild(x) && ST_isRightChild(x->parent)))
            {
                ST_rotate(x->parent, x->parent->parent);
                ST_rotate(x, x->parent);
                continue;
            }
            // Cas 3 : zig-zag
            if((ST_isLeftChild(x) && ST_isRightChild(x->parent))
                || (ST_isRightChild(x) && ST_isLeftChild(x->parent)))
            {
                ST_rotate(x, x->parent);
                ST_rotate(x, x->parent);
                continue;
            }
        }
    }
}

Data* ST_access(char* word, SplayTree* tree)
{
    return NULL;
}

SplayTree* ST_join(SplayTree* t1, SplayTree* t2)
{
    // Sort t1
    Data* ptr = t1->root;
    while(ptr->right_child != NULL) ptr = ptr->right_child;
    splay(ptr);

    // Join
    if(t1->root->right_child = NULL)
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
    // Sort the tree
    ST_access(word, tree);

    // Split
    if(strcmp(word, tree->root->word) == 0)
    {
        // should not happend
    }
    if(strcmp(word, tree->root->word) < 0)
    {
        t1 = ST_init(tree->root->left_child);
        t2 = ST_init(tree->root);
    }
    if(strcmp(word, tree->root->word) > 0)
    {
        t1 = ST_init(tree->root);
        t2 = ST_init(tree->root->right_child);
    }
}

void ST_insert(char* word, SplayTree* tree)
{
    SplayTree* t1;
    SplayTree* t2;
    split(word, tree, t1, t2);

    Data* root = ST_newData();
    root->word = word;
    root->occur = 1;

    root->left_child = t1->root;
    root->right_child = t2->root;

    free(t1);
    free(t2);
}

void ST_delete(char* word, SplayTree* tree)
{
    Data* root = ST_access(word, tree);
    
    SplayTree* t1 = ST_init(root->left_child);
    SplayTree* t2 = ST_init(root->right_child);
    
    free(root);
    
    join(t1, t2);
}