#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
#include <string>
#include <bits/stdc++.h>


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


        unsigned int get_number_of_nodes() const
        {
            return number_of_nodes;
        }


        void insert(string);

        int search(string);

        bool delete_node(string);

        void inorder();
        void preorder();
        void postorder();

        void printDebug();

        void MENU();






    protected:

    private:
        node* root = nullptr;

        unsigned int number_of_nodes; // Keeps the current number of nodes in the Tree


        node * insert(node *, string);

        node * search(node *, string);

        void printBT(const std::string& prefix, const node*, bool isLeft);
        void printBT(const node* );


        void search_Parent(node* p_node, string key_value);

        node* remove_one_child(node*);

        node* search_parent(string key);


        void debugInfo(node *p);
        void preorder(node *p);
        void inorder(node *p);
        void postorder(node *p);

        int size(node *);




};
void check_p_null_BTS(void * );
#endif // BINARYSEARCHTREE_H
