#include "TreeAVL.h"

TreeAVL::TreeAVL()
{
    //ctor
    root = nullptr;
}

TreeAVL::~TreeAVL()
{
    //dtor
}
int TreeAVL::search(int key_value)
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
node* TreeAVL::search(node* p_node, int key_value)
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

int TreeAVL::maxof2(int a, int b)      //EPISTREFEI TO MAX DYO ARITHMWN
{
    if(a>=b)
        return a;
    else
        return b;
}


int TreeAVL::height(node* mynode)      //ANADROMIKH SYNARTHSH POU VRISKEI TO MEGISTO MONOPATI APO ENAN KOMVO
{
    //TERMATIKH SYNTHHKH
    if(mynode== nullptr)        ///AN O KOMVOS POU EPELEXA H EFTASA EINAI KENOS GYRNAEI 0
        return 0;

    //AN O KOMVOS POU EPELEXA H POU EFTASA DEN EINAI KENOS
    //TOTE XANAKALW TH SYNARTHSH GIA TO MEGALYTERO MONOPATI EITE DEXIA EITE ARISTERA
    //
    //
    //
    //                  13
    //             3          56
    //                1
    //
    else
    {

        return 1 + maxof2(height(mynode->pright), height(mynode->pleft));
    }

}


int TreeAVL::get_bf(node* mynode)      //EPISTREFEI TO BALANCE FACTOR TOU KOMVOU
{
    int lheight, rheight, bf;

    lheight= height(mynode->pleft);
    rheight= height(mynode->pright);

    bf= lheight- rheight;               //maxleft- maxright; ...[-1, 0, 1]... an EINAI BALANCED

    mynode->balance_factor= bf;

    return mynode->balance_factor;
}


node* TreeAVL::insert(node *p_node,int key_value)
{
    if (p_node == nullptr)///Create the new node and return the address
    {
        p_node = new node;
        p_node->pleft = nullptr;
        p_node->pright =nullptr;
        p_node->value = key_value;
        p_node->counter = 1;
        p_node->balance_factor = 0;
        return p_node;
    }
    if (key_value > p_node->value)
        p_node->pright = insert(p_node->pright, key_value);
    else if (key_value == p_node->value)
    {
        p_node->counter += 1;                                   ///LOOK OUT REMINDER !!!!!!
        return p_node;

    }
    else
        p_node->pleft = insert(p_node->pleft, key_value);


    ///Check the balance of the TreeAVL
    int bal = get_bf(p_node);
    cout <<"Balance of "<<p_node->value<<" is "<<bal<<endl;


    if (bal >1) ///ARXIZEI ME ARISTERA
    {
        if (key_value < p_node->pleft->value)
        {
            cout<<"LL !!"<<endl;
            p_node = ll_rotation(p_node);
        }
        if (key_value > p_node->pleft->value)
        {
            cout<<"LR !!"<<endl;
            p_node = lr_rotation(p_node);
        }

    }
    if (bal < -1)///ARXIZEI ME DEXIA
    {
        if (key_value < p_node->pright->value)
        {
            cout<<"RL !!"<<endl;
            p_node = rl_rotation(p_node);
        }
        if (key_value > p_node->pright->value)
        {
            cout<<"RR !!"<<endl;
            p_node = rr_rotation(p_node);


        }

    }
    cout<<"BALANCE FACTOR : "<<p_node->balance_factor<<endl;

    return p_node;
}


void TreeAVL::display(node *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->pright, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->value;
        display(ptr->pleft, level + 1);
    }
}

node* TreeAVL::rr_rotation(node *parent)
{
    node *temp;
    temp = parent->pright;
    parent->pright = temp->pleft;
    temp->pleft = parent;
    return temp;
}


node* TreeAVL::rl_rotation(node *parent)
{
    node *temp;
    temp = parent->pright;
    parent->pright = ll_rotation (temp);
    return rr_rotation (parent);
}


node* TreeAVL::ll_rotation(node *parent)
{
    node *temp;
    temp = parent->pleft;
    parent->pleft = temp->pright;
    temp->pright = parent;
    return temp;
}


node* TreeAVL::lr_rotation(node *parent)
{
    node *temp;
    temp = parent->pleft;
    parent->pleft = rr_rotation (temp);
    return ll_rotation (parent);
}
void TreeAVL::debugInfo(node *p)
{
    if (p==NULL) return;
    debugInfo(p->pleft);
    debugInfo(p->pright);
    cout<<endl<<endl<<" ------------------------------- "<<endl<<endl;
    cout<<" Current Point : "<<p<<endl;
    cout<<" Value         : "<<p->value<<endl;
    cout<<" Balance Factor: "<<p->balance_factor<<endl;
    cout<<" Counter       : "<<p->counter<<endl<<endl;


    //cout<<endl<<" Left Pointer  : "<<p->pleft<<endl;
    if (p->pleft)
    cout<<endl<<" Left Value  : "<<p->pleft->value<<endl;
    //cout<<endl<<" Right Pointer  : "<<p->pright<<endl;
    if (p->pright)
        cout<<endl<<" Right Value : "<<p->pright->value<<endl;
    cout<<endl<<" ------------------------------- "<<endl;

}
void TreeAVL::preorder()
{
    preorder(root);
}


void TreeAVL::preorder(node *p)
{
    if (p==NULL) return;cout<<p->value<<", ";preorder(p->pleft);preorder(p->pright);
}

void TreeAVL::inorder()
{
    inorder(root);
}
void TreeAVL::inorder(node *p)
{
    if (p==NULL) return;
    inorder(p->pleft);
    cout<<p->value<<", ";
    inorder(p->pright);
}

void TreeAVL::postorder()
{
    postorder(root);
}
void TreeAVL::postorder(node *p)
{
    if (p==NULL) return;postorder(p->pleft);postorder(p->pright);cout<<p->value<<", ";
}

