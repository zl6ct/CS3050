typedef struct  {
    int keyValue; 
    int c; // 1 for red, 0 for black
    struct node* parent; // parent
    struct node* right; // right-child
    struct node* left; // left child
}RBnode;

struct node* bstInsert(struct node* trav,struct  node* temp);
void rightrotate(struct node* temp);
void leftrotate(struct node* temp);
void fixup(struct node* root,struct  node* pt);
void inorder(struct node* trav);
