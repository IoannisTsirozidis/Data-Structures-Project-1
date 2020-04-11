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
    /*
    int k, count = 0;
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
                        temp_word.erase();
                    }
                }
        }
    }
    */





}
