#include "HashTable.h"
HashTable::HashTable(int s)
{
    Array = new nodeH[s];
    check_p_null_Hash(Array);
    size = s;
    //ctor
}
HashTable::~HashTable()
{
    delete [] Array;
    //dtor
}
unsigned long int HashTable::hash_algo(string s) ///Calculates and Returns the hash code of the string
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
    return (code)%4294967296; /// limit the code to 10 digits MAX
}
void HashTable::insert(string s)
{
    unsigned long int pos = hash_algo(s)%size;



    if (Array[pos].counter != 0 )    /// Occupied cell detected
    {

        if (Array[pos].value == s) ///Found the Same String in the cell
            Array[pos].counter++;

        else                      ///Found Different String in the cell
        {
            int i = 1;
            int final_pos = pos;

            while (Array[final_pos].counter != 0 && i<size*2) /// Quadratic Probing to find the next cell
            {
                final_pos=(pos+(i*i))%size;
                i++;
            }
            Array[final_pos].value = s;
            Array[final_pos].counter =1;
        }
    }

    else ///This cell is EMPTY
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
        return Array[pos].counter; ///Found in the cell

    }

    ///Found string with the same HASHCODE
    int i = 1;
    int final_pos = pos;

    while (Array[final_pos].value != s  && i<size*2) ///Quadratic Probing to find the next cell
    {
        final_pos=(pos+(i*i))%size;
        i++;
    }

    if (Array[final_pos].value == s)
        return Array[final_pos].counter;
    return 0;
}
void check_p_null_Hash(void *p)
{
    if (!p)
    {
        cout<<"MEMORY ALLOCATION FAILED in Hash\n Exiting..."<<endl;
        exit(-1);
    }
}
