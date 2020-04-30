#include <iostream>
#include <string>
#include "TreeAVL.h"
using namespace std;


int main()
{

    TreeAVL A;

    A.insert(8);
    A.insert(26);
    A.insert(50);
    A.insert(11);
    A.insert(9);
    A.insert(4);
    A.insert(20);
    A.insert(1);


    A.display();
    A.debugInfo();





    return 0;


}
