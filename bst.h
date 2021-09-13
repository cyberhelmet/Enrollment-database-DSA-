#ifndef BST_H
#define BST_H
#include "list.h"
#include <string.h>
typedef struct bstNode
{
    long student_id;
    UnitList units;
    struct bstNode *left;
    struct bstNode *right;
} * BSTNodePtr;

typedef struct bst
{
    BSTNodePtr root;
} StudentBST;

StudentBST new_bst();
void insert_bst(StudentBST *, int);
BSTNodePtr find_bst(StudentBST *, int);
void print_in_order_bst(StudentBST *);
void delete_bst(StudentBST *, int);

#endif