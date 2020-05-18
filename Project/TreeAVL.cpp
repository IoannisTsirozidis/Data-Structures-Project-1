#include "TreeAVL.h"
#include <iostream>
#include <string>
#include "TreeAVL.h"

        using namespace std;



TreeAVL::TreeAVL()      //Default Constructor
{
    //ctor
    root = nullptr;
    number_of_nodes = 0;
}

TreeAVL::~TreeAVL()     //Default Destructor
{
    //dtor
}







///------------------Section: Search Function-------------------

//Search Function for Main
int TreeAVL::search(string key_value)
{
    nodeA* temp;

    temp = search(root, key_value);

    if(temp==nullptr)
        return 0;
    return temp->counter;
}

//Background Search function
nodeA* TreeAVL::search(nodeA* p_nodeA, string key_value)
{
        if(p_nodeA== nullptr)
            return nullptr;

        if(p_nodeA->value == key_value)
            return p_nodeA;

        else if(key_value > p_nodeA->value)
            return search(p_nodeA->pright, key_value);

        else
            return search(p_nodeA->pleft, key_value);
}

///-----------------------end of section-----------------------------------------








///---------------Section: Insert Function------------------------------------

nodeA* TreeAVL::insert(nodeA *p_nodeA,string key_value)
{
    if (p_nodeA == nullptr)      ///Create the new nodeA and return the address
    {
        p_nodeA = new nodeA;
        p_nodeA->pleft = nullptr;
        p_nodeA->pright =nullptr;
        p_nodeA->value = key_value;
        p_nodeA->counter = 1;
        p_nodeA->height = 1;
        return p_nodeA;
    }
    if (key_value > p_nodeA->value)
    {
        p_nodeA->pright = insert(p_nodeA->pright, key_value);

    }

    else if (key_value == p_nodeA->value)
    {
        p_nodeA->counter += 1;

        return p_nodeA;

    }
    else
    {
        p_nodeA->pleft = insert(p_nodeA->pleft, key_value);

    }



    int bal = get_bf(p_nodeA);


    if (bal >1)         ///Initiates Check from the LEFT Subtree.
    {
        if (key_value < p_nodeA->pleft->value)
        {
            p_nodeA = ll_rotation(p_nodeA);           //left-left rotation
        }



        if (key_value > p_nodeA->pleft->value)
        {
            p_nodeA = lr_rotation(p_nodeA);           //left-right rotation
        }

    }


    if (bal < -1)       ///Initiates Check from the RIGHT Subtree.
    {

        if (key_value < p_nodeA->pright->value)
        {
            p_nodeA = rl_rotation(p_nodeA);       //right-left rotation
        }


        if (key_value > p_nodeA->pright->value)
        {
            p_nodeA = rr_rotation(p_nodeA);       //right-right rotation


    }

    return p_nodeA;
}

///-------------------------end of section----------------------------------------------









///-------------Section:Delete Function-------------------------------------------------------------


//Sub Function         'Remove one child' for Delete Function
//-----------------------------------------------------------
nodeA* TreeAVL::remove_one_child(nodeA* p_nodeA)
{
    if(p_nodeA->pright!=nullptr && p_nodeA->pleft!=nullptr)// You liar, you said you had one child but you have two
         return nullptr;


    if(p_nodeA->pleft!= nullptr && p_nodeA->pright==nullptr) // Same sub-function as in the BST
    {
        nodeA * next;
        next = p_nodeA->pleft;

        p_nodeA->value = next->value;
        p_nodeA->counter = next->counter;
        p_nodeA->pleft = next->pleft;
        p_nodeA->pright = next->pright;

        delete p_nodeA->pleft;
    }


    if (p_nodeA->pleft==nullptr && p_nodeA->pright!=nullptr)
    {
        nodeA * next;
        next = p_nodeA->pright;

        p_nodeA->value = next->value;
        p_nodeA->counter = next->counter;
        p_nodeA->pleft = next->pleft;
        p_nodeA->pright = next->pright;
        delete next;
    }

    return p_nodeA;
}
//----------------end of Sub Function---------------------------



//------------------Main Delete Function---------------------------------


bool TreeAVL::delete_nodeA(string key_value) //a non- recursive function
{
    nodeA* p_delete_nodeA;    //the nodeA to be deleted
    nodeA *parent;
    nodeA* p_current;        //minimum nodeA

    p_delete_nodeA= search(root, key_value);         //Spotting the nodeA.

    if(!p_delete_nodeA)           //If the nodeA does not exist, return false.
        return false;



    /// CASE 1. p_delete_nodeA has NO children.
    if(p_delete_nodeA->pleft==nullptr && p_delete_nodeA->pright==nullptr)
    {

        if (p_delete_nodeA == root)//"I hate kids"
        {
            delete p_delete_nodeA;
            root =nullptr;
        }

        else
        {
            parent = search_parent(key_value);
            if (parent->pleft == p_delete_nodeA)
                parent->pleft = nullptr;
            if (parent->pright == p_delete_nodeA)
                parent->pright = nullptr;
            delete p_delete_nodeA;
        }

    }
    else
    {
        /// CASE 2. p_delete_nodeA has ONE child.
        if((p_delete_nodeA->pleft != nullptr && p_delete_nodeA->pright == nullptr) || (p_delete_nodeA->pleft == nullptr && p_delete_nodeA->pright != nullptr))
            {
                if (p_delete_nodeA == root) //I am Groot
                {
                    nodeA * previous_root = root;
                    if (p_delete_nodeA->pright!= nullptr && p_delete_nodeA->pleft == nullptr)
                        root = root->pright;
                    else
                        root = root->pleft;

                    delete previous_root;

                }
                else
                    remove_one_child(p_delete_nodeA);

            }

        /// CASE 3. p_delete_nodeA has TWO children
        else if(p_delete_nodeA->pleft!=nullptr && p_delete_nodeA->pright!=nullptr)
        {

            p_current= p_delete_nodeA->pright;

            while(p_current->pleft!= nullptr) // Will arrive at a minimum nodeA at the right subtree. (Find MIN)
                p_current= p_current->pleft;  // Copy the Value and Counter in the p_delete_nodeA





            if (p_current->pleft == nullptr && p_current->pright == nullptr) //Does not have children. Hates them too
            {
                parent = search_parent(p_current->value);
                if (parent->pleft == p_current)
                    parent->pleft = nullptr;
                if (parent->pright == p_current)
                    parent->pright = nullptr;

                p_delete_nodeA->value = p_current->value;
                p_delete_nodeA->counter = p_current->counter;

                delete p_current;
            }
            if (p_current->pright != nullptr && p_current->pleft == nullptr) //Has a child to the right
            {
                p_delete_nodeA->value = p_current->value;
                p_delete_nodeA->counter = p_current->counter;

                remove_one_child(p_current);
            }

        }
    }


    nodeA *p_nodeA = root;

    //Check the balance of the TreeAVL
    int bal = get_bf(p_nodeA);


    if (bal >1)                 ///Initiates check to the left
    {
        if (key_value < p_nodeA->pleft->value) // Left Left Rotation
            p_nodeA = ll_rotation(p_nodeA);

        if (key_value > p_nodeA->pleft->value) // Left Right Rotation
            p_nodeA = lr_rotation(p_nodeA);

    }
    if (bal < -1)              ///Initiates check to the right
    {
        if (key_value < p_nodeA->pright->value)
            p_nodeA = rl_rotation(p_nodeA);

        if (key_value > p_nodeA->pright->value)
            p_nodeA = rr_rotation(p_nodeA);
    }
    
    return true;

}
//-----------end of Main Delete Function-------------------------


///--------------------------------end of Delete Function---------------------------------------------------







///------------------------------Section: Fix Balance Factor----------------------------------------
int TreeAVL::height(nodeA *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int TreeAVL::get_bf(nodeA* p_nodeA)      //returns the balance factor of a nodeA
{
    if (p_nodeA == NULL)
        return 0;
    return (height(p_nodeA->pleft) - height(p_nodeA->pright));
}


///----------------------------end of section---------------------------------------------


















//-----------------------------Section: ROTATIONS --------------------------------
nodeA *TreeAVL::rightRotate(nodeA *y)
{
	nodeA *x = y->pleft;
	nodeA *temp = x->pright;

	// Perform rotation
	x->pright = y;
	y->pleft = temp;

	// Update heights
	y->height = max(height(y->pleft),
					height(y->pright)) + 1;
	x->height = max(height(x->pleft),
					height(x->pright)) + 1;

	// Return new root
	return x;
}
nodeA *TreeAVL::leftRotate(nodeA *x)
{
	nodeA *y = x->pright;
	nodeA *temp = y->pleft;

	// Perform rotation
	y->pleft = x;
	x->pright = temp;

	// Update heights
	x->height = max(height(x->pleft),
					height(x->pright)) + 1;
	y->height = max(height(y->pleft),
					height(y->pright)) + 1;

	// Return new root
	return y;
}
nodeA* TreeAVL::rr_rotation(nodeA *p_nodeA)            ///RIGHT RIGHT rotation
{
    return leftRotate(p_nodeA);
}

nodeA* TreeAVL::rl_rotation(nodeA *p_nodeA)            ///RIGHT-LEFT rotation
{
    p_nodeA->pright = rightRotate(p_nodeA->pright);
    return leftRotate(p_nodeA);
}



nodeA* TreeAVL::ll_rotation(nodeA *p_nodeA)            ///LEFT-LEFT rotation
{
    return rightRotate(p_nodeA);
}


nodeA* TreeAVL::lr_rotation(nodeA *p_nodeA)            ///LEFT-RIGHT rotation
{
    p_nodeA->pleft = leftRotate(p_nodeA->pleft);
    return rightRotate(p_nodeA);
}
//----------------------------------end of section-----------------------------------------------






///---------------------Section:  Debugging Information------------------------------------

void TreeAVL::debugInfo(nodeA *p)
{
    if (p==NULL) return;
    debugInfo(p->pleft);
    debugInfo(p->pright);
    cout<<endl<<endl<<" ------------------------------- "<<endl<<endl;
    cout<<" Current Point : "<<p<<endl;
    cout<<" Value         : "<<p->value<<endl;
    cout<<" Balance Factor: "<<p->balance_factor<<endl;
    cout<<" Counter       : "<<p->counter<<endl<<endl;


    if (p->pleft)
    cout<<endl<<" Left Value  : "<<p->pleft->value<<endl;

    if (p->pright)
        cout<<endl<<" Right Value : "<<p->pright->value<<endl;
    cout<<endl<<" ------------------------------- "<<endl;

}

void TreeAVL::display(nodeA *ptr, int level)
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
void TreeAVL::preorder(nodeA *p)
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
void TreeAVL::inorder(nodeA *p)
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
void TreeAVL::postorder(nodeA *p)
{
    if (p==nullptr)
        return;

    postorder(p->pleft);
    postorder(p->pright);
    cout<<p->value<<", ";
}
//------------------------------------
















//-------------------------------Auxiliary Function Search parent nodeA--------------------------------
nodeA* TreeAVL::search_parent(string key)
{
    nodeA *parent = nullptr;
    nodeA *current = root;
	// traverse the tree and search for the key
	while (current != nullptr && current->value != key)
	{
		// update parent nodeA as current nodeA
		parent = current;

		// if given key is less than the current nodeA, go to left subtree
		// else go to right subtree
		if (key < current->value)
			current = current->pleft;
		else
			current = current->pright;
	}
	return parent;
}

//----------------------end of Search function--------------------



void check_p_null_AVL(void *p)
{
    if (!p)
    {
        cout<<"MEMORY ALLOCATION FAILED in TreeAVL\n Exiting..."<<endl;
        exit(-1);
    }
}
