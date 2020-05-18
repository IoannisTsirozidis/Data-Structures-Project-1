#ifndef TREEAVL_H
#define TREEAVL_H

#include <iostream>
#include <string>

using namespace std;

struct nodeA
{
    string value;
    nodeA* pleft;
    nodeA* pright;
    int counter = 0;
    int height = 0;       ///  BALANCE FACTOR =  MAX LEFT HEIGHT  -   MAX RIGHT HEIGHT
};

class TreeAVL
{
    public:
        TreeAVL();
        virtual ~TreeAVL();

        unsigned int get_number_of_nodes() const
        {
            return number_of_nodes;
        }

        void insert(string key)                // Insert function, for main.
        {
            root = insert(root, key );
            number_of_nodes+=1;
        }


        int search(string);                    //Search function, for main.



        bool delete_nodeA(string);              //Delete function, for main.




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

        nodeA* root = nullptr;           //Private nodeA* root.
        unsigned int number_of_nodes;


        int height(nodeA*);
        int maxof2(int, int);



        ///balance factor
        int get_bf(nodeA*);
        void update_bf(nodeA *p);
        void check_balance_preorder(nodeA *p);


        void update_height(nodeA *p);
        void fix_bf_for_all(nodeA * p_nodeA);


        void display(nodeA *ptr, int level);
        void debugInfo(nodeA *);

        /// Rotations
        nodeA *rightRotate(nodeA *);
        nodeA *leftRotate(nodeA *);

        nodeA* rr_rotation(nodeA *parent);
        nodeA* rl_rotation(nodeA *parent);

        nodeA* ll_rotation(nodeA *parent);
        nodeA* lr_rotation(nodeA *parent);



        nodeA* remove_one_child(nodeA*);




        nodeA* insert(nodeA *p_nodeA, string key_value);
        nodeA * search(nodeA *, string);

        nodeA* search_parent(string key);



        void preorder(nodeA *p);
        void inorder(nodeA *p);
        void postorder(nodeA *p);

};

void check_p_null_AVL(void * );



#endif // TREEAVL_H
