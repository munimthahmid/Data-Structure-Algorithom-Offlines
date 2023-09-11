#include<bits/stdc++.h>
#include <fstream>
#include<vector>
#include<stack>
using namespace std;
class node
{
public:
    int data;
    class node *left;
    class node *right;

};

class Tree
{
public:
    node *root;

    Tree()
    {
        root=new node;
        root=NULL;
    }
    node* createNode(int key)
    {

        node *ptr;
        ptr=new node;
        ptr->data=key;
        ptr->left=NULL;
        ptr->right=NULL;
        return ptr;
    }
    void insert(int key)
    {
        node *cur=root;
        node *parent=new node;
        parent=NULL;
        node *ptr=createNode(key);
        while(cur!=NULL)
        {
            parent=cur;
            if(cur->data==key)
            {
                cout<<key<<" is already in BST"<<endl;
                return;
            }
            else if(key>cur->data)
            {
                cur=cur->right;
            }
            else cur=cur->left;
        }
        if(parent==NULL)
        {
            root=ptr;
        }
        else
        {
            if(key>parent->data)
            {
                parent->right=ptr;
            }
            else parent->left=ptr;
        }

    }
    bool find(int key)
    {
        node *cur=root;
        while(cur!=NULL)
        {
            if(cur==NULL) return false;
            else if(cur->data==key) return true;
            else if(cur->data>key) cur=cur->left;
            else cur=cur->right;
        }
        return false;

    }
    node* inorderPredecessor(node *ptr)
    {
        ptr=ptr->left;
        while(ptr->right!=NULL) ptr=ptr->right;
        return ptr;
    }
    void deleteNode(int key)
    {
      node *cur=root;
      while(cur!=NULL)
      {
        if(key<cur->data)
        {
            cur=cur->left;
        }
        else if(key>cur->data)
        {
            cur=cur->right;
        }
        else if(key==cur->data)
        {
            delete cur;
            cur=NULL;
        }
      }
    }
    node *inOrder_Predecessor(node *root)
{
    root = root->left;
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
    node* deleting(node *cur, int key)
{
    if(cur==NULL) return NULL;
     if(cur->data==key)
    {
       if(cur->left==NULL && cur->right==NULL)
       {
        delete cur;
        cur=NULL;
        return cur;

       }

    }
    if(cur->data>key) cur->left=deleting(cur->left,key);
    else if(cur->data<key) cur->right=deleting(cur->right,key);

    return cur;
}
    void printTree(node *cur,string &s)
    {
        if(cur==NULL) return;
        s.append(to_string(cur->data));
        if(cur->left==NULL && cur->right==NULL) return;
        s.push_back('(');
        printTree(cur->left,s);
        s.push_back(')');

            s.push_back('(');
            printTree(cur->right,s);
            s.push_back(')');



    }
    vector<int> preorder()
    {
        stack<node*>s;
        vector<int>ans;
        node *cur=root;
        s.push(cur);
        while(!s.empty())
        {
            cur=s.top();
            s.pop();
            ans.push_back(cur->data);
            if(cur->right!=NULL) s.push(cur->right);
            if(cur->left!=NULL) s.push(cur->left);
//            cout<<"stack front"<<s.top()->data<<endl;


        }
        return ans;
    }
    void inorder(node *cur,string &s)
{
    if(cur==NULL) return;
    inorder(cur->left,s);
    s.append(to_string(cur->data));
    s.push_back(' ');
    inorder(cur->right,s);
}
    void postorder(node *cur,string &s)
{
    if(cur==NULL) return;
    postorder(cur->left,s);
    postorder(cur->right,s);
    s.append(to_string(cur->data));
    s.push_back(' ');


}
};
int main()
{
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    Tree t;
    while(!in.eof())
    {
        if(in.eof()) break;
        char op;
        string data;
        in>>op>>data;

        if(op=='I')
        {
            int d=stoi(data);

            t.insert(d);
//            cout<<"2nd el: "<<t.root->right->data<<endl;
            vector<int>temp=t.preorder();
            string s="";
            node *tempp=t.root;
            t.printTree(tempp,s);
            out<<s<<endl;
        }
        else if(op=='F')
        {
            int d=stoi(data);
            bool check=t.find(d);
            if(check) out<<"True"<<endl;
            else out<<"False"<<endl;
        }
        else if(op=='T')
        {
            if(data=="Pre")
            {
                vector<int>temp=t.preorder();
                for(int i=0;i<temp.size();i++)
                {
                    out<<temp[i]<<" ";
                }
                out<<endl;
            }
            else if(data=="In")
            {
                string s="";
                node *ptr=t.root;
                t.inorder(ptr,s);
                out<<s<<endl;
            }
            else if(data=="Post")
            {

                string s="";
                node *ptr=t.root;
                t.postorder(ptr,s);
                out<<s<<endl;
            }
        }
        else if(op=='D')
        {
            int d=stoi(data);
            node *temp;
            t.deleting(t.root,d);
            if(t.find(d)) out<<"Invalid Operation"<<endl;
            else
            {
            string s="";
            node *tempp=t.root;
            t.printTree(tempp,s);
            out<<s<<endl;

            }








        }

    }


















    in.close();
    out.close();
}
