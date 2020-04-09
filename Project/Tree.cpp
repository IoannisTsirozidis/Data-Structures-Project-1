#include "Tree.h"
#include <iostream>
using namespace std;
Tree::Tree()
{
    //ctor
    this->root = NULL;
}

Tree::~Tree()
{
    //dtor
}

void Tree::add(int a)
{
    if (root == NULL)
    {
        root = new node;
        root->value = a;
        root->pleft = NULL;
        root->pright = NULL;
    }
    else
        if (root->value < a)
            add(a,root->pright);
        if (root->value > a)
            add(a,root->pleft);


}

void Tree::InOrder()
{
    inorder(root);
}

void Tree::inorder(node *p)
{
    if (p == NULL)
        return;
    inorder(p->pleft);
    cout<<p->value<<", ";
    inorder(p->pright);
}
void Tree::add(int a, node *p_node)
{
    if (p_node == NULL)
    {
        p_node = new node;
        p_node->value = a;
        p_node->pleft = NULL;
        p_node->pright = NULL;
    }
    else
    {
        if (p_node->value < a)
            add(a,p_node->pright);
        if (p_node->value > a)
            add(a,p_node->pleft);
    }

}
