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

        bool delete_node(string);

        void inorder();
        void preorder();
        void postorder();

        void printDebug();






    protected:

    private:
        node* root = nullptr;


        node * insert(node *, string);

        node * search(node *, string);

        node * delete_node(node *, string);

        node* remove_one_child(node*);




        void debugInfo(node *p);
        void preorder(node *p);
        void inorder(node *p);
        void postorder(node *p);




};

#endif // BINARYSEARCHTREE_H
