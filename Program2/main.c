#include <stdio.h>
#include <stdlib.h>


struct node {
    int keyValue; // data
    int c; // 1 red, 0 black
    struct node* parent; // parent
    struct node* right; // right child
    struct node* left; // left child
};


struct node* baseRoot = NULL;

struct node* creatNode(int keyValue)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->keyValue = keyValue;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->c = 1;
}
struct node* bstInsert(struct node* tree, struct node* inputNode)
{

    if (!tree)
        return inputNode;

    if (tree->keyValue > inputNode->keyValue)
    {
        tree->left = bstInsert(tree->left, inputNode);
        tree->left->parent = tree;
    }
    else if (tree->keyValue < inputNode->keyValue)
    {
        tree->right = bstInsert(tree->right, inputNode);
        tree->right->parent = tree;
    }
    else
    {
        tree->right = bstInsert(tree->right, inputNode);
        tree->right->parent = tree;	
	}

    return tree;
}


void rightrotate(struct node* inputTree)
{
    struct node* left = inputTree->left;
    inputTree->left = left->right;
    if (inputTree->left)
    {
        inputTree->left->parent = inputTree;
    }
    left->parent = inputTree->parent;
    if (!inputTree->parent)
    {
        baseRoot = left;
    }
    else if (inputTree == inputTree->parent->left)
    {
        inputTree->parent->left = left;
    }
    else
    {
        inputTree->parent->right = left;
    }
    left->right = inputTree;
    inputTree->parent = left;
}


void leftrotate(struct node* inputTree)
{
    struct node* right = inputTree->right;
    inputTree->right = right->left;
    if (inputTree->right)
    {
        inputTree->right->parent = inputTree;
    }
    right->parent = inputTree->parent;
    if (!inputTree->parent)
    {
        baseRoot = right;
    }
    else if (inputTree == inputTree->parent->left)
    {
        inputTree->parent->left = right;
    }
    else
    {
        inputTree->parent->right = right;
    }
    right->left = inputTree;
    inputTree->parent = right;
}


void fixup(struct node* rootNode, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;

    while ((pt != rootNode) && (pt->c != 0) && (pt->parent->c == 1))
    {
        grand_parent_pt = pt->parent->parent;
        parent_pt = pt->parent;
        if (grand_parent_pt->left == parent_pt)
        {
            struct node* uncle_pt = grand_parent_pt->right;

            if (uncle_pt != NULL && uncle_pt->c == 1)
            {
                uncle_pt->c = 0;
                grand_parent_pt->c = 1;
                parent_pt->c = 0;

                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->right)
                {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                rightrotate(grand_parent_pt);
                int temp1 = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = temp1;
                pt = parent_pt;
            }
        }
        else {
            struct node* uncle_pt = NULL;
            uncle_pt = grand_parent_pt->left;
            if ((uncle_pt != NULL) && (uncle_pt->c == 1))
            {
                uncle_pt->c = 0;
                parent_pt->c = 0;
                grand_parent_pt->c = 1;

                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->left)
                {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                leftrotate(grand_parent_pt);
                int temp2 = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = temp2;
                pt = parent_pt;
            }
        }
    }
    rootNode->c = 0;
}


void inorder(struct node* inputNode)
{
    if (inputNode == NULL)
        return;

    inorder(inputNode->left);
    printf("%d ", inputNode->keyValue);
    inorder(inputNode->right);
}

int main()
{
    int n = 0,j = 0;
    int* arr1;
    printf("please input the number divide by space, end with enter, eg: 1 2 3 ...\n");
    arr1 = malloc(n * sizeof(int));
    do
    {
        scanf("%d", &arr1[j++]);
        realloc(arr1, ++n * sizeof(int));

    } while (getchar() != '\n');

    for (int i = 0; i < n; i++) {

        struct node* temp = creatNode(arr1[i]);
        baseRoot = bstInsert(baseRoot, temp);
        fixup(baseRoot, temp);
    }

    printf("the in-order traversal is :");
    inorder(baseRoot);

    return 0;
}
