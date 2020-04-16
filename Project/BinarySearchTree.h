#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
#include <string>

#include <cstdlib>
#include <unistd.h>
#include <windows.h>
using namespace std;

struct node
{
    int value;
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

        void insert(int);

        int search(int);

        bool delete_node(int);

        void inorder();
        void preorder();
        void postorder();

        void printDebug();

        void MENU();






    protected:

    private:
        node* root = nullptr;


        node * insert(node *, int);

        node * search(node *, int);




        void search_Parent(node* p_node, int key_value);

        node* remove_one_child(node*);

        node* search_parent(int key);


        void debugInfo(node *p);
        void preorder(node *p);
        void inorder(node *p);
        void postorder(node *p);




};

void check_if_pointer_is_null(void *);
#endif // BINARYSEARCHTREE_H
