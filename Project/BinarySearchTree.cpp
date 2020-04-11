#include "BinarySearchTree.h"
/*
struct node
{
    int counter;
    int value;
    node* pleft;
    node* pright;
};
*/


BinarySearchTree::BinarySearchTree()        //Default Constructor
{
    root= nullptr;
}


BinarySearchTree::~BinarySearchTree()       //Default Destructor
{

}


void BinarySearchTree::insert(node* pnode, int a)
{


        if(pnode->value > a)
        {
            pnode->pright= new node;
            insert(pnode->pright, a);
        }

        else if(pnode->value < a)
        {
            pnode->pleft= new node;
            insert(pnode->pleft, a);
        }

        else
        {
            pnode->counter+=1;
        }



    }





void BinarySearchTree::insert(int a)
{
    if(root == nullptr)
    {
        root = new node;

        root->counter=1;
        root->pleft= nullptr;
        root->pright= nullptr;
        root->value= a;

    }

}






