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
#include "BinarySearchTree.h"
#include "TreeAVL.h"
#include "HashTable.h"

#define NUM_OF_WORDS 10000
using namespace std::chrono;

using namespace std;

void to_lower_str(string &data)
{
    transform(data.begin(), data.end(), data.begin(),[](unsigned char c){return tolower(c);} );
}

int main()
{
    bool show_stats_only;
    cout<<" Do you want to see the counter and search time for ALL words? : (0/1):";
    cin>>show_stats_only;
    cout<<endl;

    BinarySearchTree BTS;
    TreeAVL AVL;
    HashTable Hash(NUM_OF_WORDS*2);


    string *temp_arr = new string [NUM_OF_WORDS];
    if (!temp_arr)
    {
        cout<<"MEM ALLOCATION FOR SEARCH ARRAY FAILED!\nExiting...";
        exit(-1);


    }
    int count_words = 0;

    srand (time(NULL));
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
                        if (count_words<NUM_OF_WORDS ) //rand()%2 &&
                        {
                            BTS.insert(temp_word);
                            //AVL.insert(temp_word);
                            Hash.insert(temp_word);

                            if (Hash.search(temp_word)) /// If the word is already in don't append it to the temp_arr
                            {
                                temp_arr[count_words] = temp_word;
                                count_words++;
                            }
                        }
                        temp_word.erase();
                    }
                }
        }
    }
    //freopen("output.txt","w",stdout);

    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();              /// High resolution clock to count time elapsed
    ios_base::sync_with_stdio(false);                            /// Don't count the time interval of stdio, example cout.

    int times_appeard_BTS,times_appeard_AVL,times_appeard_Hash; /// Just variables to keep the time a word appeared in every.
    double time_BTS,time_AVL,time_Hash,time_array;             /// Another variable to keep the time it took to find each word.
    double avg_BTS = 0, avg_AVL=0, avg_Hash=0, avg_array = 0;
    for (int i = 0; i<count_words; i++)
    {
        //cout<<"-------------------------------------------------"<<endl<<endl;
        //cout<<"Searching the word '"<<temp_arr[i]<<"'."<<endl<<endl;
        ///-------- BTS Insertion -------------------
        start = chrono::high_resolution_clock::now();                                   /// Starting the timer.
        times_appeard_BTS = BTS.search(temp_arr[i]);                                   /// Finding the word.
        end = chrono::high_resolution_clock::now();                                   /// Stopping the timer.
        time_BTS = chrono::duration_cast<chrono::nanoseconds>(end - start).count();  /// Calculating the time it took and saving the result.
        time_BTS *= 1e-9;
        avg_BTS+= time_BTS;

        ///-------- AVL Insertion ------------------- ///Currently the AVL ROTATIONS HAVE BUGS SO I HAVE DISABLED IT FOR NOW
        /*
        start = chrono::high_resolution_clock::now();                                   /// Starting the timer.
        times_appeard_AVL = AVL.search(temp_arr[i]);                                   /// Finding the word.
        end = chrono::high_resolution_clock::now();                                   /// Stopping the timer.
        time_AVL = chrono::duration_cast<chrono::nanoseconds>(end - start).count();  /// Calculating the time it took and saving the result.
        time_AVL *= 1e-9;
        avg_AVL+=time_AVL;
        */
        ///-------- Hash Insertion ----------------
        start = chrono::high_resolution_clock::now();                                   /// Starting the timer.
        times_appeard_Hash = Hash.search(temp_arr[i]);                                 /// Finding the word.
        end = chrono::high_resolution_clock::now();                                   /// Stopping the timer.
        time_Hash = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); /// Calculating the time it took and saving the result.
        time_Hash *= 1e-9;
        avg_Hash+=time_Hash;

        ///-------- Simulate Linear Search ----------
        start = chrono::high_resolution_clock::now();
        int j = 0;
        while (temp_arr[i] != temp_arr[i])
        {
            j++;
        }
        end = chrono::high_resolution_clock::now();
        time_array = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_array *= 1e-9;
        avg_array+= time_BTS;




        if(show_stats_only)
        {

        cout<<"in Binary Search Tree\n     Appeared "<<times_appeard_BTS<<" time(s), took "<<fixed<<time_BTS<<" sec"<<endl<<endl;
        cout<<"in AVL Tree          \n     Appeared "<<times_appeard_AVL<<" time(s), took "<<fixed<<time_AVL<<" sec"<<endl<<endl;
        cout<<"in Hash Table        \n     Appeared "<<times_appeard_Hash<<" time(s), took "<<fixed<<time_Hash<<" sec"<<endl<<endl;
        cout<<"-------------------------------------------------"<<endl<<endl;
        }



    }
    cout<<"------------------   STATS   --------------------"<<endl<<endl;
    cout<<" Total number of words        :"<<count_words<<endl<<endl;
    cout<<" Average search time in BTS   :"<<fixed<<avg_BTS/count_words<<" sec"<<endl<<endl;
    cout<<" Average search time in AVL   :"<<fixed<<avg_AVL/count_words<<" sec"<<endl<<endl;
    cout<<" Average search time in Hash  :"<<fixed<<avg_Hash/count_words<<" sec"<<endl<<endl;
    cout<<" Average linear search time   :"<<fixed<<avg_array/count_words<<" sec"<<endl<<endl;


    return 0;

}
