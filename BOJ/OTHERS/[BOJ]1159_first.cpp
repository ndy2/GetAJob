#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
    int N;
    cin>>N;
    int cnt[26];
    memset(cnt,0,sizeof(cnt));
    
    for(int i = 0 ; i < N ; i++)
    {
        string name;
        cin>>name;
        cnt[name[0]-'a']++;
    }

    string ans;
    for(int i = 0 ; i < 26 ; i++)
        if(cnt[i] >=5)
            ans.push_back(i+'a');
    if(ans.empty()) ans = "PREDAJA";

    cout<<ans;
}