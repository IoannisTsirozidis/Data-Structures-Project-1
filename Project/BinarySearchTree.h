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

        int search(string);

        void inorder();
        void preorder();
        void postorder();

        void printDebug();






    protected:

    private:
        node* root = nullptr;


        node * insert(node *, string);

        node * search(node *, string);



        void debugInfo(node *p);
        void preorder(node *p);
        void inorder(node *p);
        void postorder(node *p);




};

#endif // BINARYSEARCHTREE_H
