#include <iostream>
#include <set>

using namespace std;

int main()
{
    int TC;
    cin>>TC;
    for(int tc =1 ; tc<=TC; tc++)
    {
        string S;
        cin>>S;
        set<char> sc;
        for(auto c : S)
            sc.insert(c);
        if(sc.size() == 2)
            printf("#%d Yes\n",tc);
        else
            printf("#%d No\n",tc);
    }    
}