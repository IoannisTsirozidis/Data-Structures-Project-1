#include <iostream>
#include <string>
#include "TreeAVL.h"
using namespace std;


int main()
{

    TreeAVL A;

    A.insert("john");
    A.insert("kostas");
    A.insert("fox");
    A.insert("pikatsu");
    A.insert("entaxei");
    A.insert("fox");
    A.insert("PepAeytomata");

    A.display();
    A.debugInfo();


    A.search("fox");
    A.delete_node("entaxei");

    A.display();
    A.debugInfo();

    //A.insert(43);
    //A.insert(46);



    return 0;


}
