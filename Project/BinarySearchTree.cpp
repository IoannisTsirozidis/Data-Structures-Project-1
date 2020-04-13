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

}
BinarySearchTree::~BinarySearchTree()       //Default Destructor
{

}
void BinarySearchTree::insert(string key_value)
{
    root = insert(root,key_value);
}
node* BinarySearchTree::insert(node *p_node,string key_value)
{
    if (p_node == nullptr)
    {
        p_node = new node;
        p_node->pleft = nullptr;
        p_node->pright =nullptr;
        p_node->value = key_value;
        return p_node;
    }
    if (key_value > p_node->value)
        p_node->pright = insert(p_node->pright, key_value);
    else
        p_node->pleft = insert(p_node->pleft, key_value);

    return p_node;
}

void BinarySearchTree::preorder()
{
    preorder(root);
}
void BinarySearchTree::preorder(node *p)
{
    if (p==NULL) return;
    cout<<p->value<<", ";
    preorder(p->pleft);
    preorder(p->pright);
}

void BinarySearchTree::inorder()
{
    inorder(root);
}
void BinarySearchTree::inorder(node *p)
{
    if (p==NULL) return;
    inorder(p->pleft);
    cout<<p->value<<", ";
    inorder(p->pright);
}

void BinarySearchTree::postorder()
{
    postorder(root);
}
void BinarySearchTree::postorder(node *p)
{
    if (p==NULL) return;
    postorder(p->pleft);
    postorder(p->pright);
    cout<<p->value<<", ";

}




void BinarySearchTree::search(string key_value)
{
    node* temp;

    temp= search(root, key_value);

    if(temp==nullptr)
        cout<<"not found"<<endl;
    else
        cout<<"<"<<temp->value<<">"<<" found ";

}


node* BinarySearchTree::search(node* p_node, string key_value)
{
        if(p_node== nullptr)
            return nullptr;

        if(p_node->value == key_value)
            return p_node;

        else if(key_value > p_node->value)
            return search(p_node->pright, key_value);

        else//if(key_value < p_node->value)
            return search(p_node->pleft, key_value);
}


void BinarySearchTree::print()
{
    cout<<endl<< root->pleft->pright->value <<endl;
}


