#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
#include <string>

using namespace std;

struct node
{
    string value;
    node* pleft;
    node* pright;
    int counter =0;
};

class BinarySearchTree
{
    public:


        BinarySearchTree();
        virtual ~BinarySearchTree();


        //FUNCTIONS

        void insert(string);
        void inorder();
        void preorder();
        void postorder();



    protected:

    private:
        node * insert(node *,string);
        node* root = nullptr;

        void preorder(node *p);
        void inorder(node *p);
        void postorder(node *p);

};

#endif // BINARYSEARCHTREE_H
