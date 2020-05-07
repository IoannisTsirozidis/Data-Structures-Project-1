#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <chrono>
#include <random>

#include "BinarySearchTree.h"
#include "TreeAVL.h"
#include "HashTable.h"

#define NUM_OF_WORDS 10
using namespace std::chrono;

using namespace std;

void to_lower_str(string &data)
{
    transform(data.begin(), data.end(), data.begin(),[](unsigned char c){return tolower(c);} );
}

int main()
{

    BinarySearchTree BTS;
    TreeAVL AVL;
    HashTable Hash(NUM_OF_WORDS*2);


    string temp_arr[NUM_OF_WORDS];

    int count_words = 0;

    srand (time(NULL));
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
                        if (rand()%2 && count_words<=NUM_OF_WORDS )
                        {
                            BTS.insert(temp_word);
                            AVL.insert(temp_word);
                            Hash.insert(temp_word);
                            //temp_arr[count_words] = "python";
                            count_words++;
                        }
                        temp_word.erase();
                    }
                }
        }
    }
/*
    for (int i = 0; i<count_words; i++)
    {
        cout<<"-------------------------------------------------"<<endl<<endl;
        cout<<"Searching the word '"<<temp_arr[i]<<"'."<<endl<<endl;
        cout<<"in Binary Search Tree\n     Appeared "<<BTS.search(temp_arr[i])<<" time(s)"<<endl<<endl;
        cout<<"in AVL Tree          \n     Appeared "<<AVL.search(temp_arr[i])<<" time(s)"<<endl<<endl;
        cout<<"in Hash Table        \n     Appeared "<<Hash.search(temp_arr[i])<<" time(s)"<<endl<<endl;
        cout<<"-------------------------------------------------"<<endl<<endl;




    }
*/

    return 0;

}
