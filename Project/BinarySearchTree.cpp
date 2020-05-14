#include "BinarySearchTree.h"


BinarySearchTree::BinarySearchTree()        //Default Constructor
{

}
BinarySearchTree::~BinarySearchTree()       //Default Destructor
{

}


//---------------Function Insert-----------------------------

void BinarySearchTree::insert(string key_value)
{
    root = insert(root,key_value);
    number_of_nodes +=1;
}

node* BinarySearchTree::insert(node *p_node,string key_value)
{
    if (p_node == nullptr)                                      /// The node doesn't exist
    {
        p_node = new node;                                      /// Dynamically allocating memory
        check_p_null_BTS(p_node);                               /// Checks if the allocation was successfully done
        p_node->pleft = nullptr;                                /// Set left and right pointer to null
        p_node->pright =nullptr;
        p_node->value = key_value;                              /// Set value of the node to the key_value
        p_node->counter = 1;                                    /// Initializing the counter to one
        return p_node;
    }
                                                                /// If the node exist - is occupied
    if (key_value > p_node->value)                              /// Check if the key_value is smaller or greater from the current node
        p_node->pright = insert(p_node->pright, key_value);     /// Recursive call of the insert
    else if (key_value == p_node->value)
        p_node->counter += 1;
    else
        p_node->pleft = insert(p_node->pleft, key_value);

    return p_node;
}

//---------------------end of Function------------------------------






//--------------------PREORDER-------------------------
void BinarySearchTree::preorder()                               /// Call from main
{
    preorder(root);
}

void BinarySearchTree::preorder(node *p)                       /// Recursive call
{
    if (p==NULL) return;cout<<p->value<<", ";preorder(p->pleft);preorder(p->pright);
}
//-----------------------------------------------------






//----------------INORDER------------------------------
void BinarySearchTree::inorder()                               /// Call from main
{
    inorder(root);
}
void BinarySearchTree::inorder(node *p)                       /// Recursive call
{
    if (p==NULL) return;
    inorder(p->pleft);
    cout<<p->value<<", ";
    inorder(p->pright);
}
//-----------------------------------------------------








//---------------POSTORDER----------------------------
void BinarySearchTree::postorder()                          /// Call from main
{
    postorder(root);
}
void BinarySearchTree::postorder(node *p)                   /// Recursive call
{
    if (p==NULL) return;postorder(p->pleft);postorder(p->pright);cout<<p->value<<", ";
}
//----------------------------------------------------






//-------------Function Search-------------------------------------------
int BinarySearchTree::search(string key_value)                  /// (Main) Returns the number of occurrences of the key_value
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
node* BinarySearchTree::search(node* p_node, string key_value)  /// (Private) Returns the key_value node
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
//---------------------------end of function--------------------------------









//----------------------------Function DebugInfo------------------------
void BinarySearchTree::debugInfo(node *p)
{
    if (p==NULL) return;
    debugInfo(p->pleft);
    debugInfo(p->pright);
    cout<<endl<<endl<<" ------------------------------- "<<endl<<endl;
    cout<<" Current Postring : "<<p<<endl;
    cout<<" Value         : "<<p->value<<endl;
    cout<<" Counter       : "<<p->counter<<endl<<endl;

    //cout<<endl<<" Left Postringer  : "<<p->pleft<<endl;
    if (p->pleft)
    cout<<endl<<" Left Value  : "<<p->pleft->value<<endl;
    //cout<<endl<<" Right Postringer  : "<<p->pright<<endl;
    if (p->pright)
        cout<<endl<<" Right Value : "<<p->pright->value<<endl;
    cout<<endl<<" ------------------------------- "<<endl;

}

void BinarySearchTree::printDebug()
{
    cout<<endl<<endl<<endl<<" ---------- DEBUG INFO ---------"<<endl;
    debugInfo(root);

}
//----------------------------end of function--------------------------









//-----------------------------------------------Function Delete-----------------------------------------------

