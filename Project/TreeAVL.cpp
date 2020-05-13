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
    if (p_nodeA == nullptr)       /// The node doesn't exist
    {
        p_nodeA = new nodeA;      /// Dynamically allocating memory

        check_p_null_AVL(p_nodeA);/// Checks if the allocation was successfully done

        p_nodeA->pleft = nullptr;  /// Set left and right pointer to null
        p_nodeA->pright =nullptr; /// Set value of the node to the key_value
        p_nodeA->value = key_value;
        p_nodeA->counter = 1;        /// Initializing the counter to one
        p_nodeA->balance_factor = 0;
        return p_nodeA;
    }
                                                 /// If the node exist
    if (key_value > p_nodeA->value)
    {
        p_nodeA->pright = insert(p_nodeA->pright, key_value); ///Recursive call of the insert

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
            return ll_rotation(p_nodeA);           //left-left rotation

        if (key_value > p_nodeA->pleft->value)
            return lr_rotation(p_nodeA);           //left-right rotation

    }


    if (bal < -1)       ///Initiates Check from the RIGHT Subtree.
    {

        if (key_value < p_nodeA->pright->value)
            return rl_rotation(p_nodeA);       //right-left rotation

        if (key_value > p_nodeA->pright->value)
            return rr_rotation(p_nodeA);       //right-right rotation


    }

    fix_bf_for_all(p_nodeA);         ///Correction of Balance Factor after Rotations.

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

    fix_bf_for_all(root);
    return true;

}
//-----------end of Main Delete Function-------------------------


///--------------------------------end of Delete Function---------------------------------------------------







///------------------------------Section: Fix Balance Factor----------------------------------------


int TreeAVL::get_bf(nodeA* mynodeA)      //returns the balance factor of a nodeA
{
    int lheight, rheight, bf;

    lheight= height(mynodeA->pleft);
    rheight= height(mynodeA->pright);

    bf= lheight- rheight;               //  (max height left) - (max height right); ...[-1, 0, 1]... if it's BALANCED

    mynodeA->balance_factor= bf;       //Updates the balance factor of (*this) nodeA

    return mynodeA->balance_factor;
}



void TreeAVL::update_bf(nodeA *p)        //UPDATES BALANCE FACTOR OF NODE
{
    int lheight, rheight, bf;

    lheight= height(p->pleft);
    rheight= height(p->pright);

    bf= lheight- rheight;               //   (max left) -   (max right); ...[-1, 0, 1]... if it is BALANCED

    p->balance_factor= bf;       //Updates the balance factor of (*this) nodeA
}


void TreeAVL::fix_bf_for_all(nodeA * p)  ///fixes the balance factor of all nodeAs
{
    if (p==nullptr)
        return;

    fix_bf_for_all(p->pleft);
    fix_bf_for_all(p->pright);
    update_bf(p);

}


int TreeAVL::height(nodeA* mynodeA)      //recursive function that returns HEIGHT (the MAX PATH), underneath a nodeA (left or right).

{
        //END CONDITION
        if(mynodeA== nullptr)        ///If the nodeA that we have arrived at is NULL or NON-existent, returns '0'.
            return 0;

        //if the nodeA, is not empty then the function is being called recursively
        //either from the right or the left path
        //
        //
        //
        //                  13
        //             3          56
        //                1
        //
        else
            return 1 + maxof2(height(mynodeA->pright), height(mynodeA->pleft));

}


int TreeAVL::maxof2(int a, int b)      //returns the max of two numbers
{
                                     //return (a>=b?a:b);
    if(a>=b)
        return a;
    else
        return b;
}



///----------------------------end of section---------------------------------------------


















///-----------------------------Section: ROTATIONS --------------------------------

nodeA* TreeAVL::rr_rotation(nodeA *parent)            /// RIGHT RIGHT rotation
{
    nodeA *temp;
    temp = parent->pright;

    parent->pright = temp->pleft;

    temp->pleft = parent;

    fix_bf_for_all(parent);


    return temp;
}


nodeA* TreeAVL::rl_rotation(nodeA *parent)            ///RIGHT-LEFT rotation
{
    nodeA *temp;
    temp = parent->pright;

    parent->pright = ll_rotation (temp);




    return rr_rotation (parent);
}



nodeA* TreeAVL::ll_rotation(nodeA *parent)            ///LEFT-LEFT rotation
{
    nodeA *temp;
    temp = parent->pleft;

    parent->pleft = temp->pright;

    temp->pright = parent;

    fix_bf_for_all(parent);

    return temp;
}


nodeA* TreeAVL::lr_rotation(nodeA *parent)            ///LEFT-RIGHT rotation
{
    nodeA *temp;
    temp = parent->pleft;
    parent->pleft = rr_rotation (temp);

    return ll_rotation (parent);
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
