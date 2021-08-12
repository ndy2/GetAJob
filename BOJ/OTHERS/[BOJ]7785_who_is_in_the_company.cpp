#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


int main()
{
    int N;
    cin>>N;
    vector<string> names;
    unordered_map<string, bool> um;
    unordered_map<string, bool> added;

    for(int i = 0 ; i < N ; i++)
    {
        string name, move_;
        cin>>name>>move_;
        if(!added[name]){
        names.push_back(name);
        added[name] = true;}
        if(move_[0] == 'e')
            um[name] = true;
        else
            um[name] = false;
    }
    sort(names.begin(),names.end(),greater<string>());

    for(auto n : names)
        if(um[n])
            cout<<n<<"\n";
}