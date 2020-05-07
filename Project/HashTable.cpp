#include "HashTable.h"

HashTable::HashTable(int s)
{
    Array = new node[s];
    size = s;
    //ctor
}
HashTable::~HashTable()
{
    delete [] Array;
    //dtor
}
unsigned long int HashTable::hash_algo(string s) ///Returns the hash code of the code
{
    unsigned long int code=s.length();
    unsigned long int p=10;
    for(int i=s.length()-1; i>=0; i--)
    {
            int key= int(s[i])-96;
            if(key<=9)
            {
                code+= key*p;
                p*=10;
            }
            else
            {
                code+=key*p;
                p*=100;
            }
    }
    return (code)%4294967296;
}
void HashTable::insert(string s)
{
    unsigned long int pos = hash_algo(s)%size;



    if (Array[pos].counter != 0 )///Not Empty Spot Detected
    {

        if (Array[pos].value == s) ///Found the Same String
            Array[pos].counter++;

        else                      ///Found Different String
        {
            int i = 1;
            int final_pos = pos;

            while (Array[final_pos].counter != 0 && i<size*2) ///Quadratic Probing
            {
                final_pos=(pos+(i*i))%size;
                i++;
            }
            Array[final_pos].value = s;
            Array[final_pos].counter =1;
        }
    }

    else ///This Spot is EMPTY
    {
        Array[pos].value = s;
        Array[pos].counter = 1 ;
    }
}
void HashTable::DebugInfo()
{
    for (int i = 0; i<size; i++)
        if (Array[i].counter != 0)
        cout<<"Value at ["<<i<<"] '"<<Array[i].value<<"'  Counter : "<<Array[i].counter<<" Hash Code : "<<hash_algo(Array[i].value)<<endl;
}
int HashTable::search(string s)
{
    unsigned long int pos = hash_algo(s)%size;
    if (Array[pos].value == s)
    {
        cout<<"I found the '"<<s<<"' original HASH position :"<<pos<<endl;
        return Array[pos].counter; ///Found

    }

    ///Found string with the same HASHCODE
    int i = 1;
    int final_pos = pos;

    while (Array[final_pos].value != s  && i<size*2) ///Quadratic Probing
    {
        final_pos=(pos+(i*i))%size;
        i++;
    }
    if (Array[final_pos].value == s)
    {
        //cout<<"I found the '"<<s<<"' NOT original HASH position :"<<final_pos<<endl;
        return Array[final_pos].counter;
    }
    //cout<<"NOT FOUND"<<endl;
    return 0;
}
