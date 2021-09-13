#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTNodePtr insert_bst_node(BSTNodePtr self, int n)
{
    if (self == NULL)
    { /* found where to put it*/
        self = malloc(sizeof(*self));
        self->student_id = n;
        self->left = self->right = NULL;
    }
    else if (n < self->student_id)
    {
        self->left = insert_bst_node(self->left, n);
    }
    else if (n > self->student_id)
    {
        self->right = insert_bst_node(self->right, n);
    }
    return self;
}

void insert_bst(StudentBST *self, int n)
{
    self->root = insert_bst_node(self->root, n);
}

void print_in_order_bst_node(BSTNodePtr self)
{

    if (self != NULL)
    {
        printf("(");
        print_in_order_bst_node(self->left);
        printf(" %ld ", self->student_id);

        print_in_order_bst_node(self->right);
        printf(")");
    }
    else
    {
        printf("_");
    }
}
void print_in_order_bst(StudentBST *self)
{
    print_in_order_bst_node(self->root);
}

BSTNodePtr find_bst_node(BSTNodePtr self, int n)
{
    if (self == NULL || (n == self->student_id))
    {
        return self;
    }
    else if (n < self->student_id)
    {
        return find_bst_node(self->left, n);
    }
    else
    {
        return find_bst_node(self->right, n);
    }
}

BSTNodePtr find_bst(StudentBST *self, int n)
{
    return find_bst_node(self->root, n);
}

BSTNodePtr min_node(BSTNodePtr self)
{
    BSTNodePtr current = self;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}
BSTNodePtr delete_bst_node(BSTNodePtr self, int n)
{
    if (self != NULL)
    {
        if (n == self->student_id)
        { // found item
            if (self->left != NULL && self->right != NULL)
            {
                // two child case
                BSTNodePtr successor = min_node(self->right);
                self->student_id = successor->student_id;
                self->right = delete_bst_node(self->right, self->student_id);
            }
            else
            { // one or zero child case
                BSTNodePtr to_free = self;
                if (self->left)
                {
                    self = self->left;
                }
                else
                {
                    self = self->right;
                }
                free(to_free);
            }
        }
        else if (n < self->student_id)
        {
            self->left = delete_bst_node(self->left, n);
        }
        else
        {
            self->right = delete_bst_node(self->right, n);
        }
    }
    return self;
}

void delete_bst(StudentBST *self, int n)
{
    self->root = delete_bst_node(self->root, n);
}
StudentBST new_bst()
{
    StudentBST temp;
    temp.root = NULL;
    return temp;
}