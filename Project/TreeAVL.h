#ifndef TREEAVL_H
#define TREEAVL_H

#include <iostream>
#include <string>

using namespace std;

struct node
{
    string value;
    node* pleft;
    node* pright;
    int counter = 0;
    int height;       ///  HEIGHT
};

class TreeAVL
{
    public:
        TreeAVL();
        virtual ~TreeAVL();



        void insert(string key)                // Insert function, for main.
        {
            root = insert(root, key );
        }


        int search(string);                    //Search function, for main.



        bool delete_node(string);              //Delete function, for main.




//--------Debugging Information. -------------------

        void display()
        {
            cout<<endl<<endl<<endl;
            display(root,1);
            cout<<endl<<endl<<endl;
        }

        void debugInfo()
        {debugInfo(root);}

//----------------------------------------------------


        //Functions 1)Inorder 2) Preorder 3) Postorder

        void inorder();
        void preorder();
        void postorder();





    protected:

    private:    ///In private there are the background functions.

        node* root = nullptr;           //Private node* root.



        int height(node*);
        int maxof2(int, int);



        ///balance factor
        int get_bf(node*);
        void update_bf(node *p);
        void check_balance_preorder(node *p);


        void update_height(node *p);
        void fix_bf_for_all(node * p_node);


        void display(node *ptr, int level);
        void debugInfo(node *);



        node* rr_rotation(node *parent);
        node* rl_rotation(node *parent);

        node* ll_rotation(node *parent);
        node* lr_rotation(node *parent);



        node* remove_one_child(node*);




        node* insert(node *p_node, string key_value);
        node * search(node *, string);

        node* search_parent(string key);



        void preorder(node *p);
        void inorder(node *p);
        void postorder(node *p);

};

#endif // TREEAVL_H
