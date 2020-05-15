#include "TreeAVL.h"
#include <iostream>
#include <string>
#include "TreeAVL.h"

        using namespace std;



TreeAVL::TreeAVL()      //Default Constructor
{
    //ctor
    root = nullptr;
}

TreeAVL::~TreeAVL()     //Default Destructor
{
    //dtor
}







///------------------Section: Search Function-------------------

//Search Function for Main
int TreeAVL::search(string key_value)
{
    node* temp;

    temp = search(root, key_value);

    if(temp==nullptr)
        {
            cout<<"Not Found"<<endl;
            return 0;
        }

    cout<<"Appeared "<<temp->counter<<" time(s)"<<endl;
    return temp->counter;

}

//Background Search function
node* TreeAVL::search(node* p_node, string key_value)
{
        if(p_node== nullptr)
            return nullptr;

        if(p_node->value == key_value)
            return p_node;

        else if(key_value > p_node->value)
            return search(p_node->pright, key_value);

        else
            return search(p_node->pleft, key_value);
}

///-----------------------end of section-----------------------------------------








///---------------Section: Insert Function------------------------------------

node* TreeAVL::insert(node *p_node,string key_value)
{
    if (p_node == nullptr)      ///Create the new node and return the address
    {
        p_node = new node;
        p_node->pleft = nullptr;
        p_node->pright =nullptr;
        p_node->value = key_value;
        p_node->counter = 1;
        p_node->height = 1;
        return p_node;
    }
    if (key_value > p_node->value)
    {
        p_node->pright = insert(p_node->pright, key_value);

    }

    else if (key_value == p_node->value)
    {
        p_node->counter += 1;

        return p_node;

    }
    else
    {
        p_node->pleft = insert(p_node->pleft, key_value);

    }



    int bal = get_bf(p_node);


    if (bal >1)         ///Initiates Check from the LEFT Subtree.
    {
        if (key_value < p_node->pleft->value)
        {
            p_node = ll_rotation(p_node);           //left-left rotation
        }



        if (key_value > p_node->pleft->value)
        {
            p_node = lr_rotation(p_node);           //left-right rotation
        }

    }


    if (bal < -1)       ///Initiates Check from the RIGHT Subtree.
    {

        if (key_value < p_node->pright->value)
        {
            p_node = rl_rotation(p_node);       //right-left rotation
        }


        if (key_value > p_node->pright->value)
        {
            p_node = rr_rotation(p_node);       //right-right rotation

        }

    }

    return p_node;
}

///-------------------------end of section----------------------------------------------









///-------------Section:Delete Function-------------------------------------------------------------


