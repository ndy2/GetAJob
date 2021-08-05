#include <iostream>
#include <string>

using namespace std;


int main()
{
    int N;
    scanf("%d",&N);
    N++;
    for(int i = 0 ; i < N ; i++)
    {
        string line;
        getline(cin,line);
        if(line.empty()) continue;
        if(line[0]>='a'&&line[0]<='z')
            line[0]+='A'-'a';
        cout<<line+"\n";
    }
}