#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    class node *right;
    class node *left;
    int data;
    int height;
};
int height(node *key)
{
    if (key == NULL)
        return 0;
    return key->height;
}
node *createNode(int key)
{

    node *ptr;
    ptr = new node;
    ptr->data = key;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->height = 1;
    return ptr;
}
node *rightRotate(node *x)
{
    node *leftChild = x->left;
    node *leftrightChild = leftChild->right;

    leftChild->right = x;
    x->left = leftrightChild;
    x->height = max(height(x->left), height(x->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
    return leftChild;
}
node *leftRotate(node *x)
{
    node *rightChild = x->right;
    node *rightleftchild = rightChild->left;
    rightChild->left = x;
    x->right = rightleftchild;

    x->height = max(height(x->left), height(x->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
    return rightChild;
}
int balanceFactor(node *x)
{
    if (x == NULL)
        return 0;
    return (height(x->left) - height(x->right));
}
node *inorderPredecessor(node *ptr)
{
    ptr = ptr->left;
    while (ptr->right != NULL)
        ptr = ptr->right;
    return ptr;
}
node *inorderSuccessor(node *ptr)
{
    ptr = ptr->right;
    while (ptr->left != NULL)
        ptr = ptr->left;
    return ptr;
}
node *insert(node *cur, int data)
{
    if (cur == NULL)
        return createNode(data);

    if (data < cur->data)
    {
        cur->left = insert(cur->left, data);
    }
    else if (data > cur->data)
    {
        cur->right = insert(cur->right, data);
    }
    else
    {
        return cur;
    }

    cur->height = 1 + max(height(cur->left), height(cur->right));

    int b = balanceFactor(cur);

    if (b > 1 && data < cur->left->data)
    {
        return rightRotate(cur);
    }

    if (b < -1 && data > cur->right->data)
    {
        return leftRotate(cur);
    }

    if (b > 1 && data > cur->left->data)
    {
        cur->left = leftRotate(cur->left);
        return rightRotate(cur);
    }

    if (b < -1 && data < cur->right->data)
    {
        cur->right = rightRotate(cur->right);
        return leftRotate(cur);
    }

    return cur;
}

node *deleteNode(node *root, int data)
{
    if (root == NULL)
        return root;
    if (root->data > data)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (root->data < data)

    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        node *temp;
        if (root->left == NULL || root->right == NULL)
        {
            if (root->left == NULL)
            {
                temp = root->right;
            }
            else if (root->right == NULL)
            {
                temp = root->left;
            }
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete temp;
        }

        else
        {
            node *temp = inorderSuccessor(root);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int b = balanceFactor(root);
    if (b > 1 && balanceFactor(root->left) >= 0)
    {
        return rightRotate(root);
    }
    if (b > 1 && balanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (b < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (b < -1 && balanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

bool find(int key, node *root)
{
    node *cur = root;
    while (cur != NULL)
    {
        if (cur == NULL)
            return false;
        else if (cur->data == key)
            return true;
        else if (cur->data > key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return false;
}
void inorder(node *ptr, ofstream &out)
{

    if (ptr != NULL)
    {
        inorder(ptr->left, out);
        out << ptr->data << " ";
        inorder(ptr->right, out);
    }
}
void printTree(node *cur, string &s)
{
    if (cur == NULL)
        return;
    s.append(to_string(cur->data));
    if (cur->left == NULL && cur->right == NULL)
        return;
    s.push_back('(');
    if (cur->left != NULL)
        printTree(cur->left, s);
    s.push_back(',');

    if (cur->right != NULL)
        printTree(cur->right, s);
    else
        s.push_back(',');
    s.push_back(')');
}
int main()
{
    ifstream in;
    ofstream out;
    ofstream out2;
    string currentFilePath = __FILE__;

    size_t found = currentFilePath.find_last_of("/\\");
    string currentDirectory = currentFilePath.substr(0, found);

    string inputFilePath = currentDirectory + "/input.txt";
    string outputFilePath = currentDirectory + "/out_avl.txt";
    string reportFilePath = currentDirectory + "/report_avl.txt";

    in.open(inputFilePath);
    out.open(outputFilePath);
    char c;
    double insertTime = 0;
    double deleteTime = 0;
    double searchTime = 0;
    double travTime = 0;
    node *root = NULL;
    while (in >> c)
    {
        if (c != 'T')
        {
            int a;
            in >> a;
            if (c == 'F')
            {
                node *ptr = root;
                auto start_time = chrono::steady_clock::now();
                bool found = find(a, ptr);
                auto end_time = chrono::steady_clock::now();
                double t = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
                searchTime += t / 1000000.00;

                if (found)
                    out << "found" << endl;
                else
                    out << "not found" << endl;
            }
            else if (c == 'I')
            {
                auto start_time = chrono::steady_clock::now();
                root = insert(root, a);
                auto end_time = chrono::steady_clock::now();
                double t = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
                insertTime += t / 1000000.00;
                string s;
                node *ptr = root;
                printTree(ptr, s);
                out << s << endl;
            }
            else if (c == 'D')
            {
                auto start_time = chrono::steady_clock::now();
                root = deleteNode(root, a);
                auto end_time = chrono::steady_clock::now();
                double t = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
                deleteTime += t / 1000000.00;
                string s;
                node *ptr = root;
                printTree(ptr, s);
                out << s << endl;
            }
        }
        else
        {
            vector<int> nodes;
            node *ptr = root;
            auto start_time = chrono::steady_clock::now();
            inorder(ptr, out);
            auto end_time = chrono::steady_clock::now();
            double t = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
            travTime += t / 1000000.00;
        }
    }

    double totalTime = travTime + insertTime + searchTime + deleteTime;
    in.close();
    out.close();
    out2 << fixed << setprecision(6);
    out2.open(reportFilePath);
    out2 << "operation time(ms) " << endl;
    out2 << "insert " << insertTime << endl;
    out2 << "search " << searchTime << endl;
    out2 << "delete " << deleteTime << endl;
    out2 << "trav " << travTime << endl;
    out2 << "total " << totalTime << endl;
    out2.close();

    return 0;
}