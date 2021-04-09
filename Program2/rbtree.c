#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

struct node* root = NULL;

struct node* bstInsert(struct node* trav, struct node* temp)
{
    if (trav == NULL)
        return temp;
  
    else
    {
	    if (temp->keyValue < trav->keyValue) 
	    {
	        trav->left = bstInsert(trav->left, temp);
	        trav->left->parent = trav;
	    }
	    else if (temp->keyValue > trav->keyValue) 
	    {
	        trav->right = bstInsert(trav->right, temp);
	        trav->right->parent = trav;
	    }
	  
	    return trav;
	}

}

void rightrotate(struct node* temp)
{
    struct node* newLeftNode=NULL;
	 newLeftNode = temp->left;
    temp->left = newLeftNode->right;
    if (temp->left)
        temp->left->parent = temp;
    newLeftNode->parent = temp->parent;
    if (!temp->parent)
        root = newLeftNode;
    else if (temp == temp->parent->left)
        temp->parent->left = newLeftNode;
    else
        temp->parent->right = newLeftNode;
    newLeftNode->right = temp;
    temp->parent = newLeftNode;
}

void leftrotate(struct node* temp)
{
    struct node* newLeftNode =NULL;
	 newLeftNode= temp->right;
    temp->right = newLeftNode->left;
    if (temp->right)
        temp->right->parent = temp;
    newLeftNode->parent = temp->parent;
    if (!temp->parent)
        root = newLeftNode;
    else if (temp == temp->parent->left)
        temp->parent->left = newLeftNode;
    else
        temp->parent->right = newLeftNode;
    newLeftNode->left = temp;
    temp->parent = newLeftNode;
}




