#ifndef TREEAVL_H
#define TREEAVL_H

#include <iostream>
#include <string>

using namespace std;

struct node
{
    int value;
    node* pleft;
    node* pright;
    int counter = 0;
    int balance_factor = 0;       ///maxleft- maxright    MONOPATIA
};

class TreeAVL
{
    public:
        TreeAVL();
        virtual ~TreeAVL();


        void insert(int key)
        {
            root = insert(root, key );
        }

        int search(int);

        void display()
        {
            cout<<endl<<endl<<endl;
            display(root,1);
            cout<<endl<<endl<<endl;
        }

        void debugInfo()
        {
            debugInfo(root);
        }



        void inorder();
        void preorder();
        void postorder();


    protected:




    private:
        node* root = nullptr;

        int height(node*);
        int maxof2(int, int);
        int get_bf(node*);

        void display(node *ptr, int level);

        node* rr_rotation(node *parent);
        node* rl_rotation(node *parent);

        node* ll_rotation(node *parent);
        node* lr_rotation(node *parent);


        node* insert(node *p_node,int key_value);
        node * search(node *, int);

        void debugInfo(node *);

        void preorder(node *p);
        void inorder(node *p);
        void postorder(node *p);

};

#endif // TREEAVL_H
