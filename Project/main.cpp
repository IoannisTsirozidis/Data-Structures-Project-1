#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <chrono>
#include <random>
#include <cstdio>

#include "AVLGeeks.h"
#define NUM_OF_WORDS 2
using namespace std::chrono;

using namespace std;

void to_lower_str(string &data)
{
    transform(data.begin(), data.end(), data.begin(),[](unsigned char c){return tolower(c);} );
}
int main()
{
    Node *root = NULL;





    string *temp_arr = new string [NUM_OF_WORDS];
    if (!temp_arr)
    {
        cout<<"MEM ALLOCATION FOR SEARCH ARRAY FAILED!\nExiting...";
        exit(-1);

    }
    int count = 0;
    int k; //count = 0;
    ifstream file("input_file.txt");
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
                         //rand()%2 &&


                        root = insert(root, 10);
                        //AVL.insert(temp_word);
                        count++;

                        temp_word.erase();
                    }
                }
        }
    }
    cout<<count;

    //freopen("output.txt","w",stdout);



    return 0;

}
