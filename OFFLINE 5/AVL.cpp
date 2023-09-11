#include<bits/stdc++.h>
using namespace std;

class node
{
public:
    class node* right;
    class node* left;
    int data;
    int height;

};
int height(node * key)
{
    if(key==NULL) return 0;
    return key->height;
}
 node* createNode(int key)
    {

        node *ptr;
        ptr=new node;
        ptr->data=key;
        ptr->left=NULL;
        ptr->right=NULL;
        ptr->height=1;
        return ptr;
    }
node* rightRotate(node * x)
{
    node* leftChild=x->left;
    node* leftrightChild=leftChild->right;

    leftChild->right=x;
    x->left=leftrightChild;
    x->height=max(height(x->left),height(x->right))+1;
    leftChild->height=max(height(leftChild->left),height(leftChild->right))+1;
    return leftChild;
}
node* leftRotate(node *x)
{
    node* rightChild=x->right;
    node* rightleftchild=rightChild->left;
    rightChild->left=x;
    x->right=rightleftchild;

    x->height=max(height(x->left),height(x->right))+1;
    rightChild->height=max(height(rightChild->left),height(rightChild->right))+1;
    return rightChild;
}
int balanceFactor(node *x)
{
    if(x==NULL) return 0;
    return (height(x->left)-height(x->right));
}
node* inorderPredecessor(node *ptr)
    {
        ptr=ptr->left;
        while(ptr->right!=NULL) ptr=ptr->right;
        return ptr;
    }
node* insert(node* cur, int data) {
    if (cur == NULL) return createNode(data);
    
    if (data < cur->data) {
        cur->left = insert(cur->left, data);
    } else if (data > cur->data) {
        cur->right = insert(cur->right, data);
    } else {
        // Data already exists in the tree (avoid duplicates).
        return cur;
    }

    // Update the height of the current node.
    cur->height = 1 + max(height(cur->left), height(cur->right));
    
    int b = balanceFactor(cur);

    if (b > 1 && data < cur->left->data) {
        return rightRotate(cur);
    }

    if (b < -1 && data > cur->right->data) {
        return leftRotate(cur);
    }

    if (b > 1 && data > cur->left->data) {
        cur->left = leftRotate(cur->left);
        return rightRotate(cur);
    }

    if (b < -1 && data < cur->right->data) {
        cur->right = rightRotate(cur->right);
        return leftRotate(cur);
    }

    return cur;
}
node *inorderSuccessor(node *ptr)
{
    ptr = ptr->right;
    while (ptr->left != NULL)
        ptr = ptr->left;
    return ptr;
}

node* deleteNode(node* root,int data)
{

    if(root->data>data) 
    {
        root->left=deleteNode(root->left,data);
    }
    else if(root->data<data)
    
    {
        root->right=deleteNode(root->right,data);
    }
    else
    {
        node* temp;
        if(root->left==NULL)
        {
            temp=root->right;
            delete root;
             *root=*temp;
        }
       else if (root->right == NULL)
        {
            temp = root->left;
            delete root;
             *root=*temp;
        }
       
        else 
        {
                node* temp=inorderSuccessor(root);
    root->data=temp->data;
    root->right=deleteNode(root->right,temp->data);
        }
    }
        if(root==NULL) return root;

    root->height=1+max(height(root->left),height(root->right));
    int b=balanceFactor(root);
    if(b>1 && balanceFactor(root->left)>=0)
    {
        return rightRotate(root);
    }
    if(b>1 && balanceFactor(root->left)<0)
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }
      if (b < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (b < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;

}
void preOrder(node *root)
{
    if (root != NULL)
    {
            preOrder(root->left);
        cout << root->data << " ";

        preOrder(root->right);
    }
}
int main()
{
node *root = NULL;
 
    /* Constructing tree given in
    the above figure */
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 8);
    root = insert(root, 1);
    root = insert(root, 3);

    root = insert(root, 10);
 
    /* The constructed AVL Tree would be
            9
        / \
        1 10
        / \ \
    0 5 11
    / / \
    -1 2 6
    */
 
    cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    preOrder(root);
 
    root = deleteNode(root, 4);
 
    /* The AVL Tree after deletion of 10
            1
        / \
        0 9
        / / \
    -1 5     11
        / \
        2 6
    */
 
    cout << "\nPreorder traversal after"
         << " deletion of 10 \n";
    preOrder(root);
 
    return 0;
}