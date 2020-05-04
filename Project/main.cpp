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
    A.insert(60);
    A.insert(61);
    A.insert(85);

    A.display();
    A.debugInfo();





    return 0;


}
