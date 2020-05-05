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


void TreeAVL::update_update(node *p)
{
        p->
}









///balance factor


int TreeAVL::get_bf(node* mynode)      //EPISTREFEI TO BALANCE FACTOR TOU KOMVOU
{
    int lheight, rheight, bf;

    lheight= height(mynode->pleft);
    rheight= height(mynode->pright);

    bf= lheight- rheight;               //maxleft- maxright; ...[-1, 0, 1]... an EINAI BALANCED

    mynode->balance_factor= bf;       ///PEIRAZEI TO VALUE BALANCE_FACTOR TOU ANTIKEIMENOU

    return mynode->balance_factor;
}



void TreeAVL::update_bf(node *p)        //UPDATES BALANCE FACTOR OF NODE
{
    int lheight, rheight, bf;

    lheight= height(p->pleft);
    rheight= height(p->pright);

    bf= lheight- rheight;               //maxleft- maxright; ...[-1, 0, 1]... an EINAI BALANCED

    p->balance_factor= bf;       //PEIRAZEI TO VALUE BALANCE_FACTOR TOU ANTIKEIMENOU
}


void TreeAVL::check_balance_preorder(node *p)
{
    if (p==nullptr)
        return;

    update_bf(p);
    preorder(p->pleft);

    update_bf(p);
    preorder(p->pright);

}





















node* TreeAVL::insert(node *p_node,int key_value) ///Anadromi
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
    {
        p_node->pright = insert(p_node->pright, key_value);
        check_balance_preorder(root);
    }

    else if (key_value == p_node->value)
    {
        p_node->counter += 1;
        check_balance_preorder(root);
        return p_node;

    }
    else
    {
        p_node->pleft = insert(p_node->pleft, key_value);
        check_balance_preorder(root);
    }


    ///Check the balance of the TreeAVL

    check_balance_preorder(root);

    int bal = get_bf(p_node);

    cout <<"Balance of "<<p_node->value<<" is "<<bal<<endl;


    if (bal >1) ///ARXIZEI ME ARISTERA
    {
        if (key_value < p_node->pleft->value)
        {
            cout<<"LL !!"<<endl;                            //LEFT LEFT ROTATION
            p_node = ll_rotation(p_node);

            check_balance_preorder(root);               ///checks balance factor
        }



        if (key_value > p_node->pleft->value)
        {
            cout<<"LR !!"<<endl;                            //LEFT RIGHT ROTATION

            p_node = lr_rotation(p_node);

            check_balance_preorder(root);               ///checks balance factor
        }

    }
    if (bal < -1)///ARXIZEI ME DEXIA
    {

        if (key_value < p_node->pright->value)
        {
            cout<<"RL !!"<<endl;                            //RIGHT LEFT ROTATION
            p_node = rl_rotation(p_node);

            check_balance_preorder(root);               ///checks balance factor
        }


        if (key_value > p_node->pright->value)
        {
            cout<<"RR !!"<<endl;                            //RIGHT RIGHT ROTATION
            p_node = rr_rotation(p_node);

            check_balance_preorder(root);               ///checks balance factor


        }

    }
    cout<<"BALANCE FACTOR : "<<p_node->balance_factor<<endl;

    check_balance_preorder(root);

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

node* TreeAVL::rr_rotation(node *parent)            ///RIGHT RIGHT ROTATION
{
    node *temp;
    temp = parent->pright;
    //update_bf(temp);

    parent->pright = temp->pleft;
    //update_bf(parent->pright);

    //update_bf(parent);

    temp->pleft = parent;
    //update_bf(temp->pleft);

    return temp;
}


node* TreeAVL::rl_rotation(node *parent)
{
    node *temp;
    temp = parent->pright;

    parent->pright = ll_rotation (temp);

    return rr_rotation (parent);
}


node* TreeAVL::ll_rotation(node *parent)            ///LEFT LEFT ROTATION
{
    node *temp;
    temp = parent->pleft;
    //update_bf(temp);

    parent->pleft = temp->pright;
    //update_bf(parent->pleft);

    temp->pright = parent;
    //update_bf(temp->pright);
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
    if (p==NULL)
        return;
    cout<<p->value<<", ";

    preorder(p->pleft);

    preorder(p->pright);
}

void TreeAVL::inorder()
{
    inorder(root);
}
void TreeAVL::inorder(node *p)
{
    if (p==NULL)
        return;

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
    if (p==nullptr)
        return;

    postorder(p->pleft);
    postorder(p->pright);
    cout<<p->value<<", ";
}