bool BinarySearchTree::delete_node(string key_value) /// Non recursive function
{
    node* p_delete_node;                                    /// the node to be deleted
    node *parent;
    node* p_current;                                        /// minimum node

    p_delete_node= search(root, key_value);                 /// Locating the node

    if(!p_delete_node)                                      /// If it does not exist, returns false
        return false;

    /// CASE 1. p_delete_node Does not have Children
    if(p_delete_node->pleft==nullptr && p_delete_node->pright==nullptr)
    {

        if (p_delete_node == root)
        {
            delete p_delete_node;
            root =nullptr;
        }

        else
        {

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
        /// CASE 2. p_delete_node HAS ONE CHILD
        if((p_delete_node->pleft != nullptr && p_delete_node->pright == nullptr) || (p_delete_node->pleft == nullptr && p_delete_node->pright != nullptr))
            {

                if (p_delete_node == root)
                {

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

        /// CASE 3. p_delete_node HAS TWO CHILDREN
        else if(p_delete_node->pleft!=nullptr && p_delete_node->pright!=nullptr)
        {

            p_current= p_delete_node->pright;

            while(p_current->pleft!= nullptr)
                p_current= p_current->pleft;

                                                            /// Will reach a minimum p_current on the right- subtree

                                                            /// Copying the "Value" and "Counter" of the p_delete_node


            if (p_current->pleft == nullptr && p_current->pright == nullptr)    /// Does not have Children
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
            if (p_current->pright != nullptr && p_current->pleft == nullptr)    /// Does have a child one the right- side
            {

                p_delete_node->value = p_current->value;
                p_delete_node->counter = p_current->counter;

                remove_one_child(p_current);

            }

        }
    }
    number_of_nodes -=1;
    return true;

}
//-------------------------------------------end of function-------------------------------------------------------------











//-------------------------Auxiliary Function Remove_One_Child-----------------------
node* BinarySearchTree::remove_one_child(node* p_node)
{
    if(p_node->pright!=nullptr && p_node->pleft!=nullptr) /// The node has two child
    {
         return nullptr;
    }

    if(p_node->pleft!= nullptr && p_node->pright==nullptr) /// The node has one child to the left
    {
        node * next;                                       // Create a temp pointer of type node
        next = p_node->pleft;                              // Assign the p_node left child to next

        p_node->value = next->value;                       // Copy to the p_node the value of the left child(next)
        p_node->counter = next->counter;                   // Copy to the p_node the counter of the left child(next)
        p_node->pleft = next->pleft;                       // Copy to the p_node the pleft of the left child(next)
        p_node->pright = next->pright;                     // Copy to the p_node the pright of the left child(next)

        delete p_node->pleft;

    }

    if (p_node->pleft==nullptr && p_node->pright!=nullptr) /// The node has one child to the right
    {
        node * next;                                       // Create a temp pointer of type node
        next = p_node->pright;                             // Assign the p_node right child to next

        p_node->value = next->value;                       // Copy to the p_node the value of the right child(next)
        p_node->counter = next->counter;                   // Copy to the p_node the counter of the right child(next)
        p_node->pleft = next->pleft;                       // Copy to the p_node the pleft of the left child(next)
        p_node->pright = next->pright;                     // Copy to the p_node the pright of the left child(next)


        delete next;
    }



    return p_node;
}
//----------------------end of function-------------------------------------













//--------------------------Auxiliary Function Search_Parent----------------------
node* BinarySearchTree::search_parent(string key)           // Recursive
{
    node *parent = nullptr;
    node *current = root;
	while (current != nullptr && current->value != key)
	{
		parent = current;
        if (key < current->value)
			current = current->pleft;
		else
			current = current->pright;
	}
	return parent;
}
//---------------------------end of function----------------------------------






//---------------------------------main MENU---------------------------------

void BinarySearchTree::MENU()
{
    int option;
    int result;
    option = -9;
    string input;
    clock_t start, end;
    start = 0;
    end = 0;
    bool was_del;
    int nodes;
    while (option)
    {
        cout<<"\n -------------------------------\n";
        cout<<" |       Binary Tree Menu      |\n";
        cout<<" -------------------------------\n";
        cout<<"\n -------------------------------\n";
        cout<<" 1. Insert to Binary Tree\n";
        cout<<" 2. Find in Binary Tree\n";
        cout<<" 3. Delete from Binary Tree\n";
        cout<<" 4. Print All Nodes\n";
        cout<<" 5. Get Number of Nodes\n";


        cout<<" 0. Quit\n";
        cout<<" -------------------------------\n  ";
        cin>>option;
        switch(option)
        {

            case 1:
                start = clock();
                cout<<" Insert : ";
                cin>>input;
                this->insert(input);
                //Sleep(1000);
                end = clock();

                break;
            case 2:

                cout<<" Find : ";
                cin>>input;
                start = clock();
                result = this->search(input);
                end = clock();
                if (result)
                    cout<<" Found '"<<input<<"' appeared "<<result<<" time/s\n";
                else
                    cout<<" '"<<input<<"' not found \n";
                    //Sleep(1500);

                break;
            case 3:
                cout<<" Delete : ";
                cin>>input;
                start = clock();
                was_del = delete_node(input);
                end = clock();
                if (was_del)
                    cout<<" '"<<input<<"' has been deleted \n";
                else
                    cout<<" '"<<input<<"' not found \n";

                break;
            case 4:
                start = clock();
                printDebug();
                end = clock();
                break;
            case 5:
                start = clock();
                nodes = size(root);
                end = clock();
                cout<<"The size is : " <<nodes<<endl;

                break;




        }
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Operation took : " << fixed<< time_taken << setprecision(5);
cout << " sec " << endl;

            //system("cls");


    }
}

//----------------------------------------end of Menu------------------------



//-----------Check Functions---------------

int BinarySearchTree::size(node* node)
{
    if (node == NULL)
        return 0;
    else
        return(size(node->pleft) + 1 + size(node->pright));
}
void check_p_null_BTS(void *p)  ///Check if memory was allocated correctly
{
    if (!p)
    {
        cout<<"MEMORY ALLOCATION FAILED in BTS\n Exiting..."<<endl;
        exit(-1);
    }
}

