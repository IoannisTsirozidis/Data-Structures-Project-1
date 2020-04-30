#ifndef AVL_TREE_H
#define AVL_TREE_H

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

class AVL_tree
{
    public:
        AVL_tree();
        virtual ~AVL_tree();



        int height(node*);
        int maxof2(int, int);

        int get_bf(node*);






    protected:




    private:
};

#endif // AVL_TREE_H