bool TreeAVL::delete_node(int key_value) ///TO KANAME XORIS ANADROMI
{
    node* p_delete_node;    //O KOMVOS POU THELOUME NA DIAGRAPSOUME
    node *parent;
    node* p_current;        ///O ELAXISTOS KOMVOS

    p_delete_node= search(root, key_value);         //VRISKOUME TON KOMVO

    if(!p_delete_node)           //AN DEN YPARXEI RETURN FALSE
        return false;

    //CASE 1. p_delete_node DEN EXEI PAIDIA
    if(p_delete_node->pleft==nullptr && p_delete_node->pright==nullptr)
    {
        cout<<"I hate kids"<<endl;
        if (p_delete_node == root)
        {
            delete p_delete_node;
            root =nullptr;
        }

        else
        {
            cout<<endl<<"The node "<<p_delete_node->value<<" has NOO child"<<endl;
            parent = search_parent(key_value);
            if (parent->pleft == p_delete_node)
                parent->pleft = nullptr;
            if (parent->pright == p_delete_node)
                parent->pright = nullptr;
            delete p_delete_node;
        }

    }
    else
    {
        //CASE 2. p_delete_node EXEI ENA PAIDI
        if((p_delete_node->pleft != nullptr && p_delete_node->pright == nullptr) || (p_delete_node->pleft == nullptr && p_delete_node->pright != nullptr))
            {
                cout<<endl<<"The node "<<p_delete_node->value<<" has one child"<<endl;
                if (p_delete_node->pright == nullptr)
                {
                    cout<<"NO RIGHT"<<endl;
                    //return false;
                }
                if (p_delete_node->pleft == nullptr)
                {
                    cout<<"NO LEFTTTTT"<<endl;
                    //return false;
                }
                if (p_delete_node == root)
                {
                    cout<<"EIMAI GROOT"<<endl;
                    node * previous_root = root;
                    if (p_delete_node->pright!= nullptr && p_delete_node->pleft == nullptr)
                        root = root->pright;
                    else
                        root = root->pleft;

                    delete previous_root;

                }
                else
                    remove_one_child(p_delete_node);

            }

        //CASE 3. p_delete_node EXEI DYO PAIDIA
        else if(p_delete_node->pleft!=nullptr && p_delete_node->pright!=nullptr)
        {
            //cout<<endl<<"The node "<<p_delete_node->value<<" has two child"<<endl;

            p_current= p_delete_node->pright;

            while(p_current->pleft!= nullptr)
                p_current= p_current->pleft;

            ///tha ftasoume se ena min p_current sto dexi ypodentro.

            ///ANTIGRAFH tou VALUE kai tou Counter min STO p_delete_node


            if (p_current->pleft == nullptr && p_current->pright == nullptr) //DEN EXEI PAIDIA
            {
                parent = search_parent(p_current->value);
                if (parent->pleft == p_current)
                    parent->pleft = nullptr;
                if (parent->pright == p_current)
                    parent->pright = nullptr;

                p_delete_node->value = p_current->value;
                p_delete_node->counter = p_current->counter;

                delete p_current;
            }
            if (p_current->pright != nullptr && p_current->pleft == nullptr) //EXEI ENA PAIDI STA DEXIA
            {

                p_delete_node->value = p_current->value;
                p_delete_node->counter = p_current->counter;

                remove_one_child(p_current);

            }

        }
    }


    node *p_node = root;
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



    return true;

}

node* TreeAVL::search_parent(int key)
{
    node *parent = nullptr;
    node *current = root;
	// traverse the tree and search for the key
	while (current != nullptr && current->value != key)
	{
		// update parent node as current node
		parent = current;

		// if given key is less than the current node, go to left subtree
		// else go to right subtree
		if (key < current->value)
			current = current->pleft;
		else
			current = current->pright;
	}
	return parent;
}

node* TreeAVL::remove_one_child(node* p_node)
{
    if(p_node->pright!=nullptr && p_node->pleft!=nullptr)
    {
         cout<<"u fcking liar you said you had one child but you have two";
         return nullptr;
    }

    if(p_node->pleft!= nullptr && p_node->pright==nullptr)
    {
        node * next;
        next = p_node->pleft;

        p_node->value = next->value;
        p_node->counter = next->counter;
        p_node->pleft = next->pleft;
        p_node->pright = next->pright;

        //next->value = 5555;
        delete p_node->pleft;

    }

    if (p_node->pleft==nullptr && p_node->pright!=nullptr)
    {
        node * next;
        next = p_node->pright;

        p_node->value = next->value;
        p_node->counter = next->counter;
        p_node->pleft = next->pleft;
        p_node->pright = next->pright;


        delete next;
    }



    return p_node;
}
