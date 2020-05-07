#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctype.h>
using namespace std;


int hasher(string s)
{
    string syn;
    for(int i = 0; i< s.length(); i++)
    {
        cout<<int(s[i])-96<<endl;
    }
    return 1;
}


int main()
{
    hasher("fox");



}
