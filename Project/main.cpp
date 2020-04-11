#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include "Tree.h"

using namespace std;

void to_lower_str(string &data)
{
    transform(data.begin(), data.end(), data.begin(),[](unsigned char c){return tolower(c);} );
}
int main()
{




    int n,k;
    ifstream file("input_file2.txt");
    string linestr;
    string temp_word;
    while (getline(file, linestr))
    {
        n = 0;
        k = linestr.length();
        while (n<k)
        {
            while ()
            temp_wordappend

            n++;
        }




        // Process linestr (e.g., eliminate punctuation marks, isolate words)
    }




    /*

    string data = "Abc";

    to_lower_str(data);

    cout<<data;

    if (data == data)
        cout<<"yes"<<endl;

    */



}
