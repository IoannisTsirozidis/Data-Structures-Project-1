#include <iostream>
#include <string>
#include "TreeAVL.h"
using namespace std;


int main()
{

    TreeAVL A;

    A.insert(10);
    A.insert(5);
    A.insert(35);
    A.insert(40);
    A.insert(45);

    A.search(45);
    //A.insert(43);
    //A.insert(46);




    A.display();
    A.debugInfo();





    return 0;


}
