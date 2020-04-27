#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include "BinarySearchTree.h"

#include <chrono>
using namespace std::chrono;

using namespace std;



void to_lower_str(string &data)
{
    transform(data.begin(), data.end(), data.begin(),[](unsigned char c){return tolower(c);} );
}



int main()
{

    BinarySearchTree A;




    int k; //count = 0;
    ifstream file("input_file2.txt");
    string linestr;
    string temp_word;
    while (getline(file, linestr))
    {
        k = linestr.length();
        for (int i=0; i<=k; i++)
        {
            if (isalpha(linestr[i]))
                temp_word+=linestr[i];
            else
                if (temp_word.length() != 0)
                {
                    if (!isalpha(linestr[i]) || i ==k  )
                    {
                        to_lower_str(temp_word);
                        //cout<<temp_word<<endl; /// This is the insert part function
                        A.insert(temp_word);
                        temp_word.erase();
                    }
                }
        }
    }
    A.MENU();


/*
    string x;


    while (x!= "end")
    {
        A.insert(x);
        cin>>x;
    }

    cout<<A.delete_node("test");

    A.printDebug();

    long double mo = 0;
    for (int i = 0; i<1000;i++)
    {
        auto start = high_resolution_clock::now();
        A.search(i);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop-start);
        //cout <<" Time elapsed : "<< duration.count() << endl;
        mo += duration.count();
    }
    cout << mo / 1000<<" microseconds "<<endl;
    */







}
