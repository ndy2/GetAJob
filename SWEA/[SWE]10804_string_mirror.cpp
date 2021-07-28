#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main()
{
    unordered_map<char,char> mirror = {{'b','d'},{'d','b'},{'q','p'},{'p','q'}};
    int TC;
    cin>>TC;
    for(int tc = 1; tc<=TC; tc++)
    {
        string line;
        cin>>line;
        reverse(line.begin(), line.end());
        for(auto &c : line)
            c = mirror[c];
        cout<<"#"<<tc<<" "<<line<<endl;       
    } 
}