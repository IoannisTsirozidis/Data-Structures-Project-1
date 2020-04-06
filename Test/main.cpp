#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    ifstream file("inputfile.txt");
    string linestr;
    while (getline(file, linestr))
    {
        cout<<linestr<<endl;
    }
}
