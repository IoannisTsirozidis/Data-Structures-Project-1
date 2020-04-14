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
        p_node->counter = 1;
        return p_node;
    }
    if (key_value > p_node->value)
        p_node->pright = insert(p_node->pright, key_value);
    else if (key_value == p_node->value)
        p_node->counter += 1;
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
    if (p==NULL) return;cout<<p->value<<", ";preorder(p->pleft);preorder(p->pright);
}

void BinarySearchTree::inorder()
{
    inorder(root);
}
void BinarySearchTree::inorder(node *p)
{
    if (p==NULL) return;inorder(p->pleft);cout<<p->value<<", ";inorder(p->pright);
}

void BinarySearchTree::postorder()
{
    postorder(root);
}
void BinarySearchTree::postorder(node *p)
{
    if (p==NULL) return;postorder(p->pleft);postorder(p->pright);cout<<p->value<<", ";
}

int BinarySearchTree::search(string key_value)
{
    node* temp;

    temp = search(root, key_value);
    if(temp==nullptr)
        return 0;
    else
        return temp->counter;
    /*
    if(temp==nullptr)
        cout<<"not found"<<endl;
    else
        cout<<"<"<<temp->value<<">"<<" found ";
    */
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



void BinarySearchTree::debugInfo(node *p)
{
    if (p==NULL) return;
    debugInfo(p->pleft);
    debugInfo(p->pright);
    cout<<endl<<endl<<" ------------------------------- "<<endl<<endl;
    cout<<" Value         : "<<p->value<<endl;
    cout<<" Counter       : "<<p->counter<<endl<<endl;

    if (p->pleft)
    cout<<endl<<" Left Value  : "<<p->pleft->value<<endl;

    if (p->pright)
        cout<<endl<<" Right Value : "<<p->pright->value<<endl;
    cout<<endl<<" ------------------------------- "<<endl;
}

void BinarySearchTree::printDebug()
{
    cout<<endl<<endl<<endl<<" ---------- DEBUG INFO ---------"<<endl;
    debugInfo(root);

}





bool BinarySearchTree::delete_node(string key_value)
{
    node* p_delete_node;    //O KOMVOS POU THELOUME NA DIAGRAPSOUME

    node* p_current;        ///O ELAXISTOS KOMVOS


    p_delete_node= search(root, key_value);         //VRISKOUME TON KOMVO


    if(!p_delete_node)           //AN DEN YPARXEI RETURN FALSE
        return false;


    //CASE 1. p_delete_node DEN EXEI PAIDIA
    if(p_delete_node->pleft==nullptr && p_delete_node->pright==nullptr)
        delete p_delete_node;


    //CASE 2. p_delete_node EXEI ENA PAIDI
    if( (p_delete_node->pleft==nullptr && p_delete_node->pright!=nullptr) || (p_delete_node->pleft!=nullptr && p_delete_node->pright==nullptr) )
        remove_one_child(p_delete_node);



    //CASE 3. p_delete_node EXEI DYO PAIDIA
    if(p_delete_node->pleft!=nullptr && p_delete_node->pright!=nullptr)
    {
        p_current= p_delete_node->pright;

        while(p_current->pleft!= nullptr)
            p_current= p_current->pleft;

        //tha ftasoume se ena min p_current sto dexi ypodentro.


        ///ANTIGRAFH STOIXEIWN min STO p_delete_node

        p_delete_node->value = p_current->value;
        p_delete_node->counter = p_current->counter;

        //SE PERIPTWSH OPOU CURRENT(min) DEN EXEI PAIDIA
        if(p_current->pleft== nullptr && p_current->pright==nullptr)
            delete p_current;

        //SE PERIPTWSH OPOU CURRENT(min) EXEI MONO ENA PAIDI STA DEXIA
        if(p_current->pright!= nullptr)
            remove_one_child(p_current);
    }

    return true;

}



node* BinarySearchTree::remove_one_child(node* p_node)
{
    if(p_node->pleft!= nullptr && p_node->pright==nullptr)
    {
        p_node->value= p_node->pleft->value;
        p_node->counter= p_node->pleft->counter;
        p_node->pleft= p_node->pleft->pleft;
        p_node->pright= p_node->pleft->pright;

        delete p_node->pleft;

    }

    if(p_node->pright!=nullptr && p_node->pleft==nullptr)
    {
        p_node->value= p_node->pright->value;
        p_node->counter= p_node->pright->counter;
        p_node->pleft= p_node->pright->pleft;
        p_node->pright= p_node->pright->pright;

        delete p_node->pright;
    }


    if(p_node->pright!=nullptr && p_node->pleft!=nullptr)
    {
         cout<<"u fcking liar";
         return nullptr;
    }

    return p_node;
}











