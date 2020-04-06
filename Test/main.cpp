#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
void remove_gar(string &s)
{
    int x;
}


int main()
{
    vector<string> ArrayWithWords;
    size_t d = 0;


    ifstream file("input_file2.txt");
    string linestr;
    while (getline(file, linestr))
    {
        ArrayWithWords.push_back(linestr);
        d++;
    }



    for (int i = 0; i < ArrayWithWords.size(); i++)
    {
        cout<<ArrayWithWords[i]<<"                                      With strlen =  "<<ArrayWithWords[i].size()<<endl;
        d+=ArrayWithWords[i].size();

    }
    cout<<"\n\n\n-------------------------------"<<endl;
    cout<<"The number of lines is "<<ArrayWithWords.size()<<endl;
    cout<<"Total number of characters = "<<d<<endl;
}
