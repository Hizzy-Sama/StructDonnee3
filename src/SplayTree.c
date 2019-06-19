#include <SplayTree.h>



bool isRightChild(Data*);
bool isRightChild(Data* d)
{
    return (d == d->parent->right_child);
}
bool isLeftChild(Data*);
bool isLeftChild(Data* d)
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

Data* ST_access(char* cle, SplayTree* tree)
{
    return NULL;
}

SplayTree* ST_joint(SplayTree* t1, SplayTree* t2)
{
    return NULL;
}

void ST_split(char* cle, SplayTree* tree, SplayTree* t1, SplayTree* t2)
{
}

void ST_insert(char* cle, SplayTree* tree)
{
}

void ST_delete(char* cle, SplayTree* tree)
{
}