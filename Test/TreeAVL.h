#ifndef TREEAVL_H
#define TREEAVL_H


class TreeAVL
{
    struct node
    {
        // members will be public without `private:` keyword
        int value; //This should be the date type of the Tree
        node *pleft;
        node *pright;
    };
    public:
        TreeAVL();
        virtual ~TreeAVL();

    protected:

    private:
};

#endif // TREEAVL_H
