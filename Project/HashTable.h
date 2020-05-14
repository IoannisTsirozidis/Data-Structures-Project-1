#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
using namespace std;

struct nodeH
{
    string value;
    int counter = 0;

};

class HashTable
{
    public:
        HashTable(int size);
        virtual ~HashTable();

        void insert(string);
        int search(string);
        void DebugInfo();

        unsigned int get_number_of_items()
        {
            return number_of_items;
        }
    protected:

    private:
        unsigned int number_of_items = 0;
        nodeH * Array;
        int size;

        unsigned long int hash_algo(string);

};
void check_p_null_Hash(void * );
#endif // HASHTABLE_H
