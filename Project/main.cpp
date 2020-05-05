#include <iostream>
#include <string>
#include "TreeAVL.h"
using namespace std;


int main()
{

    TreeAVL A;

    A.insert(8);
    A.insert(45);
    A.insert(4);
    A.insert(80);
    A.insert(81);
    //A.insert(43);
    //A.insert(46);




    A.display();
    A.debugInfo();





    return 0;


}
