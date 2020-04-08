#ifndef TREE_H
#define TREE_H

#include <string>

class Tree
{
     struct node {
        // members will be public without `private:` keyword
        int value;

        node *pleft;
        node *pright;
    };
    public:
        Tree();
        virtual ~Tree();

        void add(int);

        void InOrder();

    protected:
        void add(int, node*);
        void inorder(node*);

    private:
        node *root;

};

#endif // TREE_H
