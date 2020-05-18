#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include "BinarySearchTree.h"
#include "TreeAVL.h"
#include "HashTable.h"


/// HERE THE NUMBER OF WORDS CAN BE ADJUSTED  <------

#define NUM_OF_WORDS 50




using namespace std;

void to_lower_str(string &data)
{
    transform(data.begin(), data.end(), data.begin(),[](unsigned char c){return tolower(c);} );
}

int main()
{
    BinarySearchTree BTS; ///Create object
    TreeAVL AVL;
    HashTable Hash(385416*2);


    string *temp_arr = new string [NUM_OF_WORDS];
    if (!temp_arr)
    {
        cout<<"MEM ALLOCATION FOR SEARCH ARRAY FAILED!\nExiting...";
        exit(-1);
    }

    srand (time(NULL));
    int k; //count = 0;
    string filename = "input_file.txt";        /// <----  HERE THE FILENAME CAN BE DECLARED


    ifstream file(filename);
    if (!file.is_open())
    {
        cout<<"File NOT found!...Exiting"<<endl;
        exit(-1);
    }

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

                        //BTS.insert(temp_word);
                        AVL.insert(temp_word);
                        //Hash.insert(temp_word);

                    }
                    temp_word.erase();

                }
        }
    }
    cout<<"FINITO\n";
    cout<<"BTS: "<<BTS.get_number_of_nodes()<<endl;
    cout<<"AVL: "<<AVL.get_number_of_nodes()<<endl;
    cout<<"HASH: "<<Hash.get_number_of_items()<<endl;
    file.clear();
    file.seekg (0, ios::beg);
    while (count_words<NUM_OF_WORDS)
    {

        while (getline(file, linestr) && count_words<NUM_OF_WORDS )
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
                            if (count_words<NUM_OF_WORDS)
                            {
                                if (rand()%2)
                                {

                                    temp_arr[count_words] = temp_word;
                                    count_words++;
                                }
                            }
                            else
                                break;
                            temp_word.erase();
                        }
                    }
            }

        }
        file.clear();
        file.seekg (0, ios::beg);

    }
    file.close();

    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();              /// High resolution clock to count time elapsed
    ios_base::sync_with_stdio(false);                            /// Don't count the time interval of stdio, example cout.

    int times_appeard_BTS,times_appeard_AVL,times_appeard_Hash; /// Just variables to keep the time a word appeared in every.
    double time_BTS,time_AVL,time_Hash,time_array;             /// Another variable to keep the time it took to find each word.
    double avg_BTS = 0, avg_AVL=0, avg_Hash=0, avg_array = 0;
    for (int i = 0; i<count_words; i++)
    {

        ///-------- BTS Insertion -------------------
        start = chrono::high_resolution_clock::now();                                   /// Starting the timer.
        times_appeard_BTS = BTS.search(temp_arr[i]);                                   /// Finding the word.
        end = chrono::high_resolution_clock::now();                                   /// Stopping the timer.
        time_BTS = chrono::duration_cast<chrono::nanoseconds>(end - start).count();  /// Calculating the time it took and saving the result.
        time_BTS *= 1e-9;
        avg_BTS+= time_BTS;

        ///-------- AVL Insertion ------------------- ///Currently the AVL ROTATIONS HAVE BUGS SO I HAVE DISABLED IT FOR NOW

        start = chrono::high_resolution_clock::now();                                   /// Starting the timer.
        times_appeard_AVL = AVL.search(temp_arr[i]);                                   /// Finding the word.
        end = chrono::high_resolution_clock::now();                                   /// Stopping the timer.
        time_AVL = chrono::duration_cast<chrono::nanoseconds>(end - start).count();  /// Calculating the time it took and saving the result.
        time_AVL *= 1e-9;
        avg_AVL+=time_AVL;

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
        while (temp_arr[i] != temp_arr[j])
        {
            j++;
        }
        end = chrono::high_resolution_clock::now();
        time_array = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_array *= 1e-9;
        avg_array+= time_array;



        //cout<<" -------------------------------------------------"<<endl<<endl;
        cout<<" The word '"<<temp_arr[i]<<"'."<<endl<<endl;
        cout<<" in Binary Search Tree\n     Appeared "<<times_appeard_BTS<<" time(s), took "<<fixed<<time_BTS<<" sec"<<endl<<endl;
        cout<<" in AVL Tree          \n     Appeared "<<times_appeard_AVL<<" time(s), took "<<fixed<<time_AVL<<" sec"<<endl<<endl;
        cout<<" in Hash Table        \n     Appeared "<<times_appeard_Hash<<" time(s), took "<<fixed<<time_Hash<<" sec"<<endl<<endl;
        //cout<<" -------------------------------------------------"
        cout<<endl<<endl<<endl<<endl<<endl<<endl;



    }
    cout<<endl<<endl<<endl;
    cout<<" ------------------   STATS   --------------------"<<endl<<endl;
    cout<<" Total number of words        :"<<count_words<<endl<<endl;
    cout<<" Average search time in BTS   :"<<fixed<<avg_BTS/count_words<<" sec"<<endl<<endl;
    cout<<" Average search time in AVL   :"<<fixed<<avg_AVL/count_words<<" sec"<<endl<<endl;
    cout<<" Average search time in Hash  :"<<fixed<<avg_Hash/count_words<<" sec"<<endl<<endl;
    cout<<" Average linear search time   :"<<fixed<<avg_array/count_words<<" sec"<<endl<<endl;
    cout<<endl<<endl;

    return 0;

}
