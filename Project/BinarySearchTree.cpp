#include "BinarySearchTree.h"
/*
struct node
{
    int counter;
    string value;
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


bool BinarySearchTree::delete_node(string key_value) ///TO KANAME XORIS ANADROMI
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
    return true;

}



node* BinarySearchTree::remove_one_child(node* p_node)
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


node* BinarySearchTree::search_parent(string key)
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
                    //Sleep(1500);

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
int BinarySearchTree::size(node* node)
{
    if (node == NULL)
        return 0;
    else
        return(size(node->pleft) + 1 + size(node->pright));
}

