#include <SplayTree.h>

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

SplayTree* ST_joint(SplayTree* t1, SplayTree* t2)
{
    return NULL;
}

void ST_split(char* word, SplayTree* tree, SplayTree* t1, SplayTree* t2)
{
}

void ST_insert(char* word, SplayTree* tree)
{
}

void ST_delete(char* word, SplayTree* tree)
{
    ST_access(word, tree)
}