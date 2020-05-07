#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
using namespace std;

struct node
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

    protected:

    private:
        node * Array;
        int size;

        unsigned long int hash_algo(string);

};

#endif // HASHTABLE_H
