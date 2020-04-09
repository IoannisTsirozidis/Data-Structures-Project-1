#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tree.h"
using namespace std;


int main()
{
    /*
    vector<string> ArrayWithWords;
    size_t d = 0;


    ifstream file("input_file.txt");
    string linestr;
    while (getline(file, linestr))
    {
        ArrayWithWords.push_back(linestr);
        d++;
    }



    for (int i = 0; i < ArrayWithWords.size(); i++)
    {
        cout<<ArrayWithWords[i]<<"                                      With strlen =  "<<ArrayWithWords[i].size()<<endl;
        d+=ArrayWithWords[i].size();

    }
    cout<<"\n\n\n-------------------------------"<<endl;
    cout<<"The number of lines is "<<ArrayWithWords.size()<<endl;
    cout<<"Total number of characters = "<<d<<endl;
    */


    Tree A;
    A.add(10);
    A.add(20);
    A.add(20);
    A.InOrder();

    cout<<A.node.pleft;





}
