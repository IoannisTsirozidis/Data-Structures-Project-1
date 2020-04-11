#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


struct node
{
    int counter;
    int value;
    node* pleft;
    node* pright;
};


class BinarySearchTree
{
    public:


        BinarySearchTree();
        virtual ~BinarySearchTree();


        //FUNCTIONS

        void insert(int);




    protected:


    private:
        node* root;

        void insert(node*, int);
};

#endif // BINARYSEARCHTREE_H