//Sub Function         'Remove one child' for Delete Function
//-----------------------------------------------------------
node* TreeAVL::remove_one_child(node* p_node)
{
    if(p_node->pright!=nullptr && p_node->pleft!=nullptr)
    {
         //cout<<"u fcking liar you said you had one child but you have two";
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
//----------------end of Sub Function---------------------------



//------------------Main Delete Function---------------------------------


bool TreeAVL::delete_node(string key_value) //a non- recursive function
{
    node* p_delete_node;    //the node to be deleted
    node *parent;
    node* p_current;        //minimum node

    p_delete_node= search(root, key_value);         //Spotting the node.

    if(!p_delete_node)           //If the node does not exist, return false.
        return false;



    //CASE 1. p delete node has NO children.
    if(p_delete_node->pleft==nullptr && p_delete_node->pright==nullptr)
    {
        //cout<<"I hate kids"<<endl;
        if (p_delete_node == root)
        {
            delete p_delete_node;
            root =nullptr;
        }

        else
        {
            //cout<<endl<<"The node "<<p_delete_node->value<<" has NOO child"<<endl;
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
        //CASE 2. p_delete_node has ONE child.
        if((p_delete_node->pleft != nullptr && p_delete_node->pright == nullptr) || (p_delete_node->pleft == nullptr && p_delete_node->pright != nullptr))
            {
                //cout<<endl<<"The node "<<p_delete_node->value<<" has one child"<<endl;
                if (p_delete_node->pright == nullptr)
                {
                    //cout<<"NO RIGHT"<<endl;
                    //return false;
                }
                if (p_delete_node->pleft == nullptr)
                {
                    //cout<<"NO LEFTTTTT"<<endl;
                    //return false;
                }
                if (p_delete_node == root)
                {
                    //cout<<"EIMAI GROOT"<<endl;
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

        //CASE 3. p_delete_node has TWO children
        else if(p_delete_node->pleft!=nullptr && p_delete_node->pright!=nullptr)
        {

            p_current= p_delete_node->pright;

            while(p_current->pleft!= nullptr)
                p_current= p_current->pleft;

            //will arrive at a minimum node at the right subtree

            //Copy the Value and Counter in the p_delete_node


            if (p_current->pleft == nullptr && p_current->pright == nullptr) //Does not have children.
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
            if (p_current->pright != nullptr && p_current->pleft == nullptr) //Does not have children to the right.
            {

                p_delete_node->value = p_current->value;
                p_delete_node->counter = p_current->counter;

                remove_one_child(p_current);

            }

        }
    }


    node *p_node = root;

    //Check the balance of the TreeAVL
    int bal = get_bf(p_node);



    if (bal >1)                 //Initiates check to the left
    {
        if (key_value < p_node->pleft->value)
        {
            //cout<<"LL !!"<<endl;
            p_node = ll_rotation(p_node);
        }
        if (key_value > p_node->pleft->value)
        {
            //cout<<"LR !!"<<endl;
            p_node = lr_rotation(p_node);
        }

    }
    if (bal < -1)           //Initiates check to the right
    {
        if (key_value < p_node->pright->value)
        {
            p_node = rl_rotation(p_node);
        }


        if (key_value > p_node->pright->value)
        {
            p_node = rr_rotation(p_node);

        }

    }

    //cout<<"BALANCE FACTOR : "<<p_node->balance_factor<<endl;



    return true;

}
//-----------end of Main Delete Function-------------------------


///--------------------------------end of Delete Function---------------------------------------------------







///------------------------------Section: Fix Balance Factor----------------------------------------
int TreeAVLheight(node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int TreeAVL::get_bf(node* p_node)      //returns the balance factor of a node
{
    if (p_node == NULL)
        return 0;
    return height(p_node->pleft) - height(p_node->pright);
}



int TreeAVL::maxof2(int a, int b)      //returns the max of two numbers
{
    if(a>=b)
        return a;
    else
        return b;
}



///----------------------------end of section---------------------------------------------


















//-----------------------------Section: ROTATIONS --------------------------------
node *rightRotate(node *y)
{
	node *x = y->pleft;
	node *T2 = x->pright;

	// Perform rotation
	x->pright = y;
	y->pleft = T2;

	// Update heights
	y->height = max(height(y->pleft),
					height(y->pright)) + 1;
	x->height = max(height(x->pleft),
					height(x->pright)) + 1;

	// Return new root
	return x;
}
node *leftRotate(node *x)
{
	node *y = x->pright;
	node *T2 = y->pleft;

	// Perform rotation
	y->pleft = x;
	x->pright = T2;

	// Update heights
	x->height = max(height(x->pleft),
					height(x->pright)) + 1;
	y->height = max(height(y->pleft),
					height(y->pright)) + 1;

	// Return new root
	return y;
}
node* TreeAVL::rr_rotation(node *p_node)            ///RIGHT RIGHT rotation
{
    return leftRotate(p_node);
}


node* TreeAVL::rl_rotation(node *p_node)            ///RIGHT-LEFT rotation
{
    p_node->pright = rightRotate(p_node->pright);
    return leftRotate(p_node);
}



node* TreeAVL::ll_rotation(node *p_node)            ///LEFT-LEFT rotation
{
    return rightRotate(p_node);
}


node* TreeAVL::lr_rotation(node *p_node)            ///LEFT-RIGHT rotation
{
    p_node->pleft = leftRotate(p_node->pleft);
    return rightRotate(p_node);
}
//----------------------------------end of section-----------------------------------------------






///---------------------Section:  Debugging Information------------------------------------

void TreeAVL::debugInfo(node *p)
{
    if (p==NULL) return;
    debugInfo(p->pleft);
    debugInfo(p->pright);
    cout<<endl<<endl<<" ------------------------------- "<<endl<<endl;
    cout<<" Current Point : "<<p<<endl;
    cout<<" Value         : "<<p->value<<endl;
    cout<<" Height        : "<<p->height<<endl;
    cout<<" Counter       : "<<p->counter<<endl<<endl;


    if (p->pleft)
    cout<<endl<<" Left Value  : "<<p->pleft->value<<endl;

    if (p->pright)
        cout<<endl<<" Right Value : "<<p->pright->value<<endl;
    cout<<endl<<" ------------------------------- "<<endl;

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


///---------------------------end of section----------------------------------







//------------PREORDER function-----------
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
//--------------------------------------





//-----------INORDER function----------
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
//------------------------------------





//-------------POSTORDER function-------
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
//------------------------------------
















//-------------------------------Auxiliary Function Search parent node--------------------------------
node* TreeAVL::search_parent(string key)
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

//----------------------end of Search function--------------------


