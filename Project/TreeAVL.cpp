#include "TreeAVL.h"


int AVL_tree::maxof2(int a, int b)      //EPISTREFEI TO MAX DYO ARITHMWN
{
    if(a>=b)
        return a;
    else
        return b;
}


int AVL_tree::height(node* mynode)      //ANADROMIKH SYNARTHSH POU VRISKEI TO MEGISTO MONOPATI APO ENAN KOMVO
{
    //TERMATIKH SYNTHHKH
    if(mynode== nullptr)        ///AN O KOMVOS POU EPELEXA H EFTASA EINAI KENOS GYRNAEI 0
        return 0;

    //AN O KOMVOS POU EPELEXA H POU EFTASA DEN EINAI KENOS
    //TOTE XANAKALW TH SYNARTHSH GIA TO MEGALYTERO MONOPATI EITE DEXIA EITE ARISTERA
    //
    //
    //
    //                  13
    //             3          56
    //                1
    //

    else
    {

        return 1 + maxof2(height(mynode->pright), height(mynode->pleft));
    }

}


int AVL_tree::get_bf(node* mynode)      //EPISTREFEI TO BALANCE FACTOR TOU KOMVOU
{
    int lheight, rheight, bf;

    lheight= height(mynode->pleft);
    rheight= height(mynode->pright);

    bf= lheight- rheight;               //maxleft- maxright; ...[-1, 0, 1]... an EINAI BALANCED

    mynode->balance_factor= bf;

    return mynode->balance_factor;
}
